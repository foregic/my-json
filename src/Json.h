

#ifndef MY_JSON_JSON_H
#define MY_JSON_JSON_H

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <map>

enum Json_value_type {
    Json_value_type_null = 0,  //空类型
    Json_value_type_number,    //数字类型
    Json_value_type_string,    //字符串类型
    Json_value_type_bool,      //逻辑类型
    Json_value_type_list,      //列表类型
    Json_value_type_dict       //字典类型
};

class Json_value;

class Json_obj;

class Json_null;

class Json_bool;

class Json_string;

class Json_number;

class Json_dict;

class Json_list;

class Json_value {
protected:
    Json_value_type m_type;
public:
    explicit Json_value(Json_value_type T) : m_type(T) {}

    Json_value() : m_type(Json_value_type_null) {}

    virtual Json_value_type get_type() noexcept;

    friend std::ostream &operator<<(std::ostream &os, const std::shared_ptr<Json_value> &js);

    virtual ~Json_value();
};


class Json_obj {
protected:
    std::shared_ptr<Json_value> data;
public:
    Json_obj() : data(nullptr) {}

    Json_obj &operator=(Json_value *js);

    explicit Json_obj(std::shared_ptr<Json_value> js) : data(std::move(js)) {}

    Json_obj(const Json_obj &js) {
        *this = js;
    }

    Json_obj(Json_obj &js) {
        *this = js;
    }

    bool is_empty();

    explicit Json_obj(const Json_string &js);

    explicit Json_obj(const Json_bool &js);

    explicit Json_obj(const Json_null &js);

    explicit Json_obj(const Json_number &js);

    explicit Json_obj(const Json_dict &js);

    explicit Json_obj(const Json_list &js);

    auto operator*() {
        return *data;
    }

    void append(const std::string &str);

    void clear();

    size_t size();

    Json_value_type get_type() const;


    Json_obj &operator[](const std::string &str);

    Json_obj &operator[](const int &pos);


    friend std::ostream &operator<<(std::ostream &os, const Json_obj &js);

    friend std::ostream &operator<<(std::ostream &os, const std::shared_ptr<Json_value> &js);


    virtual ~Json_obj();
};

class Json_bool : public Json_value {
private:
    bool data;
public:
    Json_bool() : data(false) {}

    explicit Json_bool(std::string &s);


    friend std::ostream &operator<<(std::ostream &os, const std::shared_ptr<Json_value> &js);

    friend std::ostream &operator<<(std::ostream &os, const Json_bool &js);

    ~Json_bool() override;
};

class Json_string : public Json_value {
private:
    std::string data;
public:
    Json_string() : Json_value(Json_value_type_string) {}

    Json_string(const Json_string &js) : Json_value(Json_value_type_string) {
        data = js.data;
    }

    explicit Json_string(const char *s) : Json_value(Json_value_type_string), data(s) {}

    explicit Json_string(std::string s) : Json_value(Json_value_type_string), data(std::move(s)) {}

    ~Json_string() override;

    friend std::ostream &operator<<(std::ostream &os, const std::shared_ptr<Json_value> &js);

    friend std::ostream &operator<<(std::ostream &os, const Json_string &js);
};

class Json_number : public Json_value {
private:
    long double data;

public:
    Json_number() : Json_value(Json_value_type_number), data(0) {}

    explicit Json_number(std::string &s);

    friend std::ostream &operator<<(std::ostream &os, const std::shared_ptr<Json_value> &js);

    friend std::ostream &operator<<(std::ostream &os, const Json_number &js);

    ~Json_number() override;

};

class Json_dict : public Json_value {

private:
    std::map<std::string, Json_obj> dict;

public:
    Json_dict() : Json_value(Json_value_type_dict), dict({}) {}

    ~Json_dict() override;

    void insert(std::string &str, Json_obj &json);

    void insert(const std::string &str, const Json_obj &json);


    void clear();

    size_t size();

    bool empty();

    Json_obj &operator[](const std::string &str);

    friend std::ostream &operator<<(std::ostream &os, const std::shared_ptr<Json_value> &js);

    friend std::ostream &operator<<(std::ostream &os, const Json_dict &js);

    bool contains(const std::string &str);
};

class Json_list : public Json_value {
private:

    std::vector<Json_obj> list;

public:

    Json_list() : Json_value(Json_value_type_list), list({}) {}

    ~Json_list() override;

    Json_value_type get_type() noexcept override;


    void append(const Json_obj &js);

    void clear();

    size_t size();

    bool empty();

    Json_obj &operator[](const int &pos);


    friend std::ostream &operator<<(std::ostream &os, const std::shared_ptr<Json_value> &js);

    friend std::ostream &operator<<(std::ostream &os, const Json_list &js);


    void append(Json_obj &js);
};

class Json_null : public Json_value {
private:
    std::string data;
public:
    Json_null():data("null"){}

    Json_null(std::string &str) : data(str) {}

    explicit Json_null(const std::string &str);

    friend std::ostream &operator<<(std::ostream &os, const std::shared_ptr<Json_value> &js);

    friend std::ostream &operator<<(std::ostream &os, const Json_null &js);

    ~Json_null() override;
};


Json_obj get_obj(const std::string &str);


Json_obj get_string(const std::string &str, int &pos);

Json_obj get_dict(const std::string &str, int &pos);

Json_obj get_list(const std::string &str, int &pos);

Json_obj get_null(const std::string &str, int &pos);

Json_obj get_number(const std::string &str, int &pos);

Json_obj get_bool(const std::string &str, int &pos);

#endif //MY_JSON_JSON_H
