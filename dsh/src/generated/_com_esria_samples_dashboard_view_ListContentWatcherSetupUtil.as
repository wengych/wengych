






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
public class _com_esria_samples_dashboard_view_ListContentWatcherSetupUtil extends Sprite
    implements mx.binding.IWatcherSetupUtil
{
    public function _com_esria_samples_dashboard_view_ListContentWatcherSetupUtil()
    {
        super();
    }

    public static function init(fbs:IFlexModuleFactory):void
    {
        import com.esria.samples.dashboard.view.ListContent;
        (com.esria.samples.dashboard.view.ListContent).watcherSetupUtil = new _com_esria_samples_dashboard_view_ListContentWatcherSetupUtil();
    }

    public function setup(target:Object,
                          propertyGetter:Function,
                          bindings:Array,
                          watchers:Array):void
    {
        import flash.events.EventDispatcher;
        import mx.core.DeferredInstanceFromFunction;
        import mx.core.IDeferredInstance;
        import flash.net.navigateToURL;
        import mx.core.ClassFactory;
        import mx.core.mx_internal;
        import mx.controls.List;
        import mx.core.IPropertyChangeNotifier;
        import mx.utils.ObjectProxy;
        import mx.controls.Label;
        import mx.utils.UIDUtil;
        import flash.events.MouseEvent;
        import mx.events.ListEvent;
        import mx.binding.IBindingClient;
        import com.esria.samples.dashboard.view.PodContentBase;
        import mx.rpc.events.ResultEvent;
        import com.esria.samples.dashboard.renderers.ListPodRenderer;
        import mx.core.UIComponentDescriptor;
        import mx.collections.ArrayCollection;
        import mx.events.PropertyChangeEvent;
        import mx.core.IFactory;
        import flash.events.Event;
        import mx.core.DeferredInstanceFromClass;
        import mx.binding.BindingManager;
        import flash.events.IEventDispatcher;

        // writeWatcher id=0 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher shouldWriteChildren=true
        watchers[0] = new mx.binding.PropertyWatcher("dataProvider",
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
