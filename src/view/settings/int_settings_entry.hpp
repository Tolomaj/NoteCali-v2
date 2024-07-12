
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
#include <sstream>
#include <string>
#include <algorithm>

#include <iostream>
#include <vector>

#include "../../link/settings_link.hpp"
#include "../../link/window_link.hpp"

///GUI_Window : Objekt hlavního okna vytváří hlavní rozložení ovladacích prvků.
class IntEntry : public QFrame{ 
Q_OBJECT
    std::string name;
    SettingsWindowLink *settings_link;
    SettingsLinkAP *settings;
    
    QWidget * box;
    QLabel * label;

public slots:

    void numChanged(int i){
        std::cout << "settInt" << std::endl;
        settings_link->setInt(name,i);
        //this->setValue(settings->getInt(name));
    }

public: 
  
    IntEntry(SettingsWindowLink *settings_link,SettingsLinkAP *settings, std::string name,std::vector<int> options  = {}) : QFrame(){
        std::cout << "ero load settings: " << name << std::endl;
        this->name = name;
        this->settings = settings;
        this->settings_link = settings_link;

        this->setFrameStyle(QFrame::Panel);

        QBoxLayout * layout = new QBoxLayout(QBoxLayout::Direction::RightToLeft,this);

        label = new QLabel(QString::fromStdString(name));
        layout->addWidget(label);
        
        if(options.size() == 3){
            QSlider * sbox = new QSlider(Qt::Horizontal);
            sbox->setValue(settings->getInt(name));
            box = sbox;
        }else{
            QSpinBox * sbox = new QSpinBox();
            sbox->setValue(settings->getInt(name));
            box = sbox;
        }


        layout->addWidget(box);


        connect(box, SIGNAL(valueChanged(int)), this, SLOT(numChanged(int)));

    };

};
