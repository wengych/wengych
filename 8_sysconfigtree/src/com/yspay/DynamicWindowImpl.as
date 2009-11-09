package com.yspay
{
    import mx.containers.Panel;
    import mx.containers.TitleWindow;

    public class DynamicWindowImpl extends TitleWindow
    {
        private var windows_in:Panel;
        private var windows_out:Panel;
        
        public function DynamicWindowImpl()
        {
            super();
        }
        
        protected function init():void
        {
            this.addEventListener(ServiceCallCompleteEvent.OPERATION_COMPLETE, DataReady);
        }
        
        private function DataReady():void
        {
            
        }
    }
}