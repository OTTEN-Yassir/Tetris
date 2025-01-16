#include <iostream>
#include "gameoptions.h"
#include <QApplication>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameOptions gameOptions;
    gameOptions.show();

    return a.exec();
}
