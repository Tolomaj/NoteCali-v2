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

//#include "../../link/debugger.hpp"
#include "../../link/math_link.hpp"
#include "../../link/settings_link.hpp"

#pragma once

class SolutionLine : public QWidget{

    QBoxLayout * layout;
    QLabel * text;
    QLabel * variable;
    QLabel * error;
    QLabel * information;
    QWidget *parent;
    QFont * usedFont = nullptr;
    
    bool clickCopyable = true;
    bool copy_rounded = false;
    std::wstring no_round_solution;
    std::wstring round_solution;
public:
    SolutionLine(QWidget *parent,bool clickCopyable,bool copy_rounded) : QWidget(parent){
        this->parent = parent;

        layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight,this);
        layout->setSpacing(0);
        layout->setContentsMargins(0,0,0,0);

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

        text = new QLabel("NOT_SET");
        text->setAlignment(Qt::AlignCenter);
        text->setTextInteractionFlags(Qt::TextSelectableByMouse);
        layout->addWidget(text);


        this->setCopy(clickCopyable,copy_rounded);
        this->setContentsMargins(2,0,2,0);
    }

    void setWidth(int size){
       text->setFixedHeight(size);
    }

    void setFont(QFont * font){
        usedFont = font;
        text->setFont(*font);
    }


    ///@brief set copy behavior
    void setCopy(bool clickCopyable,bool copy_rounded){
        this->clickCopyable = clickCopyable;
        this->copy_rounded = copy_rounded;
        if(!clickCopyable){
            text->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
        }else{
            text->setTextInteractionFlags(Qt::NoTextInteraction);
        }
    }


    //todo add option to remove resizing option
    void resizeSolution(){
        //resize solution to fit solution line
        if(usedFont != nullptr){

            QFontMetrics metrics = QFontMetrics(*usedFont);
            QRect rect = metrics.boundingRect(text->text());

            int w = this->parent->geometry().width()-20;
            float ratio = (float)w/rect.width();

            //text is not alowed to be bigger than seted font
            if(ratio >= 1){
                ratio = 1;
            }else if(ratio <= 0.05){
                ratio = 0.05;
            }

            dbg(
                std::cout << "bound:" << w << "/" << rect.width() << " as:" << ratio << std::endl;
            )

            QFont f = *usedFont;
            f.setPointSizeF(f.pointSizeF()*ratio);
            text->setFont(f);
        }

    }



    ///@brief present solution on to line
    void setSolution(mline * solution){
        
        // save solutions texts for ClickCopy
        this->no_round_solution = solution->solutionNoRound;
        this->round_solution = solution->solution;

        if(solution->isHiden){
            // if hiden hide solution and all simbols
            text->setText("");
            error->hide();
            variable->hide();
            return;
        }

        if(solution->isError){
            //todo add option to hide error text
            text->setText(QString::fromStdWString(solution->solution));

            error->show();
        }else{

            // if not error show solution & hide error symbol
            text->setText(QString::fromStdWString(solution->solution));
            error->hide();

            // if solution is variable also show variable symbol
            (solution->localVariableName != L"") ? variable->show() : variable->hide();
 
        }

        dbg(
            std::string modi = "";

            if(!variable->isHidden())   { modi.append("📝"); }
            if(!error->isHidden())      { modi.append("⚠️"); }
            if(!information->isHidden()){ modi.append("ℹ️");  }
            if(modi == ""){ modi = "none"; }

            std::cout << "text:[" << text->text().toStdString() << "] modifiers:[" << modi << "] ";
        )

        //resize solution to fit solution line
        this->resizeSolution();
    }


    ///@brief when line clciked & ClickCopy is enabled copy text to clipboard 
    void mousePressEvent(QMouseEvent* event) override {
        if(clickCopyable){
            if(copy_rounded){
                QGuiApplication::clipboard()->setText(QString::fromStdWString(this->round_solution));
            }else{
                QGuiApplication::clipboard()->setText(QString::fromStdWString(this->no_round_solution));
            }
        }
    }


};