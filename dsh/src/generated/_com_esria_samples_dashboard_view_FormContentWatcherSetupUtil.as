






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
public class _com_esria_samples_dashboard_view_FormContentWatcherSetupUtil extends Sprite
    implements mx.binding.IWatcherSetupUtil
{
    public function _com_esria_samples_dashboard_view_FormContentWatcherSetupUtil()
    {
        super();
    }

    public static function init(fbs:IFlexModuleFactory):void
    {
        import com.esria.samples.dashboard.view.FormContent;
        (com.esria.samples.dashboard.view.FormContent).watcherSetupUtil = new _com_esria_samples_dashboard_view_FormContentWatcherSetupUtil();
    }

    public function setup(target:Object,
                          propertyGetter:Function,
                          bindings:Array,
                          watchers:Array):void
    {
        import mx.core.DeferredInstanceFromFunction;
        import flash.events.EventDispatcher;
        import mx.containers.HBox;
        import mx.formatters.DateFormatter;
        import mx.controls.dataGridClasses.DataGridColumn;
        import mx.core.IDeferredInstance;
        import mx.core.ClassFactory;
        import mx.core.mx_internal;
        import mx.containers.ViewStack;
        import mx.controls.TextInput;
        import mx.core.IPropertyChangeNotifier;
        import mx.utils.ObjectProxy;
        import mx.controls.Label;
        import mx.containers.Canvas;
        import mx.controls.TextArea;
        import mx.controls.Button;
        import mx.utils.UIDUtil;
        import flash.events.MouseEvent;
        import mx.controls.DataGrid;
        import mx.controls.DateField;
        import mx.events.ListEvent;
        import mx.binding.IBindingClient;
        import mx.rpc.events.ResultEvent;
        import com.esria.samples.dashboard.view.PodContentBase;
        import mx.events.FlexEvent;
        import mx.controls.ComboBox;
        import mx.core.UIComponentDescriptor;
        import mx.containers.VBox;
        import mx.collections.ArrayCollection;
        import mx.events.PropertyChangeEvent;
        import mx.controls.Spacer;
        import flash.events.Event;
        import mx.core.IFactory;
        import mx.core.DeferredInstanceFromClass;
        import mx.binding.BindingManager;
        import flash.events.IEventDispatcher;

        // writeWatcher id=4 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher shouldWriteChildren=true
        watchers[4] = new mx.binding.PropertyWatcher("dataProvider",
            {
                propertyChange: true
            }
,         // writeWatcherListeners id=4 size=6
        [
        bindings[4],
        bindings[8],
        bindings[6],
        bindings[3],
        bindings[7],
        bindings[5]
        ]
,
                                                                 propertyGetter
);

        // writeWatcher id=5 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher shouldWriteChildren=true
        watchers[5] = new mx.binding.PropertyWatcher("length",
            {
                collectionChange: true
            }
,         // writeWatcherListeners id=5 size=5
        [
        bindings[4],
        bindings[6],
        bindings[3],
        bindings[7],
        bindings[5]
        ]
,
                                                                 null
);

        // writeWatcher id=6 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher shouldWriteChildren=true
        watchers[6] = new mx.binding.PropertyWatcher("_selectedIndex",
            {
                propertyChange: true
            }
,         // writeWatcherListeners id=6 size=1
        [
        bindings[9]
        ]
,
                                                                 propertyGetter
);

        // writeWatcher id=1 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher shouldWriteChildren=true
        watchers[1] = new mx.binding.PropertyWatcher("addingRecord",
            {
                propertyChange: true
            }
,         // writeWatcherListeners id=1 size=2
        [
        bindings[2],
        bindings[7]
        ]
,
                                                                 propertyGetter
);

        // writeWatcher id=9 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher shouldWriteChildren=true
        watchers[9] = new mx.binding.PropertyWatcher("dataFields",
            {
                propertyChange: true
            }
,         // writeWatcherListeners id=9 size=3
        [
        bindings[15],
        bindings[13],
        bindings[11]
        ]
,
                                                                 propertyGetter
);

        // writeWatcher id=13 shouldWriteSelf=true class=flex2.compiler.as3.binding.FunctionReturnWatcher shouldWriteChildren=true
        watchers[13] = new mx.binding.FunctionReturnWatcher("getItemAt",
                                                                     target,
                                                                     function():Array { return [ 1 ]; },
            {
                collectionChange: true
            }
,
                                                                     [bindings[13]],
                                                                     null
);

        // writeWatcher id=16 shouldWriteSelf=true class=flex2.compiler.as3.binding.FunctionReturnWatcher shouldWriteChildren=true
        watchers[16] = new mx.binding.FunctionReturnWatcher("getItemAt",
                                                                     target,
                                                                     function():Array { return [ 2 ]; },
            {
                collectionChange: true
            }
,
                                                                     [bindings[15]],
                                                                     null
);

        // writeWatcher id=10 shouldWriteSelf=true class=flex2.compiler.as3.binding.FunctionReturnWatcher shouldWriteChildren=true
        watchers[10] = new mx.binding.FunctionReturnWatcher("getItemAt",
                                                                     target,
                                                                     function():Array { return [ 0 ]; },
            {
                collectionChange: true
            }
,
                                                                     [bindings[11]],
                                                                     null
);

        // writeWatcher id=0 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher shouldWriteChildren=true
        watchers[0] = new mx.binding.PropertyWatcher("selectedViewIndex",
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

        // writeWatcher id=11 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher shouldWriteChildren=true
        watchers[11] = new mx.binding.PropertyWatcher("field1Label",
            {
                propertyChange: true
            }
,         // writeWatcherListeners id=11 size=1
        [
        bindings[12]
        ]
,
                                                                 propertyGetter
);

        // writeWatcher id=12 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher shouldWriteChildren=true
        watchers[12] = new mx.binding.PropertyWatcher("text",
            {
                valueCommit: true
            }
,         // writeWatcherListeners id=12 size=1
        [
        bindings[12]
        ]
,
                                                                 null
);

        // writeWatcher id=14 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher shouldWriteChildren=true
        watchers[14] = new mx.binding.PropertyWatcher("field2Label",
            {
                propertyChange: true
            }
,         // writeWatcherListeners id=14 size=1
        [
        bindings[14]
        ]
,
                                                                 propertyGetter
);

        // writeWatcher id=15 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher shouldWriteChildren=true
        watchers[15] = new mx.binding.PropertyWatcher("text",
            {
                valueCommit: true
            }
,         // writeWatcherListeners id=15 size=1
        [
        bindings[14]
        ]
,
                                                                 null
);

        // writeWatcher id=2 shouldWriteSelf=false class=flex2.compiler.as3.binding.PropertyWatcher shouldWriteChildren=true

        // writeWatcher id=7 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher shouldWriteChildren=true
        watchers[7] = new mx.binding.PropertyWatcher("field0Label",
            {
                propertyChange: true
            }
,         // writeWatcherListeners id=7 size=1
        [
        bindings[10]
        ]
,
                                                                 propertyGetter
);

        // writeWatcher id=8 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher shouldWriteChildren=true
        watchers[8] = new mx.binding.PropertyWatcher("text",
            {
                valueCommit: true
            }
,         // writeWatcherListeners id=8 size=1
        [
        bindings[10]
        ]
,
                                                                 null
);

        // writeWatcher id=3 shouldWriteSelf=false class=flex2.compiler.as3.binding.PropertyWatcher shouldWriteChildren=true


        // writeWatcherBottom id=4 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher
        watchers[4].updateParent(target);

 





        // writeWatcherBottom id=5 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher
        watchers[4].addChild(watchers[5]);

 





        // writeWatcherBottom id=6 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher
        watchers[6].updateParent(target);

 





        // writeWatcherBottom id=1 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher
        watchers[1].updateParent(target);

 





        // writeWatcherBottom id=9 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher
        watchers[9].updateParent(target);

 





        // writeWatcherBottom id=13 shouldWriteSelf=true class=flex2.compiler.as3.binding.FunctionReturnWatcher
        // writeEvaluationWatcherPart 13 9 parentWatcher
        watchers[13].parentWatcher = watchers[9];
        watchers[9].addChild(watchers[13]);

 





        // writeWatcherBottom id=16 shouldWriteSelf=true class=flex2.compiler.as3.binding.FunctionReturnWatcher
        // writeEvaluationWatcherPart 16 9 parentWatcher
        watchers[16].parentWatcher = watchers[9];
        watchers[9].addChild(watchers[16]);

 





        // writeWatcherBottom id=10 shouldWriteSelf=true class=flex2.compiler.as3.binding.FunctionReturnWatcher
        // writeEvaluationWatcherPart 10 9 parentWatcher
        watchers[10].parentWatcher = watchers[9];
        watchers[9].addChild(watchers[10]);

 





        // writeWatcherBottom id=0 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher
        watchers[0].updateParent(target);

 





        // writeWatcherBottom id=11 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher
        watchers[11].updateParent(target);

 





        // writeWatcherBottom id=12 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher
        watchers[11].addChild(watchers[12]);

 





        // writeWatcherBottom id=14 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher
        watchers[14].updateParent(target);

 





        // writeWatcherBottom id=15 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher
        watchers[14].addChild(watchers[15]);

 





        // writeWatcherBottom id=2 shouldWriteSelf=false class=flex2.compiler.as3.binding.PropertyWatcher

 





        // writeWatcherBottom id=7 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher
        watchers[7].updateParent(target);

 





        // writeWatcherBottom id=8 shouldWriteSelf=true class=flex2.compiler.as3.binding.PropertyWatcher
        watchers[7].addChild(watchers[8]);

 





        // writeWatcherBottom id=3 shouldWriteSelf=false class=flex2.compiler.as3.binding.PropertyWatcher

 





    }
}

}
