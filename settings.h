# ifndef SETTINGS_H
# define SETTINGS_H

# include <string>
# include <vector>
# include <QDialog>

namespace Ui {
    class settings;
}

class settingsvalue {
public:
    std:: string strs[8];
    std:: string vars[8];
    std:: string funcs[8];
    settingsvalue();
    void writeIntoFile();
};

class settings : public QDialog
{
    Q_OBJECT

public:
    explicit settings(QWidget *parent = 0);
    ~settings();

private slots:
    void on_buttonBox_accepted();
    void on_comboBox_currentIndexChanged(int index);
    void on_e1_textChanged(const QString &arg1);
    void on_e2_textChanged(const QString &arg1);
    void on_e3_textChanged(const QString &arg1);
    void on_e4_textChanged(const QString &arg1);
    void on_e5_textChanged(const QString &arg1);
    void on_e6_textChanged(const QString &arg1);
    void on_e7_textChanged(const QString &arg1);
    void on_e8_textChanged(const QString &arg1);

private:
    int curIndex;
    Ui:: settings *ui;
    settingsvalue *tmpSettings;
};


#endif // SETTINGS_H
