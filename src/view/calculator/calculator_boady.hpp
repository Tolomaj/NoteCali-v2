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
class CalcBody : public QWidget { 
Q_OBJECT
private:
    SolutionBox * solution_box;
    QBoxLayout * layout;
    QSplitter *spliter;
    QTextEdit * text;
    QFont font;
    CalculatorWindowLink * controller;

public slots:

    void onTextChanged(){
        std::vector<std::wstring> lines;
        std::wstring line;
        std::wstringstream wss(text->toPlainText().toStdWString());
        while(std::getline(wss, line, L'\n')) {
            lines.push_back(line);
        }

        controller->solve(&lines);


      /*  QRect rct = text->geometry();
        rct.setWidth(rct.width() - 8 );
        QRect rect = text->fontMetrics().boundingRect(rct, Qt::AlignLeft | Qt::TextWordWrap, text->toPlainText());

        int wh = rect.height();

        solution_box->setWidth(0,wh);

        std::cout <<"text changed:" << wh << "for : " << text->toPlainText().toStdString() << std::endl;*/
    }

public: 
    CalcBody(SettingsLinkAP * settings, CalculatorWindowLink * controller) : QWidget(){
        this->controller = controller;
        font = QFont("Helvetica", 15);

        layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight,this);
        layout->setSpacing(0);
        layout->setContentsMargins(0,0,0,0);

        text = new QTextEdit();
        text->setFrameStyle(QFrame::NoFrame);
        std::wstring str = L"- helo this is🥰 anĎ lÓng teČt helo😀";
        //text->setPlainText("- helo this is and long text helo");
        text->setHtml(QString::fromStdWString(str));
        text->setFont(font);
        text->setStyleSheet("background-color:transparent;");
        connect(&(*text), SIGNAL(textChanged()), this, SLOT(onTextChanged()));
        layout->addWidget(text);

        spliter = new QSplitter(Qt::Vertical);
        spliter->setFixedWidth(6);
        spliter->setFrameStyle(QFrame::Raised);
        layout->addWidget(spliter);

        solution_box = new SolutionBox(this);
        solution_box->setContentsMargins(5,0,5,0);
        layout->addWidget(solution_box);

        updateStyles();

    };

    // nastavý styli elementů 
    void updateStyles(){
             
        spliter->setStyleSheet("background-color:#3DAEE9; margin-top:40px; border-top-left-radius: 3px; border-top-right-radius: 3px;" );
        //spliter->setStyleSheet("background-color:#3DAEE9; margin-top:20px; margin-bottom:20px; border-radius: 3px;" );
    }


    /// event když okno je zmenšeno nebo zvětšeno / řeší zvětšování a zmenšování objektů okna
    void resizeEvent(QResizeEvent* event){

        QRect rct = text->geometry();
        rct.setWidth(rct.width() - 8 );

        QRect rect = text->fontMetrics().boundingRect(rct, Qt::AlignLeft | Qt::TextWordWrap , "- helo this is and long text helo");

        std::cout <<"out_rect:"<< rect.height() << "-"<< rect.width() << "," << "in_rect:"<< text->geometry().width() << "-" << text->geometry().height() << std::endl;
    };


};
