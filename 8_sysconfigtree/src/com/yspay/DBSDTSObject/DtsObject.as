package com.yspay.DBSDTSObject
{
    import flash.utils.ByteArray;
    
    public class DtsObject
    {
        protected var _headObj:Object;
        protected var _body:ByteArray;
        
        public function DtsObject()
        {
            _headObj = new Object();
        }
        
        public function SetHead(_reqFlag:String, _reqType:String, _respFlag:String, _respType:String, _active:String):void
        {
            _headObj["reqflag"]  = _reqFlag;
            _headObj["reqtype"]  = _reqType;
            _headObj["respflag"] = _respFlag;
            _headObj["resptype"] = _respType;
            _headObj["active"]   = _active;
        }
        
        public function SetBody(body:ByteArray):void
        {
            _body = body;
        }
    }
}