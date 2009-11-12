

import flash.events.Event;
import flash.events.EventDispatcher;
import flash.events.IEventDispatcher;
import mx.core.IPropertyChangeNotifier;
import mx.events.PropertyChangeEvent;
import mx.utils.ObjectProxy;
import mx.utils.UIDUtil;

import Boolean;

class BindableProperty
{
	/**
	 * generated bindable wrapper for property editable (public)
	 * - generated setter
	 * - original getter left as-is
	 * - original public setter 'editable' moved to '_1602416228editable'
	 */

    [Bindable(event="propertyChange")]
    public function set editable(value:Boolean):void
    {
    	var oldValue:Object = this.editable;
        if (oldValue !== value)
        {
            this._1602416228editable = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "editable", oldValue, value));
        }
    }

	/**
	 * generated bindable wrapper for property value (public)
	 * - generated setter
	 * - original getter left as-is
	 * - original public setter 'value' moved to '_111972721value'
	 */

    [Bindable(event="propertyChange")]
    public function set value(value:*):void
    {
    	var oldValue:Object = this.value;
        if (oldValue !== value)
        {
            this._111972721value = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "value", oldValue, value));
        }
    }



}
