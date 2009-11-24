package com.yspay
{
    import mx.containers.HBox;
    import mx.containers.TitleWindow;
    import mx.containers.VBox;
    import mx.controls.Label;
    import mx.controls.TextInput;
    import mx.core.Container;
    
    import com.yspay.events.*;

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
                	
                    container.addChild(windows);
                    
                    show(windows, child);
                }
                else if(child.name() == 'dict')
                {
                    var hbox:HBox = new HBox;
					container.addChild(hbox);
					
					show(hbox, child);
                }
                else if(child.name() == 'LABEL')
                {
                	var lbl:Label = new Label;
                	lbl.text = child.@text;
                	container.addChild(lbl);
                }
                else if (child.name() == 'TEXTINPUT')
                {
                    var text_input:TextInput = new TextInput;
                    container.addChild(text_input);
                }
                else if (child.name() == 'doproc')
                {
                    
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
<config>
  services
  <SERVICES>
    INQBAL
    <SendPKG>
      <HEAD active="YSAccountYE" resptype="json" respflag="true" reqtype="json2userbus" reqflag="true" type="request" version="1.0"/>
      <BODY>
        <DICT>
          ACCOUNT
          <services MIN="1" LEN="21" SUFFIX="" PREFIX="" DEFAULT="" DESCRIPT="" NAME="ACCOUNT" TYPE="String"/>
          <display>
            <LABEL text="卡号"/>
            <TEXTINPUT length="21" displayAsPassword="0"/>
          </display>
        </DICT>
      </BODY>
    </SendPKG>
    <RecvPKG>
      <HEAD active="YSAccountYE" resptype="json" respflag="true" reqtype="json2userbus" reqflag="true" type="request" version="1.0"/>
      <BODY>
        <DICT>
          EXPIRY_DATE
          <services TYPE="String" NAME="EXPIRY_DATE" DESCRIPT="" DEFAULT="" PREFIX="" SUFFIX="" LEN="4" MIN="4"/>
          <display>
            <LABEL text="有效期"/>
            <TEXTINPUT displayAsPassword="1" length="4"/>
          </display>
        </DICT>
        <DICT>
          AMOUNT
          <services TYPE="NUMBER" NAME="AMOUNT" DESCRIPT="" DEFAULT="" PREFIX="" SUFFIX="" LEN="21" MIN="21"/>
          <display>
            <LABEL text="余额"/>
            <TEXTINPUT displayAsPassword="0" length="21"/>
          </display>
        </DICT>
      </BODY>
    </RecvPKG>
  </SERVICES>
</config>
 */