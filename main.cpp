#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {

    // TODO
    if (argc != 2){
        cout << "usage: " << argv[0] << " input_file" << endl;
        return 1;
    }

    string filename = argv[1];
    ifstream input(filename);
    input.open("test.txt");
    if(!input.is_open()){
        cout << "file " << filename << " could not be found or opened." << endl;
        return 1;
    }
 
    string fullFile; // if not work, rename to line
    ostringstream ss;
    ss << input.rdbuf();
    fullFile = ss.str();

    auto* lexer = new Lexer();
    lexer->Run(fullFile);

    auto* parser = new Parser(lexer->ReturnTokens());
    parser->ParseDatalog();
    
    auto* interpreter = new Interpreter(parser->GetDatalog());
    interpreter->SchemeToRelation();
    interpreter->FactToTuple();
    interpreter->EvaluateQueries();

    delete lexer;
    delete parser;
    delete interpreter;

    return 0;
}