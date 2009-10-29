// ActionScript file
package com.yspay
{
    import mx.containers.Canvas;
    import mx.containers.TitleWindow;
    import mx.controls.TextArea;
    import mx.controls.Alert;
    import mx.events.CloseEvent;
    import mx.managers.PopUpManager;
    import mx.rpc.events.FaultEvent;
    import mx.rpc.events.ResultEvent;
    import mx.managers.CursorManager;

    import flash.net.Socket;
    import flash.utils.ByteArray;
    import flash.events.SecurityErrorEvent;
    import flash.events.IOErrorEvent;
    import flash.events.ProgressEvent;
    import flash.events.Event;
    import flash.events.MouseEvent;
    import com.adobe.serialization.json.*;
    import mx.collections.ArrayCollection;

    import mx.controls.TextInput;
    import mx.controls.Label;
    import mx.controls.Button;
    import mx.collections.XMLListCollection;


    public class newview extends TitleWindow
    {
        private var socket:Socket=new Socket();
        private var tempstr:String="";
        private var receivestr:String="";
        private var jsonstr:String="";
        private var ac1:ArrayCollection=new ArrayCollection;
        private var ac2:ArrayCollection=new ArrayCollection;

        private var lb:Label;
        private var bt:Button;
        private var tx:Object = new Array() ;

        public var ta:TextArea;
        public var login:Canvas;

        public function cancleclick():void{
                PopUpManager.removePopUp(this);
        }

        internal function formatsendmsg(msg:String):String{
            var m:ByteArray = new ByteArray();
            m.writeMultiByte(msg, "GB_CN");
            var msglen:String = m.length.toString();
            var msglenlen:String = msglen.length.toString();
            msg = msglenlen + msglen + msg;
            return(msg);
        }

        public function do_job(xml_text:String):void{
            socket.addEventListener(ProgressEvent.SOCKET_DATA,funreceive);
            socket.addEventListener(Event.CONNECT,funConnect);
            socket.addEventListener(Event.CLOSE,funClose);
            socket.addEventListener(SecurityErrorEvent.SECURITY_ERROR,funSecurity);
            socket.addEventListener(IOErrorEvent.IO_ERROR,funIOError);

            var tempstr0:String = "{version:\"1.0\",type:\"request\",reqflag:false,reqtype:\"json\",respflag:false,resptype:\"json\",active:\"YSProxyDtpDTSConfigSelect\"}";
            var tempstr1:String = "{\"__DICT_IN\":[\"" + xml_text + "\"]}";
            tempstr = formatsendmsg(tempstr0) + formatsendmsg(tempstr1);
            trace("发送字串:\n" + tempstr + "\n");
            ta.text += "\n\n发送字串\n" + tempstr + "\n";
            getConnect();
        }

        internal function getConnect():void{
            var sIP:String = parentApplication.ip_text.text;
            var sPort:Number = Number(parentApplication.port_text.text);
            if(!(sIP&&sPort)){
                Alert.show('服务器地址和端口号必填！','Warning:');
            }else{
                ta.text+= '\n Connecting......\n';
                socket.connect(sIP,sPort);
            }
        }
        internal function funreceive(event:ProgressEvent):void
        {
            var mstr:ByteArray=new ByteArray;
            while(socket.bytesAvailable){
                socket.readBytes(mstr,0,socket.bytesAvailable);
            }
            ta.text+="返回字串\n"+mstr+"\r\n";
            receivestr+=mstr;
            if((receivestr.substr(-4,4)=="</L>")||(receivestr.substr(-2,2)=="?>")) {
                ta.text+="\n字串接收完毕\n";
                socket.close();
                if((receivestr.substr(-4,4)=="</L>")){
                    while (receivestr.substr(0,6)!="<L KEY"){
                        receivestr=receivestr.substring(1,receivestr.length);
                    }
                    makeview();
                }else if(receivestr.substr(-2,2)=="?>"){
                    Alert.show('DTS号错误！','Warning:');
                }
            }
        }

        internal function makeview():void
        {
            var viewxml:XML=XML(receivestr);
            var viewlist:XMLList=XMLList(viewxml.L.L);
            var viewcoll:XMLListCollection=new XMLListCollection;
            viewcoll.source=viewlist;
            var viewlen:int=viewcoll.length;
            var tempstr0:String="{\"";

            for(var i:int=0; i < viewlen; i++)
            {
                var children:XMLList = viewcoll[i].children();
                for(var j:int=0; j < children.length(); j++) {
                    trace(children[j].@KEY);
                    
                    if(children[j].@KEY.toUpperCase()=="LABEL"){
                        lb = new Label();
                        lb.id="lb"+i.toString();
                        lb.x=50;
                        lb.y=50+i*30;
                        for each(var txml:XML in children[j].children())
                        {
                            trace(txml.@KEY);
                            if(txml.@KEY.toUpperCase()=="TEXT"){
                                lb.text =txml.@VALUE;
                            }
                        }
                        login.addChild(lb);
                    }
                    else if(children[j].@KEY.toUpperCase()=="TEXTINPUT"){
                        tx[i] = new TextInput;
                        tx[i].x=150;
                        tx[i].y=50+i*30;
                        for each(txml in children[j].children())
                        {
                            trace(txml.@KEY);
                            if(txml.@KEY.toUpperCase() == "LENGTH")
                                tx[i].maxChars=int(txml.@VALUE);
                            if((txml.@KEY.toUpperCase()=="DISPLAYASPASSWORD")&&(txml.@VALUE=="1"))
                                tx[i].displayAsPassword=true;
                            if(txml.@KEY.toUpperCase()=="HOST_DICT_NAME")
                                tx[i].id=txml.@VALUE;
                        }
                        login.addChild(tx[i]);
                    }
                    else if(children[j].@KEY.toUpperCase()=="BUTTON"){
                        bt=new Button();
                        bt.id="Button"+i.toString();
                        bt.x=150;
                        bt.y=100+i*30;
                        for each(txml in children[j].children())
                        {
                            trace(txml.@KEY);
                            if(txml.@KEY.toUpperCase()=="LABEL"){
                                bt.label=txml.@VALUE;
                            }
                            if(txml.@KEY.toLowerCase()=="version"){
                                tempstr0+="version\""+txml.@VALUE;
                            }
                        }
/*                          
"{\"version\":\"1.0\",\"type\":\"request\",\"reqflag\":false,\"reqtype\":\"json\",\"respflag\":false,\"resptype\":\"json\",\"active\":\"YSProxyDtpOperatorCheckPassword\"}";
version     version" VALUE="1.0"/>
type        type" VALUE="request"/>     
reqflag     reqflag" VALUE="[bool]true"/>
reqtype     reqtype" VALUE="json2userbus"/>
respflag        respflag" VALUE="[bool]true"/>
resptype        resptype" VALUE="json"/>
active      active" VALUE="YSAccountMX"/>
*/
                        bt.addEventListener(MouseEvent.CLICK,clicktx);
                        login.addChild(bt);
                    }
                }
            }
            
        }
        internal function clicktx(event:MouseEvent):void{
            Alert.show(tx[0].id+"-----"+tx[1].id);
        }
        internal function funConnect(event:Event):void
        {
            ta.text+="\n连接已建立\n";
            receivestr="";
            socket.writeMultiByte(tempstr,"CN-GB");
            socket.flush();
        }
        internal function funClose(event:Event):void
        {
            ta.text+="\n连接已关闭\n";
        }
        internal function funSecurity(e:SecurityErrorEvent):void{
            Alert.show('安全错误：'+e.text,'Security Error');
            ta.text+= 'Security Error!';
        }
        internal function funIOError(e:IOErrorEvent):void{
            Alert.show('IO错误：'+e.text,'Socket connect Error');
            ta.text+= 'Socket connect Error!';
        }
    }
}