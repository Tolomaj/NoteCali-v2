
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
#include <sstream>
#include <string>
#include <algorithm>

#include <iostream>
#include <vector>

#include "../../link/settings_link.hpp"
#include "../../link/window_link.hpp"

///GUI_Window : Objekt hlavního okna vytváří hlavní rozložení ovladacích prvků.
class BoolEntry : public QFrame { 
Q_OBJECT
    std::string name;
    SettingsWindowLink *settings_link;
    SettingsLinkAP *settings;

    QCheckBox * checkbox;
    QBoxLayout * layout;
  
public slots:

    void box_toggled(){
        std::cout << "settbool" << std::endl;
        settings_link->setBool(name,checkbox->isChecked());
        //checkbox->setChecked(settings->getBool(name));
    }

public: 
  
    BoolEntry(SettingsWindowLink *settings_link,SettingsLinkAP *settings, std::string name) : QFrame(){
        this->name = name;
        this->settings = settings;
        this->settings_link = settings_link;

        this->setFrameStyle(QFrame::Panel);
        this->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);

        layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight,this);

        checkbox = new QCheckBox();
        checkbox->setChecked(settings->getBool(name));
        layout->addWidget(checkbox);
        
        QLabel * label = new QLabel(QString::fromStdString(name));
        label->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
        layout->addWidget(label);
        
        //connect(this, QCheckBox::toggled, this, SLOT(toggled(int)));
        connect(checkbox, SIGNAL(clicked()), this, SLOT(box_toggled()));

    };

};
