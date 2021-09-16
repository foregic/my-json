//
// Created by Administrator on 2021/9/15.
//

#include "light_json.h"
#include <bits/stdc++.h>

using std::string;


//enum Json_value_type {
//    Json_value_type_null,      //空类型
//    Json_value_type_number,    //数字类型
//    Json_value_type_string,    //字符串类型
//    Json_value_type_bool,      //逻辑类型
//    Json_value_type_list,      //列表类型
//    Json_value_type_dict       //字典类型
//};





std::ostream &operator<<(std::ostream &os, Json_obj &js) {
    os << js.data;
    return os;
}

Json_obj::~Json_obj() {
    std::cout << "Json_obj析构" << std::endl;

}


Json_obj Parser::get_obj(const string &str) {
    assert(str.size() >= 0);
    if (str[0] == '\"') {
        return make_json_obj<Json_string>(str);
    } else if (str[0] == 'f' || str[0] == 't') {
        return make_json_obj<Json_bool>(str);
    } else if (str[0] == 'n') {
        return make_json_obj<Json_null>(str);
    } else if (str[0] >= '0' || str[0] <= '9') {
        return make_json_obj<Json_number>(str);
    } else {
        throw std::invalid_argument("错误字段" + str);
    }
}


Json_value::~Json_value() {
    std::cout << "Json_value析构" << std::endl;
}


std::ostream &operator<<(std::ostream &o, const Json_string &js) {
    o << js.data;
    return o;
}

Json_string::~Json_string() {
    std::cout << "Json_string析构" << std::endl;
}


Json_number::Json_number(std::string &s) {
    m_type = Json_value_type_number;
    data = std::stol(s);
}


.
std::ostream &operator<<(std::ostream &os, std::shared_ptr<Json_value> &js);

std::ostream &operator<<(std::ostream &os, Json_number &js) {
    os << js.data;
    return os;
}

Json_number::~Json_number() {
    std::cout << "Json_number析构" << std::endl;
}


Json_bool::Json_bool(std::string &s) {
    m_type = Json_value_type_bool;
    if (s == "true") {
        data = true;
    } else if (s == "false") {
        data = false;
    } else {
        throw std::invalid_argument("错误的布尔初始化值");
    }
}

std::ostream &operator<<(std::ostream &os, Json_bool &js) {
    if (js.data) {
        os << "true";
    } else {
        os << "false";
    }
    return os;
}

Json_bool::~Json_bool() {
    std::cout << "Json_bool析构" << std::endl;
}


std::ostream &operator<<(std::ostream &os, Json_null &js) {
    os << "null";
    return os;
}


std::ostream &operator<<(std::ostream &os, Json_dict &js) {
    os << "{\r\n";
    for (auto &d:js.dict) {
        os << "\r\n" + d.first + " : ";
        os << d.second << ',';
    }
    os << "\r\n}";
    return os;
}

Json_dict::~Json_dict() {
    std::cout << "Json_dict" << std::endl;
}


Json_list::Json_list(const std::string &s) {
    m_type = Json_value_type_list;
}


std::ostream &operator<<(std::ostream &os, Json_list &js) {
    os << "[\r\n";
    for (auto &li : js.list) {
        os << "\r\n" << li << ',';
    }
    os << "\r\n]";
    return os;
}


Json_list::~Json_list() {
    std::cout << "Json_list析构" << std::endl;


}


std::ostream &operator<<(std::ostream &os, std::shared_ptr<Json_value> &js) {
    switch (js->m_type) {
        case Json_value_type_string: {
            os << *dynamic_cast<Json_string *>(js.get()) << ',';
        }
            break;
        case Json_value_type_dict: {
            os << *dynamic_cast<Json_dict *>(js.get()) << ',';
        }
            break;
        case Json_value_type_list: {
            os << *dynamic_cast<Json_list *>(js.get()) << ',';
        }
            break;
        case Json_value_type_number: {
            os << *dynamic_cast<Json_number *>(js.get()) << ',';
        }
            break;
        case Json_value_type_bool: {
            os << *dynamic_cast<Json_bool *>(js.get()) << ',';
        }
            break;
        case Json_value_type_null: {
            os << *dynamic_cast<Json_null *>(js.get()) << ',';
        }
            break;

    }
    return os;
}

Json_obj &Json_dict::operator[](const string &str) {
    if (!dict.count(str)) {
        throw std::invalid_argument("该对象没有字段" + str);
    }
    return dict[str];
}
























