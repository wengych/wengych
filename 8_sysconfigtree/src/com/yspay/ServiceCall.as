package com.yspay
{
    import flash.events.Event;
    import flash.events.EventDispatcher;
    import flash.events.IOErrorEvent;
    import flash.events.ProgressEvent;
    import flash.events.SecurityErrorEvent;
    import flash.net.Socket;
    import flash.utils.ByteArray;
    
    import mx.controls.Alert;
    
    public class ServiceCall
    {
        private var _socket:Socket = new Socket();
        private var _serverIp:String;
        private var _serverPort:int;
        // private var arr_sock_recv:ByteArray;
        private var _strRequest:String;
        private var _isGetPackageLen:Boolean = true;
        private var _isGetPackageHead:Boolean = true;
        private var _currentPackage:ByteArray = new ByteArray();
        private var _currentPackageLength:int = 0;
        private var _responseHead:String;
        private var _responseBody:String;
        private var _charSet:String = "CN-GB";
        private var _sockCompEventListener:EventDispatcher;
        
        public function ServiceCall()
        {
        }
        
        public function SetServerInfo(ip:String, port:int):void
        {
            _serverIp = ip;
            _serverPort = port;
        }
        
        public function FormatSendMsg(msg:String):String{
            var m:ByteArray = new ByteArray();
            m.writeMultiByte(msg, _charSet);
            var msglen:String = m.length.toString();
            var msglenlen:String = msglen.length.toString();
            msg = msglenlen + msglen + msg;
            return(msg);
        }
        
        public function SetCompleteHandler(req_head:String, req_body:String, event_listener:EventDispatcher):void
        {
            _socket.addEventListener(ProgressEvent.SOCKET_DATA, socket_recv_data);
            _socket.addEventListener(Event.CLOSE, socket_closed);
            _socket.addEventListener(Event.CONNECT, socket_connected);
            _socket.addEventListener(SecurityErrorEvent.SECURITY_ERROR, socket_security_error);
            _socket.addEventListener(IOErrorEvent.IO_ERROR, socket_io_error);
            
            _sockCompEventListener = event_listener;
            _strRequest = FormatSendMsg(req_head) + FormatSendMsg(req_body);
        }
        
        public function do_service_call():void
        {
            _socket.connect(_serverIp, _serverPort);
        }
        
        private function GetPackage():String
        {
            if (this._isGetPackageLen == true &&
                _socket.bytesAvailable > 0)
            {
                var len_of_len:String = _socket.readMultiByte(1, _charSet);
                this._currentPackageLength = 
                    int(_socket.readMultiByte(int(len_of_len), _charSet));
                
                trace ("接收数据长度:", _currentPackageLength);
                this._isGetPackageLen = false;
                
            }
            if (this._isGetPackageLen == false &&
                _socket.bytesAvailable > 0)
            {
                _socket.readBytes(_currentPackage, 0, _currentPackageLength);
                
                trace ("接收数据内容:", _currentPackage.toString());
                this._isGetPackageLen = true;
                
                // this._sockCompEventListener.dispatchEvent(new SocketCompleteEvent(_currentPackage));
            }
            
            var strRtn:String =  _currentPackage.readMultiByte(_currentPackage.bytesAvailable, _charSet);
            _currentPackage.length = 0;
            
            return strRtn;
        }
        private function GetResponseHead():void
        {
            _responseHead = GetPackage();
            
            if (_responseHead.length > 0)
                this._isGetPackageHead = false;
        }
        
        private function GetResponseBody():void
        {
            _responseBody = GetPackage();
        }
        internal function socket_recv_data(event:ProgressEvent):void
        {
            if (this._isGetPackageHead == true &&
                _socket.bytesAvailable > 0)
            {
                GetResponseHead();
            }
            if (this._isGetPackageHead == false &&
                _socket.bytesAvailable > 0)
            {
                GetResponseBody();
                this._isGetPackageHead = true;
                _socket.close();
                
                this._sockCompEventListener.dispatchEvent(
                    new ServiceCallCompleteEvent(this._responseHead, this._responseBody));
            }
            
        }
        
        internal function socket_connected(event:Event):void
        {
            if (_strRequest.length > 0)
            {
                trace("发送请求:", _strRequest);
                _socket.writeMultiByte(_strRequest, "CN-GB");
            }
        }
        
        internal function socket_closed(event:Event):void
        {
            // nothing todo now.
        }
        
        internal function socket_security_error(e:SecurityErrorEvent):void
        {
            Alert.show('安全错误：'+e.text,'Security Error');
        }

        internal function socket_io_error(e:IOErrorEvent):void
        {
            Alert.show('IO错误：'+e.text,'Socket connect Error');
        }
    }
}