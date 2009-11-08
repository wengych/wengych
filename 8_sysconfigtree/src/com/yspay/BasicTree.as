package com.yspay
{
    import com.adobe.serialization.json.*;

    import flash.utils.ByteArray;

    import mx.core.Application;

    public class BasicTree extends Application
    {
        protected var _charSet:String = 'CN-GB';
        protected var _serviceCall:ServiceCall;
        protected var _log:String;

        public function BasicTree()
        {
            super();
        }
		
        protected function GetService(service_type:String):void
        {
            var req_head_obj:Object = new Object;
            var req_body_obj:Object = new Object;

            req_head_obj['version'] = '1.0';
            req_head_obj['type'] = 'request';
            req_head_obj['reqflag'] = true;
            req_head_obj['reqtype'] = 'json2userbus';
            req_head_obj['respflag'] = true;
            req_head_obj['resptype'] = 'json';
            req_head_obj['active'] = 'YSDBSDTSObjectList';

            req_body_obj['YSDICT_DB_TB_DTSINFO_TYPE'] = [service_type];
            req_body_obj['YSDICT_DB_TB_DTSINFO_APPNAME'] = ['MyApp'];
            req_body_obj['YSDICT_DB_TB_STARTPOS'] = [0];
            req_body_obj['YSDICT_DB_TB_ENDPOS'] = [1000];

            var req_head:String = JSON.encode(req_head_obj);
            var req_body_string:String = JSON.encode(req_body_obj);
            var req_body:ByteArray = new ByteArray;
            req_body.writeMultiByte(req_body_string, _charSet);

            _serviceCall = new ServiceCall();
            _serviceCall.SetServerInfo("192.168.0.77", 16920);
            _serviceCall.SetCompleteEventHandler(this);
            _serviceCall.do_service_call(req_head, req_body);

            trace("发送请求:\n请求头:\n", req_head);
            trace("\n请求体:\n", req_body_string);
            _log = "发送请求:\n请求头:\n" + req_head + "\n";
            _log = _log + "\n请求体:\n" + req_body_string + "\n";
        }
    }
}