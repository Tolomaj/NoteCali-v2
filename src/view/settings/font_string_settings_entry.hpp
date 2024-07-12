
#include <QtGui>
#include <QApplication>
#include <QLabel>
#include <QtWidgets>
#include <QBoxLayout>
#include <QTextEdit>
#include <QSplitter>
#include <QFontMetrics>
#include <sstream>
#include <string>
#include <algorithm>
#include <QFontComboBox>

#include <iostream>
#include <vector>

#include "../../link/settings_link.hpp"
#include "../../link/window_link.hpp"

///GUI_Window : Objekt hlavního okna vytváří hlavní rozložení ovladacích prvků.
class FontStringEntry : public QFrame { 
Q_OBJECT
    std::string name;
    SettingsWindowLink *settings_link;
    SettingsLinkAP *settings;

    QFontComboBox * font;
    QBoxLayout * layout;
  
public slots:

    void changed(const QFont & font){
        std::wstring wtxt = font.family().toStdWString();
        settings_link->setWString(name,wtxt);
    }

public: 
  
    FontStringEntry(SettingsWindowLink *settings_link,SettingsLinkAP *settings, std::string name) : QFrame(){
        this->name = name;
        this->settings = settings;
        this->settings_link = settings_link;

        this->setFrameStyle(QFrame::Panel);
        this->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);

        layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight,this);

        font = new QFontComboBox();
        font->setCurrentFont(QFont(QString::fromStdWString(settings->getWString("Font")) , settings->getInt("FontSize")));
        layout->addWidget(font);
        
        QLabel * label = new QLabel(QString::fromStdString(name));
        label->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
        layout->addWidget(label);
        
        connect(font, SIGNAL(currentFontChanged(const QFont &)), this, SLOT(changed(const QFont &)));

    };

};
