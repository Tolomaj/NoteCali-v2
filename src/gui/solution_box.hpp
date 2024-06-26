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

class SolutionLine : public QWidget{
    QBoxLayout * layout;
public:
    SolutionLine() : QWidget(){
        layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight,this);
        layout->setSpacing(0);
        layout->setContentsMargins(0,0,0,0);

        QLabel * text = new QLabel("helo");
        layout->addWidget(text);

        this->setFixedHeight(30);

    }

};

class SolutionBox : public QWidget { 
public: 
    QBoxLayout * layout;

    SolutionBox(QMainWindow *parent = 0) : QWidget(parent){

        layout = new QBoxLayout(QBoxLayout::Direction::TopToBottom,this);
        layout->setAlignment(Qt::AlignTop);
        layout->setSpacing(0);
        layout->setContentsMargins(0,0,0,0);

        layout->addWidget(new SolutionLine());
        layout->addWidget(new SolutionLine());
        layout->addWidget(new SolutionLine());
        layout->addWidget(new SolutionLine());
        layout->addWidget(new SolutionLine());
        layout->addWidget(new SolutionLine());

    };





};
