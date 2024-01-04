#include "BHW/utils/json/JSON.hpp"

namespace BHW
{
    std::string ToString(Value& value, uint64_t indent)
    {
        if (value.Is<JSONArray  >()) return ToString<JSONArray >(value.Get<JSONArray >(), indent);
        if (value.Is<JSONObject >()) return ToString<JSONObject>(value.Get<JSONObject>(), indent);
        if (value.Is<std::string>()) return ToString<std::string>(value.Get<std::string>());
        if (value.Is<int64_t    >()) return ToString(value.Get<int64_t    >(), indent);
        if (value.Is<int32_t    >()) return ToString(value.Get<int32_t    >(), indent);
        if (value.Is<int16_t    >()) return ToString(value.Get<int16_t    >(), indent);
        if (value.Is<int8_t     >()) return ToString(value.Get<int8_t     >(), indent);
        if (value.Is<uint64_t   >()) return ToString(value.Get<uint64_t   >(), indent);
        if (value.Is<uint32_t   >()) return ToString(value.Get<uint32_t   >(), indent);
        if (value.Is<uint16_t   >()) return ToString(value.Get<uint16_t   >(), indent);
        if (value.Is<uint8_t    >()) return ToString(value.Get<uint8_t    >(), indent);
        if (value.Is<float      >()) return ToString(value.Get<float      >(), indent);
        if (value.Is<double     >()) return ToString(value.Get<double     >(), indent);
        if (value.Is<bool       >()) return ToString(value.Get<bool       >(), indent);

        BHW_ASSERT(false, "JSONObject::ToString", "Unknown type"); return "Unknown type";
    }

    template <> std::string ToString<std::string>(std::string& value, uint64_t indent) { return "\"" + value  + "\""          ; }
    template <> std::string ToString<int64_t    >(int64_t&     value, uint64_t indent) { return std::to_string(value) + "i64" ; }
    template <> std::string ToString<int32_t    >(int32_t&     value, uint64_t indent) { return std::to_string(value) + "i32" ; }
    template <> std::string ToString<int16_t    >(int16_t&     value, uint64_t indent) { return std::to_string(value) + "i16" ; }
    template <> std::string ToString<int8_t     >(int8_t&      value, uint64_t indent) { return std::to_string(value) + "i8"  ; }
    template <> std::string ToString<uint64_t   >(uint64_t&    value, uint64_t indent) { return std::to_string(value) + "ui64"; }
    template <> std::string ToString<uint32_t   >(uint32_t&    value, uint64_t indent) { return std::to_string(value) + "ui32"; }
    template <> std::string ToString<uint16_t   >(uint16_t&    value, uint64_t indent) { return std::to_string(value) + "ui16"; }
    template <> std::string ToString<uint8_t    >(uint8_t&     value, uint64_t indent) { return std::to_string(value) + "ui8" ; }
    template <> std::string ToString<float      >(float&       value, uint64_t indent) { return std::to_string(value) + "f"   ; }
    template <> std::string ToString<double     >(double&      value, uint64_t indent) { return std::to_string(value) + "d"   ; }
    template <> std::string ToString<bool       >(bool&        value, uint64_t indent) { return value ? "true" : "false"      ; }

    namespace
    {
        bool Parse(const std::string& json, JSONObject& result)
        {
            uint32_t index = 0;

            SkipToSignificant(json, index);

            BHW_ASSERT(json[index++] == '{', "BHW::Parse()", "Must start with {{");

            SkipToSignificant(json, index);

            for (; index < json.length();)
            {
                Value key;
                Value value;

                SkipToSignificant(json, index);
                
                //BHW::Console::WriteLine("\n---------------------\n" + json.substr(index, json.length() - index) + "\n---------------------\n");

                BHW_ASSERT(json[index] == '\"'           , "BHW::Parse()", "Key must start with \""        );

                BHW_ASSERT(ParseString(json, index, key) , "BHW::Parse()", "Failed to parse key"           );

                SkipToSignificant(json, ++index);

                BHW_ASSERT(json[index++] == ':'          , "BHW::Parse()", "Expected key value seperator :");

                SkipToSignificant(json, index);

                BHW_ASSERT(ParseValue(json, index, value), "BHW::Parse()", "Failed to parse value"         );
    
                SkipToSignificant(json, ++index);

                result.insert({ key.Get<std::string>(), value });

                // TODO: just tested some stuff, works for now this works somehow
                //       refactor this part later someday

                if (json[index] == '}') break;
                if (json[index] == ',') index++;
                if (json[index] == '}') break;

                SkipToSignificant(json, index);
                if (json[index] == '}') break;
            }

            return true;
        }

