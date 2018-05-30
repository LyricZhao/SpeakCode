#ifndef WRITER_H
#define WRITER_H

# include <map>
# include <string>
# include <vector>

# include "mainwindow.h"

class Writer {
private:
    MainWindow *mw;
    std:: map<std:: string, int> numbers;
    std:: map<std:: string, int> func;
    std:: map<std:: string, std:: string> spec;
    void num_construct();
    void mp_construct();
    void signal_construct();
    void takeAction(std:: string command);
    int getStrIndex(std:: string command);
    std:: string type0convert(std:: string command);
public:
    void init();
    int judgeCommandType(std:: string command);
    void splitIntoVector(std:: string command, std:: vector<std:: string> &vec);
    void commandIntoAction(std:: string command);
    void writeIntoCode(std:: string code);
    void writeIntoConsole(std:: string info);
};

#endif // WRITER_H
