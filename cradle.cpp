#include "cradle.h"
#include <iostream>
#include <print>
#include <format>

using namespace std;

void cradle::Cradle::init()
{
    getChar();
}

void cradle::Cradle::getChar()
{
    std::cin.get(look);
}

void cradle::Cradle::error(const std::string& msg)
{
    //std::println();
    //std::println("Error: {}.", msg.c_str());
    std::cerr << std::endl << "Error: " << msg << "." << std::endl;
}

void cradle::Cradle::abort(const std::string& msg)
{
    error(msg);
    exit(1);
}

void cradle::Cradle::expected(const std::string& msg)
{
    abort(std::string(msg + " Expected"));
}

void cradle::Cradle::match(char x)
{
    if (look == x)
    {
        getChar();
    }
    else
    {
        expected(std::string("'") + x + std::string("'"));
    }
}

char cradle::Cradle::getName()
{
    if (!std::isalpha(look))
    {
        expected("Name");
    }

    char token = look;
    getChar();
    return token;
}

char cradle::Cradle::getNumber()
{
    if (!std::isdigit(look))
    {
        expected("Integer");
    }

    char token = look;
    getChar();
    return token;
}

void cradle::Cradle::emit(const std::string& s)
{
    //std::print("{}{}", TAB, s);
    std::cout << TAB << s;
}

void cradle::Cradle::emitln(const std::string& s)
{
    emit(s);
    //std::println();
    std::cout << std::endl;
}