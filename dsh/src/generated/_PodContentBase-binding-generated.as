

import flash.events.Event;
import flash.events.EventDispatcher;
import flash.events.IEventDispatcher;
import mx.core.IPropertyChangeNotifier;
import mx.events.PropertyChangeEvent;
import mx.utils.ObjectProxy;
import mx.utils.UIDUtil;

import XML;

class BindableProperty
{
	/**
	 * generated bindable wrapper for property properties (public)
	 * - generated setter
	 * - generated getter
	 * - original public var 'properties' moved to '_926053069properties'
	 */

    [Bindable(event="propertyChange")]
    public function get properties():XML
    {
        return this._926053069properties;
    }

    public function set properties(value:XML):void
    {
    	var oldValue:Object = this._926053069properties;
        if (oldValue !== value)
        {
            this._926053069properties = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "properties", oldValue, value));
        }
    }



}
