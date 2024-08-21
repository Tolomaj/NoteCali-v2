
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

#pragma once
///GUI_Window : Objekt hlavního okna vytváří hlavní rozložení ovladacích prvků.
class HelpLine : public QFrame {
    QCheckBox * checkbox;
    QBoxLayout * layout;
public: 
  
    HelpLine(QString name ,QString description) : QFrame(){

        this->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
        //this->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);

        QPalette palet = qApp->palette();
        QString style = "background: " + palet.color(QPalette::Window).name();
        this->setStyleSheet(style);

        layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight,this);

        QLabel * label = new QLabel(description);
        label->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
        layout->addWidget(label);
      
        QLabel * label2 = new QLabel(description);
        label2->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
        layout->addWidget(label2);

    };

};
