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

class SolutionLine : public QWidget{
    QBoxLayout * layout;
    QLabel * text;
public:
    SolutionLine() : QWidget(){
        layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight,this);
        layout->setSpacing(0);
        layout->setContentsMargins(0,0,0,0);

        text = new QLabel("helo");
        layout->addWidget(text);

    }

    void setWidth(int size){
       //layout->heightForWidth()
       text->setFixedHeight(size);
    }

};

class SolutionBox : public QWidget { 
public: 
    QBoxLayout * layout;
    SolutionLine * line;
    QWidget *parent;

    SolutionBox(QWidget *parent = 0) : QWidget(parent){
        this->parent = parent;
        layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom,this);
        layout->setAlignment(Qt::AlignTop);
        layout->setSpacing(0);
        layout->setContentsMargins(0,0,0,0);

        line = new SolutionLine();
        

        layout->addWidget(line);
        layout->addWidget(new SolutionLine());
        layout->addWidget(new SolutionLine());
        layout->addWidget(new SolutionLine());
        layout->addWidget(new SolutionLine());
        layout->addWidget(new SolutionLine());

    };

    void setWidth(int index, int height){
        std::cout << "asa" << layout->count() << " fr: " << height << std::endl;
        if(layout->count() < index){
            SolutionLine *widget = (SolutionLine*)(layout->itemAt(index)->widget());
            if(widget == NULL){
                std::cout << "problem: " << std::endl;
            }
            line->setFixedHeight(height);
            line->updateGeometry();
            this->updateGeometry();
            layout->update();
            parent->updateGeometry();
            line->setWidth(height);
        }
    }

};
