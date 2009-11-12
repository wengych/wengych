






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
public class _com_esria_samples_dashboard_view_PieChartContentWatcherSetupUtil extends Sprite
    implements mx.binding.IWatcherSetupUtil
{
    public function _com_esria_samples_dashboard_view_PieChartContentWatcherSetupUtil()
    {
        super();
    }

    public static function init(fbs:IFlexModuleFactory):void
    {
        import com.esria.samples.dashboard.view.PieChartContent;
        (com.esria.samples.dashboard.view.PieChartContent).watcherSetupUtil = new _com_esria_samples_dashboard_view_PieChartContentWatcherSetupUtil();
    }

    public function setup(target:Object,
                          propertyGetter:Function,
                          bindings:Array,
                          watchers:Array):void
    {
        import flash.events.EventDispatcher;
        import mx.core.DeferredInstanceFromFunction;
        import qs.charts.effects.DrillDownEffect;
        import com.esria.samples.dashboard.view.PieChartContent_inlineComponent1;
        import mx.charts.series.items.PieSeriesItem;
        import mx.core.IDeferredInstance;
        import mx.charts.series.PieSeries;
        import mx.core.ClassFactory;
        import mx.core.mx_internal;
        import mx.core.IPropertyChangeNotifier;
        import mx.charts.HitData;
        import mx.utils.ObjectProxy;
        import mx.utils.UIDUtil;
        import mx.binding.IBindingClient;
        import mx.charts.PieChart;
        import mx.events.EffectEvent;
        import com.esria.samples.dashboard.view.PodContentBase;
        import mx.rpc.events.ResultEvent;
        import mx.charts.events.ChartItemEvent;
        import mx.core.UIComponentDescriptor;
        import mx.collections.ArrayCollection;
        import mx.events.PropertyChangeEvent;
        import flash.events.Event;
        import mx.core.IFactory;
        import mx.core.DeferredInstanceFromClass;
        import mx.binding.BindingManager;
        import flash.events.IEventDispatcher;
        import qs.charts.effects.DrillUpEffect;

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

        // writeWatcher id=1 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher shouldWriteChildren=true
        watchers[1] = new mx.binding.PropertyWatcher("properties",
            {
                propertyChange: true
            }
,         // writeWatcherListeners id=1 size=1
        [
        bindings[1]
        ]
,
                                                                 propertyGetter
);

        // writeWatcher id=2 shouldWriteSelf=true class=flex2.compiler.as3.binding.XMLWatcher shouldWriteChildren=true
        watchers[2] = new mx.binding.XMLWatcher("valueField",
        // writeWatcherListeners id=2 size=1
        [
        bindings[1]
        ]
        );


        // writeWatcherBottom id=0 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher
        watchers[0].updateParent(target);

 





        // writeWatcherBottom id=1 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher
        watchers[1].updateParent(target);

 





        // writeWatcherBottom id=2 shouldWriteSelf=true class=flex2.compiler.as3.binding.XMLWatcher
        watchers[1].addChild(watchers[2]);

 





    }
}

}
