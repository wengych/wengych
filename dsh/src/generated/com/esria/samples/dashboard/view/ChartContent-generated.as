
/**
 * 	Generated by mxmlc 2.0
 *
 *	Package:	com.esria.samples.dashboard.view
 *	Class: 		ChartContent
 *	Source: 	C:\Documents and Settings\a\My Documents\Flex Builder 3\dsh\src\com\esria\samples\dashboard\view\ChartContent.mxml
 *	Template: 	flex2/compiler/mxml/gen/ClassDef.vm
 *	Time: 		2009.10.21 17:04:12 CST
 */

package com.esria.samples.dashboard.view
{

import com.esria.samples.dashboard.view.ChartContent_inlineComponent1;
import com.esria.samples.dashboard.view.ChartContent_inlineComponent2;
import com.esria.samples.dashboard.view.PodContentBase;
import flash.accessibility.*;
import flash.debugger.*;
import flash.display.*;
import flash.errors.*;
import flash.events.*;
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
import mx.charts.CategoryAxis;
import mx.charts.ColumnChart;
import mx.charts.LineChart;
import mx.charts.series.ColumnSeries;
import mx.charts.series.LineSeries;
import mx.containers.Canvas;
import mx.containers.HBox;
import mx.containers.ViewStack;
import mx.controls.ComboBox;
import mx.core.ClassFactory;
import mx.core.DeferredInstanceFromClass;
import mx.core.DeferredInstanceFromFunction;
import mx.core.IDeferredInstance;
import mx.core.IFactory;
import mx.core.IPropertyChangeNotifier;
import mx.core.UIComponentDescriptor;
import mx.core.mx_internal;
import mx.events.EffectEvent;
import mx.events.ListEvent;
import mx.styles.*;
import qs.charts.effects.DrillDownEffect;
import qs.charts.effects.DrillUpEffect;



//	begin class def

public class ChartContent
	extends com.esria.samples.dashboard.view.PodContentBase
	implements mx.binding.IBindingClient
{

	//	instance variables
/**
 * @private
 **/
	public var _ChartContent_CategoryAxis1 : mx.charts.CategoryAxis;

/**
 * @private
 **/
	public var _ChartContent_CategoryAxis2 : mx.charts.CategoryAxis;

/**
 * @private
 **/
	public var _ChartContent_ComboBox1 : mx.controls.ComboBox;

	[Bindable]
/**
 * @private
 **/
	public var columnChart : mx.charts.ColumnChart;

	[Bindable]
/**
 * @private
 **/
	public var columnSeries : mx.charts.series.ColumnSeries;

	[Bindable]
/**
 * @private
 **/
	public var drillDownEffect : qs.charts.effects.DrillDownEffect;

	[Bindable]
/**
 * @private
 **/
	public var drillUpEffect : qs.charts.effects.DrillUpEffect;

	[Bindable]
/**
 * @private
 **/
	public var lineChart : mx.charts.LineChart;

	[Bindable]
/**
 * @private
 **/
	public var lineSeries : mx.charts.series.LineSeries;

	[Bindable]
/**
 * @private
 **/
	public var viewStack : mx.containers.ViewStack;


	//	type-import dummies


	//	Container document descriptor
private var _documentDescriptor_ : mx.core.UIComponentDescriptor = 
new mx.core.UIComponentDescriptor({
  type: com.esria.samples.dashboard.view.PodContentBase
  ,
  propertiesFactory: function():Object { return {
    childDescriptors: [
      new mx.core.UIComponentDescriptor({
        type: mx.containers.HBox
        ,
        stylesFactory: function():void {
          this.horizontalAlign = "right";
        }
        ,
        propertiesFactory: function():Object { return {
          percentWidth: 100.0,
          childDescriptors: [
            new mx.core.UIComponentDescriptor({
              type: mx.controls.ComboBox
              ,
              id: "_ChartContent_ComboBox1"
              ,
              events: {
                change: "___ChartContent_ComboBox1_change"
              }
              ,
              propertiesFactory: function():Object { return {
                dataProvider: ["Bar Chart", "Line Chart"]
              }}
            })
          ]
        }}
      })
    ,
      new mx.core.UIComponentDescriptor({
        type: mx.containers.ViewStack
        ,
        id: "viewStack"
        ,
        propertiesFactory: function():Object { return {
          creationPolicy: "all",
          percentWidth: 100.0,
          percentHeight: 100.0,
          childDescriptors: [
            new mx.core.UIComponentDescriptor({
              type: mx.containers.Canvas
              ,
              propertiesFactory: function():Object { return {
                percentWidth: 100.0,
                percentHeight: 100.0,
                childDescriptors: [
                  new mx.core.UIComponentDescriptor({
                    type: mx.charts.ColumnChart
                    ,
                    id: "columnChart"
                    ,
                    propertiesFactory: function():Object { return {
                      percentWidth: 100.0,
                      percentHeight: 100.0,
                      showDataTips: true,
                      dataTipFunction: columnChartDataTipFunction,
                      series: [_ChartContent_ColumnSeries1_i()],
                      horizontalAxis: _ChartContent_CategoryAxis1_i()
                    }}
                  })
                ]
              }}
            })
          ,
            new mx.core.UIComponentDescriptor({
              type: mx.containers.Canvas
              ,
              propertiesFactory: function():Object { return {
                percentWidth: 100.0,
                percentHeight: 100.0,
                childDescriptors: [
                  new mx.core.UIComponentDescriptor({
                    type: mx.charts.LineChart
                    ,
                    id: "lineChart"
                    ,
                    propertiesFactory: function():Object { return {
                      percentWidth: 100.0,
                      percentHeight: 100.0,
                      showDataTips: true,
                      dataTipFunction: columnChartDataTipFunction,
                      series: [_ChartContent_LineSeries1_i()],
                      horizontalAxis: _ChartContent_CategoryAxis2_i()
                    }}
                  })
                ]
              }}
            })
          ]
        }}
      })
    ]
  }}
})

	//	constructor (Flex display object)
    /**
     * @private
     **/
	public function ChartContent()
	{
		super();

		mx_internal::_document = this;

		//	our style settings



		//	properties
		this.percentWidth = 100.0;
		this.percentHeight = 100.0;
		_ChartContent_DrillDownEffect1_i();
		_ChartContent_DrillUpEffect1_i();

		//	events

	}

	//	initialize()
    /**
     * @private
     **/
	override public function initialize():void
	{
 		mx_internal::setDocumentDescriptor(_documentDescriptor_);

		var bindings:Array = _ChartContent_bindingsSetup();
		var watchers:Array = [];

		var target:ChartContent = this;

		if (_watcherSetupUtil == null)
		{
			var watcherSetupUtilClass:Object = getDefinitionByName("_com_esria_samples_dashboard_view_ChartContentWatcherSetupUtil");
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
	//	<Script>, line 15 - 147

			import mx.charts.chartClasses.ChartBase;
			import mx.charts.chartClasses.Series;
			import mx.charts.events.ChartItemEvent;
			import mx.charts.HitData;
			import mx.charts.series.ColumnSeries;
			import mx.collections.ArrayCollection;
			import mx.controls.ComboBox;
			import mx.events.ListEvent;
			import mx.rpc.events.ResultEvent;
			
			// The original data provider used for drillUp.
			private var initialDataProvider:ArrayCollection;
			[Bindable]
			private var dataProvider:ArrayCollection;
			[Bindable]
			private var _selectedViewIndex:Number = 0;
			
			// Chart drill down variables. Users can only drill down
			// one level then click the chart to drill up.
			// Note, the majority of the drill down code including all of the classes in the "qs" package
			// are from Ely Greenfield's blog, http://www.quietlyscheming.com/blog/charts/chart-drilldown-animations/.
			private var chart:ChartBase;
			private var series:Series;
			private var drillToIndex:Number;
			
			override protected function onResultHttpService(e:ResultEvent):void
			{
				var a:Array = xmlListToObjectArray(e.result.item);
				var ac:ArrayCollection = new ArrayCollection(a);
				initialDataProvider = ac;
				dataProvider = ac;
				
				// Get the values from properties XML.
				if (properties.@selectedViewIndex.toString() != null &&
					Number(properties.@selectedViewIndex) < viewStack.numChildren) // Make sure the index is in range.
					selectedViewIndex = Number(properties.@selectedViewIndex);
				else
					selectedViewIndex = 0;
				
				columnChart.addEventListener(ChartItemEvent.ITEM_CLICK, drillDown);
				lineChart.addEventListener(ChartItemEvent.ITEM_CLICK, drillDown);
			}
			
			private function set selectedViewIndex(n:Number):void
			{
				_selectedViewIndex = n;
				if (n == 0)
				{
					chart = columnChart;
					series = columnSeries;
				}
				else
				{
					chart = lineChart;
					series = lineSeries;
				}
			}
			
			private function onChangeComboBox(e:ListEvent):void
			{
				var index:Number = ComboBox(e.target).selectedIndex;
				selectedViewIndex = index;
				dispatchViewStackChange(index);
			}

			
			private function columnChartDataTipFunction(o:HitData):String
			{
				var a:Array = properties.@dataTipUnitLabel.split("*");
				var s:String = o.item[properties.@dataTipLabelField] + "\n";
				s += a[0] + o.item[properties.@valueField] + a[1] + "\n";
				return s;
			}
			
			// Creates random drill down data.
			// Assumes initial data is months and breaks down months into 30 days.
			public function createDrillDownData(data:Object):ArrayCollection
			{
				var ac:ArrayCollection = new ArrayCollection();
				var total:Number = data[properties.@valueField];
				var len:Number = 30;
				var randomPercents:Array = new Array();
				var totalPercents:Number = 0;
				var value:Number;
				// Generate an Array of random numbers that will be used to create percentages of the totals in the next loop.
				for (var i:Number = 0; i < len; i ++)
				{
					value = Math.max(.1, Math.random());// Make sure the number is not zero.
					randomPercents.push(value);
					totalPercents += value;
				}

				for (i = 0; i < len; i ++)
				{
					var o:Object = new Object();
					value = (randomPercents[i] / totalPercents) * total;
					o[properties.@valueField] = Math.round(value * 10) / 10;
					o[properties.@categoryField] = i + 1;
					ac.addItem(o);
				}
				
				return ac;
			}
			
			public function drillDown(e:ChartItemEvent):void
			{
				chart.showDataTips = false;
				drillToIndex = e.hitData.chartItem.index
				drillDownEffect.drillFromIndex = drillToIndex;
				series.setStyle("showDataEffect", drillDownEffect);
				dataProvider = createDrillDownData(Object(e.hitData.chartItem.item)); 
				
				columnChart.removeEventListener(ChartItemEvent.ITEM_CLICK, drillDown);
				lineChart.removeEventListener(ChartItemEvent.ITEM_CLICK, drillDown);
				columnChart.addEventListener(MouseEvent.CLICK, drillUp);
				lineChart.addEventListener(MouseEvent.CLICK, drillUp);
			}
			
			public function drillUp(e:MouseEvent):void
			{
				chart.showDataTips = false;
				drillUpEffect.drillToIndex = drillToIndex;
				series.setStyle("showDataEffect", drillUpEffect);
				dataProvider = initialDataProvider; 
				
				columnChart.addEventListener(ChartItemEvent.ITEM_CLICK, drillDown);
				lineChart.addEventListener(ChartItemEvent.ITEM_CLICK, drillDown);
				columnChart.removeEventListener(MouseEvent.CLICK, drillUp);
				lineChart.removeEventListener(MouseEvent.CLICK, drillUp);
			}
			
		

	//	end scripts


    //	supporting function definitions for properties, events, styles, effects
private function _ChartContent_DrillDownEffect1_i() : qs.charts.effects.DrillDownEffect
{
	var temp : qs.charts.effects.DrillDownEffect = new qs.charts.effects.DrillDownEffect();
	drillDownEffect = temp;
	temp.duration = 1500;
	temp.addEventListener("effectEnd", __drillDownEffect_effectEnd);
	return temp;
}

/**
 * @private
 **/
public function __drillDownEffect_effectEnd(event:mx.events.EffectEvent):void
{
	chart.showDataTips=true
}

private function _ChartContent_DrillUpEffect1_i() : qs.charts.effects.DrillUpEffect
{
	var temp : qs.charts.effects.DrillUpEffect = new qs.charts.effects.DrillUpEffect();
	drillUpEffect = temp;
	temp.duration = 1500;
	temp.addEventListener("effectEnd", __drillUpEffect_effectEnd);
	return temp;
}

/**
 * @private
 **/
public function __drillUpEffect_effectEnd(event:mx.events.EffectEvent):void
{
	chart.showDataTips=true
}

/**
 * @private
 **/
public function ___ChartContent_ComboBox1_change(event:mx.events.ListEvent):void
{
	onChangeComboBox(event)
}

private function _ChartContent_ColumnSeries1_i() : mx.charts.series.ColumnSeries
{
	var temp : mx.charts.series.ColumnSeries = new mx.charts.series.ColumnSeries();
	columnSeries = temp;
	temp.setStyle("itemRenderer", _ChartContent_ClassFactory1_c());
	temp.id = "columnSeries";
	mx.binding.BindingManager.executeBindings(this, "columnSeries", columnSeries);
	if (!temp.document) temp.document = this;
	return temp;
}

private function _ChartContent_ClassFactory1_c() : mx.core.ClassFactory
{
	var temp : mx.core.ClassFactory = new mx.core.ClassFactory();
	temp.generator = com.esria.samples.dashboard.view.ChartContent_inlineComponent1;
	temp.properties = {outerDocument: this};
	return temp;
}

private function _ChartContent_CategoryAxis1_i() : mx.charts.CategoryAxis
{
	var temp : mx.charts.CategoryAxis = new mx.charts.CategoryAxis();
	_ChartContent_CategoryAxis1 = temp;
	mx.binding.BindingManager.executeBindings(this, "_ChartContent_CategoryAxis1", _ChartContent_CategoryAxis1);
	return temp;
}

private function _ChartContent_LineSeries1_i() : mx.charts.series.LineSeries
{
	var temp : mx.charts.series.LineSeries = new mx.charts.series.LineSeries();
	lineSeries = temp;
	temp.setStyle("itemRenderer", _ChartContent_ClassFactory2_c());
	temp.id = "lineSeries";
	mx.binding.BindingManager.executeBindings(this, "lineSeries", lineSeries);
	if (!temp.document) temp.document = this;
	return temp;
}

private function _ChartContent_ClassFactory2_c() : mx.core.ClassFactory
{
	var temp : mx.core.ClassFactory = new mx.core.ClassFactory();
	temp.generator = com.esria.samples.dashboard.view.ChartContent_inlineComponent2;
	temp.properties = {outerDocument: this};
	return temp;
}

private function _ChartContent_CategoryAxis2_i() : mx.charts.CategoryAxis
{
	var temp : mx.charts.CategoryAxis = new mx.charts.CategoryAxis();
	_ChartContent_CategoryAxis2 = temp;
	mx.binding.BindingManager.executeBindings(this, "_ChartContent_CategoryAxis2", _ChartContent_CategoryAxis2);
	return temp;
}


	//	binding mgmt
    private function _ChartContent_bindingsSetup():Array
    {
        var result:Array = [];
        var binding:Binding;

        binding = new mx.binding.Binding(this,
            function():int
            {
                return (_selectedViewIndex);
            },
            function(_sourceFunctionReturnValue:int):void
            {
				
                _ChartContent_ComboBox1.selectedIndex = _sourceFunctionReturnValue;
            },
            "_ChartContent_ComboBox1.selectedIndex");
        result[0] = binding;
        binding = new mx.binding.Binding(this,
            function():int
            {
                return (_selectedViewIndex);
            },
            function(_sourceFunctionReturnValue:int):void
            {
				
                viewStack.selectedIndex = _sourceFunctionReturnValue;
            },
            "viewStack.selectedIndex");
        result[1] = binding;
        binding = new mx.binding.Binding(this,
            function():Object
            {
                return (dataProvider);
            },
            function(_sourceFunctionReturnValue:Object):void
            {
				
                columnChart.dataProvider = _sourceFunctionReturnValue;
            },
            "columnChart.dataProvider");
        result[2] = binding;
        binding = new mx.binding.Binding(this,
            function():String
            {
                var result:* = (properties.@valueField);
                var stringResult:String = (result == undefined ? null : String(result));
                return stringResult;
            },
            function(_sourceFunctionReturnValue:String):void
            {
				
                columnSeries.yField = _sourceFunctionReturnValue;
            },
            "columnSeries.yField");
        result[3] = binding;
        binding = new mx.binding.Binding(this,
            function():String
            {
                var result:* = (properties.@categoryField);
                var stringResult:String = (result == undefined ? null : String(result));
                return stringResult;
            },
            function(_sourceFunctionReturnValue:String):void
            {
				
                _ChartContent_CategoryAxis1.categoryField = _sourceFunctionReturnValue;
            },
            "_ChartContent_CategoryAxis1.categoryField");
        result[4] = binding;
        binding = new mx.binding.Binding(this,
            function():Object
            {
                return (dataProvider);
            },
            function(_sourceFunctionReturnValue:Object):void
            {
				
                lineChart.dataProvider = _sourceFunctionReturnValue;
            },
            "lineChart.dataProvider");
        result[5] = binding;
        binding = new mx.binding.Binding(this,
            function():String
            {
                var result:* = (properties.@valueField);
                var stringResult:String = (result == undefined ? null : String(result));
                return stringResult;
            },
            function(_sourceFunctionReturnValue:String):void
            {
				
                lineSeries.yField = _sourceFunctionReturnValue;
            },
            "lineSeries.yField");
        result[6] = binding;
        binding = new mx.binding.Binding(this,
            function():String
            {
                var result:* = (properties.@categoryField);
                var stringResult:String = (result == undefined ? null : String(result));
                return stringResult;
            },
            function(_sourceFunctionReturnValue:String):void
            {
				
                _ChartContent_CategoryAxis2.categoryField = _sourceFunctionReturnValue;
            },
            "_ChartContent_CategoryAxis2.categoryField");
        result[7] = binding;

        return result;
    }

    private function _ChartContent_bindingExprs():void
    {
        var destination:*;
		[Binding(id='0')]
		destination = (_selectedViewIndex);
		[Binding(id='1')]
		destination = (_selectedViewIndex);
		[Binding(id='2')]
		destination = (dataProvider);
		[Binding(id='3')]
		destination = (properties.@valueField);
		[Binding(id='4')]
		destination = (properties.@categoryField);
		[Binding(id='5')]
		destination = (dataProvider);
		[Binding(id='6')]
		destination = (properties.@valueField);
		[Binding(id='7')]
		destination = (properties.@categoryField);
    }

    /**
     * @private
     **/
    public static function set watcherSetupUtil(watcherSetupUtil:IWatcherSetupUtil):void
    {
        (ChartContent)._watcherSetupUtil = watcherSetupUtil;
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
