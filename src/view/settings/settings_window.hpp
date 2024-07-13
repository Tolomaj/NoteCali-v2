
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

#include "settings_list.hpp"
#include "settings_cathegory.hpp"


#ifndef SETTINGS_WIN_GUARD
#define SETTINGS_WIN_GUARD

#include "settings_hint.hpp"

class CathegoryList;

///GUI_Window : Objekt hlavního okna vytváří hlavní rozložení ovladacích prvků.
class SettingsWindow: public QMainWindow { 
    CathegoryList * cathegory_list;
    QHBoxLayout * layout;
    QVBoxLayout * layout2;
    SettingsWindowLink * controller;
    SettingsLinkAP *settings;
    std::vector<CathegoryPage*> categories;
    QWidget * actual_page;
    QWidget * page_not_selected;
    SettingsHint * settings_hint;

    CathegoryPage * addCathegory(std::string cathegory_name);

public: 

    SettingsWindow(SettingsLinkAP *settings,SettingsWindowLink * controller,QMainWindow *parent = 0);

    void loadSettings(SettingsLinkGP * settingsGP);

    void reloadStyles();

    void openCathegory(std::string cathegoryName);

    void closeEvent (QCloseEvent *event){
       controller->close_settings();
    }


    // add delete

};

#endif