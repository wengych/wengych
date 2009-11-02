// ActionScript file
package com.yspay.DBSDTSObject
{
    import mx.collections.ArrayCollection;
    
    public class DtsRequest extends DtsObject
    {
        //'{version:"1.0",type:"request",reqflag:true,reqtype:"json2userbus",respflag:true,resptype:"json",active:"YSCAppSysServ2"}';
        // {version:\"1.0\",type:\"request\",reqflag:true,reqtype:\"json2userbus\",respflag:true,resptype:\"xml2\",active:\"YSDBSDTSObjectConfigSelect\"}
        
        private var _reqBody:String;
        
        public function DtsRequest(reqBody:String)
        {
            _headObj["version"] = "1.0";
            _headObj["type"]    = '"request"';
            
            _reqBody = reqBody;
        }
        
        public function get RequestHead():String
        {
            var head:String =
                "{" +
                "version"  + ":" + _headObj["version"] + "," +
                "type"     + ":" + _headObj["type"] + "," +
                "reqflag"  + ":" + _headObj["reqflag"] + "," +
                "reqtype"  + ":" + _headObj["reqtype"] + "," +
                "respflag" + ":" + _headObj["respflag"] + "," +
                "resptype" + ":" + _headObj["resptype"] + "," +
                "active"   + ":" + _headObj["active"] + "}";
            return head;
        }
        
        public function get RequestBody():String
        {
            return _reqBody;
        }
    }
}