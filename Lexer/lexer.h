#pragma once

#include <string>
#include <map>
#include "token.h"
#include "word.h"
#include <memory>

using  namespace std;

namespace lexer
{
    class Lexer
    {
    public:
        Lexer();
        ~Lexer();

        shared_ptr<Token> scan();

    private:
        void reserve(shared_ptr<Word> w);
        char read_next_char();
        void skip_insignificant_chars();
        shared_ptr<Token> scan_number();
        shared_ptr<Token> scan_word();

    private:
        int line = 1;
        char peek = ' ';
        std::map<std::string, shared_ptr<Word>> words;
    };  
} // namespace lex
