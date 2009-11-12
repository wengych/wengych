package
{

import flash.text.Font;
import flash.text.TextFormat;
import flash.system.ApplicationDomain;
import flash.utils.getDefinitionByName;
import mx.core.IFlexModule;
import mx.core.IFlexModuleFactory;

import mx.managers.SystemManager;

public class _test_mx_managers_SystemManager
    extends mx.managers.SystemManager
    implements IFlexModuleFactory
{
    public function _test_mx_managers_SystemManager()
    {

        super();
    }

    override     public function create(... params):Object
    {
        if (params.length > 0 && !(params[0] is String))
            return super.create.apply(this, params);

        var mainClassName:String = params.length == 0 ? "test" : String(params[0]);
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
            compiledResourceBundleNames: [ "collections", "containers", "controls", "core", "effects", "skins", "styles" ],
            creationComplete: "initApp()",
            currentDomain: ApplicationDomain.currentDomain,
            layout: "vertical",
            mainClassName: "test",
            mixins: [ "_test_FlexInit", "_alertButtonStyleStyle", "_ScrollBarStyle", "_TabStyle", "_ToolTipStyle", "_HDividedBoxStyle", "_ComboBoxStyle", "_comboDropdownStyle", "_ListBaseStyle", "_globalStyle", "_windowStylesStyle", "_PanelStyle", "_activeButtonStyleStyle", "_DividedBoxStyle", "_errorTipStyle", "_CursorManagerStyle", "_dateFieldPopupStyle", "_ButtonBarButtonStyle", "_dataGridStylesStyle", "_LinkButtonStyle", "_TitleWindowStyle", "_DataGridItemRendererStyle", "_ColorPickerStyle", "_ControlBarStyle", "_activeTabStyleStyle", "_TabBarStyle", "_textAreaHScrollBarStyleStyle", "_TreeStyle", "_DragManagerStyle", "_advancedDataGridStylesStyle", "_TextAreaStyle", "_ContainerStyle", "_textAreaVScrollBarStyleStyle", "_linkButtonStyleStyle", "_windowStatusStyle", "_richTextEditorTextAreaStyleStyle", "_todayStyleStyle", "_TextInputStyle", "_ButtonBarStyle", "_TabNavigatorStyle", "_plainStyle", "_SwatchPanelStyle", "_ApplicationStyle", "_SWFLoaderStyle", "_headerDateTextStyle", "_ButtonStyle", "_DataGridStyle", "_popUpMenuStyle", "_opaquePanelStyle", "_swatchPanelTextFieldStyle", "_weekDayStyleStyle", "_headerDragProxyStyleStyle", "_com_flexspy_imp_DataGridValueEnumEditorWatcherSetupUtil", "_com_flexspy_imp_StyleDataGridValueRendererWatcherSetupUtil", "_com_flexspy_imp_DataGridNameRendererWatcherSetupUtil", "_com_flexspy_imp_PropertyDataGridValueRendererWatcherSetupUtil" ]
        }
    }
}

}
