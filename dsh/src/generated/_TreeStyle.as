
package 
{

import flash.display.Sprite;
import mx.core.IFlexModuleFactory;
import mx.core.mx_internal;
import mx.styles.CSSStyleDeclaration;
import mx.styles.StyleManager;

[ExcludeClass]

public class _TreeStyle
{
    [Embed(_pathsep='true', _resolvedSource='C:/Program Files/Adobe/Flex Builder 3/sdks/3.2.0/frameworks/libs/framework.swc$Assets.swf', original='Assets.swf', source='C:/Program Files/Adobe/Flex Builder 3/sdks/3.2.0/frameworks/libs/framework.swc$Assets.swf', _file='C:/Program Files/Adobe/Flex Builder 3/sdks/3.2.0/frameworks/libs/framework.swc$defaults.css', _line='1553', symbol='TreeFolderClosed')]
    private static var _embed_css_Assets_swf_TreeFolderClosed_1500473032:Class;
    [Embed(_pathsep='true', _resolvedSource='C:/Program Files/Adobe/Flex Builder 3/sdks/3.2.0/frameworks/libs/framework.swc$Assets.swf', original='Assets.swf', source='C:/Program Files/Adobe/Flex Builder 3/sdks/3.2.0/frameworks/libs/framework.swc$Assets.swf', _file='C:/Program Files/Adobe/Flex Builder 3/sdks/3.2.0/frameworks/libs/framework.swc$defaults.css', _line='1550', symbol='TreeNodeIcon')]
    private static var _embed_css_Assets_swf_TreeNodeIcon_1149873145:Class;
    [Embed(_pathsep='true', _resolvedSource='C:/Program Files/Adobe/Flex Builder 3/sdks/3.2.0/frameworks/libs/framework.swc$Assets.swf', original='Assets.swf', source='C:/Program Files/Adobe/Flex Builder 3/sdks/3.2.0/frameworks/libs/framework.swc$Assets.swf', _file='C:/Program Files/Adobe/Flex Builder 3/sdks/3.2.0/frameworks/libs/framework.swc$defaults.css', _line='1554', symbol='TreeFolderOpen')]
    private static var _embed_css_Assets_swf_TreeFolderOpen_411634122:Class;
    [Embed(_pathsep='true', _resolvedSource='C:/Program Files/Adobe/Flex Builder 3/sdks/3.2.0/frameworks/libs/framework.swc$Assets.swf', original='Assets.swf', source='C:/Program Files/Adobe/Flex Builder 3/sdks/3.2.0/frameworks/libs/framework.swc$Assets.swf', _file='C:/Program Files/Adobe/Flex Builder 3/sdks/3.2.0/frameworks/libs/framework.swc$defaults.css', _line='1551', symbol='TreeDisclosureClosed')]
    private static var _embed_css_Assets_swf_TreeDisclosureClosed_420622697:Class;
    [Embed(_pathsep='true', _resolvedSource='C:/Program Files/Adobe/Flex Builder 3/sdks/3.2.0/frameworks/libs/framework.swc$Assets.swf', original='Assets.swf', source='C:/Program Files/Adobe/Flex Builder 3/sdks/3.2.0/frameworks/libs/framework.swc$Assets.swf', _file='C:/Program Files/Adobe/Flex Builder 3/sdks/3.2.0/frameworks/libs/framework.swc$defaults.css', _line='1552', symbol='TreeDisclosureOpen')]
    private static var _embed_css_Assets_swf_TreeDisclosureOpen_1918691019:Class;

    public static function init(fbs:IFlexModuleFactory):void
    {
        var style:CSSStyleDeclaration = StyleManager.getStyleDeclaration("Tree");
    
        if (!style)
        {
            style = new CSSStyleDeclaration();
            StyleManager.setStyleDeclaration("Tree", style, false);
        }
    
        if (style.defaultFactory == null)
        {
            style.defaultFactory = function():void
            {
                this.paddingLeft = 2;
                this.folderClosedIcon = _embed_css_Assets_swf_TreeFolderClosed_1500473032;
                this.defaultLeafIcon = _embed_css_Assets_swf_TreeNodeIcon_1149873145;
                this.paddingRight = 0;
                this.verticalAlign = "middle";
                this.disclosureClosedIcon = _embed_css_Assets_swf_TreeDisclosureClosed_420622697;
                this.folderOpenIcon = _embed_css_Assets_swf_TreeFolderOpen_411634122;
                this.disclosureOpenIcon = _embed_css_Assets_swf_TreeDisclosureOpen_1918691019;
            };
        }
    }
}

}
