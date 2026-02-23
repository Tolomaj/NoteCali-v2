
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
#include <sstream>
#include <string>
#include <algorithm>

#include <iostream>
#include <vector>
#include <QPainter>

#include "../../../link/settings_link.hpp"
#include "../../../link/window_link.hpp"

#pragma once
///GUI_Window : Objekt hlavního okna vytváří hlavní rozložení ovladacích prvků.
class EntryTemplate : public QFrame {

protected: 
    std::string name;
    std::wstring description;
    SettingsWindowLink *settings_link;
    SettingsLinkAP *settings;

    QBoxLayout * layout;

public: 
  
    EntryTemplate(SettingsWindowLink *settings_link,SettingsLinkAP *settings, std::string name,std::wstring description) : QFrame(){
        this->name = name;
        this->description = description;
        this->settings = settings;
        this->settings_link = settings_link;

        this->setFrameStyle(QFrame::NoFrame);
        this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

        this->setAttribute(Qt::WA_Hover, true);
        this->setMouseTracking(true);

        layout = new QBoxLayout(QBoxLayout::Direction::LeftToRight,this);
        int horizontalSpacing = style()->pixelMetric(QStyle::PM_LayoutHorizontalSpacing, nullptr, this);
        int verticalSpacing = style()->pixelMetric(QStyle::PM_LayoutVerticalSpacing, nullptr, this);

        if (horizontalSpacing < 0) { horizontalSpacing = 6; }
        if (verticalSpacing < 0) { verticalSpacing = 6; }

        layout->setContentsMargins(horizontalSpacing, verticalSpacing / 2, horizontalSpacing, verticalSpacing / 2);
        layout->setSpacing(horizontalSpacing);

        // laber for the line
        QLabel * label = new QLabel(QString::fromStdString(name));
        label->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
        layout->addWidget(label);

        layout->addStretch();

    };

protected:
    void paintEvent(QPaintEvent *event) override {
        QFrame::paintEvent(event);

        // Theme-aware separator.
        QPainter painter(this);
        painter.setPen(palette().color(QPalette::Mid));
        painter.drawLine(rect().bottomLeft(), rect().bottomRight());
    }


    void leaveEvent(QEvent * event){
        settings_link->setHint("Settings Hint",L"this is place where hits and informations for settings would be shown");
        QFrame::leaveEvent(event);
    }

    void enterEvent(QEnterEvent * event){
        settings_link->setHint(name,description);
        QFrame::enterEvent(event);
    }
};
