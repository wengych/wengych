

import flash.events.Event;
import flash.events.EventDispatcher;
import flash.events.IEventDispatcher;
import mx.core.IPropertyChangeNotifier;
import mx.events.PropertyChangeEvent;
import mx.utils.ObjectProxy;
import mx.utils.UIDUtil;

import mx.controls.TabBar;
import mx.containers.ViewStack;
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
	 * generated bindable wrapper for property tabBar (public)
	 * - generated setter
	 * - generated getter
	 * - original public var 'tabBar' moved to '_881418178tabBar'
	 */

    [Bindable(event="propertyChange")]
    public function get tabBar():mx.controls.TabBar
    {
        return this._881418178tabBar;
    }

    public function set tabBar(value:mx.controls.TabBar):void
    {
    	var oldValue:Object = this._881418178tabBar;
        if (oldValue !== value)
        {
            this._881418178tabBar = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "tabBar", oldValue, value));
        }
    }

	/**
	 * generated bindable wrapper for property viewStack (public)
	 * - generated setter
	 * - generated getter
	 * - original public var 'viewStack' moved to '_1584105757viewStack'
	 */

    [Bindable(event="propertyChange")]
    public function get viewStack():mx.containers.ViewStack
    {
        return this._1584105757viewStack;
    }

    public function set viewStack(value:mx.containers.ViewStack):void
    {
    	var oldValue:Object = this._1584105757viewStack;
        if (oldValue !== value)
        {
            this._1584105757viewStack = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "viewStack", oldValue, value));
        }
    }



}
