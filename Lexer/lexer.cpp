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
    reserve(make_unique<Word>(Tag::GREATER_OR_EQUAL, ">="));
    reserve(make_unique<Word>(Tag::LESS_OR_EQUAL, "<="));
    reserve(make_unique<Word>(Tag::EQUAL, "=="));
    reserve(make_unique<Word>(Tag::NOT_EQUAL, "!="));
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

    if(peek == '/')
    {
        peek = read_next_char();
        if(peek == '/')
        {
            skip_line_comment();
        }
        else if (peek == '*')
        {
            skip_block_comment();
        }
        else
        {
            return make_shared<Token>('/');
        }
    }

    if(peek == '>')
    {
        return scan_greater();
    }

    if(peek == '<')
    {
        return scan_less();
    }

    if(peek == '=')
    {
        return scan_assign();
    }

    if(peek == '!')
    {
        return scan_not();
    }

    auto token = make_shared<Token>(peek);
    peek = ' ';
    return token;
}

shared_ptr<lexer::Token> lexer::Lexer::scan_not()
{
    peek = read_next_char();
    if (peek == '=')
    {
        peek = read_next_char();
        return words["!="];
    }
    
    return make_shared<Token>('!');
}

shared_ptr<lexer::Token> lexer::Lexer::scan_assign()
{
    peek = read_next_char();
    if (peek == '=')
    {
        peek = read_next_char();
        return words["=="];
    }
    
    return make_shared<Token>('=');
}

shared_ptr<lexer::Token> lexer::Lexer::scan_greater()
{
    peek = read_next_char();
    if (peek == '>')
    {
        peek = read_next_char();
        return words[">="];
    }
    
    return make_shared<Token>('>');
}

shared_ptr<lexer::Token> lexer::Lexer::scan_less()
{
    peek = read_next_char();
    if (peek == '=')
    {
        peek = read_next_char();
        return words["<="];
    }
    
    return make_shared<Token>('<');
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

void lexer::Lexer::skip_line_comment()
{
    while(peek != '\n')
    {
        peek = read_next_char();
    }

    line++;
    peek = read_next_char();
}


void lexer::Lexer::skip_block_comment()
{
    char prev_char = 0;
    do
    {
        prev_char = peek;
        peek = read_next_char();
        if(peek == '\n')
        {
            line++;
        }
    }
    while(peek != '/' || prev_char != '*');
    
    peek = read_next_char();
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