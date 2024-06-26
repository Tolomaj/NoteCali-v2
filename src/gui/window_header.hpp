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
#include <QString>
#include <QDebug>



class HeaderButton : public QPushButton{
public:
    HeaderButton(QString icon) : QPushButton(){
        this->setIcon(QIcon(icon));
        this->setIconSize(QSize(25, 25));
        this->setFixedSize(30,30);
        this->setFlat(true);
        this->setContentsMargins(0,0,0,0);
    }

};


///GUI_Window : Objekt hlavního okna vytváří hlavní rozložení ovladacích prvků.
class CalcHead : public QWidget { 
public: 
    QBoxLayout * layout;
    CalcHead(QMainWindow *parent = 0) : QWidget(parent){

        layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight,this);
        layout->setSpacing(0);
        layout->setContentsMargins(0,0,0,0);


        QPushButton * menu = new HeaderButton("assets/menu.svg");
        layout->addWidget(menu);

        QPushButton * pin = new HeaderButton("assets/pin.svg");
        layout->addWidget(pin);

        QLabel * name = new QLabel("Notecali");
        name->setAlignment(Qt::AlignCenter);
        layout->addWidget(name);

        QPushButton * minimalise = new HeaderButton("assets/minimalize.svg");
        layout->addWidget(minimalise);

        QPushButton * close = new HeaderButton("assets/close.svg");
        layout->addWidget(close);

    };

};
