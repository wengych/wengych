package 
{

import mx.resources.ResourceBundle;

[ExcludeClass]

public class en_US$charts_properties extends ResourceBundle
{

    public function en_US$charts_properties()
    {
		 super("en_US", "charts");
    }

    override protected function getContent():Object
    {
        var content:Object =
        {
            "low": "low",
            "open": "open",
            "high": "high",
            "close": "close",
            "noAxisSet": "Property axis is not set for this AxisRenderer"
        };
        return content;
    }
}



}
