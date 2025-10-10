#pragma once
#include <string>

using namespace std;

namespace cradle 
{
    class Cradle
    {
    public:
        Cradle() = default;
        ~Cradle() = default;

        void init();

        char getName();
        char getNumber();
        
        void getChar();
        
        void error(const std::string& msg);
        void abort(const std::string& msg);
        void expected(const std::string& msg);

        void match(char x);

        void emit(const std::string& s);
        void emitln(const std::string& s);

    private:
        char look; // Lookahead character

        const char TAB = '\t';
    };
}

