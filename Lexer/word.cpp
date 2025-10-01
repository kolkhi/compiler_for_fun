#include "word.h"
#include "tags.h"

using namespace std;

lexer::Word::Word(int t, const std::string& s) : Token(t), lexeme(s)
{
}

lexer::Word::~Word()
{
}

const std::string& lexer::Word::getLexeme() const
{
    return lexeme;
}