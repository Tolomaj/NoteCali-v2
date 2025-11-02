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

class SettingsVariables : public QFrame {
    Q_OBJECT

public:
    SettingsVariables() : QFrame() {
        this->setFrameStyle(QFrame::StyledPanel);
        this->setAutoFillBackground(true);
        this->setBackgroundRole(QPalette::Link);

        // Let this widget shrink as much as possible
        this->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

        // Layout
        QVBoxLayout* mainLayout = new QVBoxLayout(this);
        mainLayout->setContentsMargins(5, 5, 5, 5);  // Reduced margins
        mainLayout->setSpacing(5);                   // Reduced spacing

        QLabel* logLabel = new QLabel(this);
        logLabel->setText("helllo world");
        mainLayout->addWidget(logLabel);

    }
};
