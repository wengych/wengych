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
    
    import com.yspay.events.ServiceCallCompleteEvent;
    
    public class ServiceCall
    {
        private var _socket:Socket = new Socket();
        private var _serverIp:String;
        private var _serverPort:int;
        private var _stat:int = 1;
        private var _currentLengthOfLength:int = 0;
        private var _currentPackageLength:uint = 0;
        private var _requestHead:String;
        private var _requestBody:ByteArray;
        private var _responseHead:ByteArray;
        private var _responseBody:ByteArray;
        private var _responseBodyLength:int;
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
        
        public function SetCompleteEventHandler(event_listener:EventDispatcher):void
        {
            _socket.addEventListener(ProgressEvent.SOCKET_DATA, socket_recv_data);
            _socket.addEventListener(Event.CLOSE, socket_closed);
            _socket.addEventListener(Event.CONNECT, socket_connected);
            _socket.addEventListener(SecurityErrorEvent.SECURITY_ERROR, socket_security_error);
            _socket.addEventListener(IOErrorEvent.IO_ERROR, socket_io_error);
            
            _sockCompEventListener = event_listener;
        }
        
        public function do_service_call(req_head:String, req_body:ByteArray):void
        {
            _requestHead = req_head;
            _requestBody = req_body;
            
            _socket.connect(_serverIp, _serverPort);
        }

        internal function socket_recv_data(event:ProgressEvent):void
        {
        	while ( _socket.bytesAvailable > 0)
            {
            	switch ( this._stat )
            	{
            		case 1:
            		case 4:
            		    this._currentLengthOfLength = int(_socket.readMultiByte(1, _charSet));
				        
				        trace ("数据长度的长度:", _currentLengthOfLength);
					    this._stat ++;
				        continue;
            		case 2:
            		case 5:
            		// 根据第一个字节判断
		            // 读取指定字接数
		            // 串长度
		            	var temp:ByteArray = new ByteArray;
		            	trace("bytesAvailable",_socket.bytesAvailable);
            			if ( _socket.bytesAvailable < this._currentLengthOfLength)
            				break;
            			_socket.readBytes(temp,0,this._currentLengthOfLength);
            	    	this._currentPackageLength = int (temp.readMultiByte(this._currentLengthOfLength,_charSet));
            	    	trace("bytesAvailable",_socket.bytesAvailable);
        			  	trace ("接收数据长度:", _currentPackageLength);
        			  	
        			  	this._stat ++;
        			  	continue;
			       	case 3:           // 根据串长度读取字节数
			       	case 6:
				       	if ( _socket.bytesAvailable < this._currentPackageLength)
				       		break;
		                if(_stat == 3)
		                {
		                	this._responseHead = new ByteArray;
		               		_socket.readBytes(this._responseHead , 0, this._currentPackageLength);
		              		trace ("接收数据长度:", this._responseHead.length);
		                	trace ("接收数据内容:", this._responseHead);
		                	this._stat ++;
		                }
		                else
		                {
		                	this._responseBody = new ByteArray;
		                	this._responseBodyLength = new int;
		                	_socket.readBytes(this._responseBody , 0, this._currentPackageLength);
    	                    this._responseBodyLength = this._currentPackageLength;
    	                    trace ("接收数据长度:", this._responseBody.length);
		                	trace ("接收数据内容:", this._responseBody);
							//this._responseBody.writeMultiByte("END",this._charSet); 
		               		_socket.close();
		                	this._stat = 1;
                    
		                    this._sockCompEventListener.dispatchEvent(
		                        new ServiceCallCompleteEvent(
		                            this._responseHead.readMultiByte(this._responseHead.length, _charSet),
		                            this._responseBody));
                            break;
		                }
		                continue;
      			}
            	break;
            }
			return;
        }
        
        internal function socket_connected(event:Event):void
        {
            if (_requestHead.length > 0)
            {
                trace ("发送请求:\n\t请求头:", _requestHead);
                trace ("\t请求体:", _requestBody);
                
                
                // _requestArray = new ByteArray();
                var len:String = String(_requestHead.length);
                var len_of_len:String = String(len.length);
                _socket.writeMultiByte(len_of_len, _charSet);
                _socket.writeMultiByte(len, _charSet);
                _socket.writeMultiByte(_requestHead, _charSet);
                
                len = String(_requestBody.length);
                len_of_len = String(len.length);
                _socket.writeMultiByte(len_of_len, _charSet);
                _socket.writeMultiByte(len, _charSet);
                _socket.writeBytes(_requestBody, 0, _requestBody.length);
                // _socket.writeBytes(_requestArray, 0, _requestArray.length);
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