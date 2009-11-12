
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
import mx.controls.List;
import mx.core.ClassFactory;
import mx.core.DeferredInstanceFromClass;
import mx.core.DeferredInstanceFromFunction;
import mx.core.IDeferredInstance;
import mx.core.IFactory;
import mx.core.IPropertyChangeNotifier;
import mx.core.mx_internal;
import mx.styles.*;
import com.esria.samples.dashboard.view.PodContentBase;

public class ListContent extends com.esria.samples.dashboard.view.PodContentBase
{
	public function ListContent() {}

	[Bindable]
	public var list : mx.controls.List;

	mx_internal var _bindings : Array;
	mx_internal var _watchers : Array;
	mx_internal var _bindingsByDestination : Object;
	mx_internal var _bindingsBeginWithWord : Object;

include "C:/Documents and Settings/a/My Documents/Flex Builder 3/dsh/src/com/esria/samples/dashboard/view/ListContent.mxml:10,36";

}}
