#pragma once
#include "token.h"
#include <string>

using namespace std;

namespace lexer
{
    class Word : public Token
    {
        public:
            Word(int tag, const std::string& s);
            ~Word();
            
            const std::string& getLexeme() const;
        private:
            std::string lexeme;
    };
} // namespace lexer