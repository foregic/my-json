


#include "light_json.h"
#include <bits/stdc++.h>

using std::string;


std::ostream &operator<<(std::ostream &os, const Json_obj &js) {
    os << js.data;
    return os;
}

Json_obj::~Json_obj() {
//    std::cout << "Json_obj析构" << std::endl;

}


Json_value::~Json_value() {
//    std::cout << "Json_value析构" << std::endl;
}


Json_string::~Json_string() {
//    std::cout << "Json_string析构" << std::endl;
}


Json_number::Json_number(std::string &s) {
    m_type = Json_value_type_number;
    data = std::stold(s);
}


std::ostream &operator<<(std::ostream &os, const Json_number &js) {
    os << js.data;
    return os;
}

Json_number::~Json_number() {
//    std::cout << "Json_number析构" << std::endl;
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

std::ostream &operator<<(std::ostream &os, const Json_bool &js) {
    if (js.data) {
        os << "true";
    } else {
        os << "false";
    }
    return os;
}

Json_bool::~Json_bool() {
//    std::cout << "Json_bool析构" << std::endl;
}


std::ostream &operator<<(std::ostream &os, const Json_null &js) {
    os << "null";
    return os;
}


std::ostream &operator<<(std::ostream &os, const Json_dict &js) {
    os << "{\r\n";
    for (auto &d:js.dict) {
        os << "\"" + d.first + "\" : ";
        os << d.second << ',';
    }
    os << "\r\n}";
    return os;
}

Json_dict::~Json_dict() {
//    std::cout << "Json_dict析构" << std::endl;
}


std::ostream &operator<<(std::ostream &os, const Json_list &js) {
    os << "[\r\n";
    for (auto &li : js.list) {
        os << "\r\n" << li << ',';
    }
    os << "\r\n]";
    return os;
}


Json_list::~Json_list() {
//    std::cout << "Json_list析构" << std::endl;

}


std::ostream &operator<<(std::ostream &os, const std::shared_ptr<Json_value> &js) {
    switch (js->m_type) {
        case Json_value_type_string: {
//            Json_string js_string =*dynamic_cast<Json_string *>(js.get());
//            os << js_string;
            os << *dynamic_cast<Json_string *>(js.get());
        }
            break;
        case Json_value_type_dict: {
            os << *dynamic_cast<Json_dict *>(js.get());
        }
            break;
        case Json_value_type_list: {
            os << *dynamic_cast<Json_list *>(js.get());
        }
            break;
        case Json_value_type_number: {
            os << *dynamic_cast<Json_number *>(js.get());
        }
            break;
        case Json_value_type_bool: {
            os << *dynamic_cast<Json_bool *>(js.get());
        }
            break;
        case Json_value_type_null: {
            os << *dynamic_cast<Json_null *>(js.get());
        }
            break;

    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const Json_string &js) {
    os << '\"' << js.data << '\"';
    return os;
}

Json_null::Json_null(const std::string &str) {
    if (str != "null") {
        throw std::invalid_argument("错误的null初始值");
    }
    data = "null";
}

Json_obj &Json_list::operator[](const int &pos) {
    if (pos >= this->list.size()) {
        throw std::out_of_range("位置越界");
    }
    return this->list[pos];
}

void Json_list::append(Json_obj &js) {
    this->list.push_back(js);
}

void Json_list::append(const Json_obj &js) {
    this->list.push_back(js);
}

void Json_list::clear() {
    this->list.clear();
}

size_t Json_list::size() {
    return this->list.size();
}

bool Json_list::empty() {
    return this->list.empty();
}

Json_obj &Json_dict::operator[](const string &str) {
    if (!dict.count(str)) {
        throw std::invalid_argument("该对象没有字段" + str);
    }
    return dict[str];
}

void Json_dict::insert(const string &str, const Json_obj &json) {
    this->dict[str] = json;
}

void Json_dict::insert(string &str, Json_obj &json) {
    this->dict[str] = json;
}

Json_obj get_obj(const std::string &str) {
    int pos = 0;
    Json_obj ans;
    while (pos < str.size() && str[pos] == ' ') {
        pos++;
    }
    switch (str[pos]) {
        case '{': {
            ans = get_dict(str, ++pos);
            while (str[pos] == ' ') {
                pos++;
            }
            if (str[pos] == '}')
                pos++;
            break;
        }
        case '[': {
            ans = get_list(str, ++pos);
            while (str[pos] == ' ') {
                pos++;
            }
            if (str[pos] == ']')
                pos++;
            break;
        }
        case '\"': {
            ans = get_string(str, ++pos);
            while (str[pos] == ' ') {
                pos++;
            }
            break;
        }
        case 'n':
            ans = get_null(str, pos);
            while (str[pos] == ' ') {
                pos++;
            }
            break;
        case 't' | 'f':
            ans = get_bool(str, pos);
            while (str[pos] == ' ') {
                pos++;
            }
            break;
        case '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9' | '0': {
            ans = get_number(str, pos);
            while (str[pos] == ' ') {
                pos++;
            }
            break;
        }
    }

    while (str[pos] == ' ') {
        pos++;
    }
    if (pos >= str.size()) {
        std::cout << "解析完成" << std::endl;
    } else {
        throw std::invalid_argument("无效的json语句");
    }
    return ans;

}

Json_obj get_string(const std::string &str, int &pos) {

    if (str[pos] == '\"') {
        ++pos;
    }
    std::string tmp;
    while (str[pos] != '\"') {
        tmp.push_back(str[pos]);
        pos++;
    }
    pos++;

    return Json_obj(Json_string(tmp));

}

Json_obj get_number(const std::string &str, int &pos) {

    std::string tmp;
    while (str[pos]=='.' || (str[pos] >= '0' && str[pos] <= '9')) {
        tmp.push_back(str[pos]);
        pos++;
    }
    return Json_obj(Json_number(tmp));
}

Json_obj get_bool(const std::string &str, int &pos) {

    std::string tmp;
    while (str[pos] != ',' && str[pos] != '}' && str[pos] != ']') {
        tmp.push_back(str[pos]);
        pos++;
    }
    return Json_obj(Json_bool(tmp));
}

Json_obj get_null(const std::string &str, int &pos) {

    std::string tmp = "null";
    pos += 4;
    return Json_obj(Json_null(tmp));
}


Json_obj get_dict(const std::string &str, int &pos) {
    Json_dict tmp_dict;
    if (str[pos] == '}') {
        ++pos;
        return Json_obj(tmp_dict);
    }
    while (pos < str.size()) {
        while (str[pos] == ' ') {
            pos++;
        }
        if (str[pos] == '\"') {
            pos++;
        }
        std::string first;
        while (str[pos] != '\"') {
            first += str[pos];
            pos++;
        }
        if (str[pos] == '\"') {
            pos++;
        }
        if (str[pos] == ':') {
            pos++;
        }
        Json_obj second;
        while (str[pos] == ' ') {
            pos++;
        }
        if (str[pos] == '{') {
            second = get_dict(str, ++pos);
        } else if (str[pos] == '[') {
            second = get_list(str, ++pos);
        } else if (str[pos] == '\"') {
            second = get_string(str, pos);
        } else if (str[pos] == 'n') {
            second = get_null(str, pos);
        } else if (str[pos] == 't' || str[pos] == 'f') {
            second = get_bool(str, pos);
        } else if (str[pos] >= '0' && str[pos] <= '9') {
            second = get_number(str, pos);
        } else {
            std::cout << str.substr(pos,pos+10) << std::endl;
            throw std::invalid_argument("无效的dict解析");
        }
        if (first.empty() || second.is_empty()) {
            throw std::invalid_argument("错误的dict分析值");
        }
        tmp_dict.insert(first, second);
        while (str[pos] == ' ') {
            pos++;
        }
        if (str[pos] == '}') {
            pos++;
            return Json_obj(tmp_dict);
        }
        if (str[pos] == ',') {
            pos++;
        }
        while (str[pos] == ' ') {
            pos++;
        }
    }
}

Json_obj get_list(const std::string &str, int &pos) {
    Json_list tmp_list;
    if (str[pos] == ']') {
        ++pos;
        return Json_obj(tmp_list);
    }
    while (pos < str.size()) {
        while (str[pos] == ' ') {
            pos++;
        }
        Json_obj tmp_obj;

        if (str[pos] == '{') {
            tmp_obj = get_dict(str, ++pos);
        } else if (str[pos] == '[') {
            tmp_obj = get_list(str, ++pos);
        } else if (str[pos] == '\"') {
            tmp_obj = get_string(str, pos);
        } else if (str[pos] == 'n') {
            tmp_obj = get_null(str, pos);
        } else if (str[pos] == 't' || str[pos] == 'f') {
            tmp_obj = get_bool(str, pos);
        } else if (str[pos] >= '0' && str[pos] <= '9') {
            tmp_obj = get_number(str, pos);
        } else {
            throw std::invalid_argument("无效的list解析");
        }
        if (tmp_obj.is_empty()) {
            throw std::invalid_argument(str + std::to_string(pos) + "位置处只有','缺少对象");
        }
        tmp_list.append(tmp_obj);
        while (str[pos] == ' ') {
            pos++;
        }
        if (str[pos] == ']') {
            pos++;
            return Json_obj(tmp_list);
        }
        if (str[pos] == ',') {
            pos++;
        }
    }
}


Json_obj::Json_obj(const Json_string &js) {
    this->data = std::make_shared<Json_value>(js);
}

Json_obj::Json_obj(const Json_bool &js) {
    this->data = std::make_shared<Json_value>(js);
}

Json_obj::Json_obj(const Json_null &js) {
    this->data = std::make_shared<Json_value>(js);
}

Json_obj::Json_obj(const Json_number &js) {
    this->data = std::make_shared<Json_value>(js);
}

Json_obj::Json_obj(const Json_dict &js) {
    this->data = std::make_shared<Json_value>(js);
}

Json_obj::Json_obj(const Json_list &js) {
    this->data = std::make_shared<Json_value>(js);
}


bool Json_dict::contains(const std::string &str) {
    if (!dict.count(str)) {
        return false;
    }
    return true;
}

void Json_dict::clear() {
    this->dict.clear();
}

size_t Json_dict::size() {
    return this->dict.size();
}

bool Json_dict::empty() {
    return this->dict.empty();
}


bool Json_obj::is_empty() {
    if (data == nullptr) {
        return true;
    } else {
        return false;
    }
}

Json_obj &Json_obj::operator[](const std::string &str) {
    if (this->data->get_type() == Json_value_type_dict) {
        return (*dynamic_cast<Json_dict *>(this->data.get()))[str];
    } else {
        throw std::invalid_argument("该对象不是一个dict");
    }
}

Json_obj &Json_obj::operator[](const int &pos) {
    if (this->data->get_type() == Json_value_type_list) {
        return (*dynamic_cast<Json_list *>(this->data.get()))[pos];
    } else {
        throw std::invalid_argument("该对象不是一个list");
    }

}


Json_obj &Json_obj::operator=(const Json_obj &js) {
    this->data = js.data;
}

Json_obj &Json_obj::operator=(const std::string &str) {
    *this = get_obj(str);
}

void Json_obj::clear() {
    if (this->get_type() == Json_value_type_list) {
        dynamic_cast<Json_list *>(this->data.get())->clear();
    } else if (this->get_type() == Json_value_type_dict) {
        dynamic_cast<Json_dict *>(this->data.get())->clear();
    } else {
        throw std::invalid_argument("该对象不是dict或list，无法清除内容");
    }
}

size_t Json_obj::size() {
    if (this->get_type() == Json_value_type_list) {
        return dynamic_cast<Json_list *>(this->data.get())->size();
    } else if (this->get_type() == Json_value_type_dict) {
        return dynamic_cast<Json_dict *>(this->data.get())->size();
    } else {
        throw std::invalid_argument("该对象不是dict或list无size属性");
    }
}

Json_value_type Json_obj::get_type() const {
    return this->data->get_type();
}

void Json_obj::append(const string &str) {
    if (this->get_type() == Json_value_type_list) {
        dynamic_cast<Json_list *>(this->data.get())->append(get_obj(str));
    } else {
        throw std::invalid_argument("该对象不是list，无法添加对象");
    }
}





