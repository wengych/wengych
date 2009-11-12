

import flash.events.Event;
import flash.events.EventDispatcher;
import flash.events.IEventDispatcher;
import mx.core.IPropertyChangeNotifier;
import mx.events.PropertyChangeEvent;
import mx.utils.ObjectProxy;
import mx.utils.UIDUtil;

import mx.collections.ArrayCollection;
import mx.controls.List;

class BindableProperty
{
	/**
	 * generated bindable wrapper for property list (public)
	 * - generated setter
	 * - generated getter
	 * - original public var 'list' moved to '_3322014list'
	 */

    [Bindable(event="propertyChange")]
    public function get list():mx.controls.List
    {
        return this._3322014list;
    }

    public function set list(value:mx.controls.List):void
    {
    	var oldValue:Object = this._3322014list;
        if (oldValue !== value)
        {
            this._3322014list = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "list", oldValue, value));
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
