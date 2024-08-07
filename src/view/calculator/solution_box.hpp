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
#include <iostream>
#include <vector>
#include <QScrollArea>


#include "../../link/debugger.hpp"
#include "../../link/math_link.hpp"
#include "solution_line.hpp"

#pragma once

class SolutionBox : public QScrollArea { 
public: 
    QBoxLayout * layout;
    SolutionLine * line;
    QWidget *parent;
    QFont * font = nullptr;
    SettingsLinkAP * settings;
    bool clickCopyable;
    bool copy_rounded;

    std::vector<SolutionLine*> lines;

    SolutionBox(SettingsLinkAP * settings,QWidget *parent = 0) : QScrollArea(parent){
        this->settings = settings;
        this->parent = parent;
        this->clickCopyable = settings->getBool("ClickToCopy");
        this->copy_rounded = settings->getBool("CopyRounded");

        layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom,this);
        layout->setAlignment(Qt::AlignTop);
        layout->setSpacing(0);
        layout->setContentsMargins(0,0,0,0);

        this->setWidgetResizable(true);

        QWidget* entryes = new QWidget();
        entryes->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        
        entryes->setLayout(layout);
        this->setWidget(entryes);

        this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    };

    void setFont(QFont * font){
        this->font = font;
        for (int i = 0; i < layout->count(); i++){
            SolutionLine * line = (SolutionLine*)(layout->itemAt(i)->widget());
            line->setFont(font);
        }  
    }

    void setCopy(bool clickCopyable,bool copyRounded){
        this->clickCopyable = clickCopyable;
        this->copy_rounded = copyRounded;
        for (size_t i = 0; i < layout->count(); i++){
            SolutionLine * line = (SolutionLine*)(layout->itemAt(i)->widget());
            line->setCopy(clickCopyable,copyRounded);
        }  
    }

    /// nastaví počet řešení
    void setCount(int i){       
        int linesNeed = i - lines.size();
        bool add = true;
        if(linesNeed == 0){ return; };
        if(linesNeed < 0){ add = false;}
        linesNeed = abs(linesNeed);

        for (size_t i = 0; i < linesNeed; i++){
            if(add){
                SolutionLine * line = new SolutionLine(this,this->clickCopyable,this->copy_rounded );
                if(font != nullptr){
                    line->setFont(font);
                }
                lines.push_back(line);
                layout->addWidget(line);
            }else{
                SolutionLine * line = lines.back();
                lines.pop_back();
                layout->removeWidget(line);
                delete line;
            }
        }  
    }

    void setWidth(int index, int height){
        if(layout->count() > index){
            SolutionLine *widget = (SolutionLine*)(layout->itemAt(index)->widget());
            if(widget == NULL){ return; }
            widget->setWidth(height);
        }
    }

    void setSolution(int index, mline * solved_line){
        if(layout->count() > index){
            SolutionLine *widget = (SolutionLine*)(layout->itemAt(index)->widget());
            if(widget == NULL){ return; }
            widget->setSolution(solved_line);
        }
    }


    void resizeEvent(QResizeEvent* event) override{
        QResizeEvent *parentEvent = new QResizeEvent(event->size(), event->oldSize());
        QApplication::postEvent(parent, parentEvent);

        QScrollArea::resizeEvent(event);
    }
};
