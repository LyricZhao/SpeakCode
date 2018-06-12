# include <map>
# include <string>
# include <vector>
# include <cassert>
# include <iostream>
# include <algorithm>

# include <QTextCursor>

# include "writer.h"

extern MainWindow *mwin;

inline void to_lower_case(std:: string &command) {
    transform(command.begin(), command.end(), command.begin(), ::tolower);
}

std:: string Writer:: type0convert(std::string command) {
    if(!spec.count(command)) {
        return command;
    }
    return spec[command];
}

void Writer:: takeAction(std:: string command) {
    if(command == "backspace") {
        mw -> bs();
    } else if(command == "left") {
        mw -> ml();
    } else if(command == "right") {
        mw -> mr();
    } else if(command == "up") {
        mw -> mu();
    } else if(command == "down") {
        mw -> md();
    } else if(command == "space") {
        writeIntoCode(" ");
    } else if(command == "tab") {
        writeIntoCode("\t");
    }
}

void Writer:: mp_construct() {
    // directly write
    func["a"] = 0;
    func["b"] = 0;
    func["c"] = 0;
    func["d"] = 0;
    func["e"] = 0;
    func["f"] = 0;
    func["g"] = 0;
    func["h"] = 0;
    func["i"] = 0;
    func["j"] = 0;
    func["k"] = 0;
    func["l"] = 0;
    func["m"] = 0;
    func["n"] = 0;
    func["o"] = 0;
    func["p"] = 0;
    func["q"] = 0;
    func["r"] = 0;
    func["s"] = 0;
    func["t"] = 0;
    func["u"] = 0;
    func["v"] = 0;
    func["w"] = 0;
    func["x"] = 0;
    func["y"] = 0;
    func["z"] = 0;

    func["auto"] = 0;
    func["break"] = 0;
    func["case"] = 0;
    func["catch"] = 0;
    func["class"] = 0;
    func["const"] = 0;
    func["continue"] = 0;
    func["define"] = 0;
    func["delete"] = 0;
    func["do"] = 0;
    func["else"] = 0;
    func["endif"] = 0;
    func["extern"] = 0;
    func["false"] = 0;
    func["friend"] = 0;
    func["for"] = 0;
    func["if"] = 0;
    func["ifdef"] = 0;
    func["include"] = 0;
    func["inline"] = 0;
    func["new"] = 0;
    func["operator"] = 0;
    func["pravite"] = 0;
    func["public"] = 0;
    func["return"] = 0;
    func["sizeof"] = 0;
    func["static"] = 0;
    func["struct"] = 0;
    func["switch"] = 0;
    func["template"] = 0;
    func["this"] = 0;
    func["throw"] = 0;
    func["true"] = 0;
    func["typedef"] = 0;
    func["while"] = 0;

    func["bool"] = 0;
    func["double"] = 0;
    func["float"] = 0;
    func["int"] = 0;
    func["long"] = 0;
    func["short"] = 0;
    func["size_t"] = 0;
    func["unsigned"] = 0;
    func["void"] = 0;

    func["eight"] = 0;
    func["five"] = 0;
    func["four"] = 0;
    func["nine"] = 0;
    func["one"] = 0;
    func["seven"] = 0;
    func["six"] = 0;
    func["ten"] = 0;
    func["three"] = 0;
    func["two"] = 0;

    func["and"] = 0;
    func["apostrophe"] = 0;
    func["at"] = 0;
    func["backslash"] = 0;
    func["colon"] = 0;
    func["comma"] = 0;
    func["cut"] = 0;
    func["divide"] = 0;
    func["dollar"] = 0;
    func["dot"] = 0;
    func["equal"] = 0;
    func["exclusive_or"] = 0;
    func["hashtag"] = 0;
    func["left_big_bracket"] = 0;
    func["left_bracket"] = 0;
    func["left_square_bracket"] = 0;
    func["less"] = 0;
    func["mark"] = 0;
    func["model"] = 0;
    func["more"] = 0;
    func["multiply"] = 0;
    func["negate"] = 0;
    func["or"] = 0;
    func["plus"] = 0;
    func["question"] = 0;
    func["right_big_bracket"] = 0;
    func["right_bracket"] = 0;
    func["right_square_bracket"] = 0;
    func["semicolon"] = 0;
    func["underline"] = 0;

    // keyboard
    func["backspace"] = 1;
    func["space"] = 1;
    func["tab"] = 1;
    func["up"] = 1;
    func["down"] = 1;
    func["left"] = 1;
    func["right"] = 1;

    // special
    func["function"] = 2;
    func["string"] = 2;
    func["variable"] = 2;
}
void Writer:: signal_construct() {
    // numbers
    spec["eight"] = "8";
    spec["five"] = "5";
    spec["four"] = "4";
    spec["nine"] = "9";
    spec["one"] = "1";
    spec["seven"] = "7";
    spec["six"] = "6";
    spec["ten"] = "10";
    spec["three"] = "3";
    spec["two"] = "2";

    // signs
    spec["and"] = "&";
    spec["apostrophe"] = "'";
    spec["at"] = "@";
    spec["backslash"] = "\\";
    spec["colon"] = ":";
    spec["comma"] = ",";
    spec["cut"] = "-";
    spec["divide"] = "/";
    spec["dollar"] = "$";
    spec["dot"] = ".";
    spec["equal"] = "=";
    spec["exclusive_or"] = "^'";
    spec["hashtag"] = "#";
    spec["left_big_bracket"] = "{";
    spec["left_bracket"] = "(";
    spec["left_square_bracket"] = "[";
    spec["less"] = "<";
    spec["mark"] = "!";
    spec["model"] = "%";
    spec["more"] = ">";
    spec["multiply"] = "*";
    spec["negate"] = "~";
    spec["or"] = "|";
    spec["plus"] = "+";
    spec["question"] = "?";
    spec["right_big_bracket"] = "}";
    spec["right_bracket"] = ")";
    spec["right_square_bracket"] = "]";
    spec["semicolon"] = ";";
    spec["underline"] = "_";
}

