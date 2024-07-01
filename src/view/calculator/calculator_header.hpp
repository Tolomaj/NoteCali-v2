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
#include <QString>
#include <QDebug>

#include <iostream>

#include "../../link/window_link.hpp"
#include "../../link/debugger.hpp"

class HeaderButton : public QPushButton{
public:
    HeaderButton(QString icon) : QPushButton(){
        this->setIcon(QIcon(icon));
        this->setIconSize(QSize(25, 25));
        this->setFixedSize(30,30);
        this->setFlat(true);
        this->setContentsMargins(0,0,0,0);
    }
};

///GUI_Window : Objekt hlavního okna vytváří hlavní rozložení ovladacích prvků.
class CalcHead : public QWidget { 
Q_OBJECT
    QBoxLayout * layout;
    QMainWindow *parentWindow;
    CalculatorWindowLink * controller;
    QPushButton * pin;
    bool on_top = false;

public slots:
    void close_clicked(){      controller->close_calculator(); }
    void settings_clicked(){   controller->openSettings();     }
    void minimalise_clicked(){ parentWindow->setWindowState(Qt::WindowMinimized); }

    void pin_clicked(){ 
        if(on_top){
            pin->setIcon(QIcon("assets/pin.svg"));
            parentWindow->setWindowFlag(Qt::WindowStaysOnTopHint, false);
        }else{
            pin->setIcon(QIcon("assets/unpin.svg"));
            parentWindow->setWindowFlag(Qt::WindowStaysOnTopHint, true);
        }
        on_top = !on_top;
        parentWindow->show();
    }


public: 
  
    CalcHead(CalculatorWindowLink * controller,QMainWindow *parentWindow ) : QWidget(parentWindow){
        this->parentWindow = parentWindow;
        this->controller = controller;
        layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight,this);
        layout->setSpacing(0);
        layout->setContentsMargins(0,0,0,0);


        QPushButton * menu = new HeaderButton("assets/menu.svg");
        connect(&(*menu), SIGNAL(clicked()), this, SLOT(settings_clicked()));
        layout->addWidget(menu);

        pin = new HeaderButton("assets/pin.svg");
        connect(&(*pin), SIGNAL(clicked()), this, SLOT(pin_clicked()));
        layout->addWidget(pin);

        QLabel * name = new QLabel("Notecali");
        name->setAlignment(Qt::AlignCenter);
        layout->addWidget(name);

        QPushButton * minimalise = new HeaderButton("assets/minimalize.svg");
        connect(&(*minimalise), SIGNAL(clicked()), this, SLOT(minimalise_clicked()));
        layout->addWidget(minimalise);

        QPushButton * close = new HeaderButton("assets/close.svg");
        connect(&(*close), SIGNAL(clicked()), this, SLOT(close_clicked()));
        layout->addWidget(close);

    };

};
