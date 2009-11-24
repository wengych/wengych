package com.yspay
{
    public class DictPool
    {
        private var dict_pool:Object;
        public function DictPool()
        {
            dict_pool = new Object;
        }
        public function Add(key:String, value:*):void
        {
            if (dict_pool.hasOwnProperty(key))
            {
                dict_pool[key].push(value);
            }
            else
            {
                dict_pool[key] = new Array;
                dict_pool[key].push(value);
            }
        }
    }
}

'{version:"1.0",type:"request",reqflag:true,reqtype:"xml2",respflag:true,resptype:"json",active:"YSDBSDTSObjectConfigInsert"}'
'dict://account'
''
