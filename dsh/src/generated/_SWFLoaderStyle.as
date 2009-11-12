
package 
{

import flash.display.Sprite;
import mx.core.IFlexModuleFactory;
import mx.core.mx_internal;
import mx.styles.CSSStyleDeclaration;
import mx.styles.StyleManager;
import mx.skins.halo.BrokenImageBorderSkin;

[ExcludeClass]

public class _SWFLoaderStyle
{
    [Embed(_pathsep='true', _resolvedSource='C:/Program Files/Adobe/Flex Builder 3/sdks/3.2.0/frameworks/libs/framework.swc$Assets.swf', original='Assets.swf', source='C:/Program Files/Adobe/Flex Builder 3/sdks/3.2.0/frameworks/libs/framework.swc$Assets.swf', _file='C:/Program Files/Adobe/Flex Builder 3/sdks/3.2.0/frameworks/libs/framework.swc$defaults.css', _line='1333', symbol='__brokenImage')]
    private static var _embed_css_Assets_swf___brokenImage_1003344314:Class;

    public static function init(fbs:IFlexModuleFactory):void
    {
        var style:CSSStyleDeclaration = StyleManager.getStyleDeclaration("SWFLoader");
    
        if (!style)
        {
            style = new CSSStyleDeclaration();
            StyleManager.setStyleDeclaration("SWFLoader", style, false);
        }
    
        if (style.defaultFactory == null)
        {
            style.defaultFactory = function():void
            {
                this.brokenImageSkin = _embed_css_Assets_swf___brokenImage_1003344314;
                this.borderStyle = "none";
                this.brokenImageBorderSkin = mx.skins.halo.BrokenImageBorderSkin;
            };
        }
    }
}

}
