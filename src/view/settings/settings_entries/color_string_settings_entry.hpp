
#include <QtGui>
#include <QApplication>
#include <QLabel>
#include <QtWidgets>
#include <QBoxLayout>
#include <QTextEdit>
#include <QSplitter>
#include <QFontMetrics>
#include <sstream>
#include <string>
#include <algorithm>
#include <QFontComboBox>

#include <iostream>
#include <vector>

#include "base_entry.hpp"
#pragma once

///GUI_Window : Objekt hlavního okna vytváří hlavní rozložení ovladacích prvků.
class ColorStringEntry : public EntryTemplate { 
Q_OBJECT
    QFontComboBox * font;

    QPushButton *pb;
  
public slots:

    void click(){

        QColor color = QColorDialog::getColor(QColor(QString::fromStdWString(settings->getWString(this->name))), this,"Pick Color");

        settings_link->setWString(name,color.name().toStdWString());
        pb->setStyleSheet("background-color: " + color.name() + " ;");
    }

public: 
  
    ColorStringEntry(SettingsWindowLink *settings_link,SettingsLinkAP *settings, std::string name,std::wstring description) : EntryTemplate(settings_link,settings,name,description){

        pb = new QPushButton("color");
        pb->setStyleSheet("background-color: " + QString::fromStdWString(settings->getWString(name)) + " ;");
        pb->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
        std::cout << ("background-color: " + QString::fromStdWString(settings->getWString(name)) + " ;").toStdString() << std::endl;
        layout->addWidget(pb);
        connect( pb, SIGNAL(clicked()), this, SLOT(click()));
    
    };

};
