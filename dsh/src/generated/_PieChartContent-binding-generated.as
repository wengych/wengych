

import flash.events.Event;
import flash.events.EventDispatcher;
import flash.events.IEventDispatcher;
import mx.core.IPropertyChangeNotifier;
import mx.events.PropertyChangeEvent;
import mx.utils.ObjectProxy;
import mx.utils.UIDUtil;

import mx.collections.ArrayCollection;
import qs.charts.effects.DrillDownEffect;
import mx.charts.PieChart;
import mx.charts.series.PieSeries;
import qs.charts.effects.DrillUpEffect;

class BindableProperty
{
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
	 * generated bindable wrapper for property pieChart (public)
	 * - generated setter
	 * - generated getter
	 * - original public var 'pieChart' moved to '_718516814pieChart'
	 */

    [Bindable(event="propertyChange")]
    public function get pieChart():mx.charts.PieChart
    {
        return this._718516814pieChart;
    }

    public function set pieChart(value:mx.charts.PieChart):void
    {
    	var oldValue:Object = this._718516814pieChart;
        if (oldValue !== value)
        {
            this._718516814pieChart = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "pieChart", oldValue, value));
        }
    }

	/**
	 * generated bindable wrapper for property pieSeries (public)
	 * - generated setter
	 * - generated getter
	 * - original public var 'pieSeries' moved to '_343391453pieSeries'
	 */

    [Bindable(event="propertyChange")]
    public function get pieSeries():mx.charts.series.PieSeries
    {
        return this._343391453pieSeries;
    }

    public function set pieSeries(value:mx.charts.series.PieSeries):void
    {
    	var oldValue:Object = this._343391453pieSeries;
        if (oldValue !== value)
        {
            this._343391453pieSeries = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "pieSeries", oldValue, value));
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



}
