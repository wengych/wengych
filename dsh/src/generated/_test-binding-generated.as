

import flash.events.Event;
import flash.events.EventDispatcher;
import flash.events.IEventDispatcher;
import mx.core.IPropertyChangeNotifier;
import mx.events.PropertyChangeEvent;
import mx.utils.ObjectProxy;
import mx.utils.UIDUtil;

import mx.controls.TextArea;
import mx.controls.LinkButton;

class BindableProperty
{
	/**
	 * generated bindable wrapper for property btnFlexSpy (public)
	 * - generated setter
	 * - generated getter
	 * - original public var 'btnFlexSpy' moved to '_1964535545btnFlexSpy'
	 */

    [Bindable(event="propertyChange")]
    public function get btnFlexSpy():mx.controls.LinkButton
    {
        return this._1964535545btnFlexSpy;
    }

    public function set btnFlexSpy(value:mx.controls.LinkButton):void
    {
    	var oldValue:Object = this._1964535545btnFlexSpy;
        if (oldValue !== value)
        {
            this._1964535545btnFlexSpy = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "btnFlexSpy", oldValue, value));
        }
    }

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
