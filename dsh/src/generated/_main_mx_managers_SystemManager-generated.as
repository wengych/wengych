package
{

import flash.text.Font;
import flash.text.TextFormat;
import flash.system.ApplicationDomain;
import flash.utils.getDefinitionByName;
import mx.core.IFlexModule;
import mx.core.IFlexModuleFactory;

import mx.managers.SystemManager;

public class _main_mx_managers_SystemManager
    extends mx.managers.SystemManager
    implements IFlexModuleFactory
{
    public function _main_mx_managers_SystemManager()
    {

        super();
    }

    override     public function create(... params):Object
    {
        if (params.length > 0 && !(params[0] is String))
            return super.create.apply(this, params);

        var mainClassName:String = params.length == 0 ? "main" : String(params[0]);
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
            applicationComplete: "onApplicationComplete()",
            backgroundColor: "#ffffff",
            backgroundSize: "100%",
            compiledLocales: [ "en_US" ],
            compiledResourceBundleNames: [ "SharedResources", "charts", "collections", "containers", "controls", "core", "effects", "formatters", "logging", "messaging", "rpc", "skins", "styles" ],
            currentDomain: ApplicationDomain.currentDomain,
            horizontalAlign: "left",
            mainClassName: "main",
            minHeight: "600",
            minWidth: "600",
            mixins: [ "_main_FlexInit", "_alertButtonStyleStyle", "_ScrollBarStyle", "_TabStyle", "_ToolTipStyle", "_HDividedBoxStyle", "_ComboBoxStyle", "_comboDropdownStyle", "_ListBaseStyle", "_DateChooserStyle", "_globalStyle", "_windowStylesStyle", "_PanelStyle", "_activeButtonStyleStyle", "_DividedBoxStyle", "_errorTipStyle", "_CursorManagerStyle", "_dateFieldPopupStyle", "_ButtonBarButtonStyle", "_dataGridStylesStyle", "_LinkButtonStyle", "_TitleWindowStyle", "_AlertStyle", "_DataGridItemRendererStyle", "_ColorPickerStyle", "_ControlBarStyle", "_activeTabStyleStyle", "_TabBarStyle", "_textAreaHScrollBarStyleStyle", "_TreeStyle", "_DragManagerStyle", "_advancedDataGridStylesStyle", "_TextAreaStyle", "_DateFieldStyle", "_ContainerStyle", "_textAreaVScrollBarStyleStyle", "_linkButtonStyleStyle", "_windowStatusStyle", "_richTextEditorTextAreaStyleStyle", "_todayStyleStyle", "_TextInputStyle", "_ButtonBarStyle", "_TabNavigatorStyle", "_plainStyle", "_SwatchPanelStyle", "_ApplicationStyle", "_SWFLoaderStyle", "_headerDateTextStyle", "_ButtonStyle", "_DataGridStyle", "_popUpMenuStyle", "_CalendarLayoutStyle", "_opaquePanelStyle", "_swatchPanelTextFieldStyle", "_weekDayStyleStyle", "_headerDragProxyStyleStyle", "_com_esria_samples_dashboard_view_FormContentWatcherSetupUtil", "_com_esria_samples_dashboard_view_PieChartContentWatcherSetupUtil", "_com_esria_samples_dashboard_view_ChartContentWatcherSetupUtil", "_com_esria_samples_dashboard_view_ListContentWatcherSetupUtil", "_com_flexspy_imp_DataGridValueEnumEditorWatcherSetupUtil", "_com_flexspy_imp_StyleDataGridValueRendererWatcherSetupUtil", "_com_flexspy_imp_DataGridNameRendererWatcherSetupUtil", "_com_flexspy_imp_PropertyDataGridValueRendererWatcherSetupUtil" ],
            paddingBottom: "35",
            paddingLeft: "45",
            paddingRight: "45",
            paddingTop: "34",
            viewSourceURL: "srcview/index.html"
        }
    }
}

}
