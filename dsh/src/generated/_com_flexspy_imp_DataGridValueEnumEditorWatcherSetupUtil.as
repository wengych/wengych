






package
{
import flash.display.Sprite;
import mx.core.IFlexModuleFactory;
import mx.binding.ArrayElementWatcher;
import mx.binding.FunctionReturnWatcher;
import mx.binding.IWatcherSetupUtil;
import mx.binding.PropertyWatcher;
import mx.binding.RepeaterComponentWatcher;
import mx.binding.RepeaterItemWatcher;
import mx.binding.StaticPropertyWatcher;
import mx.binding.XMLWatcher;
import mx.binding.Watcher;

[ExcludeClass]
[Mixin]
public class _com_flexspy_imp_DataGridValueEnumEditorWatcherSetupUtil extends Sprite
    implements mx.binding.IWatcherSetupUtil
{
    public function _com_flexspy_imp_DataGridValueEnumEditorWatcherSetupUtil()
    {
        super();
    }

    public static function init(fbs:IFlexModuleFactory):void
    {
        import com.flexspy.imp.DataGridValueEnumEditor;
        (com.flexspy.imp.DataGridValueEnumEditor).watcherSetupUtil = new _com_flexspy_imp_DataGridValueEnumEditorWatcherSetupUtil();
    }

    public function setup(target:Object,
                          propertyGetter:Function,
                          bindings:Array,
                          watchers:Array):void
    {
        import flash.events.EventDispatcher;
        import mx.core.DeferredInstanceFromFunction;
        import mx.events.FlexMouseEvent;
        import mx.core.IDeferredInstance;
        import mx.events.DropdownEvent;
        import mx.core.ClassFactory;
        import mx.core.mx_internal;
        import mx.core.IPropertyChangeNotifier;
        import mx.utils.ObjectProxy;
        import mx.containers.Canvas;
        import mx.utils.UIDUtil;
        import mx.controls.DataGrid;
        import mx.binding.IBindingClient;
        import mx.events.FlexEvent;
        import mx.controls.ComboBox;
        import mx.core.UIComponentDescriptor;
        import mx.collections.ArrayCollection;
        import mx.events.PropertyChangeEvent;
        import mx.controls.listClasses.IListItemRenderer;
        import flash.events.Event;
        import mx.core.IFactory;
        import mx.core.DeferredInstanceFromClass;
        import mx.events.DataGridEvent;
        import mx.binding.BindingManager;
        import flash.events.IEventDispatcher;

        // writeWatcher id=0 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher shouldWriteChildren=true
        watchers[0] = new mx.binding.PropertyWatcher("possibleValues",
            {
                propertyChange: true
            }
,         // writeWatcherListeners id=0 size=1
        [
        bindings[0]
        ]
,
                                                                 propertyGetter
);


        // writeWatcherBottom id=0 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher
        watchers[0].updateParent(target);

 





    }
}

}
