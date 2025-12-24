#include "CCMainWindow.h"
#include <QtWidgets/QApplication>
#include "UserLogin.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //CCMainWindow window;
    //window.show();


    UserLogin userWindow;
    userWindow.show();
    return app.exec();
}
