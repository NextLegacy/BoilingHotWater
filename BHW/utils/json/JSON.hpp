#pragma once

#include <string>
#include <map>
#include <tuple>
#include <vector>

#include "BHW/utils/reflection/Reflection.hpp"
#include "BHW/utils/Debug.hpp"

namespace BHW
{
    typedef std::vector<Value> JSONArray;
    typedef std::map<std::string, Value> JSONObject;

    template <typename T>
    struct JSONKeyValue
    {
        std::string key;
        T value;

        JSONKeyValue(std::string key, T value) : key(key), value(value) { }
    };

    std::string ToString(Value& value, uint64_t indent = 0);

    template <typename T>
    inline std::string ToString(T& object, uint64_t indent = 0)
    {
        if (!IsRegistered<T>()) return "null";

        return Serialize<T>(object, indent);
    }

    template <> std::string ToString<std::string>(std::string& value, uint64_t indent);
    template <> std::string ToString<int64_t    >(int64_t&     value, uint64_t indent);
    template <> std::string ToString<int32_t    >(int32_t&     value, uint64_t indent);
    template <> std::string ToString<int16_t    >(int16_t&     value, uint64_t indent);
    template <> std::string ToString<int8_t     >(int8_t&      value, uint64_t indent);
    template <> std::string ToString<uint64_t   >(uint64_t&    value, uint64_t indent);
    template <> std::string ToString<uint32_t   >(uint32_t&    value, uint64_t indent);
    template <> std::string ToString<uint16_t   >(uint16_t&    value, uint64_t indent);
    template <> std::string ToString<uint8_t    >(uint8_t&     value, uint64_t indent);
    template <> std::string ToString<float      >(float&       value, uint64_t indent);
    template <> std::string ToString<double     >(double&      value, uint64_t indent);
    template <> std::string ToString<bool       >(bool&        value, uint64_t indent);

    /*
    template <typename T>
    inline std::string ToString(const Value& value)
    {
        if (value.Is<T>())
            return ToString(value.Get<T>());
        else
            return "null";
    }*/

    template <typename T> 
    inline std::string ToString(std::vector<T>& vector, uint64_t indent = 0)
    {
        std::string result = "[\n";

        std::string indentString = "";

        for (uint64_t i = 0; i < indent; i++) indentString += "    ";

        for (T& value : vector)
        {
            std::string valueString = ToString(value, indent + 1);

            result += "    " + indentString + valueString + ",\n";
        }

        return result + indentString + "]";
    }


    template <typename T> 
    inline std::string ToString(std::map<std::string, T>& map, uint64_t indent = 0)
    {
        std::string result = "{\n";

        std::string indentString = "";

        for (uint64_t i = 0; i < indent; i++) indentString += "    ";

        for (auto& [key, value] : map)
        {
            std::string valueString = ToString(value, indent + 1);

            result += indentString + "    " + "\"" + key + "\": "+ valueString + ",\n";
        }

        return result + indentString + "}}";
    }

    namespace
    {
        bool Parse(const std::string& json, JSONObject& result);

        void SkipToSignificant (const std::string& json, uint32_t& index);

        bool ParseValue (const std::string& json, uint32_t& index, Value& result);
        bool ParseString(const std::string& json, uint32_t& index, Value& result);
        bool ParseNumber(const std::string& json, uint32_t& index, Value& result);
        bool ParseBool  (const std::string& json, uint32_t& index, Value& result);
        bool ParseArray (const std::string& json, uint32_t& index, Value& result);
        bool ParseObject(const std::string& json, uint32_t& index, Value& result);
    }

    template <typename ...T>
    inline std::string SerializeKeyValuePairs(JSONKeyValue<T>... keyValue)
    {
        std::string result = "{\n";

        std::apply([&](auto&&... keyValue)
        {
            ((result += "    \"" + keyValue.key + "\": " + ToString(keyValue.value) + ",\n"), ...);
        }, std::tuple(keyValue...));        

        return result + "}";
    }

    JSONObject DeserializeToMap(const std::string& string);

    template <typename T>
    inline std::string Serialize(T& object, uint64_t indent = 0)
    {
        BHW_ASSERT(BHW::IsRegistered<T>(), "Serialize()", "Type is not registered!");

        std::string result = "{\n";

        std::string indentString = "";

        for (uint64_t i = 0; i < indent; i++) indentString += "    ";
        
        std::apply([&](auto&&... members)
        {
            ((result += indentString + "    \"" + std::string(members.Name.begin(), members.Name.end()) + "\": " + ToString(members(object), 1) + ",\n"), ...);
        }, GetMembersOfType<T>());      
        return result + indentString + "}";
    }

    template <typename T>
    inline T Deserialize(std::string string, T* result = nullptr)
    {
        BHW_ASSERT(BHW::IsRegistered<T>(), "Deserialize()", "Type is not registered!");

        JSONObject object = DeserializeToMap(string);

        if (result == nullptr) result = new T();

        std::apply([&](auto&&... members)
        {
            (..., [&]()
            {
                if (object.find(std::string(members.Name.begin(), members.Name.end())) == object.end()) return;

                Value& value = object[std::string(members.Name.begin(), members.Name.end())];
    
                members(*result) = value.Is<JSONObject>() ? Deserialize<typename std::remove_reference<decltype(members(*result))>::type>(ToString(value.Get<JSONObject>())) : 
                                                            value.Get  <typename std::remove_reference<decltype(members(*result))>::type>();
            }());
        }, GetMembersOfType<T>());

        return *result;
    }
}