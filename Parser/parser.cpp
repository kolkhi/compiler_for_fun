#include <iostream>
#include "parser.h"

using namespace std;
 
int parser::Parser::lookahead = 0; // Definition and initialization

// namespace lex;
parser::Parser::Parser()
{
    char c;
    std::cin.get(c);
    lookahead = c;
}

parser::Parser::~Parser()
{
}

void parser::Parser::expr()
{
    term();
    while(true)
    {
        if (lookahead == '+')
        {
            match('+');
            term();
            //cout << "+" << std::endl;
            parsed.append(1, '+');
        }
        else if (lookahead == '-')
        {
            match('-');
            term();
            //cout << "-" << std::endl;
            parsed.append(1, '-');
        }
        else
        {
            break;
        }
    }
}

void parser::Parser::term()
{
    if(isdigit(lookahead))
    {
        //cout << (char)lookahead << std::endl;
        parsed.append(1, (char)lookahead);
        match(lookahead); 
    }
    else 
    {
        cerr << "Error: Unexpected token " << (char)lookahead << std::endl;
        throw std::runtime_error("Syntax error");
    }
}

void parser::Parser::match(int token)
{
    if(lookahead == token)
    {
        char c;
        std::cin.get(c);
        lookahead = c;
    }
    else 
    {
        cerr << "Error: Expected token " << (char)token << ", got " << (char)lookahead << std::endl;
        throw std::runtime_error("Syntax error");
    }
}

const std::string& parser::Parser::getParsed() const
{
    return parsed;
}


