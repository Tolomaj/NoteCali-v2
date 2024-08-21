
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

#include "../../../link/settings_link.hpp"
#include "../../../link/window_link.hpp"

#pragma once
///GUI_Window : Objekt hlavního okna vytváří hlavní rozložení ovladacích prvků.
class EntryTemplate : public QFrame {

protected: 
    std::string name;
    std::wstring description;
    SettingsWindowLink *settings_link;
    SettingsLinkAP *settings;

public: 
  
    EntryTemplate(SettingsWindowLink *settings_link,SettingsLinkAP *settings, std::string name,std::wstring description) : QFrame(){
        this->name = name;
        this->description = description;
        this->settings = settings;
        this->settings_link = settings_link;

        this->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
        //this->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);

        QPalette palet = qApp->palette();
        QString style = "background: " + palet.color(QPalette::Window).name();
        this->setStyleSheet(style);

        this->setAttribute(Qt::WA_Hover, true);
        this->setMouseTracking(true);

    };


    void leaveEvent(QEvent * event){
        settings_link->setHint("Settings Hint",L"this is place where hits and informations for settings would be shown");
        QFrame::leaveEvent(event);
    }

    void enterEvent(QEnterEvent * event){
        settings_link->setHint(name,description);
        QFrame::enterEvent(event);
    }
};
