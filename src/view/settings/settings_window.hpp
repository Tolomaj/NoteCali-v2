
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
#include "../../link/window_link.hpp"
#include "../../link/settings_link.hpp"

#include "settings_sidepanel.hpp"
#include "settings_cathegory.hpp"

#include "settings_hint.hpp"
#include "settings_page.hpp"

#ifndef SETTINGS_WIN_GUARD
#define SETTINGS_WIN_GUARD



//predefine used classes
class CathegoryList;
class SettingsSidePanel;

///GUI_Window : Objekt hlavního okna vytváří hlavní rozložení ovladacích prvků.
class SettingsWindow: public QMainWindow { 
    SettingsSidePanel * cathegory_list;
    QHBoxLayout * layout;
    SettingsWindowLink * controller;
    SettingsLinkAP *settings;

public: 
    SettingsPage * pageS;

    SettingsWindow(SettingsLinkAP *settings,SettingsWindowLink * controller,QMainWindow *parent = 0);

    void loadSettings(SettingsLinkGP * settingsGP);

    void reloadStyles();

    void openCathegory(std::string cathegoryName);

    void setHint(std::string name, std::wstring description);

    void closeEvent (QCloseEvent *event){
       controller->close_settings();
    }


    // add delete

};

#endif