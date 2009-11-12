






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
public class _com_esria_samples_dashboard_view_ChartContentWatcherSetupUtil extends Sprite
    implements mx.binding.IWatcherSetupUtil
{
    public function _com_esria_samples_dashboard_view_ChartContentWatcherSetupUtil()
    {
        super();
    }

    public static function init(fbs:IFlexModuleFactory):void
    {
        import com.esria.samples.dashboard.view.ChartContent;
        (com.esria.samples.dashboard.view.ChartContent).watcherSetupUtil = new _com_esria_samples_dashboard_view_ChartContentWatcherSetupUtil();
    }

    public function setup(target:Object,
                          propertyGetter:Function,
                          bindings:Array,
                          watchers:Array):void
    {
        import mx.core.DeferredInstanceFromFunction;
        import flash.events.EventDispatcher;
        import mx.containers.HBox;
        import com.esria.samples.dashboard.view.ChartContent_inlineComponent1;
        import qs.charts.effects.DrillDownEffect;
        import mx.charts.series.ColumnSeries;
        import mx.core.IDeferredInstance;
        import mx.charts.ColumnChart;
        import com.esria.samples.dashboard.view.ChartContent_inlineComponent2;
        import mx.core.ClassFactory;
        import mx.core.mx_internal;
        import mx.containers.ViewStack;
        import mx.core.IPropertyChangeNotifier;
        import mx.charts.chartClasses.ChartBase;
        import mx.charts.HitData;
        import mx.utils.ObjectProxy;
        import mx.containers.Canvas;
        import mx.utils.UIDUtil;
        import mx.charts.LineChart;
        import mx.events.ListEvent;
        import mx.binding.IBindingClient;
        import mx.rpc.events.ResultEvent;
        import com.esria.samples.dashboard.view.PodContentBase;
        import mx.events.EffectEvent;
        import mx.controls.ComboBox;
        import mx.charts.events.ChartItemEvent;
        import mx.core.UIComponentDescriptor;
        import mx.collections.ArrayCollection;
        import mx.events.PropertyChangeEvent;
        import mx.charts.chartClasses.Series;
        import mx.charts.CategoryAxis;
        import flash.events.Event;
        import mx.core.IFactory;
        import mx.charts.series.LineSeries;
        import mx.core.DeferredInstanceFromClass;
        import mx.binding.BindingManager;
        import flash.events.IEventDispatcher;
        import qs.charts.effects.DrillUpEffect;

        // writeWatcher id=1 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher shouldWriteChildren=true
        watchers[1] = new mx.binding.PropertyWatcher("dataProvider",
            {
                propertyChange: true
            }
,         // writeWatcherListeners id=1 size=2
        [
        bindings[2],
        bindings[5]
        ]
,
                                                                 propertyGetter
);

        // writeWatcher id=0 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher shouldWriteChildren=true
        watchers[0] = new mx.binding.PropertyWatcher("_selectedViewIndex",
            {
                propertyChange: true
            }
,         // writeWatcherListeners id=0 size=2
        [
        bindings[1],
        bindings[0]
        ]
,
                                                                 propertyGetter
);

        // writeWatcher id=2 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher shouldWriteChildren=true
        watchers[2] = new mx.binding.PropertyWatcher("properties",
            {
                propertyChange: true
            }
,         // writeWatcherListeners id=2 size=4
        [
        bindings[4],
        bindings[6],
        bindings[3],
        bindings[7]
        ]
,
                                                                 propertyGetter
);

        // writeWatcher id=4 shouldWriteSelf=true class=flex2.compiler.as3.binding.XMLWatcher shouldWriteChildren=true
        watchers[4] = new mx.binding.XMLWatcher("categoryField",
        // writeWatcherListeners id=4 size=2
        [
        bindings[4],
        bindings[7]
        ]
        );

        // writeWatcher id=3 shouldWriteSelf=true class=flex2.compiler.as3.binding.XMLWatcher shouldWriteChildren=true
        watchers[3] = new mx.binding.XMLWatcher("valueField",
        // writeWatcherListeners id=3 size=2
        [
        bindings[6],
        bindings[3]
        ]
        );


        // writeWatcherBottom id=1 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher
        watchers[1].updateParent(target);

 





        // writeWatcherBottom id=0 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher
        watchers[0].updateParent(target);

 





        // writeWatcherBottom id=2 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher
        watchers[2].updateParent(target);

 





        // writeWatcherBottom id=4 shouldWriteSelf=true class=flex2.compiler.as3.binding.XMLWatcher
        watchers[2].addChild(watchers[4]);

 





        // writeWatcherBottom id=3 shouldWriteSelf=true class=flex2.compiler.as3.binding.XMLWatcher
        watchers[2].addChild(watchers[3]);

 





    }
}

}
