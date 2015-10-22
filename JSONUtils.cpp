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

#include "JSONUtils.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include <iomanip>

#include "JSONLoad.h"

USING_NS_CC;

#pragma mark - single ton

static JSONUtils* _sharedManager = NULL;

JSONUtils* JSONUtils::getInstance()
{
    if(_sharedManager == NULL){
        _sharedManager = new JSONUtils();
    }
    return _sharedManager;
}

void JSONUtils::destroyInstance()
{
    if(_sharedManager != NULL){
        delete _sharedManager;
        _sharedManager = NULL;
    }
}

#pragma mark - public

std::string JSONUtils::stringFromJSON(const rapidjson::Value &value)
{
    if(value.IsNull()){
        return std::string();
    }
    // Convert JSON document to string
    rapidjson::StringBuffer strbuf;
	rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
	value.Accept(writer);
    
    std::string str = strbuf.GetString();
    return str;
}

bool JSONUtils::parseJSONFromString(rapidjson::Document &document, const std::string str)
{
    return !(document.Parse<rapidjson::kParseDefaultFlags> (str.c_str()).HasParseError());
}

#pragma mark - common parse array

std::vector<int> JSONUtils::vectorIntFromJSON(const rapidjson::Value &value)
{
    std::vector<int> vec;
    if(!value.IsArray()){
        return vec;
    }
    
    int size = value.Size();
    for(int i = 0; i < size; i++){
        const rapidjson::Value &v = value[i];
        if(v.IsInt()){
            vec.push_back(v.GetInt());
        }else{
            //format error
            std::vector<int> k;
            return k;
        }
    }
    return vec;
}

std::vector<double> JSONUtils::vectorDoubleFromJSON(const rapidjson::Value &value)
{
    std::vector<double> vec;
    if(!value.IsArray()){
        return vec;
    }
    
    int size = value.Size();
    for(int i = 0; i < size; i++){
        const rapidjson::Value &v = value[i];
        if(v.IsDouble()){
            vec.push_back(v.GetDouble());
        }else{
            //format error
            std::vector<double> k;
            return k;
        }
    }
    return vec;
}

std::vector<bool> JSONUtils::vectorBoolFromJSON(const rapidjson::Value &value)
{
    std::vector<bool> vec;
    if(!value.IsArray()){
        return vec;
    }
    
    int size = value.Size();
    for(int i = 0; i < size; i++){
        const rapidjson::Value &v = value[i];
        if(v.IsBool()){
            vec.push_back(v.GetBool());
        }else{
            //format error
            std::vector<bool> k;
            return k;
        }
    }
    return vec;
}

#pragma mark - fast parse - deprecated

