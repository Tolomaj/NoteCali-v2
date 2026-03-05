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

    bool hide_warning_text = true;
    bool clickCopyable = true;
    bool copy_rounded = false;
    bool scaling = true;
    std::wstring no_round_solution;
    std::wstring round_solution;
public:
    SolutionLine(QWidget *parent,bool hide_warning_text,bool clickCopyable,bool copy_rounded,bool scaling) : QWidget(parent){
        this->parent = parent;

        layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight,this);
        layout->setSpacing(0);
        layout->setAlignment(Qt::AlignCenter);
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


        //todo center text verticali
        text = new QLabel("NOT_SET");
        text->setAlignment(Qt::AlignCenter);

        text->setTextInteractionFlags(Qt::TextSelectableByMouse);
        layout->addWidget(text);

        this->setShowWarningText(hide_warning_text);
        this->setCopy(clickCopyable,copy_rounded);
        this->setScaling(scaling);
        this->setContentsMargins(2,0,2,0);
    }

    ~SolutionLine(){
        delete layout;
        delete variable;
        delete error;
        delete information;
        delete text;
    }

    void setWidth(int size){
       text->setFixedHeight(size);
    }

    void setFont(QFont * font){
        usedFont = font;
        text->setFont(*font);
    }

    void setShowWarningText(bool enable){
        this->hide_warning_text = enable;
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

    ///@brief set scaling behavior
    void setScaling(bool scaling){
        this->scaling = scaling;
    }

    void resizeSolution(){
        //resize solution to fit solution line
        if(usedFont != nullptr && this->scaling == true){

            // get size of original text
            QRect rect = QFontMetrics(*usedFont).boundingRect(text->text());

            // calculate haw many symbols are displayed for calculating margin of text
            int symbol_num = (!variable->isHidden() + !error->isHidden() + !information->isHidden());
            int w = this->parent->geometry().width() - rect.height()*symbol_num;
            float ratio = (float)w/rect.width();

            //text is not alowed to be bigger than seted font so (1 >= x > 0.5)
            if(ratio >= 1)   { ratio = 1;    }else 
            if(ratio <= 0.05){ ratio = 0.05; }

            dbg(  std::cout << "bound:" << w << "/" << rect.width() << " as:" << ratio << " pad:" << symbol_num << std::endl;  )

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

        // if hiden hide solution and all simbols
        if(solution->isHiden){
            text->setText("");
            error->hide();
            variable->hide();
            return;
        }

        if(solution->isError){
            if(this->hide_warning_text){
                text->setText(QString::fromStdWString(solution->solution));
            }else{
                text->setText("");
            }
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

            std::cout << "text:[" << text->text().toStdString() << "] modifiers:[" << modi << "] ";
        )

        //resize solution to fit solution line
        this->resizeSolution();
    }


    ///@brief when line clciked & ClickCopy is enabled copy text to clipboard 
    void mousePressEvent(QMouseEvent* event) override {
        Q_UNUSED(event);
        if(clickCopyable){
            if(copy_rounded){
                QGuiApplication::clipboard()->setText(QString::fromStdWString(this->round_solution));
            }else{
                QGuiApplication::clipboard()->setText(QString::fromStdWString(this->no_round_solution));
            }
        }
    }

};