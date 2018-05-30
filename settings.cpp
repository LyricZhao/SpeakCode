# include <fstream>
# include <cstring>
# include <iostream>
# include <cassert>

# include "settings.h"
# include "ui_settings.h"

# define MAXLENGTH 256

settingsvalue globalSettings;

// index = 0, strings
// index = 1, variables
// index = 2, functions

settings::settings(QWidget *parent) : QDialog(parent), ui(new Ui::settings) {
    ui -> setupUi(this);

    tmpSettings = new settingsvalue(globalSettings);

    // default comboBox index = 0, strings
    curIndex = 0;
    this -> ui -> e1 -> setText(tr(tmpSettings -> strs[0].c_str()));
    this -> ui -> e2 -> setText(tr(tmpSettings -> strs[1].c_str()));
    this -> ui -> e3 -> setText(tr(tmpSettings -> strs[2].c_str()));
    this -> ui -> e4 -> setText(tr(tmpSettings -> strs[3].c_str()));
    this -> ui -> e5 -> setText(tr(tmpSettings -> strs[4].c_str()));
    this -> ui -> e6 -> setText(tr(tmpSettings -> strs[5].c_str()));
    this -> ui -> e7 -> setText(tr(tmpSettings -> strs[6].c_str()));
    this -> ui -> e8 -> setText(tr(tmpSettings -> strs[7].c_str()));

}

settings::~settings() {
    delete ui;
}

void settings::on_buttonBox_accepted() {
    // save the settings here
    globalSettings = *(this -> tmpSettings);
    globalSettings.writeIntoFile();

    // debug
    // std:: cout << "on_buttonBox_accepted" << std:: endl;
}

void processStr(char *str, std:: string &istr) {
    str += 2;
    istr = str;
}

settingsvalue:: settingsvalue() {
    // the user settings
    std:: ifstream settingsfileIn;
    settingsfileIn.open("settingsFile");

    char inputStr[MAXLENGTH];

    // strs
    for(int i = 0; i < 8; ++ i) {
        settingsfileIn.getline(inputStr, MAXLENGTH);
        processStr(inputStr, strs[i]);
    }

    // vars
    for(int i = 0; i < 8; ++ i) {
        settingsfileIn.getline(inputStr, MAXLENGTH);
        processStr(inputStr, vars[i]);
    }

    // funcs
    for(int i = 0; i < 8; ++ i) {
        settingsfileIn.getline(inputStr, MAXLENGTH);
        processStr(inputStr, funcs[i]);
    }

    settingsfileIn.close();
}

void settingsvalue:: writeIntoFile() {
    // the user settings
    std:: ofstream settingsfileOut;
    settingsfileOut.open("settingsFile");

    // strs
    for(int i = 0; i < 8; ++ i) {
        settingsfileOut << i + 1 << " " << strs[i] << std:: endl;
    }

    // vars
    for(int i = 0; i < 8; ++ i) {
        settingsfileOut << i + 1 << " " << vars[i] << std:: endl;
    }

    // funcs
    for(int i = 0; i < 8; ++ i) {
        settingsfileOut << i + 1 << " " << funcs[i] << std:: endl;
    }

    settingsfileOut.close();
}

void settings::on_comboBox_currentIndexChanged(int index) {
    // std:: cout << "on comboBox current Index Changed" << std:: endl;
    // std:: cout << index << std:: endl;

    curIndex = index;

    // to see what changed here
    std:: string *opt = NULL;
    if(index == 0) {
        opt = tmpSettings -> strs;
    } else if(index == 1) {
        opt = tmpSettings -> vars;
    } else if(index == 2) {
        opt = tmpSettings -> funcs;
    }

    assert(opt != NULL);

    // set edit line
    this -> ui -> e1 -> setText(tr(opt[0].c_str()));
    this -> ui -> e2 -> setText(tr(opt[1].c_str()));
    this -> ui -> e3 -> setText(tr(opt[2].c_str()));
    this -> ui -> e4 -> setText(tr(opt[3].c_str()));
    this -> ui -> e5 -> setText(tr(opt[4].c_str()));
    this -> ui -> e6 -> setText(tr(opt[5].c_str()));
    this -> ui -> e7 -> setText(tr(opt[6].c_str()));
    this -> ui -> e8 -> setText(tr(opt[7].c_str()));
}