        inline void SkipToSignificant(const std::string& data, uint32_t& i)
        {
            //BHW_ASSERT(i < data.length(), "BHW::ParserSkip()", "Index out of range");

            while (data[i] == '\t' || data[i] == '\r' || data[i] == '\n' || data[i] == ' ') ++i;

            //if (data[i] == ' ' || data[i] == '\n') { ParserSkip(data, ++i); return; }
            //if (data[i] == '\\'                  ) { ++i; return; }

            if (data[i] != '/') { return; }

            if      (data[i] == '/') for (; i   < data.length() && data[i    ] != '\n'                 ; i++);
            else if (data[i] == '*') for (; i++ < data.length() && data[i - 1] != '*' && data[i] != '/'; i++);

            SkipToSignificant(data, i);
        }

        inline bool ParseValue(const std::string& data, uint32_t& i, Value& result)
        {
            return ParseString(data, i, result) || ParseNumber(data, i, result) || 
                   ParseBool  (data, i, result) || ParseArray (data, i, result) || 
                   ParseObject(data, i, result);
        }

        inline bool ParseNumber(const std::string& data, uint32_t& i, Value& result)
        {
            if (!(data[i] == '0' ||
                  data[i] == '1' ||
                  data[i] == '2' ||
                  data[i] == '3' ||
                  data[i] == '4' ||
                  data[i] == '5' ||
                  data[i] == '6' ||
                  data[i] == '7' ||
                  data[i] == '8' ||
                  data[i] == '9')) return false;

            int base = 10;
            bool isFloatingPointNumber = false;
            bool isExponential = false;

            if (data[i] == '0')
                if (data[i + 1] == 'b') base = 2;
                if (data[i + 1] == 'o') base = 8;
                if (data[i + 1] == 'x') base = 16;

            if (base != 10) i += 2;

            int pos = i ;

            if (data[i] == '+') i++;
            if (data[i] == '-') i++;

            for (; i < data.length(); i++)
            {
                if (data[i] == '.')
                {
                    BHW_ASSERT(!isFloatingPointNumber, "BHW::ParseNumber()", "Number can't have more than one .");

                    if (!isFloatingPointNumber) isFloatingPointNumber = true;
                }

                if (base == 10 && data[i] == 'e')
                {
                    BHW_ASSERT(!isExponential, "BHW::ParseNumber()", "Exponential number can't have more than one e");

                    if (!isExponential) isExponential = true;
                }

                SkipToSignificant(data, i);

                if (data[i] == ',')
                {
                    if (isFloatingPointNumber) { result.Set(new float (std::stof(data.substr(pos, i - pos), nullptr))); break; }
                    else                       { result.Set(new double(std::stod(data.substr(pos, i - pos), nullptr))); break; }
                }

                /*
                if (!(data[i] == '0' ||
                      data[i] == '1' ||
                      data[i] == '2' ||
                      data[i] == '3' ||
                      data[i] == '4' ||
                      data[i] == '5' ||
                      data[i] == '6' ||
                      data[i] == '7' ||
                      data[i] == '8' ||
                      data[i] == '9')) { result.Set(new int64_t(std::stoll(data.substr(pos, i - pos), nullptr, base))); break; }
                */

                if (data[i] == 'i' && data[i + 1] == '6' && data[i + 2] == '4') { result.Set(new int64_t(std::stoll(data.substr(pos, i - pos), nullptr, base))); i += 3; break; }
                if (data[i] == 'i' && data[i + 1] == '3' && data[i + 2] == '2') { result.Set(new int32_t(std::stoi (data.substr(pos, i - pos), nullptr, base))); i += 3; break; }
                if (data[i] == 'i' && data[i + 1] == '1' && data[i + 2] == '6') { result.Set(new int16_t(std::stoi (data.substr(pos, i - pos), nullptr, base))); i += 3; break; }
                if (data[i] == 'i' && data[i + 1] == '8')                       { result.Set(new int8_t (std::stoi (data.substr(pos, i - pos), nullptr, base))); i += 2; break; }

                if (data[i] == 'u' && data[i + 1] == 'i' && data[i + 2] == '6' && data[i + 3] == '4') { result.Set(new uint64_t(std::stoull(data.substr(pos, i - pos), nullptr, base))); i += 4; break; }
                if (data[i] == 'u' && data[i + 1] == 'i' && data[i + 2] == '3' && data[i + 3] == '2') { result.Set(new uint32_t(std::stoul (data.substr(pos, i - pos), nullptr, base))); i += 4; break; }
                if (data[i] == 'u' && data[i + 1] == 'i' && data[i + 2] == '1' && data[i + 3] == '6') { result.Set(new uint16_t(std::stoul (data.substr(pos, i - pos), nullptr, base))); i += 4; break; }
                if (data[i] == 'u' && data[i + 1] == 'i' && data[i + 2] == '8')                       { result.Set(new uint8_t (std::stoul (data.substr(pos, i - pos), nullptr, base))); i += 3; break; }

                if (data[i] == 'f') { result.Set(new float (std::stof(data.substr(pos, i - pos), nullptr))); i++; break; }
                if (data[i] == 'd') { result.Set(new double(std::stod(data.substr(pos, i - pos), nullptr))); i++; break; }
            }

            return true;
        }

