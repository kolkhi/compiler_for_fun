#pragma once
#include "tags.h"

using namespace std;

namespace lexer
{
    class Token
    {
        public:
            Token(int t);
            ~Token();

        private:
            int tag;
    };
}