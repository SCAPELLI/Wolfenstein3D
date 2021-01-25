#include <QtWidgets/QApplication>
#include <ScreenManager.h>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ScreenManager screenManager;
    screenManager.show();
    return app.exec();
}
