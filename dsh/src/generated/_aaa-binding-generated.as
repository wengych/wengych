

import flash.events.Event;
import flash.events.EventDispatcher;
import flash.events.IEventDispatcher;
import mx.core.IPropertyChangeNotifier;
import mx.events.PropertyChangeEvent;
import mx.utils.ObjectProxy;
import mx.utils.UIDUtil;

import mx.controls.TextArea;

class BindableProperty
{
	/**
	 * generated bindable wrapper for property myText (public)
	 * - generated setter
	 * - generated getter
	 * - original public var 'myText' moved to '_1060040455myText'
	 */

    [Bindable(event="propertyChange")]
    public function get myText():mx.controls.TextArea
    {
        return this._1060040455myText;
    }

    public function set myText(value:mx.controls.TextArea):void
    {
    	var oldValue:Object = this._1060040455myText;
        if (oldValue !== value)
        {
            this._1060040455myText = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "myText", oldValue, value));
        }
    }



}
