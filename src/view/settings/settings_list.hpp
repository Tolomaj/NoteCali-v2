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


#ifndef SETTINGS_LIST_GUARD
#define SETTINGS_LIST_GUARD

#include "settings_window.hpp"

class CathegoryList : public QFrame { 
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
    CathegoryList(SettingsWindow *parent = 0) : QFrame(parent){
        this->parent = parent;
        this->setFrameStyle(QFrame::Panel | QFrame::Sunken);

        QBoxLayout * layoutA = new QBoxLayout(QBoxLayout::Direction::TopToBottom,this);
        layoutA->setAlignment(Qt::AlignHCenter);


            

        QPixmap pixelmap("assets/icon.ico");

        QLabel * myLabel = new QLabel();
        myLabel->setPixmap(pixelmap.scaled(50,50,Qt::KeepAspectRatio));
        myLabel->setMargin(20);
        layoutA->addWidget(myLabel);


        layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom,this);
        layoutA->addLayout(layout);

        layoutA->addWidget(new QLabel("helo")); // todo změny verzí
        

    };

    void addCathegory(std::string cathegory_name){
        QPushButton *pb = new QPushButton(QString(cathegory_name.c_str()));
        pb->setText(QString(cathegory_name.c_str()));
        layout->addWidget(pb);
        connect( pb, SIGNAL(clicked()), this, SLOT(buttonclick()));
    }
};

#endif