

import flash.events.Event;
import flash.events.EventDispatcher;
import flash.events.IEventDispatcher;
import mx.core.IPropertyChangeNotifier;
import mx.events.PropertyChangeEvent;
import mx.utils.ObjectProxy;
import mx.utils.UIDUtil;

import mx.controls.Label;

class BindableProperty
{
	/**
	 * generated bindable wrapper for property nameLabel (public)
	 * - generated setter
	 * - generated getter
	 * - original public var 'nameLabel' moved to '_1215755049nameLabel'
	 */

    [Bindable(event="propertyChange")]
    public function get nameLabel():mx.controls.Label
    {
        return this._1215755049nameLabel;
    }

    public function set nameLabel(value:mx.controls.Label):void
    {
    	var oldValue:Object = this._1215755049nameLabel;
        if (oldValue !== value)
        {
            this._1215755049nameLabel = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "nameLabel", oldValue, value));
        }
    }



}
