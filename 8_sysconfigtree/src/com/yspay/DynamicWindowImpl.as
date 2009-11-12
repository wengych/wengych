package com.yspay
{
    import mx.containers.Panel;
    import mx.containers.TitleWindow;

    public class DynamicWindowImpl extends TitleWindow
    {
        protected var windows:Array; // Panels array
        public var windows_in:Panel;
        public var windows_out:Panel;
        
        protected var service_call:ServiceCall;
        
        public function DynamicWindowImpl()
        {
            super();
        }
        
        protected function init():void
        {
            this.addEventListener(ServiceCallCompleteEvent.OPERATION_COMPLETE, DataReady);
        }
        
        private function DataReady():void
        {
            
        }
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