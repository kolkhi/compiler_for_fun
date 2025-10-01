#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "./Lexer/lexer.h"
#include "./Parser/postfix.h"

using namespace std;


int main(int argc, char* argv[]) 
{
    /*if(argc < 2) 
    {
        cerr << "Usage: " << argv[0] << " <source-file>" << endl;
        return 1;
    }

    std::ifstream input_file(argv[1]);
    
    if(!input_file.is_open()) 
    {
        cerr << "Error: Could not open file " << argv[1] << endl;
        return 1;
    }

    lex::LexicalAnalyzer lexer = lex::LexicalAnalyzer();
    std::string line;
    while(!std::getline(input_file, line).eof()) 
    {
        lexer.analyze(line);

        cout << line << endl;
    }*/

    auto postfix_transaltor = parser::Postfix();
    postfix_transaltor.translate();

    return 0;
}