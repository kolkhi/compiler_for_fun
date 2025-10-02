#include <iostream>
#include "lexer.h"
#include "num.h"

using namespace std;
using namespace lexer;
 
// namespace lex;
lexer::Lexer::Lexer()
{
    reserve(make_unique<Word>(Tag::TRUE, "true"));
    reserve(make_unique<Word>(Tag::FALSE, "false"));
}

lexer::Lexer::~Lexer()
{
}

void lexer::Lexer::reserve(shared_ptr<Word> w)
{
    words[w->getLexeme()] = w;
}

char lexer::Lexer::read_next_char()
{
    char c;
    std::cin.get(c);
    return c;
}

shared_ptr<lexer::Token> lexer::Lexer::scan()
{
    skip_insignificant_chars();

    if(isdigit(peek))
    {
       return scan_number(); 
    }

    if(isalpha(peek))
    {
        return scan_word();
    }

    auto token = make_shared<Token>(peek);
    peek = ' ';
    return token;
}

void lexer::Lexer::skip_insignificant_chars()
{
    for(;; peek = read_next_char())
    {
        if(peek == ' ' || peek == '\t')
        {
            continue;
        }
        else if(peek == '\n')
        {
            line++;
        }
        else
        {
            break;
        }
    }
}

shared_ptr<lexer::Token> lexer::Lexer::scan_number()
{
    int v = 0;
    do
    {
        v = 10 * v + (peek - '0');
        peek = read_next_char();
    } while (isdigit(peek));
    
    return make_shared<Num>(v);
}

shared_ptr<lexer::Token> lexer::Lexer::scan_word()
{
    std::string s;
    do
    {
        s.push_back(peek);
        peek = read_next_char();
    }
    while(isalnum(peek));

    if(words.find(s) != words.end())
    {
        return words[s];
    }
    
    auto word = make_shared<Word>(Tag::ID, s);
    reserve(word);
    return word;
}