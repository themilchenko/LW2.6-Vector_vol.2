#include <string>
#include <iostream>

#pragma once

struct MyDataType
{
    std::string _name;
    size_t _age;
    std::string _hobby;

    MyDataType() : _name(""), _age(0), _hobby("") { };
    MyDataType(const std::string& n, size_t a, const std::string& h) :
    _name(n),
    _age(a),
    _hobby(h) { };

    friend std::ostream& operator<<(std::ostream& output, const MyDataType& ob)
    {
        output << "{ " << ob._name << ", " << ob._age << ", " << ob._hobby << " }\n";
        return output;
    }
};