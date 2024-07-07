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
#include <QDebug>
#include <iostream>
#include <vector>
#include <QScrollArea>

#include "../../link/math_link.hpp"

#pragma once

class SolutionLine : public QWidget{
    QBoxLayout * layout;
    QLabel * text;
    QLabel * variable;
    QLabel * error;
    QLabel * information;
public:
    SolutionLine() : QWidget(){
        layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight,this);
        layout->setSpacing(0);
        layout->setContentsMargins(0,0,0,0);

        text = new QLabel("AA");
        text->setAlignment(Qt::AlignCenter);
        layout->addWidget(text);

        // todo crete as images
        variable = new QLabel("📝");
            variable->hide();
            layout->addWidget(variable);
        error = new QLabel("⚠️");
            error->hide();
            layout->addWidget(error);
        information = new QLabel("ℹ️");
            information->hide();
            layout->addWidget(information);

        this->setContentsMargins(2,0,2,0);
    }

    void setWidth(int size){
       text->setFixedHeight(size);
    }

    void setSolution(MathSolutionLine * solution){
        //todo inplement whole solutions
        std::cout << "set solutionn: " << solution->solution << std::endl;
        text->setText(QString::fromStdString(solution->solution));

        solution->isVariable ? variable->show() :variable->hide();
        solution->isError ? error->show() : error->hide();
        solution->isInformation ? information->show() : information->hide();
    }

};

class SolutionBox : public QScrollArea { 
public: 
    QBoxLayout * layout;
    SolutionLine * line;
    QWidget *parent;

    std::vector<SolutionLine*> lines;

    SolutionBox(QWidget *parent = 0) : QScrollArea(parent){

        this->parent = parent;

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



        /*QScrollArea* scrollArea = new QScrollArea;
        scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
        scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAsNeeded );
        scrollArea->setWidgetResizable( true );
        scrollArea->setWidget( this );

        scrollArea->setLayout(layout);
        scrollArea->setWidget(this);*/

    };

    /// nastaví počet řešení
    void setCount(int i){
        int linesNeed = i - lines.size();
        bool add = true;
        if(linesNeed == 0){ return; };
        if(linesNeed < 0){ add = false;}
        linesNeed = abs(linesNeed);

        for (size_t i = 0; i < linesNeed; i++){
            if(add){
                SolutionLine * line = new SolutionLine();
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

    void setSolution(int index, MathSolutionLine * solution){
        if(layout->count() > index){
            SolutionLine *widget = (SolutionLine*)(layout->itemAt(index)->widget());
            if(widget == NULL){ return; }
            widget->setSolution(solution);
        }
    }


    void resizeEvent(QResizeEvent* event) override{
        QResizeEvent *parentEvent = new QResizeEvent(event->size(), event->oldSize());
        QApplication::postEvent(parent, parentEvent);

        QScrollArea::resizeEvent(event);
    }
};
