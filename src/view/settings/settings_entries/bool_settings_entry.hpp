
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

#include "base_entry.hpp"
#pragma once

///GUI_Window : Objekt hlavního okna vytváří hlavní rozložení ovladacích prvků.
class BoolEntry : public EntryTemplate { 
Q_OBJECT
    QCheckBox * checkbox;
    
public slots:

    void box_toggled(){
        std::cout << "settbool" << std::endl;
        this->settings_link->setBool(this->name,checkbox->isChecked());
        //checkbox->setChecked(settings->getBool(name));
    }

public: 
  
    BoolEntry(SettingsWindowLink *settings_link,SettingsLinkAP *settings, std::string name,std::wstring description) : EntryTemplate(settings_link,settings,name,description){

        checkbox = new QCheckBox();
        checkbox->setChecked(settings->getBool(name));
        layout->addWidget(checkbox);

        
        
        connect(checkbox, SIGNAL(clicked()), this, SLOT(box_toggled()));

    };

};
