
package com.esria.samples.dashboard.view
{
import com.esria.samples.dashboard.view.PodContentBase;
import flash.accessibility.*;
import flash.debugger.*;
import flash.display.*;
import flash.errors.*;
import flash.events.*;
import flash.external.*;
import flash.filters.*;
import flash.geom.*;
import flash.media.*;
import flash.net.*;
import flash.printing.*;
import flash.profiler.*;
import flash.system.*;
import flash.text.*;
import flash.ui.*;
import flash.utils.*;
import flash.xml.*;
import mx.binding.*;
import mx.containers.ViewStack;
import mx.controls.Button;
import mx.controls.DateField;
import mx.controls.Label;
import mx.controls.TextArea;
import mx.controls.TextInput;
import mx.core.ClassFactory;
import mx.core.DeferredInstanceFromClass;
import mx.core.DeferredInstanceFromFunction;
import mx.core.IDeferredInstance;
import mx.core.IFactory;
import mx.core.IPropertyChangeNotifier;
import mx.core.mx_internal;
import mx.styles.*;
import mx.containers.HBox;
import mx.controls.Button;
import mx.containers.VBox;
import mx.controls.dataGridClasses.DataGridColumn;
import mx.controls.DataGrid;
import mx.controls.Spacer;
import com.esria.samples.dashboard.view.PodContentBase;
import mx.controls.Label;
import mx.controls.ComboBox;
import mx.containers.Canvas;

public class FormContent extends com.esria.samples.dashboard.view.PodContentBase
{
	public function FormContent() {}

	[Bindable]
	public var viewStack : mx.containers.ViewStack;
	[Bindable]
	public var field0Label : mx.controls.Label;
	[Bindable]
	public var field0Input : mx.controls.TextInput;
	[Bindable]
	public var field1Label : mx.controls.Label;
	[Bindable]
	public var field1Input : mx.controls.DateField;
	[Bindable]
	public var field2Label : mx.controls.Label;
	[Bindable]
	public var field2Input : mx.controls.TextArea;
	[Bindable]
	public var newButton : mx.controls.Button;
	[Bindable]
	public var indexInput : mx.controls.TextInput;
	[Bindable]
	public var deleteButton : mx.controls.Button;

	mx_internal var _bindings : Array;
	mx_internal var _watchers : Array;
	mx_internal var _bindingsByDestination : Object;
	mx_internal var _bindingsBeginWithWord : Object;

include "C:/Documents and Settings/a/My Documents/Flex Builder 3/dsh/src/com/esria/samples/dashboard/view/FormContent.mxml:12,137";

}}
