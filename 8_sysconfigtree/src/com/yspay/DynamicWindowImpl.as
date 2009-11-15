package com.yspay
{
    import mx.containers.HBox;
    import mx.containers.TitleWindow;
    import mx.containers.VBox;
    import mx.controls.Label;
    import mx.controls.TextInput;
    import mx.core.Container;

    public class DynamicWindowImpl extends TitleWindow
    {
        protected var windows:Array; // Panels array
        public var windows_vbox:VBox;

        protected var service_call:ServiceCall;

        public function DynamicWindowImpl()
        {
            super();
        }

        protected function init():void
        {
            this.addEventListener(ServiceCallCompleteEvent.OPERATION_COMPLETE, DataReady);
            this.show(windows_vbox, disp_xml);
        }

        public function show(container:Container, xml_node:XML):void
        {
            for each (var child:XML in xml_node.elements())
            {
            	trace (child.name());
            	trace (child.text());
            	trace (child.attributes());
            	
                if (child.name() == 'windows')
                {
                	var windows:Windows = new Windows;
                	windows.width = container.width;
                	windows.height = container.height / 3;
                	windows['horizontalAlign'] = 'middle';
                	
                    container.addChild(windows);
                    
                    show(windows, child);
                }
                else if(child.name() == 'dict')
                {
                    var hbox:HBox = new HBox;
					var lbl:Label = new Label;
					lbl.text = child.LABEL.@text;
					var text_input:TextInput = new TextInput();
					container.addChild(hbox);
					hbox.addChild(lbl);
					hbox.addChild(text_input);
                }
                else if(child.name() == '')
                {
                	;
                }
            }
        }

        private function DataReady(event:ServiceCallCompleteEvent):void
        {

        }

        protected var disp_xml:XML = <config version="1.0" Trancode="0001">
                <windows version="1.0">
                    windows IN
                    <dict>
                        <LABEL text="账号"/>
                        <TEXTINPUT length="21" displayAsPassword="0" host_Dict_name="ACCOUNT"/>
                    </dict>
                    <doproc>
                        <button label="提交主机" version="1.0" type="request" reqflag="true" reqtype="json2userbus" respflag="true" resptype="json" active="YSAccountYE"/>
                    </doproc>
                </windows>
                <windows version="1.0">
                    windows OUT
                    <dict>
                        <LABEL text="有效期"/>
                        <TEXTINPUT length="4" displayAsPassword="0" host_Dict_name="EXPIRY_DATE"/>
                    </dict>
                    <dict>
                        <LABEL text="余额"/>
                        <TEXTINPUT length="21" displayAsPassword="0" host_Dict_name="AMOUNT"/>
                    </dict>
                    <doproc>
                        <button label="关闭" active="Close"/>
                    </doproc>
                </windows>
            </config>
    }
}

/*
   <config version="1.0" Trancode="0001">

   <windows version="1.0">
   windows IN
   <dict>
   <LABEL text="账号"/>
   <TEXTINPUT length="21" displayAsPassword="0" host_Dict_name="ACCOUNT"/>
   </dict>
   <doproc>
   <button label="提交主机" version="1.0" type="request" reqflag="true" reqtype="json2userbus" respflag="true" resptype="json" active="YSAccountYE"/>
   </doproc>
   </windows>
   <windows version="1.0">
   windows OUT
   <dict>
   <LABEL text="有效期"/>
   <TEXTINPUT length="4" displayAsPassword="0" host_Dict_name="EXPIRY_DATE"/>
   </dict>
   <dict>
   <LABEL text="余额"/>
   <TEXTINPUT length="21" displayAsPassword="0" host_Dict_name="AMOUNT"/>
   </dict>
   <doproc>
   <button label="关闭" active="Close"/>
   </doproc>
   </windows>
   </config>
 */