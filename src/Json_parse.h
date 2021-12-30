#ifndef _JSON_PARSE_H_
#define _JSON_PARSE_H_

#include "Json_value.h"
#include <iostream>

namespace Json {
    class Json_parse {
        using Json_obj = Json_value *;
        using const_iterator = std::string::const_iterator;

    public:
        Json_parse() = delete;
        Json_parse(const std::string &str) {
            data = str;
            // escape_string(str);
            cur = data.cbegin();
            end = data.cend();
        }

        friend std::ostream &operator<<(std::ostream &os, const Json::Json_parse &js) {
            return os;
        }

        Json_value *parse_obj();
        Json_value *parse_string();
        Json_value *parse_dict();
        Json_value *parse_list();
        Json_value *parse_null();
        Json_value *parse_number();
        Json_value *parse_bool();

    private:
        void escape_string(const std::string &str) {
            auto iter = str.begin();
            auto end = str.end();
            while (iter != end) {
                switch (*iter) {
                case '\\': {

                    switch (*(iter + 1)) {
                    case 't': {
                        data.push_back('\t');
                        iter++;

                    } break;
                    case 'n': {
                        data.push_back('\n');
                        iter++;

                    } break;
                    case 'r': {
                        data.push_back('\r');
                        iter++;

                    } break;
                    case '\\': {
                        data.push_back('\\');
                        iter++;

                    } break;

                    case '\'': {

                        data.push_back('\'');
                        iter++;
                    } break;
                    case '\"':
                        data.push_back('\"');
                        iter++;
                        break;
                    default:
                        break;
                    }
                } break;
                default:
                    data.push_back(*iter);
                    break;
                }
                iter++;
            }
        }
        bool skip_whitespace() {
            while (cur != end) {
                switch (*cur) {
                case ' ':
                    ++cur;
                    break;
                case '\t':
                    ++cur;
                    break;
                case '\n':
                    ++cur;
                    break;
                default:
                    return true;
                }
            }
            return false;
        }

        bool skip_digit() noexcept {
            if (cur != end && std::isdigit(*cur)) {
                ++cur;
            } else {
                return false;
            }

            while (cur != end && std::isdigit(*cur)) {
                ++cur;
            }

            if (cur != end) {
                return true;
            } else {
                return false;
            }
        }
        std::string data;
        const_iterator cur, end;
    };
}

#endif