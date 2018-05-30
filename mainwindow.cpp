# include <QString>
# include <QTextCursor>
# include <QFileDialog>

# include <fstream>
# include <iostream>

# include "mainwindow.h"
# include "ui_mainwindow.h"

# include "about.h"
# include "settings.h"
# include "spk_core.h"

extern settingsvalue globalSettings;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui -> setupUi(this);

    // no current file
    curFile = "";

    // sphinx core preparation
    // int ret = speak_init();
    // assert(ret == 1);
}

MainWindow::~MainWindow() {
    delete ui;

    // sphinx core
    int ret = speak_exit();
    assert(ret == 1);
}

void MainWindow:: loadSpeakConfig() {
    // sphinx core preparation
    int ret = speak_init();
    assert(ret == 1);
    return;
}

void MainWindow::on_aboutButton_clicked() {
    // status bar
    this -> ui -> statusBar -> showMessage("The related information about this software.");

    // about dialog
    about *aboutDialog = new about;
    aboutDialog -> show();

}

void MainWindow::on_settingsButton_clicked() {
    // status bar
    this -> ui -> statusBar -> showMessage("The settings");

    // setting dialog
    settings *settingsDialog = new settings;
    settingsDialog -> show();
}

# define READ_BUFFER_SIZE 256

void MainWindow::on_openButton_clicked() {
    // open dialog
    QString fileName = QFileDialog:: getOpenFileName(this, "Open File", "", "");
    // std:: cout << fileName.toUtf8().constData() << std:: endl;

    // cancel dialog
    if(fileName.size() == 0) {
        return;
    }

    // read context & set context
    std:: ifstream fileInput;
    fileInput.open(fileName.toUtf8().constData());

    this -> ui -> mainCode -> clear();

    char readBuffer[READ_BUFFER_SIZE];
    while(!fileInput.eof()) {
        fileInput.getline(readBuffer, READ_BUFFER_SIZE, '\n');
        this -> ui -> mainCode -> append(tr(readBuffer));
    }

    fileInput.close();

    // set the current file
    this -> curFile = fileName;

    // status bar
    this -> ui -> statusBar -> showMessage("File has opened");
}

void MainWindow::on_saveButton_clicked() {
   // get current file
   if(this -> curFile.size() == 0) {
        curFile = QFileDialog:: getSaveFileName(this, "Save File", "", "");
   //     std:: cout << curFile.toUtf8().constData() << std:: endl;
   }

   // get context of the code
   QString context = this -> ui -> mainCode -> toPlainText();

   // write data
   std:: ofstream fileOutput;
   fileOutput.open(curFile.toUtf8().constData());
   fileOutput << context.toUtf8().constData();

   fileOutput.close();

   // status bar
   this -> ui -> statusBar -> showMessage("File has saved");
}

void MainWindow::on_speakButton_clicked() {
    // set button inactive
    this -> ui -> speakButton -> setEnabled(false);

    // core
    recognize_from_microphone();

    // set button active
    this -> ui -> speakButton -> setEnabled(true);
}

void MainWindow::printOnMainCode(const std::string &str) {
    this -> ui -> mainCode -> append(tr(str.c_str()));
}

void MainWindow:: insertCode(const std:: string &str) {
    this -> ui -> mainCode -> insertPlainText(tr(str.c_str()));
}

void MainWindow:: printOnConsole(const std::string &str) {
    this -> ui -> consoleOutput -> append(tr(str.c_str()));
}

void MainWindow:: printOnConsoleWON(const std:: string &str) {
    this -> ui -> consoleOutput -> insertPlainText(tr(str.c_str()));
    this -> ui -> consoleOutput -> moveCursor(QTextCursor:: End);
}

void MainWindow:: bs() {
    QTextCursor cursor = this -> ui -> mainCode -> textCursor();
    cursor.deletePreviousChar();
    ui -> mainCode -> setTextCursor(cursor);
}

void MainWindow:: ml() {
    this -> ui -> mainCode -> moveCursor(QTextCursor:: Left);
}

void MainWindow:: mr() {
    this -> ui -> mainCode -> moveCursor(QTextCursor:: Right);
}

void MainWindow:: mu() {
    this -> ui -> mainCode -> moveCursor(QTextCursor:: Up);
}

void MainWindow:: md() {
    this -> ui -> mainCode -> moveCursor(QTextCursor:: Down);
}

void MainWindow:: writeFunction(int id) {
    assert((1 <= id) && (id < 8));
    insertCode(globalSettings.funcs[id - 1]);
}

void MainWindow:: writeString(int id) {
    assert((1 <= id) && (id < 8));
    insertCode(globalSettings.strs[id - 1]);
}

void MainWindow:: writeVars(int id) {
    assert((1 <= id) && (id < 8));
    insertCode(globalSettings.vars[id - 1]);
}