void Writer:: num_construct() {
    numbers["one"] = 1;
    numbers["two"] = 2;
    numbers["three"] = 3;
    numbers["four"] = 4;
    numbers["five"] = 5;
    numbers["six"] = 6;
    numbers["seven"] = 7;
    numbers["eight"] = 8;
   // numbers["nine"] = 9;
   // numbers["ten"] = 10;
}

void Writer:: init() {
    mw = mwin;

    num_construct();
    mp_construct();
    signal_construct();

}

void Writer:: splitIntoVector(std::string command, std::vector<std::string> &vec) {
    vec.clear();
    unsigned long cur = 0;
    for(;;) {
        unsigned long next_pos = command.find(" ", cur);
        // std:: cout << "next_pos = " << next_pos << std:: endl;
        if(next_pos == std:: string:: npos) break;
        vec.push_back(command.substr(cur, next_pos - cur));
        // std:: cout << "putting " << cur << " " << next_pos << std:: endl;
        cur = next_pos + 1;
        if(cur >= command.size()) break;
    }
    if(cur < command.size()) {
        vec.push_back(command.substr(cur, command.size()));
    }
}

int Writer:: judgeCommandType(std:: string command) {
    if(func.count(command) == 0) return -1;
    return func[command];
}

int Writer:: getStrIndex(std::string command) {
    if(!numbers.count(command)) {
        return -1;
    }
    return numbers[command];
}
void Writer:: commandIntoAction(std:: string command) {
    to_lower_case(command);
    std:: cout << command << std:: endl;
    if(command.length() < 1) {
        return;
    }
    std:: vector<std:: string> comcc;
    splitIntoVector(command, comcc);
    for(unsigned i = 0; i < comcc.size(); ++ i) {
        int tpoc = judgeCommandType(comcc[i]);
        // std:: cout << "spliting " << comcc[i] << std:: endl;
        assert(tpoc != -1);
        switch (tpoc) {
        case 0:
            writeIntoCode(type0convert(comcc[i]));
            break;

        case 1:
            takeAction(command);
            break;

        case 2: // here need next comcc
            if(i == comcc.size() - 1) {
                // error
                writeIntoConsole(std:: string("Command Error!\n"));
                goto end_label;
            }
            int rp = getStrIndex(comcc[i + 1]);
            if(rp == -1) {
                // error
                writeIntoConsole(std:: string("Command Error!\n"));
                goto end_label;
            }
            if(comcc[i] == "function") {
                mw -> writeFunction(rp);
            } else if(comcc[i] == "string") {
                mw -> writeString(rp);
            } else if(comcc[i] == "variable") {
                mw -> writeVars(rp);
            }
            i ++;
            break;
        }
    }
    end_label:
    return;
}

void Writer:: writeIntoCode(std:: string code) {
    mw -> insertCode(code);
}

void Writer:: writeIntoConsole(std::string info) {
    mw -> printOnConsoleWON(info);
}
