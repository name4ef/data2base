#include "application.h"
#include "dialog.h"

int main(int argc, char *argv[])
{
    Application a(argc, argv);
    Dialog d;
    d.setWindowTitle(argv[0]);
    d.show();
    return a.exec();
}