std::string JSONUtils::JSONStringFromParamsDictionary(cocos2d::__Dictionary *dictionary)
{
    if (dictionary == NULL) {
        return std::string();
    }
    
    //get allkey in dictionary
    cocos2d::__Array *allKey = dictionary->allKeys();
    cocos2d::Ref *anObject;
    std::string returnValue = std::string("{");
    
    CCARRAY_FOREACH(allKey, anObject){
        //get string for key
        __String *key = (__String *)anObject;
        Ref *aValue = dictionary->objectForKey(key->getCString());
        if(dynamic_cast<__Float *>(aValue)){
            //support float cast
            __Float *aValueString = (__Float *)aValue;
            returnValue.append("\"");
            returnValue.append(key->getCString());
            returnValue.append("\"");
            returnValue.append(":");
            returnValue.append(__String::createWithFormat("%f",aValueString->getValue())->getCString());
            returnValue.append(",");
        }else if (dynamic_cast<__String*>(aValue)){
            //support string cast
            __String *aValueString = (__String *)aValue;
            returnValue.append("\"");
            returnValue.append(key->getCString());
            returnValue.append("\"");
            returnValue.append(":");
            returnValue.append("\"");
            returnValue.append(aValueString->getCString());
            returnValue.append("\"");
            returnValue.append(",");
        }else if (dynamic_cast<__Integer*>(aValue)){
            //support integer cast
            __Integer *aValueString = (__Integer *)aValue;
            returnValue.append("\"");
            returnValue.append(key->getCString());
            returnValue.append("\"");
            returnValue.append(":");
            returnValue.append(__String::createWithFormat("%d",aValueString->getValue())->getCString());
            returnValue.append(",");
        }else if (dynamic_cast<__Double*>(aValue)){
            //support double cast
            __Double *aValueString = (__Double *)aValue;
            returnValue.append("\"");
            returnValue.append(key->getCString());
            returnValue.append("\"");
            returnValue.append(":");
            returnValue.append(__String::createWithFormat("%f",aValueString->getValue())->getCString());
            returnValue.append(",");
        }else if (dynamic_cast<__Bool*>(aValue)){
            //support double cast
            __Bool *aValueString = (__Bool *)aValue;
            returnValue.append("\"");
            returnValue.append(key->getCString());
            returnValue.append("\"");
            returnValue.append(":");
            if(aValueString->getValue()){
                returnValue.append("true");
            }else{
                returnValue.append("false");
            }
            returnValue.append(",");
        }else if(dynamic_cast<__Array*>(aValue)){
            //support array cast
            __Array *aValueString = (__Array *)aValue;
            returnValue.append("\"");
            returnValue.append(key->getCString());
            returnValue.append("\"");
            returnValue.append(":");
            returnValue.append(JSONStringFromParamsArray(aValueString));
            returnValue.append(",");
        }else if (dynamic_cast<__Dictionary *>(aValue)){
            __Dictionary *aValueString = (__Dictionary *)aValue;
            returnValue.append("\"");
            returnValue.append(key->getCString());
            returnValue.append("\"");
            returnValue.append(":");
            returnValue.append(JSONStringFromParamsDictionary(aValueString));
            returnValue.append(",");
        }else{
            CCLOGERROR("don't know format");
        }
    }
    
    if(returnValue.length() > 1){
        std::string st = returnValue.substr(0, returnValue.size()-1);
        st.append("}");
        
        return st;
    }else{
        return std::string();
    }
}


std::string JSONUtils::JSONStringFromParamsArray(cocos2d::__Array *array)
{
    if(array == NULL){
        return std::string();
    }
    
    cocos2d::Ref *anObject;
    std::string returnString = std::string("[");
    CCARRAY_FOREACH(array, anObject){
        if(dynamic_cast<__String*>(anObject)){
            returnString.append("\"");
            returnString.append(std::string(((__String *)anObject)->getCString()));
            returnString.append("\"");
            returnString.append(",");
        }else if (dynamic_cast<__Float*>(anObject)){
            //support float cast
            __Float *aValueString = (__Float *)anObject;
            returnString.append(__String::createWithFormat("%f",aValueString->getValue())->getCString());
            returnString.append(",");
        }else if (dynamic_cast<__Integer*>(anObject)){
            //support integer cast
            __Integer *aValueString = (__Integer *)anObject;
            returnString.append(__String::createWithFormat("%d",aValueString->getValue())->getCString());
            returnString.append(",");
        }else if (dynamic_cast<__Double*>(anObject)){
            //support double cast
            __Double *aValueString = (__Double *)anObject;
            returnString.append(__String::createWithFormat("%f",aValueString->getValue())->getCString());
            returnString.append(",");
        }else if (dynamic_cast<__Bool*>(anObject) ){
            //support double cast
            __Bool *aValueString = (__Bool *)anObject;
            if(aValueString->getValue()){
                returnString.append("true");
            }else{
                returnString.append("false");
            }
            returnString.append(",");
        }else if (dynamic_cast<__Dictionary*>(anObject)){
            __Dictionary *aValueString = (__Dictionary *)anObject;
            returnString.append(JSONStringFromParamsDictionary(aValueString));
            returnString.append(",");
        }else{
            CCLOG("dont know type");
        }
    }
    if(returnString.length() > 1){
        std::string st = returnString.substr(0, returnString.size()-1);
        st.append("]");
        return st;
    }else{
        return std::string();
    }
}

