# include <iostream>
# include <QApplication>

# include "writer.h"
# include "mainwindow.h"

MainWindow *mwin;
Writer resultWriter;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindow window;
    mwin = &window;
    window.loadSpeakConfig();
    resultWriter.init();
    window.show();

    return a.exec();
}
