#include "CCMainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    CCMainWindow window;
    window.show();
    return app.exec();
}
