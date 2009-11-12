

import flash.events.Event;
import flash.events.EventDispatcher;
import flash.events.IEventDispatcher;
import mx.core.IPropertyChangeNotifier;
import mx.events.PropertyChangeEvent;
import mx.utils.ObjectProxy;
import mx.utils.UIDUtil;

import mx.collections.ArrayCollection;
import mx.controls.ComboBox;

class BindableProperty
{
	/**
	 * generated bindable wrapper for property combobox (public)
	 * - generated setter
	 * - generated getter
	 * - original public var 'combobox' moved to '_612288131combobox'
	 */

    [Bindable(event="propertyChange")]
    public function get combobox():mx.controls.ComboBox
    {
        return this._612288131combobox;
    }

    public function set combobox(value:mx.controls.ComboBox):void
    {
    	var oldValue:Object = this._612288131combobox;
        if (oldValue !== value)
        {
            this._612288131combobox = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "combobox", oldValue, value));
        }
    }

	/**
	 * generated bindable wrapper for property possibleValues (private)
	 * - generated setter
	 * - generated getter
	 * - original private var 'possibleValues' moved to '_774743565possibleValues'
	 */

    [Bindable(event="propertyChange")]
    private function get possibleValues():ArrayCollection
    {
        return this._774743565possibleValues;
    }

    private function set possibleValues(value:ArrayCollection):void
    {
    	var oldValue:Object = this._774743565possibleValues;
        if (oldValue !== value)
        {
            this._774743565possibleValues = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "possibleValues", oldValue, value));
        }
    }



}
