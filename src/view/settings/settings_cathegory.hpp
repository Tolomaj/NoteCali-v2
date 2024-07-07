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
#include <QCheckBox>
#include <QColorDialog>

#include "../../link/window_link.hpp"

#pragma once

class CathegoryPage : public QWidget { 
    SettingsWindowLink *settings_link;
    std::string name;
    QLayout * layout;
public: 
    CathegoryPage(SettingsWindowLink *settings_link,std::string name){
        this->settings_link = settings_link;
        this->name = name;
        layout =  new QBoxLayout(QBoxLayout::Direction::TopToBottom);
        this->setLayout(layout);
        this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        layout->addWidget(new QLabel(QString::fromStdString(name),this));
    };

    std::string getName(){
        return name;
    }

    void add_to_page(QWidget * widget){
        layout->addWidget(widget);
    }

};
