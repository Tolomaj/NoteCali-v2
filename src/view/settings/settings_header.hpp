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

///GUI_Window : Objekt hlavního okna vytváří hlavní rozložení ovladacích prvků.
class SettingsHeader : public QWidget { 
public: 
    QBoxLayout * layout;
    SettingsHeader(QMainWindow *parent = 0) : QWidget(parent){

        layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight,this);
        layout->setSpacing(0);
        layout->setContentsMargins(0,0,0,0);


        QLabel * name = new QLabel("Settings");
        this->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Maximum);
        name->setAlignment(Qt::AlignLeft);
        name->setContentsMargins(15,0,0,0);
        layout->addWidget(name);

        QPushButton * minimalise = new HeaderButton("assets/minimalize.svg");
        layout->addWidget(minimalise);

        QPushButton * close = new HeaderButton("assets/close.svg");
        layout->addWidget(close);

    };

};
