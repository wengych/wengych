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
        private var _strRequest:String;
        private var _isGetLenOfLen:Boolean = true;
        private var _isGetPackageLen:Boolean = false;
        private var _bGetResponseHead:Boolean = true;
        private var _bGetPackageFinish:Boolean = false;
        private var _currentPackage:ByteArray = new ByteArray();
        private var _currentLengthOfLength:int = 0;
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
        
        public function SetCompleteHandler(event_listener:EventDispatcher):void
        {
            _socket.addEventListener(ProgressEvent.SOCKET_DATA, socket_recv_data);
            _socket.addEventListener(Event.CLOSE, socket_closed);
            _socket.addEventListener(Event.CONNECT, socket_connected);
            _socket.addEventListener(SecurityErrorEvent.SECURITY_ERROR, socket_security_error);
            _socket.addEventListener(IOErrorEvent.IO_ERROR, socket_io_error);
            
            _sockCompEventListener = event_listener;
        }
        
        public function do_service_call(req_head:String, req_body:String):void
        {
            _strRequest = FormatSendMsg(req_head) + FormatSendMsg(req_body);
            _socket.connect(_serverIp, _serverPort);
        }
        
        private function GetPackage():String
        {
            var strRtn:String = "";
            if (this._isGetLenOfLen == true &&
                _socket.bytesAvailable > 0)
            {
                this._currentLengthOfLength = int(_socket.readMultiByte(1, _charSet));
                
                trace ("数据长度的长度:", _currentLengthOfLength);
                this._isGetLenOfLen = false;
                this._isGetPackageLen = true;
            }
            if (this._isGetPackageLen == true &&
                _socket.bytesAvailable >= this._currentLengthOfLength)
            {
                this._currentPackageLength = 
                    int(_socket.readMultiByte(this._currentLengthOfLength, _charSet));
                
                trace ("接收数据长度:", _currentPackageLength);
                this._isGetPackageLen = false;
                
            }
            if (this._isGetPackageLen == false &&
                _socket.bytesAvailable >= this._currentPackageLength)
            {
                _socket.readBytes(_currentPackage, 0, _currentPackageLength);
                
                this._isGetLenOfLen = true;
            }
            
            if (_currentPackage.length == _currentPackageLength)
            {
                strRtn =  _currentPackage.readMultiByte(_currentPackage.bytesAvailable, _charSet);
                _currentPackage.length = 0;
            }
            return strRtn;
        }
        private function GetResponseHead():void
        {
            _responseHead = GetPackage();
            
            if (_responseHead.length > 0)
                this._bGetResponseHead = false;
        }
        
        private function GetResponseBody():void
        {
            _responseBody = GetPackage();
            
            if (_responseBody.length == _currentPackageLength)
                _bGetPackageFinish = true;
        }
        internal function socket_recv_data(event:ProgressEvent):void
        {
            if (this._bGetResponseHead == true &&
                _socket.bytesAvailable > 0)
            {
                // 接收包头
                GetResponseHead();
            }
            if (this._bGetResponseHead == false &&
                _socket.bytesAvailable > 0)
            {
                // 接收包体
                GetResponseBody();
                
                // 接收包体成功后，关闭当前socket连接，并且发送数据接收完成事件
                if (_bGetPackageFinish == true)
                {
                    this._bGetResponseHead = true;
                    _socket.close();
                    
                    this._sockCompEventListener.dispatchEvent(
                        new ServiceCallCompleteEvent(this._responseHead, this._responseBody));
                }
            }
        }
        
        internal function socket_connected(event:Event):void
        {
            if (_strRequest.length > 0)
            {
                trace("发送请求:", _strRequest);
                _socket.writeMultiByte(_strRequest, _charSet);
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