        inline bool ParseBool(const std::string& data, uint32_t& i, Value& result)
        {
            if (data[i] == 't' && data[i + 1] == 'r' &&data[i + 2] == 'u' && data[i + 3] == 'e') 
            {
                result.Set(new bool(true));

                i += 4;

                return true;
            }
            
            if (data[i] == 'f' && data[i + 1] == 'a' &&data[i + 2] == 'l' && data[i + 3] == 's' && data[i + 4] == 'e') 
            {
                result.Set(new bool(false));

                i += 5;

                return true;
            }

            return false;
        }

        inline bool ParseString(const std::string& data, uint32_t& i, Value& result)
        {
            if (data[i] != '\"') return false;

            i++;

            int pos = i;
            
            for (; i < data.length() && data[i] != '\"' && data[i - 1] != '\\'; i++);

            std::string string = data.substr(pos, i - pos);
            result.Set(new std::string(string));

            BHW_ASSERT(data[i] == '\"', "BHW::ParseString()", "String must end with \"");

            return true;
        }

        inline bool ParseArray(const std::string& data, uint32_t& i, Value& result)
        {
            if (data[i] != '[') return false;
            
            i++;

            uint32_t index = 0;

            JSONArray* array = new JSONArray();

            result.Set(array);

            SkipToSignificant(data, i);

            Value inArrayResult;

            while (ParseValue(data, i, inArrayResult))
            {
                array->push_back(inArrayResult);

                inArrayResult = Value();

                SkipToSignificant(data, ++i);

                if (data[i++] == ']') { break; }
                if (data[i  ] == ',') { i++  ; }

                SkipToSignificant(data, i);
            }

            return true;
        }

        inline bool ParseObject(const std::string& data, uint32_t& i, Value& result)
        {
            if (data[i] != '{') return false;

            int count = 1;

            int pos = i;

            for (; i < data.length(); i++)
            {
                if      (data[i] == '{') count++;
                else if (data[i] == '}') count--;

                if (count == 0) break;
            }

            if (count != 0) return false;

            std::string substr = data.substr(pos, i - pos);
            
            JSONObject deserializedMap = DeserializeToMap(substr);

            JSONObject* map = new JSONObject();

            for (auto& [key, value] : deserializedMap)
            {
                map->insert({ key, value });
            }

            result.Set(map);

            return true;
        }
    }

    JSONObject DeserializeToMap(const std::string& string)
    {
        JSONObject result;

        Parse(string, result);

        return result;
    }
}