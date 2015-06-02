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

#include "JSONLoad.h"

int JSONLoad::loadInt(const rapidjson::Value &value, const char *key)
{
    const rapidjson::Value &v = value[key];
    if(v.IsNull()){
        CCLOGERROR("load %s error", key);
        return 0;
    }else if (v.IsInt()){
        return v.GetInt();
    }else if (v.IsString()){
        cocos2d::Value k = cocos2d::Value(v.GetString());
        return k.asInt();
    }else{
        return 0;
    }
}

double JSONLoad::loadFloat(const rapidjson::Value &value, const char *key)
{
    if(value[key].IsNull()){
        CCLOGERROR("load %s error", key);
        return 0.0f;
    }else{
        return value[key].GetDouble();
    }
}
std::string JSONLoad::loadString(const rapidjson::Value &value, const char *key)
{
    if(!value[key].IsString()){
        CCLOGERROR("load %s error", key);
        return std::string();
    }else{
        return value[key].GetString();
    }
}

bool JSONLoad::loadBool(const rapidjson::Value &value, const char *key)
{
    if(!value[key].IsBool()){
        CCLOGERROR("load %s error", key);
        return false;
    }else{
        return value[key].GetBool();
    }
}

cocos2d::ValueVector JSONLoad::loadArray_Int(const rapidjson::Value &value, const char *key)
{
    if(!value[key].IsArray()){
        CCLOGERROR("load %s error", key);
        return cocos2d::ValueVectorNull;
    }else{
    	cocos2d::ValueVector array = cocos2d::ValueVector();
        const rapidjson::Value &v = value[key];
        int count = v.Size();
        for (int i = 0; i < count; i ++){
            const rapidjson::Value &vv = v[i];
            if(vv.IsInt()){
                array.push_back(cocos2d::Value(vv.GetInt()));
            }else{
                CCLOGERROR("Load %s at %d error", key, i);
            }
        }
        return array;
    }
}

std::vector<int> JSONLoad::loadArrayInt(const rapidjson::Value &value, const char *key)
{
    if(!value[key].IsArray()){
        CCLOGERROR("load %s error", key);
        return std::vector<int>();
    }else{
        std::vector<int> array;
        const rapidjson::Value &v = value[key];
        int count = v.Size();
        for (int i = 0; i < count; i ++){
            const rapidjson::Value &vv = v[i];
            if(vv.IsInt()){
                array.push_back(vv.GetInt());
            }else{
                CCLOGERROR("Load %s at %d error", key, i);
            }
        }
        return array;
    }
}

cocos2d::ValueVector JSONLoad::loadArray_Float(const rapidjson::Value &value, const char *key)
{
    if(!value[key].IsArray()){
        CCLOGERROR("load %s error", key);
        return cocos2d::ValueVectorNull;
    }else{
    	cocos2d::ValueVector array = cocos2d::ValueVector();
        const rapidjson::Value &v = value[key];
        int count = v.Size();
        for (int i = 0; i < count; i ++){
            const rapidjson::Value &vv = v[i];
            if(vv.IsDouble()){
            	array.push_back(cocos2d::Value(vv.GetDouble()));
            }else if(vv.IsInt()){
                array.push_back(cocos2d::Value(cocos2d::Value(vv.GetInt()).asDouble()));
            }else{
                CCLOGERROR("Load %s at %d error", key, i);
            }
        }
        return array;
    }
}

std::vector<float> JSONLoad::loadArrayFloat(const rapidjson::Value &value, const char *key)
{
    if(!value[key].IsArray()){
        CCLOGERROR("load %s error", key);
        return std::vector<float>();
    }else{
        std::vector<float> array;
        const rapidjson::Value &v = value[key];
        int count = v.Size();
        for (int i = 0; i < count; i ++){
            const rapidjson::Value &vv = v[i];
            if(vv.IsDouble()){
            	array.push_back(vv.GetDouble());
            }else if(vv.IsInt()){
                array.push_back(vv.GetInt());
            }else{
                CCLOGERROR("Load %s at %d error", key, i);
            }
        }
        return array;
    }
}

cocos2d::ValueVector JSONLoad::loadArray_String(const rapidjson::Value &value, const char *key)
{
    if(!value[key].IsArray()){
        CCLOGERROR("load %s error", key);
        return cocos2d::ValueVectorNull;
    }else{
    	cocos2d::ValueVector array = cocos2d::ValueVector();
        const rapidjson::Value &v = value[key];
        int count = v.Size();
        for (int i = 0; i < count; i ++){
            const rapidjson::Value &vv = v[i];
            if(vv.IsString()){
            	array.push_back(cocos2d::Value(vv.GetString()));
            }else{
                CCLOGERROR("Load %s at %d error", key, i);
            }
        }
        return array;
    }
}

std::vector<std::string> JSONLoad::loadArrayString(const rapidjson::Value &value, const char *key)
{
    if(!value[key].IsArray()){
        CCLOGERROR("load %s error", key);
        return std::vector<std::string>();
    }else{
        std::vector<std::string> array;
        const rapidjson::Value &v = value[key];
        int count = v.Size();
        for (int i = 0; i < count; i ++){
            const rapidjson::Value &vv = v[i];
            if(vv.IsString()){
            	array.push_back(vv.GetString());
            }else{
                CCLOGERROR("Load %s at %d error", key, i);
            }
        }
        return array;
    }
}

