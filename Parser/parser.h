#pragma once

#include <string>

namespace parser
{
    class Parser
    {
    public:
        Parser();
        ~Parser();

        void expr();
        void term();
        void match(int token);

        const std::string& getParsed() const;
        
    private:
        static int lookahead;

        std::string parsed;
    };  
} // namespace parser