// line 1
void settings::on_e1_textChanged(const QString &arg1) {
    // to see current index
    std:: string *opt = NULL;
    if(curIndex == 0){
        opt = tmpSettings -> strs;
    } else if(curIndex == 1) {
        opt = tmpSettings -> vars;
    } else if(curIndex == 2) {
        opt = tmpSettings -> funcs;
    }

    assert(opt != NULL);

    opt[0] = arg1.toUtf8().constData();
}

// line 2
void settings::on_e2_textChanged(const QString &arg1) {
    // to see current index
    std:: string *opt = NULL;
    if(curIndex == 0){
        opt = tmpSettings -> strs;
    } else if(curIndex == 1) {
        opt = tmpSettings -> vars;
    } else if(curIndex == 2) {
        opt = tmpSettings -> funcs;
    }

    assert(opt != NULL);

    opt[1] = arg1.toUtf8().constData();
}

// line 3
void settings::on_e3_textChanged(const QString &arg1) {
    // to see current index
    std:: string *opt = NULL;
    if(curIndex == 0){
        opt = tmpSettings -> strs;
    } else if(curIndex == 1) {
        opt = tmpSettings -> vars;
    } else if(curIndex == 2) {
        opt = tmpSettings -> funcs;
    }

    assert(opt != NULL);

    opt[2] = arg1.toUtf8().constData();
}

// line 4
void settings::on_e4_textChanged(const QString &arg1) {
    // to see current index
    std:: string *opt = NULL;
    if(curIndex == 0){
        opt = tmpSettings -> strs;
    } else if(curIndex == 1) {
        opt = tmpSettings -> vars;
    } else if(curIndex == 2) {
        opt = tmpSettings -> funcs;
    }

    assert(opt != NULL);

    opt[3] = arg1.toUtf8().constData();
}

// line 5
void settings::on_e5_textChanged(const QString &arg1) {
    // to see current index
    std:: string *opt = NULL;
    if(curIndex == 0){
        opt = tmpSettings -> strs;
    } else if(curIndex == 1) {
        opt = tmpSettings -> vars;
    } else if(curIndex == 2) {
        opt = tmpSettings -> funcs;
    }

    assert(opt != NULL);

    opt[4] = arg1.toUtf8().constData();
}

// line 6
void settings::on_e6_textChanged(const QString &arg1) {
    // to see current index
    std:: string *opt = NULL;
    if(curIndex == 0){
        opt = tmpSettings -> strs;
    } else if(curIndex == 1) {
        opt = tmpSettings -> vars;
    } else if(curIndex == 2) {
        opt = tmpSettings -> funcs;
    }

    assert(opt != NULL);

    opt[5] = arg1.toUtf8().constData();
}

// line 7
void settings::on_e7_textChanged(const QString &arg1) {
    // to see current index
    std:: string *opt = NULL;
    if(curIndex == 0){
        opt = tmpSettings -> strs;
    } else if(curIndex == 1) {
        opt = tmpSettings -> vars;
    } else if(curIndex == 2) {
        opt = tmpSettings -> funcs;
    }

    assert(opt != NULL);

    opt[6] = arg1.toUtf8().constData();
}

// line 8
void settings::on_e8_textChanged(const QString &arg1) {
    // to see current index
    std:: string *opt = NULL;
    if(curIndex == 0){
        opt = tmpSettings -> strs;
    } else if(curIndex == 1) {
        opt = tmpSettings -> vars;
    } else if(curIndex == 2) {
        opt = tmpSettings -> funcs;
    }

    assert(opt != NULL);

    opt[7] = arg1.toUtf8().constData();
}

