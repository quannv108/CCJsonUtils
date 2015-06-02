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

#ifndef __Funny__JSONLoad__
#define __Funny__JSONLoad__

#include "cocos2d.h"
#include "json/document.h"

class JSONLoad {
    
public:
    static int loadInt(const rapidjson::Value &value, const char *key);
    static double loadFloat(const rapidjson::Value &value, const char *key);
    static std::string loadString(const rapidjson::Value &value, const char *key);
    static bool loadBool(const rapidjson::Value &value, const char *key);
    
    static cocos2d::ValueVector loadArray_Int(const rapidjson::Value &value, const char *key);
    static cocos2d::ValueVector loadArray_Float(const rapidjson::Value &value, const char *key);
    static cocos2d::ValueVector loadArray_String(const rapidjson::Value &value, const char *key);
    static cocos2d::ValueVector loadArray_Bool(const rapidjson::Value &value, const char *key);
    static cocos2d::ValueVector loadArray(const rapidjson::Value &value, const char *key);
    static cocos2d::ValueVector toArray(const rapidjson::Value &value);
    
    static std::vector<int> loadArrayInt(const rapidjson::Value &value, const char *key);
    static std::vector<float> loadArrayFloat(const rapidjson::Value &value, const char *key);
    static std::vector<std::string> loadArrayString(const rapidjson::Value &value, const char *key);
    static std::vector<bool> loadArrayBool(const rapidjson::Value &value, const char *key);
    
    static cocos2d::ValueMap toDictionary(const rapidjson::Value &value);
    static cocos2d::ValueMap loadDictionary(const rapidjson::Value &value, const char *key);
};


#endif /* defined(__Funny__JSONLoad__) */
