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


#ifndef SETTINGS_LIST_GUARD
#define SETTINGS_LIST_GUARD

#include "settings_window.hpp"

class SettingsSidePanel : public QFrame { 
Q_OBJECT
    SettingsWindow *parent;
    QBoxLayout * layout;
public slots:
    void buttonclick(){
        QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
        if (clickedButton) {
            parent->openCathegory(clickedButton->text().remove('&').toStdString());
        }
    }
    
public: 
    SettingsSidePanel(SettingsWindow *parent = 0) : QFrame(parent){
        this->parent = parent;
        
        QPalette palet = qApp->palette();
        this->setStyleSheet("background: " + palet.color(QPalette::Base).name());

        QBoxLayout * layoutA = new QBoxLayout(QBoxLayout::Direction::TopToBottom,this);
        layoutA->setAlignment(Qt::AlignHCenter);

        //create app icon
        QPixmap pixelmap("assets/icon.ico");
        QLabel * myLabel = new QLabel();
        myLabel->setPixmap(pixelmap.scaled(50,50,Qt::KeepAspectRatio));
        myLabel->setMargin(15);
        myLabel->setFixedHeight(90);
        layoutA->addWidget(myLabel);

        // layout do kterého se budou ukládat všechny kategorie které nejsou před definované
        layout = new QBoxLayout(QBoxLayout::Direction::BottomToTop);
        layoutA->addLayout(layout);

        // mezera mezi spodní a horní sekcí tlačítek
        layoutA->addItem(new QSpacerItem(0,25,QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding));

        // vytvoření 2 speciálních spodních tlačítek
        QPushButton *about_app_BTN = new QPushButton("AboutApp");
        connect( about_app_BTN, SIGNAL(clicked()), this, SLOT(buttonclick()));
        layoutA->addWidget(about_app_BTN);

        QPushButton *updates_BTN = new QPushButton("Updates");
        connect( updates_BTN, SIGNAL(clicked()), this, SLOT(buttonclick()));
        layoutA->addWidget(updates_BTN);

    };

    void addCathegoryButton(std::string cathegory_name){

        //tyto dvě kategorie jsou speciální a vytváří se pro ně čudlíky v setupu
        if(cathegory_name == "AboutApp" || cathegory_name == "Updates"){ return; }; 

        QPushButton *pb = new QPushButton(QString(cathegory_name.c_str()));
        pb->setText(QString(cathegory_name.c_str()));
        layout->addWidget(pb);
        connect( pb, SIGNAL(clicked()), this, SLOT(buttonclick()));
    }
};

#endif