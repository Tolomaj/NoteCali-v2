#include "settings_window.hpp"

#include "settings_entries/bool_settings_entry.hpp"
#include "settings_entries/int_settings_entry.hpp"
#include "settings_entries/wstring_settings_entry.hpp"
#include "settings_entries/font_string_settings_entry.hpp"
#include "settings_entries/color_string_settings_entry.hpp"

#include "settings_page.hpp"

SettingsWindow::SettingsWindow(SettingsLinkAP *settings,SettingsWindowLink * controller,QMainWindow *parent) : QMainWindow(parent){
    this->controller = controller;
    this->settings = settings;
    this->resize(450,450);

    // set background color type
    QPalette palet = qApp->palette();
    this->setStyleSheet("background: " + palet.color(QPalette::Base).name());
        

    QWidget * centralWidget = new QWidget(this);
    layout = new QHBoxLayout(centralWidget); //new QBoxLayout(QBoxLayout::Direction::LeftToRight,centralWidget);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    this->setCentralWidget(centralWidget);

    cathegory_list = new SettingsSidePanel(this);
    cathegory_list->setFixedWidth(100);
    layout->addWidget(cathegory_list);

    /// testting area
    pageS = new SettingsPage(controller,settings,this);
    layout->addWidget(pageS);

    // create help page
    pageS->add_help_info("test","text");
    // create variables page
    pageS->add_to_page((SettingsTextEntry){"This is unfinished Variables page","Variables"});
    // create AboutApp page
    pageS->add_to_page((SettingsTextEntry){"This is unfinished about app page","AboutApp"});
    // create Updates page
    pageS->add_to_page((SettingsTextEntry){"This is unfinished Updates page","Updates"});

    this->reloadStyles();
    this->show();
};

void SettingsWindow::loadSettings(SettingsLinkGP * settingsGP){
    int i = 0;
    while(1) {
        SettingsEntryBool entryBool = settingsGP->getBoolEntry(i);        
        if(entryBool.name == ""){ break; } 
        i++;

        pageS->add_to_page(entryBool);
    }

    i = 0;
    while(1) {
        SettingsEntryInt entryInt = settingsGP->getIntEntry(i);
        if(entryInt.name == ""){ break; }
        i++;

        pageS->add_to_page(entryInt);
    }

    i = 0;
    while(1) {
        SettingsEntryWString entryWString = settingsGP->getWStringEntry(i);
        if(entryWString.name == ""){ break; }
        i++;

        pageS->add_to_page(entryWString);
    }

    i = 0;
    while(1) {
        std::string name = pageS->get_cathegory_name(i);
        if(name == ""){ break; }
        i++;

        cathegory_list->addCathegoryButton(name);
    } 

}

void SettingsWindow::setHint(std::string name, std::wstring description){
    pageS->setHint(name,description);
}

void SettingsWindow::openCathegory(std::string cathegory_name) {
    this->pageS->open_page(cathegory_name);
}

void SettingsWindow::reloadStyles(){

}
