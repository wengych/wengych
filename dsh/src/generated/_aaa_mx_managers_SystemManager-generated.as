package
{

import flash.text.Font;
import flash.text.TextFormat;
import flash.system.ApplicationDomain;
import flash.utils.getDefinitionByName;
import mx.core.IFlexModule;
import mx.core.IFlexModuleFactory;

import mx.managers.SystemManager;

public class _aaa_mx_managers_SystemManager
    extends mx.managers.SystemManager
    implements IFlexModuleFactory
{
    public function _aaa_mx_managers_SystemManager()
    {

        super();
    }

    override     public function create(... params):Object
    {
        if (params.length > 0 && !(params[0] is String))
            return super.create.apply(this, params);

        var mainClassName:String = params.length == 0 ? "aaa" : String(params[0]);
        var mainClass:Class = Class(getDefinitionByName(mainClassName));
        if (!mainClass)
            return null;

        var instance:Object = new mainClass();
        if (instance is IFlexModule)
            (IFlexModule(instance)).moduleFactory = this;
        return instance;
    }

    override    public function info():Object
    {
        return {
            compiledLocales: [ "en_US" ],
            compiledResourceBundleNames: [ "containers", "controls", "core", "effects", "skins", "styles" ],
            creationComplete: "initApp()",
            currentDomain: ApplicationDomain.currentDomain,
            layout: "vertical",
            mainClassName: "aaa",
            mixins: [ "_aaa_FlexInit", "_alertButtonStyleStyle", "_ScrollBarStyle", "_activeTabStyleStyle", "_textAreaHScrollBarStyleStyle", "_ToolTipStyle", "_advancedDataGridStylesStyle", "_TextAreaStyle", "_comboDropdownStyle", "_ContainerStyle", "_textAreaVScrollBarStyleStyle", "_linkButtonStyleStyle", "_globalStyle", "_windowStatusStyle", "_windowStylesStyle", "_activeButtonStyleStyle", "_errorTipStyle", "_richTextEditorTextAreaStyleStyle", "_CursorManagerStyle", "_todayStyleStyle", "_dateFieldPopupStyle", "_plainStyle", "_dataGridStylesStyle", "_ApplicationStyle", "_headerDateTextStyle", "_ButtonStyle", "_popUpMenuStyle", "_swatchPanelTextFieldStyle", "_opaquePanelStyle", "_weekDayStyleStyle", "_headerDragProxyStyleStyle" ]
        }
    }
}

}
