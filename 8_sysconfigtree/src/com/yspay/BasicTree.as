package com.yspay
{
    import com.adobe.serialization.json.*;
    
    import flash.events.*;
    import flash.ui.ContextMenu;
    import flash.ui.ContextMenuItem;
    import flash.utils.ByteArray;
    
    import mx.collections.XMLListCollection;
    import mx.containers.TitleWindow;
    import mx.controls.Alert;
    import mx.controls.CheckBox;
    import mx.controls.TextArea;
    import mx.controls.TextInput;
    import mx.controls.Tree;
    import mx.core.Application;
    import mx.events.*;
    import mx.managers.PopUpManager;

    public class BasicTree extends Application
    {
        protected var _charSet:String = 'CN-GB';
        protected var _serviceCall:ServiceCall;
        protected var _log:String;
        protected var dtsxml2:XML = <L KEY="config" KEYNAME="字段定义1" VALUE="field"/>;
        protected var dtsxml3:XML = <L KEY="config" KEYNAME="字段定义1" VALUE="field">
                    <L KEY="待定" KEYNAME="待定" VALUE=""><A KEY="待定属性" KEYNAME="待定属性" VALUE=""/></L>
                </L>;
        
        protected var dynamicWindow:DynamicWindowImpl;
        protected var loginWindow:TitleWindow;
        [Bindable] public var systree:Tree;
        [Bindable] public var usertree:Tree;
        public var ta:TextArea;
        public var ip_text:TextInput;
        public var port_text:TextInput;
        public var headkeyname:TextInput;
        public var headversion:TextInput;
        public var head_isused:CheckBox;
        public var headvalue:TextInput;
        public var editxml_text:TextInput;
        [Bindable] protected var dtsxml:XML = <L/>;
        [Bindable] protected var sysdtsxml:XMLListCollection = new XMLListCollection(dtsxml.*);
        [Bindable] protected var userdtsxml:XMLListCollection = new XMLListCollection(dtsxml2.*);

        public function BasicTree()
        {
            super();
        }
        
		protected function init():void
        {
            loginWindow = PopUpManager.createPopUp(this, login, true) as TitleWindow;
            PopUpManager.centerPopUp(loginWindow);
            
            var expandMenu:ContextMenu = new ContextMenu;
            expandMenu.hideBuiltInItems();
            
            var menumodtree:ContextMenuItem = new ContextMenuItem("删除节点");
            menumodtree.addEventListener(ContextMenuEvent.MENU_ITEM_SELECT, removenode);

            expandMenu = new ContextMenu();
            expandMenu.hideBuiltInItems();
            menumodtree = new ContextMenuItem("删除节点");
            menumodtree.addEventListener(ContextMenuEvent.MENU_ITEM_SELECT, removenode);
            expandMenu.customItems.push(menumodtree);
            systree.contextMenu = expandMenu;

            var expandMenu2:ContextMenu = new ContextMenu();
            expandMenu2.hideBuiltInItems();
            var menuremovenode2:ContextMenuItem = new ContextMenuItem("删除节点");
            menuremovenode2.addEventListener(ContextMenuEvent.MENU_ITEM_SELECT, removenode2);
            expandMenu2.customItems.push(menuremovenode2);
            
            menuremovenode2 = new ContextMenuItem("保存用户配置");
            menuremovenode2.addEventListener(ContextMenuEvent.MENU_ITEM_SELECT, saveconfig);
            expandMenu2.customItems.push(menuremovenode2);
            
            usertree.contextMenu = expandMenu2;
            showtext();
            
            this.addEventListener(ServiceCallCompleteEvent.OPERATION_COMPLETE, DataReady);
        }
        
        protected function removenode(event:Event):void
        {
            if (systree.selectedIndex >= 0)
            {
                if (systree.selectedItem.@KEY == "DTS")
                {
                    Alert.show("是否要删除节点？-->" + systree.selectedItem.@KEYNAME, "删除节点", 3, this, removeClickHandler);
                }
                else
                {
                    Alert.show("请选择DTS节点！");
                }
            }
            else
            {
                Alert.show("请选择节点！");
            }
        }
        
        protected function removeClickHandler(event:CloseEvent):void
        {
            if (event.detail == Alert.YES)
            {
                
                var req_head_obj:Object = new Object();
                req_head_obj['version'] = '1.0';
                req_head_obj['type'] = 'request';
                req_head_obj['reqflag'] = true;
                req_head_obj['reqtype'] = 'json2userbus';
                req_head_obj['respflag'] = true;
                req_head_obj['resptype'] = 'json';
                req_head_obj['active'] = 'YSDBSDTSObjectConfigDelete';
                var req_head:String = JSON.encode(req_head_obj);

                var userbus:Object = new Object();
                userbus['__DICT_IN'] = [String(systree.selectedItem.@VALUE)];
                var req_body:ByteArray = new ByteArray();
                req_body.writeMultiByte(JSON.encode(userbus), _charSet);

                _serviceCall = new ServiceCall();
                _serviceCall.SetServerInfo(ip_text.text, int(port_text.text));
                _serviceCall.SetCompleteEventHandler(this);
                _serviceCall.do_service_call(req_head, req_body);

                ta.text += "发送请求:\n请求头:\n";
                ta.text += req_head;
                ta.text += "\n请求体:\n"
                ta.text += JSON.encode(userbus);
            }
        }
        
        protected function removenode2(event:Event):void
        {
            if (usertree.selectedIndex >= 0)
            {
                var children:XMLList = XMLList(usertree.selectedItem.parent().children());
                for (var i:int = 0; i < children.length(); i++)
                {
                    if (children[i].@KEYNAME == XML(usertree.selectedItem).@KEYNAME)
                    {
                        delete children[i];
                    }
                }
                dtsxml2.@KEYNAME = headkeyname.text;
                dtsxml2.@VALUE = headvalue.text;
                ta.text = dtsxml2.toXMLString();
                userdtsxml.source = XMLList(dtsxml2.*);
                userdtsxml.refresh();
            }
            else
            {
                Alert.show("请选择节点！");
            }
        }
        
        protected function saveconfig(event:Event):void
        {
            Alert.show("是否要保存配置？", "保存配置", 3, this, saveconfigHandler);
        }
        
        protected function saveconfigHandler(event:CloseEvent):void
        {
            if (event.detail == Alert.YES)
            {
                var req_head:Object = new Object();
                req_head['version'] = '1.0';
                req_head['type'] = 'request';
                req_head['reqflag'] = true;
                req_head['reqtype'] = 'xml2';
                req_head['respflag'] = true;
                req_head['resptype'] = 'json';
                req_head['active'] = 'YSDBSDTSObjectConfigInsert';
                
                // <L TYPE="filed" NAME="余额" VER="20091103123456" ISUSED="1" APPNAME="MyApp" CUSER="admin">
                var insert_xml:XML = new XML('<L TYPE="type" NAME="name" VER="20091103123456" ISUSED="1" APPNAME="MyApp" CUSER="admin" />');
                insert_xml.@TYPE = headvalue.text;
                insert_xml.@NAME = headkeyname.text;
                insert_xml.@VER = headversion.text;
                if (head_isused.toggle == true)
                    insert_xml.@ISUSED = '1';
                else
                    insert_xml.@ISUSED = '0';
                insert_xml.appendChild(dtsxml2);
                
                // var strReqBody:String = '<?xml version="1.0" encoding="gbk" ?>';
                // strReqBody += '<L TYPE="filed" NAME="余额" VER="20091103123456" ISUSED="1" APPNAME="MyApp" CUSER="admin">';
                // strReqBody += dtsxml2.toXMLString();
                // strReqBody += '</L>';
                var req_body:ByteArray = new ByteArray();
                var req_body_string:String = '<?xml version="1.0" encoding="gbk" ?>\n';
                req_body_string += insert_xml.toXMLString();
                req_body.writeMultiByte(req_body_string, _charSet);
                
                _serviceCall = new ServiceCall();
                _serviceCall.SetServerInfo(ip_text.text, int(port_text.text));
                _serviceCall.SetCompleteEventHandler(this);
                _serviceCall.do_service_call(JSON.encode(req_head), req_body);
                
                ta.text += "\n发送请求:\n请求头:\n";
                ta.text += JSON.encode(req_head);
                ta.text += "\n请求体:\n" + req_body_string;
            }
        }
        
        protected function showtext():void
        {
            dtsxml2.@KEYNAME = headkeyname.text;
            dtsxml2.@VALUE = headvalue.text;
            ta.text = dtsxml2.toXMLString();
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
        
        protected function DataReady(event:ServiceCallCompleteEvent):void
        {
            trace("DataReady:head:", event.ResponseHead);
            // trace ("DataReady:body:", event.ResponseBody);
    
            ta.text += "\n接收数据包头:\n";
            ta.text += event.ResponseHead;
    
            var obj:Object = JSON.decode(event.ResponseHead) as Object;
    
            if (obj['active'] == 'YSDBSDTSObjectList')
            {
                trace('YSDBSDTSOjbectList');
                var req_body_string:String = event.ResponseBody.readMultiByte(event.ResponseBody.length, 'CN-GB');
                var req_head:Object = JSON.decode(event.ResponseHead) as Object;
                var req_body:Object = JSON.decode(req_body_string) as Object;
    
    
                ta.text += "\n接收数据包体:\n";
                ta.text += req_body_string;
                ta.text += "\n\n";
            }
            else if (obj['active'] == 'YSDBSDTSObjectConfigSelect' && (obj['resptype'] == 'xml' || obj['resptype'] == 'xml2'))
            {
                var xml_string:String = event.ResponseBody.readMultiByte(event.ResponseBody.length, 'CN-GB');
                trace("xml_string:", xml_string);
                dtsxml = XML(xml_string);
                sysdtsxml.source = XMLList(dtsxml.L);
                sysdtsxml.refresh();
    
    
                ta.text += "\n接收数据包体:\n";
                ta.text += xml_string;
                ta.text += "\n\n";
            }
            else if (obj['active'] == 'YSDBSDTSObjectConfigDelete' || obj['active'] == 'YSDBSDTSObjectConfigInsert')
            {
                ta.text += "\n接收数据包体:\n";
                ta.text += event.ResponseBody;
                ta.text += '\n';
    
                UpdateDtsTree('ALL');
            }
            else if (obj['active'] == 'YSDBSDTSObjectSelect')
            {
                var xml_string:String = event.ResponseBody.readMultiByte(event.ResponseBody.length, 'CN-GB');
                
                var disp_xml:XML = XML(xml_string);
                
//                if (do_disp_xml)
                    ;
//                else
                    ;
                // dynamicWindow = new DynamicWindow(disp_xml);
                // dynamicWindow = PopUpManager.createPopUp(this, DynamicWindow, true) as DynamicWindowImpl;
                // PopUpManager.centerPopUp(dynamicWindow);
                
                ta.text += "\n接收数据包体:\n";
                ta.text += disp_xml.toXMLString();
                ta.text += '\n';
            }
        }
        
        protected function UpdateDtsTree(dictIn:String):void
        {
            var userbus:Object = new Object();
            userbus['__DICT_IN'] = [dictIn];
            var req_body:ByteArray = new ByteArray();
            req_body.writeMultiByte(JSON.encode(userbus), _charSet);
            var req_head:Object = new Object();
            req_head['version'] = '1.0';
            req_head['type'] = 'request';
            req_head['reqflag'] = true;
            req_head['reqtype'] = 'json2userbus';
            req_head['respflag'] = true;
            req_head['resptype'] = 'xml2';
            req_head['active'] = 'YSDBSDTSObjectConfigSelect';
            // dtsCfgSel.SetHead('true', '"json2userbus"', 'true', '"xml2"', '"YSDBSDTSObjectConfigSelect"');

            _serviceCall = new ServiceCall();
            _serviceCall.SetServerInfo(ip_text.text, int(port_text.text));
            _serviceCall.SetCompleteEventHandler(this);
            _serviceCall.do_service_call(JSON.encode(req_head), req_body);

            ta.text += "发送请求:\n请求头:\n";
            ta.text += JSON.encode(req_head);
            ta.text += "\n请求体:\n" + JSON.encode(userbus);
        }
        
        protected function editxml():void
        {
            if (editxml_text.text.length == 0)
                UpdateDtsTree('ALL');
            else
                UpdateDtsTree(editxml_text.text);
        }
        protected function onTreeDragComplete(event:DragEvent):void
        {
            showtext();
        }

        protected function cleartree():void
        {
            dtsxml2.@KEYNAME = headkeyname.text;
            dtsxml2.@VALUE = headvalue.text;
            userdtsxml.source = XMLList(dtsxml2.*);
            while (userdtsxml.length > 0)
            {
                userdtsxml.removeAll();
            }
            ta.text = dtsxml2.toXMLString();
        }
        
        protected function disxml():void
        {
//            do_disp_xml = true;
        }

        protected function newwin():void
        {
            if (editxml_text.text != "")
            {
                var userbus:Object = new Object();
                userbus['__DICT_IN'] = [editxml_text.text];
                var req_body:ByteArray = new ByteArray;
                req_body.writeMultiByte(JSON.encode(userbus), _charSet);
            
                var req_head:Object = new Object;
                req_head['version'] = '1.0';
                req_head['type'] = 'request';
                req_head['reqflag'] = true;
                req_head['reqtype'] = 'json2userbus';
                req_head['respflag'] = true;
                req_head['resptype'] = 'xml2';
                req_head['active'] = 'YSDBSDTSObjectSelect';

                // var dtsSel:DtsObject = new DtsObject();
                // dtsSel.SetHead('true', 'json', 'true', 'json', 'YSDBSDTSObjectSelect');

                _serviceCall = new ServiceCall();
                _serviceCall.SetServerInfo(ip_text.text, int(port_text.text));
                _serviceCall.SetCompleteEventHandler(this);
                _serviceCall.do_service_call(JSON.encode(req_head), req_body);

                ta.text += "发送请求:\n请求头:\n";
                ta.text += JSON.encode(req_head);
                ta.text += '\n请求体:\n';
                ta.text += JSON.encode(userbus) + '\n';

                // dynamicWindow = PopUpManager.createPopUp(this, DynamicWindow, true) as DynamicWindowImpl;
                // PopUpManager.centerPopUp(dynamicWindow);
                // tempstr="<views>"+userdtsxml.source.toXMLString()+"</views>";
            }
            else
            {
                Alert.show("请输入DTS号！");
            }
        }

        protected function chgsocket():void
        {
            if (ip_text.text == "192.168.0.77")
            {
                ip_text.text = "192.168.0.201";
                port_text.text = "6900";
            }
            else
            {
                ip_text.text = "192.168.0.77";
                port_text.text = "16920";
            }
        }
    }
}