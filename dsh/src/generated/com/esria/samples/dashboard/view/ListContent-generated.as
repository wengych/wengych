
/**
 * 	Generated by mxmlc 2.0
 *
 *	Package:	com.esria.samples.dashboard.view
 *	Class: 		ListContent
 *	Source: 	C:\Documents and Settings\a\My Documents\Flex Builder 3\dsh\src\com\esria\samples\dashboard\view\ListContent.mxml
 *	Template: 	flex2/compiler/mxml/gen/ClassDef.vm
 *	Time: 		2009.10.21 17:04:12 CST
 */

package com.esria.samples.dashboard.view
{

import com.esria.samples.dashboard.renderers.ListPodRenderer;
import com.esria.samples.dashboard.view.PodContentBase;
import flash.accessibility.*;
import flash.debugger.*;
import flash.display.*;
import flash.errors.*;
import flash.events.*;
import flash.events.MouseEvent;
import flash.external.*;
import flash.filters.*;
import flash.geom.*;
import flash.media.*;
import flash.net.*;
import flash.printing.*;
import flash.profiler.*;
import flash.system.*;
import flash.text.*;
import flash.ui.*;
import flash.utils.*;
import flash.xml.*;
import mx.binding.*;
import mx.binding.IBindingClient;
import mx.controls.List;
import mx.core.ClassFactory;
import mx.core.DeferredInstanceFromClass;
import mx.core.DeferredInstanceFromFunction;
import mx.core.IDeferredInstance;
import mx.core.IFactory;
import mx.core.IPropertyChangeNotifier;
import mx.core.UIComponentDescriptor;
import mx.core.mx_internal;
import mx.styles.*;



//	begin class def

public class ListContent
	extends com.esria.samples.dashboard.view.PodContentBase
	implements mx.binding.IBindingClient
{

	//	instance variables
	[Bindable]
/**
 * @private
 **/
	public var list : mx.controls.List;


	//	type-import dummies


	//	Container document descriptor
private var _documentDescriptor_ : mx.core.UIComponentDescriptor = 
new mx.core.UIComponentDescriptor({
  type: com.esria.samples.dashboard.view.PodContentBase
  ,
  propertiesFactory: function():Object { return {
    childDescriptors: [
      new mx.core.UIComponentDescriptor({
        type: mx.controls.List
        ,
        id: "list"
        ,
        events: {
          click: "__list_click"
        }
        ,
        stylesFactory: function():void {
          this.borderStyle = "none";
          this.themeColor = 16777215;
        }
        ,
        propertiesFactory: function():Object { return {
          percentWidth: 100.0,
          percentHeight: 100.0,
          itemRenderer: _ListContent_ClassFactory1_c()
        }}
      })
    ]
  }}
})

	//	constructor (Flex display object)
    /**
     * @private
     **/
	public function ListContent()
	{
		super();

		mx_internal::_document = this;

		//	our style settings



		//	properties
		this.percentWidth = 100.0;
		this.percentHeight = 100.0;

		//	events

	}

	//	initialize()
    /**
     * @private
     **/
	override public function initialize():void
	{
 		mx_internal::setDocumentDescriptor(_documentDescriptor_);

		var bindings:Array = _ListContent_bindingsSetup();
		var watchers:Array = [];

		var target:ListContent = this;

		if (_watcherSetupUtil == null)
		{
			var watcherSetupUtilClass:Object = getDefinitionByName("_com_esria_samples_dashboard_view_ListContentWatcherSetupUtil");
			watcherSetupUtilClass["init"](null);
		}

		_watcherSetupUtil.setup(this,
					function(propertyName:String):* { return target[propertyName]; },
					bindings,
					watchers);

		for (var i:uint = 0; i < bindings.length; i++)
		{
			Binding(bindings[i]).execute();
		}

		mx_internal::_bindings = mx_internal::_bindings.concat(bindings);
		mx_internal::_watchers = mx_internal::_watchers.concat(watchers);


		super.initialize();
	}

	//	scripts
	//	<Script>, line 10 - 36

			import mx.controls.Label;
			import flash.net.navigateToURL;
			import mx.collections.ArrayCollection;
			import mx.events.ListEvent;
			import mx.rpc.events.ResultEvent;
							
			[Bindable]
			private var dataProvider:ArrayCollection;
			
			override protected function onResultHttpService(e:ResultEvent):void
			{
				var a:Array = xmlListToObjectArray(e.result.item);
				dataProvider = new ArrayCollection(a);
			}
			
			private function onClickList(e:MouseEvent):void
			{
				// Only respond to clicks if the user clicks the label rather than the entire width of the renderer.
				if (e.target is Label)
				{
					var urlRequest:URLRequest = new URLRequest(dataProvider[List(e.currentTarget).selectedIndex].url);
					navigateToURL(urlRequest, "_blank");
				}
			}
			
		

	//	end scripts


    //	supporting function definitions for properties, events, styles, effects
private function _ListContent_ClassFactory1_c() : mx.core.ClassFactory
{
	var temp : mx.core.ClassFactory = new mx.core.ClassFactory();
	temp.generator = com.esria.samples.dashboard.renderers.ListPodRenderer;
	return temp;
}

/**
 * @private
 **/
public function __list_click(event:flash.events.MouseEvent):void
{
	onClickList(event)
}


	//	binding mgmt
    private function _ListContent_bindingsSetup():Array
    {
        var result:Array = [];
        var binding:Binding;

        binding = new mx.binding.Binding(this,
            function():Object
            {
                return (dataProvider);
            },
            function(_sourceFunctionReturnValue:Object):void
            {
				
                list.dataProvider = _sourceFunctionReturnValue;
            },
            "list.dataProvider");
        result[0] = binding;

        return result;
    }

    private function _ListContent_bindingExprs():void
    {
        var destination:*;
		[Binding(id='0')]
		destination = (dataProvider);
    }

    /**
     * @private
     **/
    public static function set watcherSetupUtil(watcherSetupUtil:IWatcherSetupUtil):void
    {
        (ListContent)._watcherSetupUtil = watcherSetupUtil;
    }

    private static var _watcherSetupUtil:IWatcherSetupUtil;



	//	embed carrier vars
	//	end embed carrier vars

	//	binding management vars
    /**
     * @private
     **/
    mx_internal var _bindings : Array = [];
    /**
     * @private
     **/
    mx_internal var _watchers : Array = [];
    /**
     * @private
     **/
    mx_internal var _bindingsByDestination : Object = {};
    /**
     * @private
     **/
    mx_internal var _bindingsBeginWithWord : Object = {};

//	end class def
}

//	end package def
}