#pragma mark - fast parse

std::string convert_string(const std::string& s) {
    std::stringstream ss;
    for (size_t i = 0; i < s.length(); ++i) {
        if (unsigned(s[i]) < '\x20' || s[i] == '\\' || s[i] == '"') {
            ss << "\\u" << std::setfill('0') << std::setw(4) << std::hex << unsigned(s[i]);
        } else {
            ss << s[i];
        }
    }
    return ss.str();
}

std::string JSONUtils::JSONStringFromDictionary(const cocos2d::ValueMap& dictionary)
{
	if (dictionary.empty()) {
		return std::string("{}");
	}

	std::string returnValue = std::string("{");
	for (auto it = dictionary.begin(); it != dictionary.end(); ++it) {
		std::string key = it->first;
        const cocos2d::Value& aValue = it->second;
		if (aValue.getType() == cocos2d::Value::Type::STRING) {
			//support string cast
			returnValue.append("\"");
			returnValue.append(key.c_str());
			returnValue.append("\"");
			returnValue.append(":");
			returnValue.append("\"");
            std::string originalString = aValue.asString();
            originalString = convert_string(originalString);
			returnValue.append(originalString);
			returnValue.append("\"");
			returnValue.append(",");
		} else if (aValue.getType() == cocos2d::Value::Type::FLOAT) {
			//support float cast
			std::stringstream ret;
			ret << std::setprecision( 7 )<< aValue.asFloat();
			returnValue.append("\"");
			returnValue.append(key.c_str());
			returnValue.append("\"");
			returnValue.append(":");
			returnValue.append(ret.str().c_str());
			returnValue.append(",");
		} else if (aValue.getType() == cocos2d::Value::Type::DOUBLE) {
			//support double cast
			std::stringstream ret;
			ret << std::setprecision( 16 )<< aValue.asDouble();
			returnValue.append("\"");
			returnValue.append(key.c_str());
			returnValue.append("\"");
			returnValue.append(":");
			returnValue.append(ret.str().c_str());
			returnValue.append(",");
		} else if (aValue.getType() == cocos2d::Value::Type::INTEGER) {
			//support integer cast
			returnValue.append("\"");
			returnValue.append(key.c_str());
			returnValue.append("\"");
			returnValue.append(":");
			returnValue.append(aValue.asString().c_str());
			returnValue.append(",");
		} else if (aValue.getType() == cocos2d::Value::Type::BOOLEAN) {
			//support bool cast
			returnValue.append("\"");
			returnValue.append(key.c_str());
			returnValue.append("\"");
			returnValue.append(":");
			if (aValue.asBool()) {
				returnValue.append("true");
			} else {
				returnValue.append("false");
			}
			returnValue.append(",");
		} else if (aValue.getType() == cocos2d::Value::Type::VECTOR) {
			//support array cast
            returnValue.append("\"");
			returnValue.append(key.c_str());
            returnValue.append("\"");
			returnValue.append(":");
			returnValue.append(JSONUtils::JSONStringFromArray(aValue.asValueVector()));
			returnValue.append(",");
		} else if (aValue.getType() == cocos2d::Value::Type::MAP) {
			//support dictionary cast
            returnValue.append("\"");
			returnValue.append(key.c_str());
            returnValue.append("\"");
			returnValue.append(":");
			returnValue.append(JSONUtils::JSONStringFromDictionary(aValue.asValueMap()));
			returnValue.append(",");
		} else {
			CCLOGERROR("JSONUtils: unknown format type.");
		}
	}
	if (returnValue.length() > 1) {
		std::string st = returnValue.substr(0, returnValue.size() - 1);
		st.append("}");
		return st;
	} else {
		return std::string();
	}
}

