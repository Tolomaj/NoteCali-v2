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
    QLayout * settings_widget_list;
    bool has_hint;
public: 
    CathegoryPage(SettingsWindowLink *settings_link,std::string name,QWidget *parent = 0 , bool has_hint = true) : QScrollArea(parent){
        this->settings_link = settings_link;
        this->name = name;
        this->has_hint = has_hint;

        this->setFrameStyle(QFrame::NoFrame);

        // set background color type
        //QPalette palet = qApp->palette();
        //this->setStyleSheet("background: " + palet.color(QPalette::AlternateBase).name());
        
        // set widget behavior
        this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        this->setWidgetResizable(true);
        this->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        this->setMinimumHeight(20);

        // list for settings widgets
        settings_widget_list = new QBoxLayout(QBoxLayout::Direction::TopToBottom,this);
        settings_widget_list->setAlignment(Qt::AlignTop);

        QWidget* entryes = new QWidget();
        entryes->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        entryes->setLayout(settings_widget_list);
        this->setWidget(entryes);
    };

    bool hasHint(){
        return has_hint;
    }

    void setHint(bool has_hint){
        this->has_hint = has_hint;
    }

    std::string getName(){
        return name;
    }

    void add_to_page(QWidget * widget){
        settings_widget_list->addWidget(widget);
    }

};
