#include "Automaton.h"

void AddAutomaton::S0(const std::string &input) {
    if (input[index] == '+') {
        inputRead = 1;
    }
    else {
        Serr();
    }

}

void ColonAutomaton::S0(const std::string& input) {
    if(index+1 <= input.size()) {
        if (input[index] == ':' && input[index + 1] != '-') {
            inputRead = 1;
        } else {
            Serr();
        }
    } else {
        Serr();
    }
}

void ColonDashAutomaton::S0(const std::string& input) {
    if (input[index] == ':') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}

void ColonDashAutomaton::S1(const std::string& input) {
    if (input[index] == '-') {
        inputRead++;
    }
    else {
        Serr();
    }
}

void CommaAutomaton::S0(const std::string& input) {
    if (input[index] == ',') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}

void CommentAutomaton::S0(const std::string &input) {
    if(input.size() >= 2) {
        char firstChar = input.at(0);
        char secondChar = input.at(1);
        if(firstChar == '#' && secondChar == '|'){
            //Block Comment
            int unsigned i;
            inputRead+=2; // accounts for the 2 already read
            for(i = 2; i < input.size(); i++){
                char currChar = input.at(i);
                if(currChar == '\n'){
                    newLines++;
                } else if(currChar == '|'){
                    if(i+1 <= input.size() && input.at(i+1) == '#') { // reached a valid end
                        inputRead+=2;
                        break;
                    }
                }
                inputRead++;
            }
            if (i == input.size()){
                Serr();
            }
        } else if (firstChar == '#') {
            //Normal Comment
            inputRead = input.find('\n');
        } else {
            //Not a comment
            Serr();
        }
    } else {
        Serr();
    }
}

void EOFAutomaton::S0(const std::string &input) {
    if (input == "") {
        inputRead = 0;
    }
    else {
        Serr();
    }
}

void FactsAutomaton::S0(const std::string &input) {
    std::string newInput = input.substr(index, index+5);
    if (newInput == "Facts") {
        int idx = (int)input.at(newInput.size());
        if((idx < 65 || (idx > 90 && idx < 97) || idx > 123)) {
            inputRead = 5;
        }
    }
    else {
        Serr();
    }
}

void IDAutomaton::S0(const std::string &input) {
    int unsigned i = 0;
    if(input.size() < 1){
        Serr();
    }else {
        char currChar = input.at(i);
        if (!std::isdigit(currChar) && currChar != '\'' && currChar != '#') {
            while (i < input.size() && (isdigit(currChar) || (currChar > 64 && currChar < 91) || (currChar > 96 && currChar < 123))) {
                inputRead++;
                i++;
                currChar = input.at(i);
            }
        } else {
            Serr();
        }
    }
}

void LeftParenAutomaton::S0(const std::string &input) {
    if (input[index] == '(') {
        inputRead = 1;
    }
    else {
        Serr();
    }

}

void MultiplyAutomaton::S0(const std::string &input) {
    if (input[index] == '*') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}

void PeriodAutomaton::S0(const std::string& input) {
    if (input[index] == '.') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}

void QMarkAutomaton ::S0(const std::string &input) {
    if(input[index] == '?'){
        inputRead = 1;
    } else {
        Serr();
    }
}

void QueriesAutomaton::S0(const std::string &input) {
    std::string newInput = input.substr(index, index+7);
    if (newInput == "Queries") {
        int idx = (int)input.at(newInput.size());
        if((idx < 65 || (idx > 90 && idx < 97) || idx > 123)) {
            inputRead = 7;
        }
    }
    else {
        Serr();
    }
}

void RightParenAutomaton::S0(const std::string &input) {
    if (input[index] == ')') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}

void RulesAutomaton::S0(const std::string &input) {
    std::string newInput = input.substr(index, index+5);
    if (newInput == "Rules") {
        int idx = (int)input.at(newInput.size());
        if((idx < 65 || (idx > 90 && idx < 97) || idx > 123)) {
            inputRead = 5;
        }
    }
    else {
        Serr();
    }
}

void SchemesAutomaton::S0(const std::string &input) {
    if(index+7 <= input.size()) {
        std::string newInput = input.substr(index, index + 7);
        if (newInput == "Schemes") {
            int idx = input.at(0);
            if ((idx < 65 || (idx > 90 && idx < 97) || idx > 123)) {
                Serr();
            } else {
                inputRead = 7;
            }
        } else {
            Serr();
        }
    } else {
        Serr();
    }
}

void StringAutomaton::S0(const std::string &input) {
    int unsigned i = 0;
    char firstChar = input.at(i);
    if(firstChar == '\'') {
        i++;
        while (i != input.size()){
            char currChar = input.at(i);
            if(currChar == '\''){
                if(i+1 <= input.size() && input.at(i+1) == '\''){
                    inputRead+=2;
                    i+=2;
                    continue;
                } else {
                    inputRead+=2;
                    break;
                }
            } else if(input.at(i) == '\n'){
                newLines++;
            }
            inputRead++;
            i++;
        }
        if (i == input.size()){
            Serr();
        }
    } else{
        Serr();
    }
}

void UndefinedAutomaton::S0(const std::string &input) {
    int unsigned i = 0;
    char currChar = input.at(i);
    if (currChar == '\'' || currChar == '#') { // Just checking basics again, because if String or comment, then it would've caught
        //I automatically know that these are invalid cases
        while(i != input.size()){
            if(input.at(i) == '\n'){
                newLines++;
            }
            inputRead++;
            i++;
        }
    } else {
        inputRead = 1;
    }
}