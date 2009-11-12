






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
public class _com_flexspy_imp_DataGridNameRendererWatcherSetupUtil extends Sprite
    implements mx.binding.IWatcherSetupUtil
{
    public function _com_flexspy_imp_DataGridNameRendererWatcherSetupUtil()
    {
        super();
    }

    public static function init(fbs:IFlexModuleFactory):void
    {
        import com.flexspy.imp.DataGridNameRenderer;
        (com.flexspy.imp.DataGridNameRenderer).watcherSetupUtil = new _com_flexspy_imp_DataGridNameRendererWatcherSetupUtil();
    }

    public function setup(target:Object,
                          propertyGetter:Function,
                          bindings:Array,
                          watchers:Array):void
    {
        import mx.core.DeferredInstanceFromFunction;
        import flash.events.EventDispatcher;
        import mx.utils.UIDUtil;
        import mx.binding.IBindingClient;
        import mx.core.IDeferredInstance;
        import mx.core.ClassFactory;
        import mx.core.UIComponentDescriptor;
        import mx.core.mx_internal;
        import mx.events.PropertyChangeEvent;
        import flash.events.Event;
        import mx.core.IFactory;
        import mx.core.IPropertyChangeNotifier;
        import mx.core.DeferredInstanceFromClass;
        import mx.utils.ObjectProxy;
        import mx.binding.BindingManager;
        import mx.controls.Label;
        import mx.containers.Canvas;
        import flash.events.IEventDispatcher;

        // writeWatcher id=0 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher shouldWriteChildren=true
        watchers[0] = new mx.binding.PropertyWatcher("data",
            {
                dataChange: true
            }
,         // writeWatcherListeners id=0 size=1
        [
        bindings[0]
        ]
,
                                                                 propertyGetter
);

        // writeWatcher id=1 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher shouldWriteChildren=true
        watchers[1] = new mx.binding.PropertyWatcher("displayName",
            null
,         // writeWatcherListeners id=1 size=1
        [
        bindings[0]
        ]
,
                                                                 null
);


        // writeWatcherBottom id=0 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher
        watchers[0].updateParent(target);

 





        // writeWatcherBottom id=1 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher
        watchers[0].addChild(watchers[1]);

 





    }
}

}
