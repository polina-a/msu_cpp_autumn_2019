#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>


template<class T>
std::string to_string(T&& arg)
{
    std::ostringstream stream;
    stream << arg;
    return stream.str();
}

template<class... T>
std::string format(const std::string& str, T&&... args)
{
    std::vector<std::string> args_ = {to_string(std::forward<T>(args))...};
    std::ostringstream result;

    for (size_t i = 0; i < str.length(); i++)
    {

        if (str[i] == '}')
            throw std::runtime_error("left bound not found");

        if (str[i] == '{')
        {
            i++;
            size_t arg_num = 0;

            if (str[i] == '}')
                throw std::runtime_error("no argumets");

            while ((str[i] != '}') && (i < str.length()))
            {
                arg_num = 10 * arg_num + str[i] - '0';
                i++;
            }

            if (i >= str.length())
                throw std::runtime_error("right bound not found");

            if (arg_num > args_.size() - 1)
                throw std::runtime_error("argument does not exist");

            result << args_[arg_num];
            continue;
        }

        result << str[i];
    }

    return result.str();
}