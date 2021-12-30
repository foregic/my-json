/*
 * @Author       : foregic
 * @Date         : 2021-12-22 11:09:35
 * @LastEditors  : foregic
 * @LastEditTime : 2021-12-30 20:11:25
 * @FilePath     : /json/src/Json_parse.cpp
 * @Description  :
 */

#include "Json_parse.h"

Json::Json_parse::Json_obj Json::Json_parse::parse_obj() {
    if (cur == end) {
        throw std::invalid_argument("invalid string");
    }
    if (skip_whitespace()) {
        switch (*cur) {
        case 'n':
            return parse_null();
        case 't':
        case 'f':
            return parse_bool();
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '-':
            return parse_number();
        case '\"':
            return parse_string();
        case '[':
            return parse_list();
        case '{':
            return parse_dict();
        default:
            throw std::invalid_argument("this string is not json");
        }
    }
    throw std::invalid_argument("as");
}

Json::Json_parse::Json_obj Json::Json_parse::parse_dict() {
    if (*cur == '{') {
        ++cur;
    }

    if (!skip_whitespace()) {
        throw std::invalid_argument("not a list");
    } else if (*cur == '}') {
        ++cur;
        return new Json_dict();
    }
    Json_obj Dict = new Json_dict();
    while (*cur != '}') {
        std::string key;

        skip_whitespace();
        if (*cur == '\"') {
            ++cur;
        } else {
            throw std::invalid_argument("not a Dict");
        }

        while (*cur != '\"') {
            key.push_back(*cur);
            cur++;
        }
        if (*cur == '\"') {
            cur++;
        } else {
            throw std::invalid_argument("not a Dict");
        }
        skip_whitespace();
        if (*cur == ':') {
            cur++;
        } else {
            throw std::invalid_argument("not a Dict");
        }
        auto value = parse_obj();
        Dict->insert(key, value);

        skip_whitespace();

        if (*cur == ',') {
            ++cur;

        } else {
            break;
        }
    }
    if (skip_whitespace() && *cur == '}') {
        cur++;
    } else {
        throw std::invalid_argument("not a Dict");
    }
    return Dict;
}

Json::Json_parse::Json_obj Json::Json_parse::parse_list() {
    if (*cur == '[') {
        ++cur;
    } else {
        throw std::invalid_argument("not a list");
    }

    if (!skip_whitespace()) {
        throw std::invalid_argument("not a list");
    } else if (*cur == ']') {
        ++cur;
        return new Json_list();
    }

    Json_obj result = new Json_list();
    while (true) {
        if (!skip_whitespace()) {
            throw std::invalid_argument("not a list");
        }

        auto val = parse_obj();

        if (!skip_whitespace()) {
            throw std::invalid_argument("not a list");
        }

        result->append(val);
        // std::cout << *result << std::endl;

        if (*cur == ',') {
            ++cur;
        } else {
            break;
        }
        if (!skip_whitespace()) {
            throw std::invalid_argument("not a list");
        }
    }

    if (skip_whitespace() && *cur == ']') {
        ++cur;
    } else {
        throw std::invalid_argument("not a list");
    }
    return result;

    // if (*cur == '[') {
    //     cur++;
    // }
    // Json_obj list = new Json_value();
    // while (*cur != ']') {
    //     skip_whitespace();
    //     auto obj = parse_obj();

    //     list->append(obj);

    //     skip_whitespace();

    //     if (*cur == ',') {
    //         ++cur;

    //     } else {
    //         break;
    //     }
    // }
    // if (skip_whitespace() && *cur == ']') {
    //     cur++;
    // } else {
    //     throw std::invalid_argument("not a list");
    // }
    // return list;
}

Json::Json_parse::Json_obj Json::Json_parse::parse_string() {
    if (*cur == '\"') {
        ++cur;
    }
    Json_obj str = new Json_value(Json_value_type::String);
    while (*cur != '\"') {
        str->append(*cur);
        ++cur;
    }
    if (*cur == '\"' && cur != end) {
        ++cur;
    } else {
        throw std::invalid_argument("not string");
    }
    return str;
}

Json::Json_parse::Json_obj Json::Json_parse::parse_bool() {
    static std::string true_string = "true";
    static std::string false_string = "false";
    switch (*cur) {
    case 't': {

        for (const auto &ch : true_string) {
            if (*cur != ch) {
                throw std::invalid_argument("this is not a boolean : " + std::to_string(*cur));
            }
            ++cur;
        }
        Json_obj tmp = new Json_value(Json_value_type::Bool, true_string);
        return tmp;
    }

    case 'f': {

        for (const auto &ch : false_string) {
            if (*cur != ch) {
                throw std::invalid_argument("this is not a boolean : " + std::to_string(*cur));
            }
            ++cur;
        }
        Json_obj tmp = new Json_value(Json_value_type::Bool, false_string);
        return tmp;
    }
    default:
        throw std::invalid_argument("this is not a boolean : " + std::to_string(*cur));
    }
}

Json::Json_parse::Json_obj Json::Json_parse::parse_null() {
    static std::string null_string = "null";
    for (const auto &ch : null_string) {
        if (*cur != ch) {
            throw std::invalid_argument("this is not a null : " + std::to_string(*cur));
        }
        ++cur;
    }
    Json_obj tmp = new Json_value(Json_value_type::Null, null_string);
    return tmp;
}

Json::Json_parse::Json_obj Json::Json_parse::parse_number() {

    const auto first = cur;
    if (*cur == '-') {
        ++cur;
    }

    if (cur != end && *cur == '0' &&
        cur + 1 != end && std::isdigit(*(cur + 1))) {
        throw std::invalid_argument("invalid number");
    }

    if (!skip_digit()) {
        throw std::invalid_argument("invalid number");
    }

    if (*cur == '.') {
        ++cur;
        if (!skip_digit()) {
            throw std::invalid_argument("invalid number");
        }
    }

    if (*cur == 'e' || *cur == 'E') {
        if (++cur == end) {
            throw std::invalid_argument("invalid number");
        }
        if (*cur == '+' || *cur == '-') {
            ++cur;
        }
        if (!skip_digit()) {
            throw std::invalid_argument("invalid number");
        }
    }
    Json_obj tmp = new Json_value(Json_value_type::Number, first, cur);
    return tmp;
}
