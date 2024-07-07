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
#include <QFrame>
#include "solution_box.hpp"
#include <iostream>
#include <QDebug>
#include <sstream>
#include <string>

#include "../../link/debugger.hpp"
#include "../../link/math_link.hpp"
#include "../../link/window_link.hpp"
#include "../../link/settings_link.hpp"

///GUI_Window : Objekt hlavního okna vytváří hlavní rozložení ovladacích prvků.
class CalcBody : public QSplitter { 
Q_OBJECT
private:
    SolutionBox * solution_box;
    QBoxLayout * layout;
    QTextEdit * text;
    QFont font;
    CalculatorWindowLink * controller;
    SettingsLinkAP * settings;

    void sincSolutions(std::vector<std::wstring> * lines){      
        solution_box->setCount(lines->size());

        // resize solutions

        QRect rct = text->geometry();
        rct.setWidth(rct.width() - 8 );

        for (size_t i = 0; i < lines->size(); i++){
            std::wstring line = lines->at(i);
            QRect rect = text->fontMetrics().boundingRect(rct, Qt::AlignLeft | Qt::TextWordWrap , QString::fromStdWString(line));
            solution_box->setWidth(i,rect.height());
        }
    }

    std::vector<std::wstring> getLines(){
        std::vector<std::wstring> lines;
        std::wstring line;
        std::wstringstream wss(text->toPlainText().toStdWString());
        while(std::getline(wss, line, L'\n')) {
            lines.push_back(line);
        }
        return lines;
    };



public slots:

    void resized(){

    }

    void onTextChanged(){
        std::vector<std::wstring>lines = this->getLines();
        this->sincSolutions(&lines);

        for (size_t i = 0; i < lines.size(); i++){
            std::wstring line = lines.at(i);
            MathSolutionLine solution;
            solution.solution = std::string( line.begin(), line.end() );
            solution_box->setSolution(i,&solution);
        }
        controller->solve(&lines);
        text->style()->pixelMetric(QStyle::PM_ScrollBarExtent);
    }

public: 
    CalcBody(SettingsLinkAP * settings, CalculatorWindowLink * controller) : QSplitter(Qt::Horizontal){
        this->settings = settings;
        this->controller = controller;
        font = QFont("Helvetica", 15);

        this->setContentsMargins(0,0,0,0);
        this->setChildrenCollapsible(false);

        text = new QTextEdit();
        text->setMinimumWidth(40);
        text->setFrameStyle(QFrame::NoFrame);
        text->setHtml(QString::fromStdWString(L"- helo this is🥰 anĎ lÓng teČt helo😀"));
        text->setFont(font);
        text->setStyleSheet("background-color:transparent;");
        text->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        text->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        text->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        connect(&(*text), SIGNAL(textChanged()), this, SLOT(onTextChanged()));
        this->addWidget(text);



        solution_box = new SolutionBox(this);
        solution_box->setMinimumWidth(20);
        solution_box->setFrameStyle(QFrame::NoFrame);
        solution_box->setContentsMargins(5,0,5,0);
        solution_box->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        solution_box->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        solution_box->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        this->addWidget(solution_box);

 
        this->reloadStyles();

        /* todo scroll sinc*/
        connect(text->verticalScrollBar(), &QScrollBar::valueChanged, [this](int value){
            solution_box->verticalScrollBar()->setValue(value);
            
        });
        connect(solution_box->verticalScrollBar(), &QScrollBar::valueChanged, [this](int value){
            text->verticalScrollBar()->setValue(value);
        });


    };

    void present(std::vector<MathSolutionLine>* solved_lines) {

        
        //todo
    };
    
    void highlite(std::vector<MathHighlite>* highlites) {
        //todo
    };

    // nastavý styli elementů 
    void reloadStyles(){
        if(settings->getBool("FloatingDivider")){
            this->setStyleSheet(R"(
                QSplitter::handle {
                    background-color:#3DAEE9; 
                    margin-top:40px;
                    margin-bottom:40px;
                    border-radius: 3px; 
                }
        
                QSplitter::handle:vertical {
                    margin: 0;
                    height: 6px;
                }
            )");
        }else{
            this->setStyleSheet(R"(
                QSplitter::handle {
                    background-color:#3DAEE9; 
                    margin-top:40px;
                    border-top-left-radius: 3px; 
                    border-top-right-radius: 3px;
                }
        
                QSplitter::handle:vertical {
                    margin: 0;
                    height: 6px;
                }
            )");
        }
   }


    void resizeEvent(QResizeEvent* event) override{
        std::vector<std::wstring>lines = this->getLines();
        this->sincSolutions(&lines);

        QSplitter::resizeEvent(event);
    }

};
