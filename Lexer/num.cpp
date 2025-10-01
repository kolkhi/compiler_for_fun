#include "num.h"
#include "tags.h"

using namespace std;

lexer::Num::Num(int v) : Token(Tag::NUM), value(v)
{
}

lexer::Num::~Num()
{
}