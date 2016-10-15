#include "bcontroller.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName("SoundDeviceChanger");
    a.setOrganizationName("CABASoft");
    a.setOrganizationDomain("caba.gen.tr");
    a.setApplicationVersion("v1.0");

    a.setQuitOnLastWindowClosed(false);

    BController w;
    Q_UNUSED(w)

    return a.exec();
}
