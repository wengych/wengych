

import flash.events.Event;
import flash.events.EventDispatcher;
import flash.events.IEventDispatcher;
import mx.core.IPropertyChangeNotifier;
import mx.events.PropertyChangeEvent;
import mx.utils.ObjectProxy;
import mx.utils.UIDUtil;

import mx.controls.TextArea;
import mx.controls.Button;
import mx.collections.ArrayCollection;
import Boolean;
import mx.containers.ViewStack;
import mx.controls.TextInput;
import Number;
import mx.controls.DateField;
import mx.controls.Label;

class BindableProperty
{
	/**
	 * generated bindable wrapper for property deleteButton (public)
	 * - generated setter
	 * - generated getter
	 * - original public var 'deleteButton' moved to '_1245745987deleteButton'
	 */

    [Bindable(event="propertyChange")]
    public function get deleteButton():mx.controls.Button
    {
        return this._1245745987deleteButton;
    }

    public function set deleteButton(value:mx.controls.Button):void
    {
    	var oldValue:Object = this._1245745987deleteButton;
        if (oldValue !== value)
        {
            this._1245745987deleteButton = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "deleteButton", oldValue, value));
        }
    }

	/**
	 * generated bindable wrapper for property field0Input (public)
	 * - generated setter
	 * - generated getter
	 * - original public var 'field0Input' moved to '_682786060field0Input'
	 */

    [Bindable(event="propertyChange")]
    public function get field0Input():mx.controls.TextInput
    {
        return this._682786060field0Input;
    }

    public function set field0Input(value:mx.controls.TextInput):void
    {
    	var oldValue:Object = this._682786060field0Input;
        if (oldValue !== value)
        {
            this._682786060field0Input = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "field0Input", oldValue, value));
        }
    }

	/**
	 * generated bindable wrapper for property field0Label (public)
	 * - generated setter
	 * - generated getter
	 * - original public var 'field0Label' moved to '_680416738field0Label'
	 */

    [Bindable(event="propertyChange")]
    public function get field0Label():mx.controls.Label
    {
        return this._680416738field0Label;
    }

    public function set field0Label(value:mx.controls.Label):void
    {
    	var oldValue:Object = this._680416738field0Label;
        if (oldValue !== value)
        {
            this._680416738field0Label = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "field0Label", oldValue, value));
        }
    }

	/**
	 * generated bindable wrapper for property field1Input (public)
	 * - generated setter
	 * - generated getter
	 * - original public var 'field1Input' moved to '_654156909field1Input'
	 */

    [Bindable(event="propertyChange")]
    public function get field1Input():mx.controls.DateField
    {
        return this._654156909field1Input;
    }

    public function set field1Input(value:mx.controls.DateField):void
    {
    	var oldValue:Object = this._654156909field1Input;
        if (oldValue !== value)
        {
            this._654156909field1Input = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "field1Input", oldValue, value));
        }
    }

	/**
	 * generated bindable wrapper for property field1Label (public)
	 * - generated setter
	 * - generated getter
	 * - original public var 'field1Label' moved to '_651787587field1Label'
	 */

    [Bindable(event="propertyChange")]
    public function get field1Label():mx.controls.Label
    {
        return this._651787587field1Label;
    }

    public function set field1Label(value:mx.controls.Label):void
    {
    	var oldValue:Object = this._651787587field1Label;
        if (oldValue !== value)
        {
            this._651787587field1Label = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "field1Label", oldValue, value));
        }
    }

	/**
	 * generated bindable wrapper for property field2Input (public)
	 * - generated setter
	 * - generated getter
	 * - original public var 'field2Input' moved to '_625527758field2Input'
	 */

    [Bindable(event="propertyChange")]
    public function get field2Input():mx.controls.TextArea
    {
        return this._625527758field2Input;
    }

    public function set field2Input(value:mx.controls.TextArea):void
    {
    	var oldValue:Object = this._625527758field2Input;
        if (oldValue !== value)
        {
            this._625527758field2Input = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "field2Input", oldValue, value));
        }
    }

	/**
	 * generated bindable wrapper for property field2Label (public)
	 * - generated setter
	 * - generated getter
	 * - original public var 'field2Label' moved to '_623158436field2Label'
	 */

    [Bindable(event="propertyChange")]
    public function get field2Label():mx.controls.Label
    {
        return this._623158436field2Label;
    }

    public function set field2Label(value:mx.controls.Label):void
    {
    	var oldValue:Object = this._623158436field2Label;
        if (oldValue !== value)
        {
            this._623158436field2Label = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "field2Label", oldValue, value));
        }
    }

	/**
	 * generated bindable wrapper for property indexInput (public)
	 * - generated setter
	 * - generated getter
	 * - original public var 'indexInput' moved to '_726659608indexInput'
	 */

    [Bindable(event="propertyChange")]
    public function get indexInput():mx.controls.TextInput
    {
        return this._726659608indexInput;
    }

    public function set indexInput(value:mx.controls.TextInput):void
    {
    	var oldValue:Object = this._726659608indexInput;
        if (oldValue !== value)
        {
            this._726659608indexInput = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "indexInput", oldValue, value));
        }
    }

	/**
	 * generated bindable wrapper for property newButton (public)
	 * - generated setter
	 * - generated getter
	 * - original public var 'newButton' moved to '_1081408270newButton'
	 */

    [Bindable(event="propertyChange")]
    public function get newButton():mx.controls.Button
    {
        return this._1081408270newButton;
    }

    public function set newButton(value:mx.controls.Button):void
    {
    	var oldValue:Object = this._1081408270newButton;
        if (oldValue !== value)
        {
            this._1081408270newButton = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "newButton", oldValue, value));
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

	/**
	 * generated bindable wrapper for property dataFields (private)
	 * - generated setter
	 * - generated getter
	 * - original private var 'dataFields' moved to '_894268163dataFields'
	 */

    [Bindable(event="propertyChange")]
    private function get dataFields():ArrayCollection
    {
        return this._894268163dataFields;
    }

    private function set dataFields(value:ArrayCollection):void
    {
    	var oldValue:Object = this._894268163dataFields;
        if (oldValue !== value)
        {
            this._894268163dataFields = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "dataFields", oldValue, value));
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

	/**
	 * generated bindable wrapper for property selectedViewIndex (private)
	 * - generated setter
	 * - generated getter
	 * - original private var 'selectedViewIndex' moved to '_1014548690selectedViewIndex'
	 */

    [Bindable(event="propertyChange")]
    private function get selectedViewIndex():Number
    {
        return this._1014548690selectedViewIndex;
    }

    private function set selectedViewIndex(value:Number):void
    {
    	var oldValue:Object = this._1014548690selectedViewIndex;
        if (oldValue !== value)
        {
            this._1014548690selectedViewIndex = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "selectedViewIndex", oldValue, value));
        }
    }

	/**
	 * generated bindable wrapper for property _selectedIndex (private)
	 * - generated setter
	 * - generated getter
	 * - original private var '_selectedIndex' moved to '_652640504_selectedIndex'
	 */

    [Bindable(event="propertyChange")]
    private function get _selectedIndex():Number
    {
        return this._652640504_selectedIndex;
    }

    private function set _selectedIndex(value:Number):void
    {
    	var oldValue:Object = this._652640504_selectedIndex;
        if (oldValue !== value)
        {
            this._652640504_selectedIndex = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "_selectedIndex", oldValue, value));
        }
    }

	/**
	 * generated bindable wrapper for property addingRecord (private)
	 * - generated setter
	 * - generated getter
	 * - original private var 'addingRecord' moved to '_847926446addingRecord'
	 */

    [Bindable(event="propertyChange")]
    private function get addingRecord():Boolean
    {
        return this._847926446addingRecord;
    }

    private function set addingRecord(value:Boolean):void
    {
    	var oldValue:Object = this._847926446addingRecord;
        if (oldValue !== value)
        {
            this._847926446addingRecord = value;
            this.dispatchEvent(mx.events.PropertyChangeEvent.createUpdateEvent(this, "addingRecord", oldValue, value));
        }
    }



}
