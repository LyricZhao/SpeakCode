# ifndef MAINWINDOW_H
# define MAINWINDOW_H

# include <string>
# include <QMainWindow>

# include "settings.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void loadSpeakConfig();
    void insertCode(const std:: string &str);
    void printOnMainCode(const std:: string &str);
    void printOnConsole(const std:: string &str);
    void printOnConsoleWON(const std:: string &str);
    void bs();
    void ml(); void mr();
    void mu(); void md();
    void writeFunction(int id);
    void writeString(int id);
    void writeVars(int id);

private slots:
    void on_aboutButton_clicked();
    void on_settingsButton_clicked();
    void on_openButton_clicked();
    void on_saveButton_clicked();
    void on_speakButton_clicked();

private:
    Ui::MainWindow *ui;
    QString curFile;
};

#endif // MAINWINDOW_H
