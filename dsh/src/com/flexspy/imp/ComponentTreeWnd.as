/**
 * FlexSpy 1.2
 * 
 * <p>Code released under WTFPL [http://sam.zoy.org/wtfpl/]</p>
 * @author Arnaud Pichery [http://coderpeon.ovh.org]
 */
package com.flexspy.imp {

	import flash.display.DisplayObject;
	import flash.events.Event;
	import flash.events.KeyboardEvent;
	import flash.events.MouseEvent;
	
	import mx.collections.ArrayCollection;
	import mx.collections.Sort;
	import mx.collections.SortField;
	import mx.containers.HDividedBox;
	import mx.containers.TabNavigator;
	import mx.containers.TitleWindow;
	import mx.controls.Alert;
	import mx.controls.Button;
	import mx.controls.Spacer;
	import mx.controls.Tree;
	import mx.core.Application;
	import mx.core.Container;
	import mx.core.UIComponent;
	import mx.effects.Effect;
	import mx.effects.Glow;
	import mx.effects.Zoom;
	import mx.effects.effectClasses.GlowInstance;
	import mx.events.CloseEvent;
	import mx.events.CollectionEvent;
	import mx.events.FlexEvent;
	import mx.events.ListEvent;
	import mx.managers.FocusManager;
	import mx.managers.PopUpManager;

	/**
	 * <p>Displays details about a component and its children in a window.</p>
	 * 
	 * <p>To display the window, you call the method <code>show(root: DisplayObject, modal: Boolean)</code>.</p>
	 */
	public class ComponentTreeWnd extends ResizableTitleWindow {
		// Only instance of our window. Non-null when window is displayed, null otherwise.
		private static var _instance: ComponentTreeWnd;

		// UI component displaying the tree of all components.
		private var _componentTree: Tree;
		
		// UI component displaying the properties of a component.
		private var _componentProperties: ComponentProperties;

		// UI component displaying the styles of a component.
		private var _componentStyles: ComponentStyles;
		
		// Root component of the tree
		private var _root: DisplayObject;
		
		// Indicates whether the window is displayed in a modal mode.
		private var _modal: Boolean;
		
		// Button used to highlight selected component.
		private var highlightButton: Button;
		
		// Effect used to highlight the selected component
		private var _highlightComponentEffect: Effect;
		
	    /**
	     * This method is not intented to be used. Use <code>show</code> method instead.
	     */
		public function ComponentTreeWnd() {
			super();
			
			// Singleton pattern
			if (_instance != null)
				throw new Error("Only one instance of ComponentTreeWnd can be created.");
			_instance = this;
			
			// properties
			this.layout = "vertical";
			this.title = "FlexSpy";
			this.width = 900;
			this.height = 678;
			this.showCloseButton = true;

			// events
			this.addEventListener("close", closeWindow);
			this.addEventListener("creationComplete", onCreationComplete);
		}
		
		override protected function createChildren(): void {
			super.createChildren();
			
			var vbox: mx.containers.HDividedBox = new mx.containers.HDividedBox();
			vbox.percentWidth = 100.0;
			vbox.percentHeight = 100.0;
			
			_componentTree = new Tree();
			_componentTree.percentWidth = 50.0;
			_componentTree.percentHeight = 100.0;
			_componentTree.addEventListener(ListEvent.CHANGE, onItemSelected);
			_componentTree.iconFunction = getTreeNodeIcon;
			vbox.addChild(_componentTree);
			
			var _rightTab: TabNavigator = new TabNavigator();
			_rightTab.historyManagementEnabled = false;
			_rightTab.percentWidth = 50.0;
			_rightTab.percentHeight = 100.0;
			vbox.addChild(_rightTab);
			
			_componentProperties = new ComponentProperties();
			_componentProperties.percentWidth = 100.0;
			_componentProperties.percentHeight = 100.0;
			_rightTab.addChild(_componentProperties);

			_componentStyles = new ComponentStyles();
			_componentStyles.percentWidth = 100.0;
			_componentStyles.percentHeight = 100.0;
			_rightTab.addChild(_componentStyles);

			this.addChild(vbox);

			
			var cbar: mx.containers.Box = new mx.containers.HBox();
   			cbar.setStyle("horizontalAlign", "right");
   			cbar.percentWidth = 100.0;

			// Add Find button
			var findButton: Button = new Button();
			findButton.label = "Find Component";
			findButton.setStyle("icon", FindWnd.TARGET_ICON);
			findButton.addEventListener(MouseEvent.CLICK, onFindButtonClicked);
			cbar.addChild(findButton);

			// Add Spacer
			var spacer: Spacer = new Spacer();
			spacer.percentWidth = 100.0;
			cbar.addChild(spacer);

			if (!_modal) {
				// Add refresh button when window is not modal
				var refreshButton: Button = new Button();
				refreshButton.label = "Refresh";
				refreshButton.addEventListener(MouseEvent.CLICK, onRefreshButtonClicked);
				cbar.addChild(refreshButton);
			}
			var closeButton: Button = new Button();
			closeButton.label = "Close";
			closeButton.addEventListener("click", closeWindow);
			cbar.addChild(closeButton);
			this.addChild(cbar);
		}
		
		/**
		 * Displays the tree of the specified DisplayObject (its children, the children of its children, etc.)
		 * 
		 * @param root Root of the displayed tree. If it is null, the current application is used.
		 * @param modal true to display a modal window (default), false to display a modeless window.
		 */
		public static function show(root: DisplayObject = null, modal: Boolean = true): void {
			if (root == null) {
				root = DisplayObject(Application.application);
			}
						
			if (_instance == null) {
				_instance = ComponentTreeWnd(PopUpManager.createPopUp(DisplayObject(Application.application), ComponentTreeWnd, modal));
				_instance._root = root;
				_instance._modal = modal;
				PopUpManager.centerPopUp(_instance);
			} else {
				// Modeless or modal window displayed, update the root component and refresh.
				if (_instance._root != root) {
					_instance._root = root;
					_instance.initWindow();
				}
				if (!_instance.visible) {
					_instance.visible = true;
					PopUpManager.addPopUp(_instance, DisplayObject(Application.application), _instance._modal);
				}
			}
		}

		private function closeWindow(event: Event = null): void {
			PopUpManager.removePopUp(this);
			_instance.visible = false;
		}
		
		private function onCreationComplete(event: Event): void {
			initWindow();
			focusManager.activate();
			focusManager.setFocus(_componentTree);
		}

		private function onRefreshButtonClicked(event: Event): void {
			initWindow();
		}
		
		private function highlightComponent(item: ComponentTreeItem): void {
			var uiComponent: UIComponent = (item == null) ? null : (item.displayObject as UIComponent);
			if (uiComponent != null) {
				highlightComponentEffect.end();
				highlightComponentEffect.target = uiComponent;
				highlightComponentEffect.play();
			}
		}
		
		private function onFindButtonClicked(event: Event): void {
			var findWnd: FindWnd = FindWnd(PopUpManager.createPopUp(DisplayObject(Application.application), FindWnd, false));
			findWnd.treeWnd = this;
			PopUpManager.centerPopUp(findWnd);
			
			this.visible = false;
		}
		
		public function getComponentItemAt(stageX: Number, stageY: Number): ComponentTreeItem {
			var rootNode: IComponentTreeItem = IComponentTreeItem(ArrayCollection(_componentTree.dataProvider).getItemAt(0));
			var pointedItem: ComponentTreeItem = rootNode.getHitComponent(stageX, stageY, true);
			if (pointedItem != null) {
				// Adjust pointedItem to point on an UIComponent
				var uiPointedItem: IComponentTreeItem = pointedItem;
				while (uiPointedItem != null && 
						(!(uiPointedItem is ComponentTreeItem) ||
						!(ComponentTreeItem(uiPointedItem).displayObject is UIComponent))) {
					uiPointedItem = uiPointedItem.parent;
				}
			}
			pointedItem = ComponentTreeItem(uiPointedItem);
			return pointedItem;
		}
		
		public function selectComponentAt(stageX: Number, stageY: Number): void {
			var pointedItem: ComponentTreeItem = getComponentItemAt(stageX, stageY);
			
			if (pointedItem != null) {
				// Compute the path within the tree
				var treePath: Array = new Array();
				var parent: IComponentTreeItem = pointedItem.parent;
				while (parent != null) {
					treePath.push(parent);
					parent = parent.parent;
				}
				treePath.reverse();
				
				// Collapse all nodes, then expand the path to the selected item
				var rootNode: IComponentTreeItem = IComponentTreeItem(ArrayCollection(_componentTree.dataProvider).getItemAt(0));
				_componentTree.expandChildrenOf(rootNode, false);
				for each (var treeItem: Object in treePath) {
					_componentTree.expandItem(treeItem, true, false);
				}

				// Select the item
				_componentTree.selectedItem = pointedItem;
				onItemSelected(null);
				
				// Highlight the selected item
				highlightComponentEffect.end();
				if (pointedItem.displayObject != null) {
					highlightComponentEffect.target = pointedItem.displayObject;
					highlightComponentEffect.play();
				}
			}
		}
		
		/**
		 * Fill-in the component tree with the root component.
		 * 
		 * This method is called the first time the window is created, 
		 * and when users click the "refresh" button.
		 */
		private function initWindow(): void {
			// Compute the component tree and display it
			var rootItem: IComponentTreeItem = new ComponentTreeItem(_root, null);
			var treeNodes: ArrayCollection = new ArrayCollection();
			treeNodes.addItem(rootItem);
			_componentTree.dataProvider = treeNodes;
			_componentTree.validateNow();
			_componentTree.expandItem(rootItem, true);
			_componentProperties.showComponentProperties(null);
			_componentStyles.showComponentStyles(null);
		}
		
        private function onItemSelected(event: Event): void {
			var item: ComponentTreeItem = selectedComponent as ComponentTreeItem;
			var displayObject: DisplayObject = (item == null) ? null : item.displayObject;
			_componentProperties.showComponentProperties(displayObject);
			_componentStyles.showComponentStyles(displayObject);
			highlightComponent(item);
        }
        
        private function get selectedComponent(): IComponentTreeItem {
			return (_componentTree.selectedItem as IComponentTreeItem);
        }
        
		private function getTreeNodeIcon(item:Object):Class{
		   return IComponentTreeItem(item).icon;
		}

		private function get highlightComponentEffect(): Effect {
			if (_highlightComponentEffect == null) {
				var glow: Glow = new Glow();
				glow.color = 0xFFFF00;
				glow.strength = 10;
				glow.inner = false;
				glow.duration = 1000;
				_highlightComponentEffect = glow;
			}
			return _highlightComponentEffect;
		}
	}
}
