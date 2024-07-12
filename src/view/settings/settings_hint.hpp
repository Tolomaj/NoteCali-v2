
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

///GUI_Window : Objekt hlavního okna vytváří hlavní rozložení ovladacích prvků.
class SettingsHint : public QFrame{ 
    QLabel *name;
    QLabel *description;

    QBoxLayout * layout;
public: 
  
    SettingsHint() : QFrame(){
        this->setFrameStyle(QFrame::Panel | QFrame::Raised);

        layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom,this);
        layout->setAlignment(Qt::AlignCenter);

        name = new QLabel("Settings Hint");
        name->setAlignment(Qt::AlignCenter);
        layout->addWidget(name);

        description = new QLabel();
        description->setText("this is place where hits and informations for settings would be shown");
        layout->addWidget(description);
    
    };

    void setLabel(QString name, QString description){

    }

};