std::string JSONUtils::JSONStringFromArray(const cocos2d::ValueVector& array)
{
	if (array.empty()) {
		return std::string("[]");
	}
	std::string returnString = std::string("[");
	for (auto it = array.begin(); it != array.end(); ++it) {
		const cocos2d::Value& aValue = *it;
		if (aValue.getType() == cocos2d::Value::Type::STRING) {
			//support string cast
			returnString.append("\"");
            std::string original = aValue.asString();
            original = convert_string(original);
			returnString.append(original);
			returnString.append("\"");
			returnString.append(",");
		} else if (aValue.getType() == cocos2d::Value::Type::FLOAT) {
			//support float cast
			std::stringstream ret;
			ret << std::setprecision( 7 )<< aValue.asFloat();
			returnString.append(ret.str().c_str());
			returnString.append(",");
		} else if (aValue.getType() == cocos2d::Value::Type::DOUBLE) {
			//support double cast
			std::stringstream ret;
			ret << std::setprecision( 16 )<< aValue.asDouble();
			returnString.append(ret.str().c_str());
			returnString.append(",");
		} else if (aValue.getType() == cocos2d::Value::Type::INTEGER) {
			//support integer cast
			returnString.append(aValue.asString().c_str());
			returnString.append(",");
		} else if (aValue.getType() == cocos2d::Value::Type::BOOLEAN) {
			//support bool cast
			if (aValue.asBool()) {
				returnString.append("true");
			} else {
				returnString.append("false");
			}
			returnString.append(",");
		} else if (aValue.getType() == cocos2d::Value::Type::MAP) {
			//support dictionary cast
			returnString.append(JSONUtils::JSONStringFromDictionary(aValue.asValueMap()));
			returnString.append(",");
		} else if (aValue.getType() == cocos2d::Value::Type::VECTOR) {
			//support array cast
			returnString.append(",");
			returnString.append(JSONUtils::JSONStringFromArray(aValue.asValueVector()));
		} else {
			CCLOGERROR("JSONUtils: unknown format type.");
		}
	}
	if (returnString.length() > 1) {
		std::string st = returnString.substr(0, returnString.size() - 1);
		st.append("]");
		return st;
	} else {
		return std::string();
	}
}

#pragma mark - fast convert to json

std::string JSONUtils::JSONStringFromValue(const cocos2d::Value& value)
{
	if (value.isNull()) {
		return std::string();
	}
	std::string returnString = std::string("");
	if (value.getType() == cocos2d::Value::Type::MAP) {
		returnString.append(JSONUtils::JSONStringFromDictionary(value.asValueMap()));
	} else if (value.getType() == cocos2d::Value::Type::VECTOR) {
		returnString.append(JSONUtils::JSONStringFromArray(value.asValueVector()));
	} else {
		CCLOGERROR("JSONUtils: invalid json object.");
	}
	return returnString;
}

cocos2d::Value JSONUtils::valueFromString(const std::string& fileContent)
{
	Value returnValue = Value();
	rapidjson::Document document;
    
    if(!parseJSONFromString(document, fileContent)){
		CCLOG("=======Cannot parse json string: %s", fileContent.c_str());
		return returnValue;
	}
    
	if (!document.IsNull()) {
		if (document.GetType() == rapidjson::kObjectType) {
			const rapidjson::Value &aDict = document;
			ValueMap objectValue =  JSONLoad::toDictionary(aDict);
			returnValue = objectValue;
		} else if (document.GetType() == rapidjson::kArrayType) {
			const rapidjson::Value &aDict = document;
			ValueVector arrayValue = JSONLoad::toArray(aDict);
			returnValue = arrayValue;
		} else {
			CCLOG("=======Unknown json type: %d", (int)(document.GetType()));
		}
	}
	return returnValue;
}