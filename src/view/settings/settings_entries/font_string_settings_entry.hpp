
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
class FontStringEntry : public EntryTemplate { 
Q_OBJECT
    QFontComboBox * font;
  
public slots:

    void changed(const QFont & font){
        std::wstring wtxt = font.family().toStdWString();
        std::wcout << L"font changed: " << wtxt << std::endl;
        settings_link->setWString(name,wtxt);
        std::wcout << L"font changed ende: " << wtxt << std::endl;
    }

public: 
  
    FontStringEntry(SettingsWindowLink *settings_link,SettingsLinkAP *settings, std::string name,std::wstring description) : EntryTemplate(settings_link,settings,name,description){

        font = new QFontComboBox();
        font->setCurrentFont(QFont(QString::fromStdWString(settings->getWString("Font")) , settings->getInt("FontSize")));
        font->setContentsMargins(0,0,0,0);
        layout->addWidget(font);
 
        connect(font, SIGNAL(currentFontChanged(const QFont &)), this, SLOT(changed(const QFont &)));

    };

};
