

#ifndef _JSON_H_
#define _JSON_H_

#include <memory>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace Json {
    enum class Json_value_type : char {
        Null,   //空类型
        Number, //数字类型
        String, //字符串类型
        Bool,   //逻辑类型
        List,   //列表类型
        Dict,   //字典类型
        Invalid //非法字符类型
    };

    class Json_value {
        // using Json_obj = std::unique_ptr<Json_value>;
        using Json_obj = Json_value *;

    public:
        explicit Json_value() : type(Json_value_type::Invalid) {}
        explicit Json_value(const Json_value_type type_) : type(type_) {}

        explicit Json_value(const Json_value &other);
        explicit Json_value(Json_value &&other) noexcept;

        explicit Json_value(const Json_value_type type_, const std::string &str) : type(type_), data(str) {}
        explicit Json_value(const Json_value_type type_, const std::string::const_iterator &begin, const std::string::const_iterator &end)
            : type(type_), data(begin, end) {}

        Json_value &operator=(const Json_value &other);
        Json_value &operator=(Json_value &&other) noexcept;

        virtual ~Json_value() = default;

        virtual Json_value_type getType() const noexcept { return type; }
        virtual std::string to_string() ;

        virtual void append(char ch) {
            data.push_back(ch);
        }
        virtual void append(const Json_obj js);
        virtual void insert(const std::string &key, const Json_obj js);

        virtual Json_obj operator[](const std::string &str);
        virtual Json_obj operator[](const size_t &index);

        friend std::ostream &operator<<(std::ostream &os,  Json_value &js) noexcept;

        virtual bool isNull() const noexcept;
        virtual bool isNumber() const noexcept;
        virtual bool isDict() const noexcept;
        virtual bool isString() const noexcept;
        virtual bool isList() const noexcept;
        virtual bool isBool() const noexcept;

        explicit operator bool() ;
        explicit operator int() ;
        explicit operator float() ;
        explicit operator double() ;
        explicit operator long double() ;
        explicit operator unsigned long() ;
        explicit operator long long() ;
        explicit operator std::string() ;

    protected:
        std::string data;
        Json_value_type type;
    };

    class Json_list : public Json_value {
        using Json_obj = Json_value *;
        using List = std::vector<Json_obj>;
        using iterator = List::iterator;
        using const_iterator = List::const_iterator;
        using size_type = List::size_type;

    public:
        explicit Json_list() : Json_value(Json_value_type::List) {}
        explicit Json_list(const Json_list &other);
        explicit Json_list(Json_list &&other) noexcept;

        Json_list &operator=(const Json_list &other);
        Json_list &operator=(Json_list &&other) noexcept;

        ~Json_list() { clear(); }

        std::string to_string() ;
        virtual Json_obj operator[](const std::string &str);
        virtual Json_obj operator[](const size_t &index);
        virtual Json_obj operator[](const size_t &index) const;

        void clear();

        size_t size() const;
        bool empty() const;
        virtual void append(const Json_obj js);

        friend std::ostream &operator<<(std::ostream &os,  Json_list &js) noexcept;

    private:
        List list;
    };

    class Json_dict : public Json_value {

        using Json_obj = Json_value *;

        using Dict = std::unordered_map<std::string, Json_obj>;
        using key_type = Dict::key_type;
        using iterator = Dict::iterator;
        using const_iterator = Dict::const_iterator;
        using value_type = Dict::value_type;
        using insert_return_type = std::pair<iterator, bool>;

    public:
        explicit Json_dict() : Json_value(Json_value_type::Dict) {}
        explicit Json_dict(const Json_dict &other);
        explicit Json_dict(Json_dict &&other) noexcept;

        Json_dict &operator=(const Json_dict &other);
        Json_dict &operator=(Json_dict &&other) noexcept;

        ~Json_dict() {
            clear();
        }

    public:
        virtual std::string to_string() ;
        virtual Json_obj operator[](const std::string &str);
        virtual Json_obj operator[](const size_t &index);

    public:
        void clear() noexcept;
        size_t size() const noexcept;
        bool empty() const noexcept;
        size_t count(const key_type &key) const;
        bool contains(const key_type &key) const;

        template <typename... Args>
        void emplace(Args &&...args);

        virtual void insert(const std::string &key, const Json_obj js) override;

    public:
        iterator begin() noexcept;
        const_iterator cbegin() const noexcept;

        iterator end() noexcept;
        const_iterator cend() const noexcept;

        friend std::ostream &operator<<(std::ostream &os,  Json_dict &js) noexcept;

    private:
        Dict dict;
    };

}

#endif