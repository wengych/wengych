package com.yspay.DBSDTSObject
{
    import flash.utils.ByteArray;
    import com.adobe.serialization.json.*;
    
    public class DtsObject extends Object
    {
        protected var _body:ByteArray;
        
        public function DtsObject()
        {
        }
        
        public function AddHead(_key:String, _value:String):void
        {
        }
        
        public function set Body(body:ByteArray):void
        {
            _body = body;
        }
        
        public function get Body():ByteArray
        {
            return _body;
        }
        
        public function get Head():String
        {
            return JSON.encode(this);
        }
    }
}