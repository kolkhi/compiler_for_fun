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
        void skip_line_comment();
        void skip_block_comment();
        
        shared_ptr<Token> scan_number();
        shared_ptr<Token> scan_word();
        shared_ptr<Token> scan_greater();
        shared_ptr<Token> scan_less();
        shared_ptr<Token> scan_assign();
        shared_ptr<Token> scan_not();
    private:
        int line = 1;
        char peek = ' ';
        std::map<std::string, shared_ptr<Word>> words;
    };  
} // namespace lex
