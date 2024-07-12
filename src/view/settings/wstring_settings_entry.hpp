
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

#include "../../link/settings_link.hpp"
#include "../../link/window_link.hpp"

///GUI_Window : Objekt hlavního okna vytváří hlavní rozložení ovladacích prvků.
class WStringEntry : public QFrame { 
Q_OBJECT
    std::string name;
    SettingsWindowLink *settings_link;
    SettingsLinkAP *settings;

    QLineEdit * text;
    QBoxLayout * layout;
  
public slots:

    void changed(const QString & txt){
        std::wstring wtxt = txt.toStdWString();
        settings_link->setWString(name,wtxt);
    }

public: 
  
    WStringEntry(SettingsWindowLink *settings_link,SettingsLinkAP *settings, std::string name) : QFrame(){
        this->name = name;
        this->settings = settings;
        this->settings_link = settings_link;

        this->setFrameStyle(QFrame::Panel);
        this->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);

        layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight,this);

        text = new QLineEdit();
        text->setText(QString::fromStdWString(settings->getWString(name)));
        layout->addWidget(text);
        
        QLabel * label = new QLabel(QString::fromStdString(name));
        label->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
        layout->addWidget(label);
        
        //connect(this, QCheckBox::toggled, this, SLOT(toggled(int)));
        //connect(text, SIGNAL(textChanged()), this, SLOT(changed()));
        connect(text, SIGNAL(textChanged(const QString &)), this, SLOT(changed(const QString &)));

    };

};
