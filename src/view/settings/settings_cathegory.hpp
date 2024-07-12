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
#include <QCheckBox>
#include <QColorDialog>

#include "../../link/window_link.hpp"

#pragma once

class CathegoryPage : public QScrollArea { 
    SettingsWindowLink *settings_link;
    std::string name;
    QLayout * layout;
public: 
    CathegoryPage(SettingsWindowLink *settings_link,std::string name,QWidget *parent = 0) : QScrollArea(parent){
        this->settings_link = settings_link;
        this->name = name;

        this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        this->setWidgetResizable(true);
        this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

        layout =  new QBoxLayout(QBoxLayout::Direction::TopToBottom,this);
        layout->setAlignment(Qt::AlignTop);

        this->setWidgetResizable(true);

        QWidget* entryes = new QWidget();
        entryes->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        
        entryes->setLayout(layout);
        this->setWidget(entryes);

        layout->addWidget(new QLabel(QString::fromStdString(name),this));
    };

    std::string getName(){
        return name;
    }

    void add_to_page(QWidget * widget){
        layout->addWidget(widget);
    }

};
