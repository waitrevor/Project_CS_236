#include "Lexer.h"
#include "Automaton.h"
#include <vector>

using namespace std;
Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    // TODO: need to clean up the memory in `automata` and `tokens`
    for(int unsigned i = 0; i < tokens.size(); i++){
        delete tokens[i];
    }
    for(int unsigned i = 0; i < automata.size(); i++){
        //delete automata[i];
    }
}

void Lexer::CreateAutomata() {
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    // TODO: Add the other needed automata here
    automata.push_back(new CommaAutomaton());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new QMarkAutomaton());
    automata.push_back(new LeftParenAutomaton());
    automata.push_back(new RightParenAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new AddAutomaton());
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new IDAutomaton());
    automata.push_back(new CommentAutomaton());
    //automata.push_back(new UndefinedAutomaton());
    automata.push_back(new EOFAutomaton());
}

void Lexer::Run(std::string& input) {
    int lineNumber = 1; // set lineNumber to 1
    while (!input.empty()){ // While there's more to tokenize
        int unsigned maxRead = 0; // set maxRead to 0
        Automaton* maxAutomaton = automata.at(0); //set maxAutomation tothe first automata
        //Handle whitespace
        while(input.at(maxRead) == ' ' || input.at(maxRead) == '\t' || input.at(maxRead) == '\n'){
            if(input.at(maxRead) == '\n'){
                lineNumber++;
            }
            maxRead++;
            if(maxRead == input.size()){
                break;
            }
        }
        input.erase(0,maxRead);
        maxRead = 0;
        if(input.empty()){
            break;
        }

        //Parallel Part
        for (Automaton* automaton : automata){
            int unsigned inputRead = automaton->Start(input);
            if(inputRead > maxRead){
                maxRead = inputRead;
                maxAutomaton = automaton;
                break;
            }
        }
        //Max part
        if (maxRead > 0){
            string newInput = input.substr(0,maxRead);
            Token *newToken = maxAutomaton->CreateToken(newInput, lineNumber);
            lineNumber+=maxAutomaton->NewLinesRead();
            tokens.push_back(newToken);
        }
        else {
            maxRead = 1;
            /**string newInput = input.substr(0,maxRead);
            Token* newToken = new Token(TokenType::UNDEFINED, newInput, lineNumber);
            tokens.push_back(newToken);
            std::cout << newToken << std::endl;
             **/
        }
        input.erase(0,maxRead);
    }
    tokens.push_back(new Token(TokenType::EOF_TYPE,"",lineNumber));
}

string Lexer::toString(){
    string output;
    for (Token* token : tokens){
        output += token->toString() + "\n";
    }
    output += "Total Tokens = ";
    output += to_string(tokens.size());
    return output;
};

vector<Token*> Lexer::ReturnTokens(){
    return tokens;
}