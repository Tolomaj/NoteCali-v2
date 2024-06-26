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

#include "link/link.hpp"
#include "gui/window.hpp"

int main(int argc, char **argv) {
    dbgInfo("App Starting");
    QApplication app(argc, argv);

    Window *main_win = new Window;

    return app.exec(); 
}