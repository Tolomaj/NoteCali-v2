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

#include "window_boady.hpp"
#include "window_header.hpp"

///GUI_Window : Objekt hlavního okna vytváří hlavní rozložení ovladacích prvků.
class Window: public QMainWindow { 
public: 
    QBoxLayout * layout;
    QWidget * calculator_boady;
    QWidget * calculator_header;

    Window(QMainWindow *parent = 0){
        this->resize(250,330);

        QWidget * centralWidget = new QWidget(this);
    
        layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom,centralWidget);
        layout->setSpacing(0);
        layout->setContentsMargins(0,0,0,0);

        calculator_header = new CalcHead(this);
        layout->addWidget(calculator_header);

        calculator_boady = new CalcBody(this);
        layout->addWidget(calculator_boady);

        this->setCentralWidget(centralWidget);
        //this->setWindowFlags(Qt::FramelessWindowHint);
        //this->setAttribute(Qt::WA_TranslucentBackground);
        //this->setStyleSheet("border-radius:5px");
        this->show();

    };

};
