#include <QtGui>
#include <QApplication>
#include <QLabel>
#include <QtWidgets>
#include <QBoxLayout>
#include <QTextEdit>
#include <QSplitter>
#include <QTextBlock>
#include <QSpacerItem>
#include <QTextDocument>
#include <QFontMetrics>
#include <sstream>
#include <string>
#include <algorithm>

#include "settings_hint.hpp"

#include "settings_cathegory.hpp"

#include "settings_entries/bool_settings_entry.hpp"
#include "settings_entries/int_settings_entry.hpp"
#include "settings_entries/wstring_settings_entry.hpp"
#include "settings_entries/font_string_settings_entry.hpp"
#include "settings_entries/color_string_settings_entry.hpp"
#include "settings_entries/settings_help_line.hpp"

#pragma once

//todo delete this
struct SettingsTextEntry{ std::string text; std::string category;}; 


class SettingsPage: public QFrame { 
    SettingsHint * settings_hint;
    std::vector<CathegoryPage*> page_list;
    SettingsWindowLink * settings_link;
    SettingsLinkAP *settingsAP;
    QWidget * actual_page = nullptr; // aktuálně zobrazené stránka s nastavením
    QBoxLayout * pagesLayout; // otázkou jhestli je potřeba iterovatelné pole Cathegory page když je tu toto
    CathegoryPage * help_page = nullptr; //zrychlí populování help stránky

    CathegoryPage * add_cathegory(std::string cathegory_name){
    // najdeme jestli kategorie už neexistuje pokud ano vrátí jen odkaz
        for(int i = 0; i < page_list.size(); i++){
            CathegoryPage * category = page_list.at(i);
            if(category->getName() == cathegory_name){
                std::cout << "cathegory already existed" << std::endl;
                return category;
            }
        }
        CathegoryPage * page = new CathegoryPage(settings_link,cathegory_name,this,false);
        page->hide();
        pagesLayout->addWidget(page);
        page_list.push_back(page);

        if(actual_page == nullptr){
            page->show();
            actual_page = page;
        }
        
        return page;
    }

public: 
    SettingsPage(SettingsWindowLink *settings_link,SettingsLinkAP *settingsAP,QWidget *parent = 0) : QFrame(parent){
        this->settings_link = settings_link;
        this->settingsAP = settingsAP;
        
        this->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        QPalette palet = qApp->palette();
        this->setStyleSheet("background: " + palet.color(QPalette::AlternateBase).name());
    
        pagesLayout = new QBoxLayout(QBoxLayout::Direction::TopToBottom,this);

        settings_hint = new SettingsHint();
        pagesLayout->addWidget(settings_hint);


    };

    std::string get_cathegory_name(int i){
        if(i >= page_list.size()){
            return "";
        };
        return page_list.at(i)->getName();
    }
    

    // open page
    void open_page(std::string cathegory_name){
        actual_page->hide();
        for(auto page : page_list){
            if ( page->getName() == cathegory_name){
                actual_page = page;
                page->show();

                if(page->hasHint()){
                    settings_hint->show();
                }else{
                    settings_hint->hide();
                }

                break;
            }
        }
    }

    void add_to_page(SettingsEntryBool option){ //also create cathegory if not exist
        CathegoryPage * page = this->add_cathegory(option.category);
        BoolEntry * entry = new BoolEntry(settings_link,settingsAP,option.name,option.desription);
        page->add_to_page(entry);

        // pokud alespoň jedna možnost na stránce má hint tak nastaví stránku jako že má hint
        if(option.desription != L""){ page->setHint(true); }
    }

    void add_to_page(SettingsEntryInt option){ //also create cathegory if not exist
        CathegoryPage * page = this->add_cathegory(option.category);
        //todo few types slider a splinbox by value
        IntEntry * entry = new IntEntry(settings_link,settingsAP,option.name,option.desription,option.options);
        page->add_to_page(entry);

        // pokud alespoň jedna možnost na stránce má hint tak nastaví stránku jako že má hint
        if(option.desription != L""){ page->setHint(true); }
    }

    void add_to_page(SettingsEntryWString option){
        CathegoryPage * page = this->add_cathegory(option.category);
        // add dropbox option
        QWidget * entry;

        switch (option.type){
            case PLAIN:
                entry = new WStringEntry(settings_link,settingsAP,option.name,option.desription);
                break;
            case FONT:
                entry = new FontStringEntry(settings_link,settingsAP,option.name,option.desription);
                break;
            case COLOR:
                entry = new ColorStringEntry(settings_link,settingsAP,option.name,option.desription); 
                break;
            default:
                return;
        }
        page->add_to_page(entry); 

        // pokud alespoň jedna možnost na stránce má hint tak nastaví stránku jako že má hint
        if(option.desription != L""){ page->setHint(true); } 
    }

    void add_to_page(SettingsTextEntry textEntry){
        CathegoryPage * page = this->add_cathegory(textEntry.category);
        QLabel * entry = new QLabel(QString::fromStdString(textEntry.text));
        page->add_to_page(entry);
    }

    void add_help_info(QString name, QString description){
        if(help_page == nullptr){
            help_page = this->add_cathegory("Help");
        }

        help_page->add_to_page(new HelpLine(name,description));
    }

    void setHint(std::string name, std::wstring description){
        settings_hint->setHint(QString::fromStdString(name),QString::fromStdWString(description));
    }

};