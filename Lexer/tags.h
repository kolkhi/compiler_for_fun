#pragma once

namespace lexer
{
    class Tag
    {
    public:
        static inline const int NUM = 256;
        static inline const int ID = 257;
        static inline const int TRUE = 258;
        static inline const int FALSE = 259;
        static inline const int GREATER_OR_EQUAL = 260;
        static inline const int LESS_OR_EQUAL = 261;
        static inline const int EQUAL = 262;
        static inline const int NOT_EQUAL = 263;
    };
} // namespace lexer