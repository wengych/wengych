

import flash.events.Event;
import flash.events.EventDispatcher;
import flash.events.IEventDispatcher;
import mx.core.IPropertyChangeNotifier;
import mx.events.PropertyChangeEvent;
import mx.utils.ObjectProxy;
import mx.utils.UIDUtil;

import mx.controls.Image;
import mx.controls.Label;

class BindableProperty
{
	/**
	 * generated bindable wrapper for property editButton (public)
	 * - generated setter
	 * - generated getter
	 * - original public var 'editButton' moved to '_1454002652editButton'
	 */

    [Bindable(event="propertyChange")]
    public function get editButton():mx.controls.Image
    {
        return this._1454002652editButton;
    }

    public function set editButton(value:mx.controls.Image):void
    {
    	var oldValue:Object = this._1454002652editButton;
        if (oldValue !== value)
        {
            this._1454002652editButton = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "editButton", oldValue, value));
        }
    }

	/**
	 * generated bindable wrapper for property valueLabel (public)
	 * - generated setter
	 * - generated getter
	 * - original public var 'valueLabel' moved to '_2025208835valueLabel'
	 */

    [Bindable(event="propertyChange")]
    public function get valueLabel():mx.controls.Label
    {
        return this._2025208835valueLabel;
    }

    public function set valueLabel(value:mx.controls.Label):void
    {
    	var oldValue:Object = this._2025208835valueLabel;
        if (oldValue !== value)
        {
            this._2025208835valueLabel = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "valueLabel", oldValue, value));
        }
    }



}
