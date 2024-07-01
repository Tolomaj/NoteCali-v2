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

#include "settings_list.hpp"
#include "../../link/window_link.hpp"

///GUI_Window : Objekt hlavního okna vytváří hlavní rozložení ovladacích prvků.
class SettingsWindow: public QMainWindow { 
    CathegoryList * cathegory_list;
    QLayout * layout;
    SettingsWindowLink * controller;
public: 

    SettingsWindow(SettingsWindowLink * controller,QMainWindow *parent = 0){
        this->controller = controller;
        this->resize(450,450);

        QWidget * centralWidget = new QWidget(this);
        QLayout * layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight,centralWidget);
        this->setCentralWidget(centralWidget);

        layout->setSpacing(0);
        layout->setContentsMargins(0,0,0,0);


        cathegory_list = new CathegoryList();
        cathegory_list->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
        layout->addWidget(cathegory_list);

        layout->addWidget(new QSplitter());

        layout->addWidget(new QLabel("helo "));

        
        this->reloadStyles();
        this->show();
    };


    void reloadStyles(){

    }


    void showCategory(std::string cathegory){
        
    }

};
