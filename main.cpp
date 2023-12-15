/*
Author: Emma Luk
Github: emma-luky
Assignment: A6: Qt Simon Game
Creative Element: My creative element is starting the sequence off
with three moves, additionally having three buttons(red, blue, and green)
*/

#include "view.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model m;
    View w(m);
    w.show();
    return a.exec();
}
