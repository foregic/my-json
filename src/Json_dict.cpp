/*
 * @Author       : foregic
 * @Date         : 2021-12-21 21:59:54
 * @LastEditors  : foregic
 * @LastEditTime : 2021-12-30 19:47:48
 * @FilePath     : /json/src/Json_dict.cpp
 * @Description  :
 */

#include "Json_value.h"

std::size_t Json::Json_dict::count(const key_type &key) const {
    return dict.count(key);
}

bool Json::Json_dict::contains(const key_type &key) const {
    return dict.count(key) != 0;
}
void Json::Json_dict::clear() noexcept {
    for (auto iter = dict.begin(); iter != dict.end(); iter++) {
        iter->second->~Json_value();
    }
    dict.clear();
}

size_t Json::Json_dict::size() const noexcept {
    return this->dict.size();
}

bool Json::Json_dict::empty() const noexcept {
    return this->dict.empty();
}
std::string Json::Json_dict::to_string() {
    if (size() == 0)
        return "{}";
    std::string str = "{\n";
    if (size() > 0) {
        for (const auto &it : dict) {
            str += "\"" + it.first + "\":";
            str += it.second->to_string() + ",\n";
        }
        if (str.back() == '\n') {
            str.pop_back();
        }
        if (str.back() == ',') {
            str.pop_back();
        }
    }
    str += "\n}";
    return str;
}

//    virtual Json_obj operator[](const std::string &str);
//    virtual Json_obj operator[](const size_t &index);

Json::Json_dict::Json_obj Json::Json_dict::operator[](const size_t &index) {
    throw std::invalid_argument("Dict can't get data according to index");
}

Json::Json_dict::Json_obj Json::Json_dict::operator[](const std::string &str) {
    if (!dict.count(str)) {
        return nullptr;
    }
    return dict[str];
}

std::ostream &Json::operator<<(std::ostream &os, Json::Json_dict &js) noexcept {

    os << js.to_string();
    return os;
}

Json::Json_dict::iterator Json::Json_dict::begin() noexcept {
    return dict.begin();
}

Json::Json_dict::const_iterator Json::Json_dict::cbegin() const noexcept {
    return dict.cbegin();
}

Json::Json_dict::iterator Json::Json_dict::end() noexcept {
    return dict.end();
}

Json::Json_dict::const_iterator Json::Json_dict::cend() const noexcept {
    return dict.cend();
}

Json::Json_dict::Json_dict(const Json::Json_dict &other) {
    clear();
    for (auto iter = other.dict.begin(); iter != other.dict.end(); iter++) {
        switch (iter->second->getType()) {
        case Json_value_type::Null:
        case Json_value_type::Number:
        case Json_value_type::String:
        case Json_value_type::Bool:
            dict.emplace(iter->first, new Json_value(*iter->second));
            break;
        case Json_value_type::Dict:
            dict.emplace(iter->first, new Json_dict(*dynamic_cast<Json_dict *>(iter->second)));
            break;
        case Json_value_type::List:
            dict.emplace(iter->first, new Json_list(*dynamic_cast<Json_list *>(iter->second)));
            break;
        default:
            throw std::runtime_error("wrong type");
        }
    }
}

Json::Json_dict::Json_dict(Json::Json_dict &&other) noexcept {
    dict = std::forward<Dict>(other.dict);
}

Json::Json_dict &Json::Json_dict::operator=(const Json::Json_dict &other) {
    this->~Json_dict();
    *this = Json_dict(other);
}

Json::Json_dict &Json::Json_dict::operator=(Json::Json_dict &&other) noexcept {
    this->~Json_dict();
    *this = Json_dict(std::forward<Json_dict>(other));
}

// template <typename... Args>
// decltype(auto) emplace(Args &&...args) {
//     static_assert(
//         std::is_constructible<raw_object::value_type, Args...>::value,
//         "Parameter can't be used to construct a raw_object::value_type");
//     return _object_data.emplace(std::forward<Args>(args)...);
// }

template <typename... Args>
void Json::Json_dict::emplace(Args &&...args) {
    dict.emplace(std::forward<Args>(args)...);
}

void Json::Json_dict::insert(const std::string &key, const Json::Json_dict::Json_obj js) {
    dict.insert(std::make_pair(key, js));
    // emplace(key, js;

    // switch (js->getType()) {
    // case Json_value_type::Null:
    // case Json_value_type::Number:
    // case Json_value_type::String:
    // case Json_value_type::Bool:
    //     dict.emplace(key, new Json_value(*js));
    //     break;
    // case Json_value_type::Dict:
    //     dict.emplace(key, new Json_dict(*dynamic_cast<Json_dict *>(js)));
    //     // dict.emplace(new Json_dict(*dynamic_cast<Json_dict *>(iter->second)));
    //     break;
    // case Json_value_type::List:
    //     dict.emplace(key, new Json_list(*dynamic_cast<Json_list *>(js)));
    //     // dict.emplace(new Json_list(*dynamic_cast<Json_list *>(iter->second)));
    //     break;
    // default:
    //     throw std::runtime_error("wrong type");
    // }
}
