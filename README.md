# CCJsonUtils
parse JSON String to cocos2d::Value
encode cocos2d::Value into JSON string

#JsonUtil class support 2 common function to convert between json string & cocos2d::Value
    /*parse an object to JSON string
     *  support string, float, integer, double, array, dictionary, bool
     *  @return JSON string
     */


    std::string JSONStringFromValue(const cocos2d::Value& value);

    
    /** parse a string to JSON
     *  @return JSON Object
     */
    cocos2d::Value valueFromString(const std::string& fileContent);
