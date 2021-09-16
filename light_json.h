//
// Created by Administrator on 2021/9/15.
//

#ifndef MY_JSON_LIGHT_JSON_H
#define MY_JSON_LIGHT_JSON_H

#include <bits/stdc++.h>


enum Json_value_type {
    Json_value_type_null,      //空类型
    Json_value_type_number,    //数字类型
    Json_value_type_string,    //字符串类型
    Json_value_type_bool,      //逻辑类型
    Json_value_type_list,      //列表类型
    Json_value_type_dict       //字典类型
};


class Json_value;


class Json_value {
protected:

    Json_value_type m_type;
public:
    Json_value(Json_value_type T) : m_type(T) {}

    Json_value() : m_type(Json_value_type_null) {}

    virtual inline Json_value_type get_type() {
        return m_type;
    }

    friend std::ostream &operator<<(std::ostream &os, std::shared_ptr<Json_value> &js);

    virtual void print();

    virtual ~Json_value();
};


class Json_obj {
protected:
    std::shared_ptr<Json_value> data;
public:
    void set(std::shared_ptr<Json_value> p) {
        data = p;
    }

    friend std::ostream &operator<<(std::ostream &os, Json_obj &js);

    friend class Parser;

    virtual ~Json_obj();
};


class Json_string : public Json_value {
private:
    std::string data;
public:
    Json_string() : Json_value(Json_value_type_string), data("") {}

    Json_string(const char *s) : data(s) {}

    ~Json_string();

    friend std::ostream &operator<<(std::ostream &os, std::shared_ptr<Json_value> &js);

    friend std::ostream &operator<<(std::ostream &o, const Json_string &js);
};


class Json_number : public Json_value {
private:
    long data;

public:
    Json_number() : Json_value(Json_value_type_number), data(0) {}

    explicit Json_number(std::string &s);

    friend std::ostream &operator<<(std::ostream &os, std::shared_ptr<Json_value> &js);

    friend std::ostream &operator<<(std::ostream &os, Json_number &js);

    ~Json_number() override;

};


class Json_null : public Json_value {
private:
    std::string data;
public:
    Json_null() : data("null") {}

    friend std::ostream &operator<<(std::ostream &os, std::shared_ptr<Json_value> &js);

    friend std::ostream &operator<<(std::ostream &os, Json_null &js);
};

class Json_bool : public Json_value {
private:
    bool data;
public:
    Json_bool() : data(false) {}

    explicit Json_bool(std::string &s);

    friend std::ostream &operator<<(std::ostream &os, std::shared_ptr<Json_value> &js);

    friend std::ostream &operator<<(std::ostream &os, Json_bool &js);

    ~Json_bool() override;
};

class Json_list : public Json_value {
private:
    std::vector<Json_obj> list;

public:
    Json_list(const std::string &s);

    Json_list() : Json_value(Json_value_type_list), list({}) {}

    ~Json_list() override;

    void append();

    Json_obj &operator[](const int &pos);


    friend std::ostream &operator<<(std::ostream &os, std::shared_ptr<Json_value> &js);

    friend std::ostream &operator<<(std::ostream &os, Json_list &js);
};

class Json_dict : public Json_value {
private:
    std::unordered_map<std::string, Json_obj> dict;

public:
    Json_dict() : Json_value(Json_value_type_dict), dict({}) {}

    ~Json_dict() override;

    Json_dict(const std::string &s, int pos);

    Json_obj &operator[](const std::string &str);

    friend std::ostream &operator<<(std::ostream &os, std::shared_ptr<Json_value> &js);

    friend std::ostream &operator<<(std::ostream &os, Json_dict &js);
};


class Parser {
public:
    static Json_obj get_obj(const std::string &str);

    static std::shared_ptr<Json_value> json_dict_parser(const std::string &str, int pos);
};

template<typename T>
Json_obj make_json_obj(const std::string &str) {
    Json_obj js;
    js.set(std::make_shared<Json_value>(new T(str)));
    return js;
}


#endif //MY_JSON_LIGHT_JSON_H
