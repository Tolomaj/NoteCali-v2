#include "settings_window.hpp"

#include "bool_settings_entry.hpp"
#include "int_settings_entry.hpp"
#include "wstring_settings_entry.hpp"
#include "font_string_settings_entry.hpp"


CathegoryPage * SettingsWindow::addCathegory(std::string cathegory_name){
    for(int i = 0; i < categories.size(); i++){
        CathegoryPage * category = categories.at(i);
        if(category->getName() == cathegory_name){
            std::cout << "cathegory already existed" << std::endl;
            return category;
        }
    }
    cathegory_list->addCathegory(cathegory_name);
    CathegoryPage * page = new CathegoryPage(controller,cathegory_name,this);
    page->hide();
    categories.push_back(page);
    layout2->addWidget(page);

    if(actual_page == nullptr){
        page->show();
        actual_page = page;
    }
    
    return page;
}

SettingsWindow::SettingsWindow(SettingsLinkAP *settings,SettingsWindowLink * controller,QMainWindow *parent) : QMainWindow(parent){
    this->controller = controller;
    this->settings = settings;
    this->resize(450,450);

    QWidget * centralWidget = new QWidget(this);
    layout = new QHBoxLayout(centralWidget); //new QBoxLayout(QBoxLayout::Direction::LeftToRight,centralWidget);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    this->setCentralWidget(centralWidget);

    cathegory_list = new CathegoryList(this);
    cathegory_list->setFixedWidth(100);
    layout->addWidget(cathegory_list);

    actual_page = nullptr;

    layout2 = new QVBoxLayout(centralWidget);

    settings_hint = new SettingsHint();
    layout2->addWidget(settings_hint);

    layout->addLayout(layout2);

    this->reloadStyles();
    this->show();
};

void SettingsWindow::loadSettings(SettingsLinkGP * settingsGP){
    int i = 0;
    while(1) {
        SettingsEntryBool entryBool = settingsGP->getBoolEntry(i);
        i++;
        if(entryBool.name == ""){ break; }  
        CathegoryPage * page = addCathegory(entryBool.category);

        BoolEntry * entry = new BoolEntry(controller,settings,entryBool.name);
        page->add_to_page(entry);

    }

    i = 0;
    while(1) {
        SettingsEntryInt entryInt = settingsGP->getIntEntry(i);
        i++;
        if(entryInt.name == ""){ break; }
        CathegoryPage * page = addCathegory(entryInt.category);
        
        //todo few types slider a splinbox by value
        IntEntry * entry = new IntEntry(controller,settings,entryInt.name,entryInt.options);
        page->add_to_page(entry);
    }

    i = 0;
    while(1) {
        SettingsEntryWString entryWString = settingsGP->getWStringEntry(i);
        i++;
        if(entryWString.name == ""){ break; }
        CathegoryPage * page = addCathegory(entryWString.category);

        // add dropbox option

        if(entryWString.type == PLAIN){
            QWidget * entry = new WStringEntry(controller,settings,entryWString.name);
            page->add_to_page(entry);
        }else if(entryWString.type == FONT){
            QWidget * entry = new FontStringEntry(controller,settings,entryWString.name);
            page->add_to_page(entry);
        }
        

    }
}


void SettingsWindow::openCathegory(std::string cathegory_name) {
    if(actual_page != nullptr){
        actual_page->hide();
    }

    for(int i = 0; i < categories.size(); i++){
        CathegoryPage * category = categories.at(i);

        if(category->getName() == cathegory_name){
            category->show();
            actual_page = category;
            return;
        }
    }
}

void SettingsWindow::reloadStyles(){

}
