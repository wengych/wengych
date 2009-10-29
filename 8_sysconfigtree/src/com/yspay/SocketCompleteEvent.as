package com.yspay
{
    import flash.events.Event;

    public class SocketCompleteEvent extends Event
    {
        public static const OPERATION_COMPLETE:String = "OperationComplete"; 
        private var _resultData:String; 
        
        public function SocketCompleteEvent(result_data:String)
        {
            super(OPERATION_COMPLETE);
            _resultData = result_data;
        }
        public function get resultData():String {  
            return _resultData;  
        }
    }
}
