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
#include "solution_box.hpp"
#include <QDebug>


///GUI_Window : Objekt hlavního okna vytváří hlavní rozložení ovladacích prvků.
class CalcBody : public QWidget { 
public: 
    QBoxLayout * layout;
    QSplitter *spliter;
    QTextEdit * text;
    QFont font;

    CalcBody(QMainWindow *parent = 0) : QWidget(parent){
        font = QFont("Helvetica", 15);

        layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight,this);
        layout->setSpacing(0);
        layout->setContentsMargins(0,0,0,0);

        text = new QTextEdit();
        text->setFrameStyle(QFrame::NoFrame);
        text->setPlainText("- helo this is and long text helo");
        text->setFont(font);
        text->setStyleSheet("background-color:transparent;");
        layout->addWidget(text);

        spliter = new QSplitter(Qt::Vertical);
        spliter->setFixedWidth(5);
        spliter->setStyleSheet( "background-color:red; margin-top:20px;" );
        layout->addWidget(spliter);


        SolutionBox * slution_box = new SolutionBox();
        layout->addWidget(slution_box);

    };


    /// event když okno je zmenšeno nebo zvětšeno / řeší zvětšování a zmenšování objektů okna
    void resizeEvent(QResizeEvent* event){
        //QFontMetrics metric(font);

        QRect rct = text->geometry();
        rct.setWidth(rct.width() - 8 );

        QRect rect = text->fontMetrics().boundingRect(rct, Qt::AlignLeft | Qt::TextWordWrap , "- helo this is and long text helo");

        std::cout <<"out_rect:"<< rect.height() << "-"<< rect.width() << "," << "in_rect:"<< text->geometry().width() << "-" << text->geometry().height() << std::endl;
    };


};
