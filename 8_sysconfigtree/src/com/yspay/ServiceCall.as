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
        private var _isSocketFirstPackage:Boolean = true;
        private var _currentPackage:String;
        private var _currentPackageLenth:int = 0;
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
        
        private function FormatSendMsg(msg:String):String{
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
        
        internal function socket_recv_data(event:ProgressEvent):void
        {
            if (this._isSocketFirstPackage == true &&
                _socket.bytesAvailable > 0)
            {
                var len_of_len:String = _socket.readMultiByte(1, _charSet);
                this._currentPackageLenth = 
                    int(_socket.readMultiByte(int(len_of_len), _charSet));
                
                trace ("接收数据长度:", _currentPackageLenth);
                this._isSocketFirstPackage = false;
            }
            if (this._isSocketFirstPackage == false &&
                _socket.bytesAvailable > 0)
            {
                _currentPackage =
                    _socket.readMultiByte(_currentPackageLenth, _charSet);
                
                trace ("接收数据内容:", _currentPackage);
                this._isSocketFirstPackage = true;
                this._socket.close();
                
                this._sockCompEventListener.dispatchEvent(new SocketCompleteEvent(_currentPackage));
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