cocos2d::ValueVector JSONLoad::loadArray_Bool(const rapidjson::Value &value, const char *key)
{
    if(!value[key].IsArray()){
        CCLOGERROR("load %s error", key);
        return cocos2d::ValueVectorNull;
    }else{
    	cocos2d::ValueVector array = cocos2d::ValueVector();
        const rapidjson::Value &v = value[key];
        int count = v.Size();
        for (int i = 0; i < count; i ++){
            const rapidjson::Value &vv = v[i];
            if(vv.IsBool()){
            	array.push_back(cocos2d::Value(vv.GetBool()));
            }else{
                CCLOGERROR("Load %s at %d error", key, i);
            }
        }
        return array;
    }
}

std::vector<bool> JSONLoad::loadArrayBool(const rapidjson::Value &value, const char *key)
{
    if(!value[key].IsArray()){
        CCLOGERROR("load %s error", key);
        return std::vector<bool>();
    }else{
        std::vector<bool> array;
        const rapidjson::Value &v = value[key];
        int count = v.Size();
        for (int i = 0; i < count; i ++){
            const rapidjson::Value &vv = v[i];
            if(vv.IsBool()){
            	array.push_back(vv.GetBool());
            }else{
                CCLOGERROR("Load %s at %d error", key, i);
            }
        }
        return array;
    }
}

cocos2d::ValueVector JSONLoad::loadArray(const rapidjson::Value &value, const char *key)
{
    if(!value[key].IsArray()){
        CCLOGERROR("load %s error", key);
        return cocos2d::ValueVectorNull;
    }
    return JSONLoad::toArray(value[key]);
}

cocos2d::ValueVector JSONLoad::toArray(const rapidjson::Value &value)
{
    if(!value.IsArray()){
        CCLOGERROR("get array failed");
        return cocos2d::ValueVectorNull;
    }
    cocos2d::ValueVector array = cocos2d::ValueVector();
    const rapidjson::Value &v = value;
    int count = v.Size();
    for (int i = 0; i < count; i ++){
        const rapidjson::Value &vv = v[i];
        rapidjson::Type type = vv.GetType();
        switch (type) {
            case rapidjson::kNullType:
                break;
            case rapidjson::kArrayType:
                array.push_back(cocos2d::Value(JSONLoad::toArray(vv)));
                break;
            case rapidjson::kFalseType:
            case rapidjson::kTrueType:
            	array.push_back(cocos2d::Value(vv.GetBool()));
                break;
            case rapidjson::kStringType:
            	array.push_back(cocos2d::Value(vv.GetString()));
                break;
            case rapidjson::kNumberType:
                if(vv.IsInt()){
                	array.push_back(cocos2d::Value(vv.GetInt()));
                }else{
                	array.push_back(cocos2d::Value(vv.GetDouble()));
                }
                break;
            case rapidjson::kObjectType:
            	array.push_back(cocos2d::Value(JSONLoad::toDictionary(vv)));
                break;
            default:
                break;
        }
    }
    return array;
}

cocos2d::ValueMap JSONLoad::loadDictionary(const rapidjson::Value &value, const char *key)
{
    if(value.IsNull()){
        CCLOGERROR("load dictionary params null");
        return cocos2d::ValueMapNull;
    }
    
    if(value[key].IsNull()){
        CCLOGERROR("load %s failed", key);
        return cocos2d::ValueMapNull;
    }
    
    return JSONLoad::toDictionary(value[key]);
}

cocos2d::ValueMap JSONLoad::toDictionary(const rapidjson::Value &value)
{
    if(value.IsNull()){
        CCLOGERROR("load dictionary params null");
        return cocos2d::ValueMapNull;
    }
    
    cocos2d::ValueMap dic = cocos2d::ValueMap();
    //get all key
    for (rapidjson::Value::ConstMemberIterator itr = value.MemberonBegin(); itr != value.MemberonEnd(); ++itr){
        //        printf("Type of member %s is %s\n", itr->name.GetString(), kTypeNames[itr->value.GetType()]);
        std::string aKey = itr->name.GetString();
        //get type
        rapidjson::Type type = itr->value.GetType();
        /*
         kNullType = 0,		//!< null
         kFalseType = 1,		//!< false
         kTrueType = 2,		//!< true
         kObjectType = 3,	//!< object
         kArrayType = 4,		//!< array
         kStringType = 5,	//!< string
         kNumberType = 6,	//!< number
         */
        switch (type) {
            case rapidjson::kNullType:
                break;
            case rapidjson::kFalseType:
            case rapidjson::kTrueType:{
                dic[aKey] = cocos2d::Value(JSONLoad::loadBool(value, aKey.c_str()));
                break;
            }
            case rapidjson::kNumberType:{
                if(itr->value.IsInt()){
                	dic[aKey] = cocos2d::Value(JSONLoad::loadInt(value, aKey.c_str()));
                }else{
                	dic[aKey] = cocos2d::Value(JSONLoad::loadFloat(value, aKey.c_str()));
                }
                break;
            }
            case rapidjson::kStringType:{
                dic[aKey] = cocos2d::Value(JSONLoad::loadString(value, aKey.c_str()));
                break;
            }
            case rapidjson::kArrayType:{
            	dic[aKey] = cocos2d::Value(JSONLoad::loadArray(value, aKey.c_str()));
                break;
            }
            case rapidjson::kObjectType:{
            	dic[aKey] = cocos2d::Value(JSONLoad::loadDictionary(value, aKey.c_str()));
                break;
            }
            default:
                break;
        }
    }
    return dic;
}
