#include <iostream>
#include "parser.h"
#include "postfix.h"

using namespace std;
 
// namespace lex;
parser::Postfix::Postfix()
{
}

parser::Postfix::~Postfix()
{
}

void parser::Postfix::translate()
{
    auto parser = Parser();
    parser.expr();
    cout << parser.getParsed()<<std::endl;
}