#include "settings_window.hpp"

#include "settings_entries/bool_settings_entry.hpp"
#include "settings_entries/int_settings_entry.hpp"
#include "settings_entries/wstring_settings_entry.hpp"
#include "settings_entries/font_string_settings_entry.hpp"
#include "settings_entries/color_string_settings_entry.hpp"

#include "settings_about.hpp"
#include "settings_page.hpp"

SettingsWindow::SettingsWindow(SettingsLinkAP *settings,SettingsWindowLink * controller,QMainWindow *parent) : QMainWindow(parent){
    this->controller = controller;
    this->settings = settings;
    this->resize(450,450);

    // set background color type
    this->setAutoFillBackground(true);
    this->setBackgroundRole(QPalette::Base);
        

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
    pageS->add_to_page(new SettingsAbout(R"(Big Thanks to you <span style="font-family: 'Segoe UI Emoji';">💕</span>)",
        R"( My name was Ondřej Gross and big thanks to you user for downloading this app.<br>
            I hope you are happy about NoteCali.<br>
            I am trying my best to keep NoteCali updated and in best shape.<br>
            If you find some bug or want to appraise my work, I'll be happy for a small email about your thoughts.<br>
            Please in email subject use word NOTECALI or NoteCali or notecali, Thanks.<br>
            <a href='mailto:vydrysekg@gmail.com?subject=NOTE_CALI_FEADBACK'>vydrysekg@gmail.com</a><br><br>
            Thanks again for giving NoteCali a chance.<br>  )" 
        ),std::string("AboutApp"));

    pageS->add_to_page(new SettingsAbout("About App",
        R"( NoteCali has a goal to be best calculator.<br>
            It trying to be:<br>
            &emsp;- Easy to use.<br>
            &emsp;- User frendly.<br>
            &emsp;- Allow work with multiple data.<br>
            &emsp;- And has advanced features mising in other calculators.<br>
            <br>
            NoteCali Web can be found here:<br>
            <a target="@system" href="https://notecali.zironet.cz/">notecali.zironet.cz</a>   )" 
        ),std::string("AboutApp"));

    pageS->add_to_page(new SettingsAbout("Credits for used librataries",
        R"( This aplication uses Sciter for creting UI.<br>
            Thanks to Andrew Fedoniouk for creting sciter <span style="font-family: 'Segoe UI Emoji';">💕</span>.<br>
            Project can be found on site:.<br>
            <a target="@system" href="https://sciter.com/">sciter.com</a>
            <br>
            <br>
            Core of this aplication runs on ttmath that do every mathematical hevy lifting.<br>
            Thanks to Tomasz Sowa for creting ttmath <span style="font-family: 'Segoe UI Emoji';">💕</span>.<br>
            Project can be found on site:.<br>
            <a target="@system" href="https://www.ttmath.org/">ttmath.org</a>
            <br>
            <br>
            Last Library used in NoteCali is CURL.<br>
            CURL works because contributors,<br>
            big thangs to them for this library <span style="font-family: 'Segoe UI Emoji';">💕</span>.<br>
            Project can be found on site:.<br>
            <a target="@system" href="https://curl.se/">curl.se</a>   )" 
        ),std::string("AboutApp"));

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
