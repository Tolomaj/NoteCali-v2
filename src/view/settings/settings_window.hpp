
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

#include <iostream>
#include <vector>
#include "../../link/window_link.hpp"
#include "../../link/settings_link.hpp"

#include "settings_list.hpp"
#include "settings_cathegory.hpp"



#ifndef SETTINGS_WIN_GUARD
#define SETTINGS_WIN_GUARD

class CathegoryList;

///GUI_Window : Objekt hlavního okna vytváří hlavní rozložení ovladacích prvků.
class SettingsWindow: public QMainWindow { 
    CathegoryList * cathegory_list;
    QLayout * layout;
    SettingsWindowLink * controller;
    SettingsLinkAP *settings;
    std::vector<CathegoryPage*> categories;
    QWidget * actual_page;
    QWidget * page_not_selected;

    CathegoryPage * addCathegory(std::string cathegory_name);

public: 

    SettingsWindow(SettingsLinkAP *settings,SettingsWindowLink * controller,QMainWindow *parent = 0);

    void loadSettings(SettingsLinkGP * settingsGP);

    void reloadStyles();

    void openCathegory(std::string cathegoryName);

    // add delete

};

#endif