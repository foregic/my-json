

#include "Json_value.h"
#include <iostream>

Json::Json_value::Json_value(const Json::Json_value &other) {
    type = other.type;
    data = other.data;
}

Json::Json_value::Json_value(Json::Json_value &&other) noexcept {
    type = std::forward<Json_value_type>(other.type);
    data = std::forward<std::string>(other.data);
}

Json::Json_value &Json::Json_value::operator=(const Json::Json_value &other) {
    type = other.type;
    data = other.data;
}

Json::Json_value &Json::Json_value::operator=(Json::Json_value &&other) noexcept {
    type = std::forward<Json_value_type>(other.type);
    data = std::forward<std::string>(other.data);
}

std::string Json::Json_value::to_string() {
    switch (getType()) {
    case Json_value_type::Number:
    case Json_value_type::Bool:
    case Json_value_type::Null:
        return data;
    case Json_value_type::String:
        return '\"' + data + '\"';
    case Json_value_type::Dict:
        std::cout << "&this dict to_string" << std::endl;
        return (&(*this))->to_string();
        // return (*dynamic_cast<Json_dict *>(this)).to_string();

    case Json_value_type::List:
        std::cout << "&this list to_string" << std::endl;
        return this->to_string();
        // return (*dynamic_cast<Json_list *>(this)).to_string();
    default:
        std::cout << data << std::endl;
        throw std::runtime_error("invalid type to_string()");
    }
}

Json::Json_value *Json::Json_value::operator[](const std::string &str) {
    if (getType() == Json::Json_value_type::Dict) {
        return operator[](str);
    } else {
        throw std::runtime_error("wrong type");
    }
}

Json::Json_value *Json::Json_value::operator[](const size_t &index) {
    if (getType() == Json::Json_value_type::List) {
        return operator[](index);
    } else {
        throw std::runtime_error("wrong type");
    }
}

bool Json::Json_value::isNull() const noexcept {
    return getType() == Json_value_type::Null;
}

bool Json::Json_value::isNumber() const noexcept {
    return getType() == Json_value_type::Number;
}

bool Json::Json_value::isDict() const noexcept {
    return getType() == Json_value_type::Dict;
}

bool Json::Json_value::isString() const noexcept {
    return getType() == Json_value_type::String;
}

bool Json::Json_value::isList() const noexcept {
    return getType() == Json_value_type::List;
}

bool Json::Json_value::isBool() const noexcept {
    return getType() == Json_value_type::Bool;
}

Json::Json_value::operator bool() {
    if (getType() == Json::Json_value_type::Bool) {
        if (data == "false") {
            return false;
        } else if (data == "true") {
            return true;
        } else {
            throw std::runtime_error("type is not match expected");
        }
    } else {
        throw std::runtime_error("wrong type");
    }
}

Json::Json_value::operator int() {
    if (getType() == Json::Json_value_type::Number) {
        return std::stoi(data);
    } else {
        throw std::runtime_error("wrong type");
    }
}

Json::Json_value::operator float() {
    if (getType() == Json::Json_value_type::Number) {
        return std::stof(data);
    } else {
        throw std::runtime_error("wrong type");
    }
}

Json::Json_value::operator double() {
    if (getType() == Json::Json_value_type::Number) {
        return std::stod(data);
    } else {
        throw std::runtime_error("wrong type");
    }
}

Json::Json_value::operator long double() {
    if (getType() == Json::Json_value_type::Number) {
        return std::stold(data);
    } else {
        throw std::runtime_error("wrong type");
    }
}

Json::Json_value::operator unsigned long() {
    if (getType() == Json::Json_value_type::Number) {
        return std::stoul(data);
    } else {
        throw std::runtime_error("wrong type");
    }
}

Json::Json_value::operator long long() {
    if (getType() == Json::Json_value_type::Number) {
        return std::stoll(data);
    } else {
        throw std::runtime_error("wrong type");
    }
}

Json::Json_value::operator std::string() {

    return to_string();
    if (getType() == Json::Json_value_type::String) {
        return data;
    } else {
        throw std::runtime_error("wrong type");
    }
}

std::ostream &Json::operator<<(std::ostream &os, Json::Json_value &js) noexcept {
    switch (js.getType()) {
    case Json_value_type::Null:
    case Json_value_type::String:
    case Json_value_type::Number:
    case Json_value_type::Bool:
        os << js.to_string();
        break;
    case Json_value_type::Dict:
        std::cout << " isdict" << std::endl;
        os << (&js)->to_string();
        // os << dynamic_cast<Json_dict *>(&js)->to_string();
        break;
    case Json_value_type::List:
        std::cout << " islist" << std::endl;
        os << (&js)->to_string();
        // os << dynamic_cast<Json_list *>(&js)->to_string();
        break;
    }
    return os;
}

void Json::Json_value::append(Json::Json_value::Json_obj const js) {
}

void Json::Json_value::insert(const std::string &key, Json::Json_value::Json_obj const js) {
}
