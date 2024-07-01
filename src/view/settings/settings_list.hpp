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
#include <QFrame>
#include <iostream>


class CathegoryList : public QFrame { 
public: 
    QBoxLayout * layout;
    QWidget *parent;

    CathegoryList(QWidget *parent = 0) : QFrame(parent){
        this->parent = parent;
        this->setFrameStyle(QFrame::Panel | QFrame::Raised);

        layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom,this);
        layout->setAlignment(Qt::AlignTop);

        QPixmap pixelmap("assets/icon.ico");

        QLabel * myLabel = new QLabel();
        myLabel->setPixmap(pixelmap.scaled(20,20,Qt::KeepAspectRatio));
        myLabel->setMargin(10);

        layout->addWidget(myLabel);

        layout->addWidget(new QPushButton("cathegory1"));
        layout->addWidget(new QPushButton("cathegory2"));
        layout->addWidget(new QPushButton("cathegory3"));

    };

    void addCathegory(){

    }

};
