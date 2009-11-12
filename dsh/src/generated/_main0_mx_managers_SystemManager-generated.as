package
{

import flash.text.Font;
import flash.text.TextFormat;
import flash.system.ApplicationDomain;
import flash.utils.getDefinitionByName;
import mx.core.IFlexModule;
import mx.core.IFlexModuleFactory;

import mx.managers.SystemManager;

public class _main0_mx_managers_SystemManager
    extends mx.managers.SystemManager
    implements IFlexModuleFactory
{
    public function _main0_mx_managers_SystemManager()
    {

        super();
    }

    override     public function create(... params):Object
    {
        if (params.length > 0 && !(params[0] is String))
            return super.create.apply(this, params);

        var mainClassName:String = params.length == 0 ? "main0" : String(params[0]);
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
            mainClassName: "main0",
            minHeight: "600",
            minWidth: "600",
            mixins: [ "_main0_FlexInit", "_alertButtonStyleStyle", "_ControlBarStyle", "_ScrollBarStyle", "_TabBarStyle", "_activeTabStyleStyle", "_TabStyle", "_textAreaHScrollBarStyleStyle", "_ToolTipStyle", "_ComboBoxStyle", "_DragManagerStyle", "_TextAreaStyle", "_advancedDataGridStylesStyle", "_DateFieldStyle", "_comboDropdownStyle", "_ListBaseStyle", "_DateChooserStyle", "_textAreaVScrollBarStyleStyle", "_ContainerStyle", "_linkButtonStyleStyle", "_globalStyle", "_windowStatusStyle", "_PanelStyle", "_windowStylesStyle", "_activeButtonStyleStyle", "_errorTipStyle", "_richTextEditorTextAreaStyleStyle", "_CursorManagerStyle", "_todayStyleStyle", "_dateFieldPopupStyle", "_TextInputStyle", "_ButtonBarStyle", "_ButtonBarButtonStyle", "_plainStyle", "_dataGridStylesStyle", "_ApplicationStyle", "_headerDateTextStyle", "_ButtonStyle", "_DataGridStyle", "_CalendarLayoutStyle", "_popUpMenuStyle", "_AlertStyle", "_swatchPanelTextFieldStyle", "_opaquePanelStyle", "_weekDayStyleStyle", "_headerDragProxyStyleStyle", "_DataGridItemRendererStyle", "_com_esria_samples_dashboard_view_ChartContentWatcherSetupUtil", "_com_esria_samples_dashboard_view_FormContentWatcherSetupUtil", "_com_esria_samples_dashboard_view_ListContentWatcherSetupUtil", "_com_esria_samples_dashboard_view_PieChartContentWatcherSetupUtil" ],
            paddingBottom: "35",
            paddingLeft: "45",
            paddingRight: "45",
            paddingTop: "34",
            viewSourceURL: "srcview/index.html"
        }
    }
}

}
