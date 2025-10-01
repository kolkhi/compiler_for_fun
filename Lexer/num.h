#pragma once
#include "token.h"

namespace lexer
{
    class Num : public Token
    {
        public:
            Num(int v);
            ~Num();

        private:
            int value;
    };
} // namespace lexer