#include <QtGui>
#include <QApplication>
#include <QLabel>
#include <QtWidgets>
#include <QBoxLayout>
#include <QTextEdit>
#include <QSplitter>
#include <QTextBlock>
#include <QTextDocument>
#include <QFontMetrics>
#include <QDebug>
#include <iostream>


#define DEBUG 2

#include "link/debugger.hpp"
#include "link/math_link.hpp"
#include "model/settings/settings.hpp"

#include "controler/controller.hpp"


int main(int argc, char **argv) {
    dbgInfo("App Starting");
    QApplication app(argc, argv);

    Settings * settings = new Settings("setings.ini");

    /* test area */

    settings->createBoolEntry("NativeTitleBar","Style",false);
    settings->createBoolEntry("FloatingDivider","Style",false);
    settings->createBoolEntry("ss","tst",false);

    settings->createWStringEntry("ss","tst",L"one",{L"one",L"two"});

    settings->createWStringEntry("ss","tsta",L"helo");

    settings->setBool("NativeTitleBar",false);



    Controller * controller = new Controller(settings);


    return app.exec(); 
}