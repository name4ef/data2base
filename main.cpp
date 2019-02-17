#include "dialog.h"
#include "application.h"

int main(int argc, char *argv[])
{
    Application a(argc, argv);
    Dialog w;
    w.show();

    return a.exec();
}
