/****************************************************************************
 Copyright (c) 2014 QuanNguyen
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __FunnyFramework__JSONUtils__
#define __FunnyFramework__JSONUtils__

#include "cocos2d.h"
#include "json/document.h"

class JSONUtils {
    
public:
    
#pragma mark - single ton
    /*
     *  get a single ton
     */
    static JSONUtils* getInstance();
    
    /*
     *  get a single ton
     */
    static void destroyInstance();
    
#pragma mark - deprecated
    /** parse a dictionary to JSON string
     *  support string, float, integer, double, array, dictionary, bool
     *  @return JSON string
     */
    std::string JSONStringFromParamsDictionary(cocos2d::__Dictionary *dictionary);
    
    /** parse a array of object o JSON string
     *  support string, float, integer, double, array, dictionary, bool
     *  @return JSON string
     */
    std::string JSONStringFromParamsArray(cocos2d::__Array *array);
    
#pragma mark - parse from JSON Object
    /** get string as json format from a value of json
     */
    std::string stringFromJSON(const rapidjson::Value &value);
    
    /** parse a string to json value     
     */
    bool parseJSONFromString(rapidjson::Document &document, const std::string str);
    
    /** parse a JSON to Array
     */
    std::vector<int> vectorIntFromJSON(const rapidjson::Value &value);
    
    /** parse a JSON to Array
     */
    std::vector<double> vectorDoubleFromJSON(const rapidjson::Value &value);
    
    /** parse a JSON to Array
     */
    std::vector<std::string> vectorStringFromJSON(const rapidjson::Value &value);
    
    /** parse a JSON to Array
     */
    std::vector<bool> vectorBoolFromJSON(const rapidjson::Value &value);
    
    /** parse a JSON to dictionary aka ValueMap
     */
    cocos2d::ValueMap dictionaryFromJSON(const rapidjson::Value &value);
    
    /** parse a JSON to Array Value
     */
    cocos2d::ValueVector arrayFromJSON(const rapidjson::Value &value);
    
#pragma mark - fast parse
    /** parse a dictionary to JSON string
     *  support string, float, integer, double, array, dictionary, bool
     *  @return JSON string
     */
    std::string JSONStringFromDictionary(cocos2d::ValueMap dictionary);
    
    /** parse a array of object to JSON string
     *  support string, float, integer, double, array, dictionary, bool
     *  @return JSON string
     */
    std::string JSONStringFromArray(cocos2d::ValueVector array);
    
    /** parse an object to JSON string
     *  support string, float, integer, double, array, dictionary, bool
     *  @return JSON string
     */
    std::string JSONStringFromValue(cocos2d::Value value);
    
    /** parse a string to JSON
     *  @return JSON Object
     */
    cocos2d::Value valueFromString(std::string fileContent);
    
};

#endif /* defined(__FunnyFramework__JSONUtils__) */
