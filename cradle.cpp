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

void cradle::Cradle::term()
{
    factor();
    while (look == '*' || look == '/')
    {
        emitln(std::string("push eax"));
        switch (look)
        {
        case '*':
            multiply();
            break;
        case '/':
            divide();
            break;
        default:
            expected("Multiplicative Operator");
            break;
        }
    }
}

void cradle::Cradle::factor()
{
    if (look == '(')
    {
        match('(');
        expression();
        match(')');
    }
    else
    {
        emitln(std::string("mov eax, ") + getNumber());
    }
}

void cradle::Cradle::add()
{
    match('+');
    term();

    emitln(std::string("pop ecx"));
    emitln(std::string("add eax, ecx"));
}

void cradle::Cradle::subtract()
{
    match('-');
    term();

    emitln(std::string("pop ecx"));
    emitln(std::string("sub eax, ecx"));
    emitln(std::string("neg eax"));
}

void cradle::Cradle::multiply()
{
    match('*');
    factor();

    emitln(std::string("pop ecx"));
    emitln(std::string("mul ecx"));
}

void cradle::Cradle::divide()
{
    match('/');
    factor();

    emitln(std::string("pop ecx"));
    emitln(std::string("mov edx, 0"));
    emitln(std::string("div ecx"));
}

void cradle::Cradle::expression()
{
    if(isaddop(look))
    {
        emitln(std::string("mov eax, 0"));
    }
    else
    {
        term();
    }

    while (isaddop(look))
    {
        emitln(std::string("push eax"));
        switch (look)
        {
        case '+':
            add();
            break;
        case '-':
            subtract();
            break;
        default:
            expected("Additive Operator");
            break;
        }
    }
}

bool cradle::Cradle::isaddop(char c)
{
    return c == '+' || c == '-';
}