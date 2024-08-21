
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

#pragma once

///GUI_Window : Objekt hlavního okna vytváří hlavní rozložení ovladacích prvků.
class SettingsHint : public QFrame{ 
    QLabel * hint_name;
    QLabel * hint_description;

    QBoxLayout * layout;
public: 
  
    SettingsHint() : QFrame(){
        //this->setContentsMargins(2,2,2,2);

        QPalette palet = qApp->palette();
        this->setStyleSheet("background: " + palet.color(QPalette::Window ).name());


        layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom,this);
        layout->setAlignment(Qt::AlignCenter);

        hint_name = new QLabel("Settings Hint",this);
        hint_name->setAlignment(Qt::AlignCenter);
        layout->addWidget(hint_name);

        hint_description = new QLabel(this);
        hint_description->setWordWrap(true);
        hint_description->setMinimumHeight(55);
        hint_description->setAlignment(Qt::AlignCenter);
        hint_description->setText("this is place where hits and informations for settings would be shown");
        layout->addWidget(hint_description);
    }

    //todo, thwos segmenttion fault
    void setHint(QString name, QString description){
        hint_name->setText(name);
        hint_description->setText(description);
    }

};
