
package com.esria.samples.dashboard.view
{
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
import mx.charts.ColumnChart;
import mx.charts.LineChart;
import mx.charts.series.ColumnSeries;
import mx.charts.series.LineSeries;
import mx.containers.ViewStack;
import mx.core.ClassFactory;
import mx.core.DeferredInstanceFromClass;
import mx.core.DeferredInstanceFromFunction;
import mx.core.IDeferredInstance;
import mx.core.IFactory;
import mx.core.IPropertyChangeNotifier;
import mx.core.mx_internal;
import mx.styles.*;
import qs.charts.effects.DrillDownEffect;
import qs.charts.effects.DrillUpEffect;
import mx.containers.HBox;
import mx.charts.CategoryAxis;
import mx.core.IFactory;
import com.esria.samples.dashboard.view.PodContentBase;
import mx.controls.ComboBox;
import mx.containers.Canvas;

public class ChartContent extends com.esria.samples.dashboard.view.PodContentBase
{
	public function ChartContent() {}

	[Bindable]
	public var drillDownEffect : qs.charts.effects.DrillDownEffect;
	[Bindable]
	public var drillUpEffect : qs.charts.effects.DrillUpEffect;
	[Bindable]
	public var viewStack : mx.containers.ViewStack;
	[Bindable]
	public var columnChart : mx.charts.ColumnChart;
	[Bindable]
	public var columnSeries : mx.charts.series.ColumnSeries;
	[Bindable]
	public var lineChart : mx.charts.LineChart;
	[Bindable]
	public var lineSeries : mx.charts.series.LineSeries;

	mx_internal var _bindings : Array;
	mx_internal var _watchers : Array;
	mx_internal var _bindingsByDestination : Object;
	mx_internal var _bindingsBeginWithWord : Object;

include "C:/Documents and Settings/a/My Documents/Flex Builder 3/dsh/src/com/esria/samples/dashboard/view/ChartContent.mxml:15,147";

}}
