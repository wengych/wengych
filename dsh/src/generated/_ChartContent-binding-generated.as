

import flash.events.Event;
import flash.events.EventDispatcher;
import flash.events.IEventDispatcher;
import mx.core.IPropertyChangeNotifier;
import mx.events.PropertyChangeEvent;
import mx.utils.ObjectProxy;
import mx.utils.UIDUtil;

import mx.collections.ArrayCollection;
import mx.containers.ViewStack;
import mx.charts.LineChart;
import qs.charts.effects.DrillDownEffect;
import Number;
import mx.charts.series.ColumnSeries;
import mx.charts.series.LineSeries;
import mx.charts.ColumnChart;
import qs.charts.effects.DrillUpEffect;

class BindableProperty
{
	/**
	 * generated bindable wrapper for property columnChart (public)
	 * - generated setter
	 * - generated getter
	 * - original public var 'columnChart' moved to '_860964312columnChart'
	 */

    [Bindable(event="propertyChange")]
    public function get columnChart():mx.charts.ColumnChart
    {
        return this._860964312columnChart;
    }

    public function set columnChart(value:mx.charts.ColumnChart):void
    {
    	var oldValue:Object = this._860964312columnChart;
        if (oldValue !== value)
        {
            this._860964312columnChart = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "columnChart", oldValue, value));
        }
    }

	/**
	 * generated bindable wrapper for property columnSeries (public)
	 * - generated setter
	 * - generated getter
	 * - original public var 'columnSeries' moved to '_464296595columnSeries'
	 */

    [Bindable(event="propertyChange")]
    public function get columnSeries():mx.charts.series.ColumnSeries
    {
        return this._464296595columnSeries;
    }

    public function set columnSeries(value:mx.charts.series.ColumnSeries):void
    {
    	var oldValue:Object = this._464296595columnSeries;
        if (oldValue !== value)
        {
            this._464296595columnSeries = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "columnSeries", oldValue, value));
        }
    }

	/**
	 * generated bindable wrapper for property drillDownEffect (public)
	 * - generated setter
	 * - generated getter
	 * - original public var 'drillDownEffect' moved to '_1056393102drillDownEffect'
	 */

    [Bindable(event="propertyChange")]
    public function get drillDownEffect():qs.charts.effects.DrillDownEffect
    {
        return this._1056393102drillDownEffect;
    }

    public function set drillDownEffect(value:qs.charts.effects.DrillDownEffect):void
    {
    	var oldValue:Object = this._1056393102drillDownEffect;
        if (oldValue !== value)
        {
            this._1056393102drillDownEffect = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "drillDownEffect", oldValue, value));
        }
    }

	/**
	 * generated bindable wrapper for property drillUpEffect (public)
	 * - generated setter
	 * - generated getter
	 * - original public var 'drillUpEffect' moved to '_1677428103drillUpEffect'
	 */

    [Bindable(event="propertyChange")]
    public function get drillUpEffect():qs.charts.effects.DrillUpEffect
    {
        return this._1677428103drillUpEffect;
    }

    public function set drillUpEffect(value:qs.charts.effects.DrillUpEffect):void
    {
    	var oldValue:Object = this._1677428103drillUpEffect;
        if (oldValue !== value)
        {
            this._1677428103drillUpEffect = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "drillUpEffect", oldValue, value));
        }
    }

	/**
	 * generated bindable wrapper for property lineChart (public)
	 * - generated setter
	 * - generated getter
	 * - original public var 'lineChart' moved to '_1822289846lineChart'
	 */

    [Bindable(event="propertyChange")]
    public function get lineChart():mx.charts.LineChart
    {
        return this._1822289846lineChart;
    }

    public function set lineChart(value:mx.charts.LineChart):void
    {
    	var oldValue:Object = this._1822289846lineChart;
        if (oldValue !== value)
        {
            this._1822289846lineChart = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "lineChart", oldValue, value));
        }
    }

	/**
	 * generated bindable wrapper for property lineSeries (public)
	 * - generated setter
	 * - generated getter
	 * - original public var 'lineSeries' moved to '_200617077lineSeries'
	 */

    [Bindable(event="propertyChange")]
    public function get lineSeries():mx.charts.series.LineSeries
    {
        return this._200617077lineSeries;
    }

    public function set lineSeries(value:mx.charts.series.LineSeries):void
    {
    	var oldValue:Object = this._200617077lineSeries;
        if (oldValue !== value)
        {
            this._200617077lineSeries = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "lineSeries", oldValue, value));
        }
    }

	/**
	 * generated bindable wrapper for property viewStack (public)
	 * - generated setter
	 * - generated getter
	 * - original public var 'viewStack' moved to '_1584105757viewStack'
	 */

    [Bindable(event="propertyChange")]
    public function get viewStack():mx.containers.ViewStack
    {
        return this._1584105757viewStack;
    }

    public function set viewStack(value:mx.containers.ViewStack):void
    {
    	var oldValue:Object = this._1584105757viewStack;
        if (oldValue !== value)
        {
            this._1584105757viewStack = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "viewStack", oldValue, value));
        }
    }

	/**
	 * generated bindable wrapper for property dataProvider (private)
	 * - generated setter
	 * - generated getter
	 * - original private var 'dataProvider' moved to '_339742651dataProvider'
	 */

    [Bindable(event="propertyChange")]
    private function get dataProvider():ArrayCollection
    {
        return this._339742651dataProvider;
    }

    private function set dataProvider(value:ArrayCollection):void
    {
    	var oldValue:Object = this._339742651dataProvider;
        if (oldValue !== value)
        {
            this._339742651dataProvider = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "dataProvider", oldValue, value));
        }
    }

	/**
	 * generated bindable wrapper for property _selectedViewIndex (private)
	 * - generated setter
	 * - generated getter
	 * - original private var '_selectedViewIndex' moved to '_781955667_selectedViewIndex'
	 */

    [Bindable(event="propertyChange")]
    private function get _selectedViewIndex():Number
    {
        return this._781955667_selectedViewIndex;
    }

    private function set _selectedViewIndex(value:Number):void
    {
    	var oldValue:Object = this._781955667_selectedViewIndex;
        if (oldValue !== value)
        {
            this._781955667_selectedViewIndex = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "_selectedViewIndex", oldValue, value));
        }
    }



}
