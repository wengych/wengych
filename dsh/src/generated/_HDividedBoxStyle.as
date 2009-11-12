
package 
{

import flash.display.Sprite;
import mx.core.IFlexModuleFactory;
import mx.core.mx_internal;
import mx.styles.CSSStyleDeclaration;
import mx.styles.StyleManager;

[ExcludeClass]

public class _HDividedBoxStyle
{
    [Embed(_pathsep='true', _resolvedSource='C:/Program Files/Adobe/Flex Builder 3/sdks/3.2.0/frameworks/libs/framework.swc$Assets.swf', original='Assets.swf', source='C:/Program Files/Adobe/Flex Builder 3/sdks/3.2.0/frameworks/libs/framework.swc$Assets.swf', _file='C:/Program Files/Adobe/Flex Builder 3/sdks/3.2.0/frameworks/libs/framework.swc$defaults.css', _line='787', symbol='mx.skins.BoxDividerSkin')]
    private static var _embed_css_Assets_swf_mx_skins_BoxDividerSkin_1205638374:Class;
    [Embed(_pathsep='true', _resolvedSource='C:/Program Files/Adobe/Flex Builder 3/sdks/3.2.0/frameworks/libs/framework.swc$Assets.swf', original='Assets.swf', source='C:/Program Files/Adobe/Flex Builder 3/sdks/3.2.0/frameworks/libs/framework.swc$Assets.swf', _file='C:/Program Files/Adobe/Flex Builder 3/sdks/3.2.0/frameworks/libs/framework.swc$defaults.css', _line='789', symbol='mx.skins.cursor.HBoxDivider')]
    private static var _embed_css_Assets_swf_mx_skins_cursor_HBoxDivider_1853143207:Class;
    [Embed(_pathsep='true', _resolvedSource='C:/Program Files/Adobe/Flex Builder 3/sdks/3.2.0/frameworks/libs/framework.swc$Assets.swf', original='Assets.swf', source='C:/Program Files/Adobe/Flex Builder 3/sdks/3.2.0/frameworks/libs/framework.swc$Assets.swf', _file='C:/Program Files/Adobe/Flex Builder 3/sdks/3.2.0/frameworks/libs/framework.swc$defaults.css', _line='791', symbol='mx.skins.cursor.VBoxDivider')]
    private static var _embed_css_Assets_swf_mx_skins_cursor_VBoxDivider_1828003463:Class;

    public static function init(fbs:IFlexModuleFactory):void
    {
        var style:CSSStyleDeclaration = StyleManager.getStyleDeclaration("HDividedBox");
    
        if (!style)
        {
            style = new CSSStyleDeclaration();
            StyleManager.setStyleDeclaration("HDividedBox", style, false);
        }
    
        if (style.defaultFactory == null)
        {
            style.defaultFactory = function():void
            {
                this.verticalDividerCursor = _embed_css_Assets_swf_mx_skins_cursor_VBoxDivider_1828003463;
                this.dividerAffordance = 6;
                this.verticalGap = 10;
                this.horizontalGap = 10;
                this.dividerThickness = 3;
                this.dividerAlpha = 0.75;
                this.horizontalDividerCursor = _embed_css_Assets_swf_mx_skins_cursor_HBoxDivider_1853143207;
                this.dividerSkin = _embed_css_Assets_swf_mx_skins_BoxDividerSkin_1205638374;
                this.dividerColor = 0x6f7777;
            };
        }
    }
}

}
