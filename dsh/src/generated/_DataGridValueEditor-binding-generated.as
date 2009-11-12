

import flash.events.Event;
import flash.events.EventDispatcher;
import flash.events.IEventDispatcher;
import mx.core.IPropertyChangeNotifier;
import mx.events.PropertyChangeEvent;
import mx.utils.ObjectProxy;
import mx.utils.UIDUtil;

import mx.controls.TextInput;

class BindableProperty
{
	/**
	 * generated bindable wrapper for property textArea (public)
	 * - generated setter
	 * - generated getter
	 * - original public var 'textArea' moved to '_1004197030textArea'
	 */

    [Bindable(event="propertyChange")]
    public function get textArea():mx.controls.TextInput
    {
        return this._1004197030textArea;
    }

    public function set textArea(value:mx.controls.TextInput):void
    {
    	var oldValue:Object = this._1004197030textArea;
        if (oldValue !== value)
        {
            this._1004197030textArea = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "textArea", oldValue, value));
        }
    }



}
