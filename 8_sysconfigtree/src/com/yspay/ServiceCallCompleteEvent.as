package com.yspay
{
    import flash.events.Event;
    import flash.utils.ByteArray;

    public class ServiceCallCompleteEvent extends Event
    {
        public static const OPERATION_COMPLETE:String = "OperationComplete"; 
        private var _respHead:String;
        private var _respBody:ByteArray;
        
        public function ServiceCallCompleteEvent(resp_head:String, resp_body:ByteArray)
        {
            super(OPERATION_COMPLETE);
            _respHead = resp_head;
            _respBody = resp_body;
            
            trace ("ServiceCallCompleteEvent:_respHead:", _respHead);
            trace ("ServiceCallCompleteEvent:_respHead:", _respBody);
        }
        public function get ResponseHead():String {  
            return _respHead;  
        }
        public function get ResponseBody():ByteArray {
            return _respBody;
        }
    }
}
