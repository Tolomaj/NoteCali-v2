
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
class WStringEntry : public EntryTemplate { 
Q_OBJECT

    QLineEdit * text;
    QBoxLayout * layout;
  
public slots:

    void changed(const QString & txt){
        std::wstring wtxt = txt.toStdWString();
        settings_link->setWString(name,wtxt);
    }

public: 
  
    WStringEntry(SettingsWindowLink *settings_link,SettingsLinkAP *settings, std::string name,std::wstring description) : EntryTemplate(settings_link,settings,name,description){

        layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight,this);

        text = new QLineEdit();
        text->setText(QString::fromStdWString(settings->getWString(name)));
        layout->addWidget(text);
        
        QLabel * label = new QLabel(QString::fromStdString(name));
        label->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
        layout->addWidget(label);
        
        connect(text, SIGNAL(textChanged(const QString &)), this, SLOT(changed(const QString &)));

    };

};
