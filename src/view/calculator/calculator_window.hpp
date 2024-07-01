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
    QWidget * calculator_boady;
    QWidget * calculator_header = nullptr;
    SettingsLinkAP * settings;
    CalculatorWindowLink * controller;
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
        layout->addWidget(calculator_boady);

        this->setCentralWidget(centralWidget);
        //this->setWindowFlags(Qt::FramelessWindowHint);
        //this->setAttribute(Qt::WA_TranslucentBackground);
        //this->setStyleSheet("border-radius:5px");

        this->reloadStyles();

        this->show();

    };

    void present(std::vector<MathSolutionLine>* solved_lines) {}; //todo
    void highlite(std::vector<MathHighlite>* highlites) {}; //todo

    void reloadStyles(){
        if(settings->getBool("NativeTitleBar")){
            // if is set header, remove it
            if(calculator_header != nullptr){
                layout->removeWidget(calculator_header);
                delete calculator_header;
                calculator_header = nullptr;
            }
            // set window to have native header
            this->setWindowFlags(this->windowFlags() & ~Qt::FramelessWindowHint);

        }else{
            //set window as frameless
            this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);

            //if dont have custom header, create one
            if(calculator_header == nullptr){
                calculator_header = new CalcHead(controller,this);
                layout->addWidget(calculator_header);
            }
        }
    }

};
