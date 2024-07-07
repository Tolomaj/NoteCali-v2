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

#include "calculator_boady.hpp"
#include "calculator_header.hpp"
#include "../../link/settings_link.hpp"
#include "../../link/math_link.hpp"
#include "../../link/window_link.hpp"


///GUI_Window : Objekt hlavního okna vytváří hlavní rozložení ovladacích prvků.
class CalculatorWindow: public QMainWindow { 
    QBoxLayout * layout;
    CalcBody * calculator_boady;
    QWidget * calculator_header = nullptr;
    SettingsLinkAP * settings;
    CalculatorWindowLink * controller;
    bool keyAlt[2] = {false,false};

public: 

    CalculatorWindow(SettingsLinkAP * settings, CalculatorWindowLink * controller){
        this->settings = settings;
        this->controller = controller;
        this->resize(250,330);

        QWidget * centralWidget = new QWidget(this);
    
        layout = new QBoxLayout(QBoxLayout::Direction::BottomToTop,centralWidget);
        layout->setSpacing(0);
        layout->setContentsMargins(0,0,0,0);
        
        calculator_boady = new CalcBody(settings,controller);
        calculator_boady->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        layout->addWidget(calculator_boady);

        this->setCentralWidget(centralWidget);
        //this->setAttribute(Qt::WA_TranslucentBackground);
        //this->setStyleSheet("border-radius:5px");

        this->reloadStyles();

        this->show();

    };

    void present(std::vector<MathSolutionLine>* solved_lines) { calculator_boady->present(solved_lines); };
    void highlite(std::vector<MathHighlite>* highlites) { calculator_boady->highlite(highlites);  };

    void reloadStyles(){
        calculator_boady->reloadStyles();

        if(settings->getBool("NativeTitleBar")){
            // if is set header, remove it
            if(calculator_header != nullptr){
                layout->removeWidget(calculator_header);
                delete calculator_header;
                calculator_header = nullptr;
            }
            // set window to have native header
            this->setWindowFlags(this->windowFlags() & ~Qt::FramelessWindowHint);
            this->show();

        }else{
            //set window as frameless
            this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint | Qt::Window | Qt::WindowSystemMenuHint);

            //if dont have custom header, create one
            if(calculator_header == nullptr){
                calculator_header = new CalcHead(controller,this);
                layout->addWidget(calculator_header);
            }
            this->show();
        }
    }

    void keyPressEvent(QKeyEvent *e) override{
        if(e->key()==Qt::Key_Alt){ keyAlt[0] = true; }
        if(e->key()==Qt::Key_AltGr){ keyAlt[1] = true; }      
        
        if(keyAlt[0] == true && keyAlt[1] == true){
            keyAlt[0] = keyAlt[1] = false;
            controller->openSettings();
        }
    }

    void keyReleaseEvent(QKeyEvent *e) override{
        if(e->key()==Qt::Key_Alt){ keyAlt[0] = false; }
        if(e->key()==Qt::Key_AltGr){ keyAlt[1] = false; }      
    }

};
