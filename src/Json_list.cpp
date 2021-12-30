/*
 * @Author       : foregic
 * @Date         : 2021-12-21 23:15:46
 * @LastEditors  : foregic
 * @LastEditTime : 2021-12-30 19:30:54
 * @FilePath     : /json/src/Json_list.cpp
 * @Description  :
 */
#include "Json_value.h"

void Json::Json_list::clear() {
    for (int i = 0; i < list.size(); i++) {
        list[i]->~Json_value();
    }
    list.clear();
}
size_t Json::Json_list::size() const {
    return this->list.size();
}
std::string Json::Json_list::to_string()  {
    std::string str = "[\n";
    if (size() > 0) {
        for (const auto &it : list) {
        
            str += it->to_string() + ",\n";
        }
        if (str.back() == '\n') {
            str.pop_back();
        }
        if (str.back() == ',') {
            str.pop_back();
        }
    }
    str += "\n]";
    return str;
}
// virtual Json_obj operator[](const std::string &str);
// virtual Json_obj operator[](const size_t &index);

Json::Json_list::Json_obj Json::Json_list::operator[](const size_t &index) {
    if (index < 0 || index >= size()) {
        throw std::invalid_argument("index over size");
    }
    return this->list[index];
}

Json::Json_list::Json_obj Json::Json_list::operator[](const size_t &index) const {
    if (index < 0 || index >= size()) {
        throw std::invalid_argument("index over size");
    }
    return this->list[index];
}

Json::Json_list::Json_obj Json::Json_list::operator[](const std::string &str) {
    throw std::invalid_argument("Dict can't get data according to index");
}

std::ostream &Json::operator<<(std::ostream &os,  Json::Json_list &js) noexcept {
    os << js.to_string();
    return os;
}

void Json::Json_list::append(const Json_obj value) {
    list.emplace_back(value);
}

Json::Json_list::Json_list(const Json::Json_list &other) {
    clear();
    for (int i = 0; i < other.size(); i++) {
        switch (other[i]->getType()) {
        case Json_value_type::Number:
        case Json_value_type::Null:
        case Json_value_type::String:
        case Json_value_type::Bool:
            list.emplace_back(new Json_value(*other[i]));
            break;
        case Json_value_type::Dict:
            list.emplace_back(new Json_dict(*dynamic_cast<Json_dict *>(other[i])));
            break;
        case Json_value_type::List:
            list.emplace_back(new Json_list(*dynamic_cast<Json_list *>(other[i])));
            break;
        }
    }
}

Json::Json_list::Json_list(Json::Json_list &&other) noexcept {
    std::swap(list, other.list);
}

Json::Json_list &Json::Json_list::operator=(const Json::Json_list &other) {
}

Json::Json_list &Json::Json_list::operator=(Json::Json_list &&other) noexcept {
    for (int i = 0; i < other.size(); i++) {
        list.emplace_back(std::move(other[i]));
    }
}

bool Json::Json_list::empty() const {
    list.empty();
}
