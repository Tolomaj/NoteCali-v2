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

class SettingsAbout : public QFrame {
    Q_OBJECT

public:
    SettingsAbout(const QString& name, const QString& content) : QFrame() {
        this->setFrameStyle(QFrame::StyledPanel);
        this->setAutoFillBackground(true);
        this->setBackgroundRole(QPalette::Window);

        // Let this widget shrink as much as possible
        this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

        // Layout
        QVBoxLayout* mainLayout = new QVBoxLayout(this);
        mainLayout->setContentsMargins(5, 5, 5, 5);  // Reduced margins
        mainLayout->setSpacing(5);                   // Reduced spacing

        // Font
        QFont titleFont;
        titleFont.setPointSize(12);  // Slightly smaller for minimal height
        titleFont.setBold(true);

        // Title Label
        QLabel* titleLabel = new QLabel(name, this);
        titleLabel->setTextFormat(Qt::RichText);
        titleLabel->setFont(titleFont);
        titleLabel->setAlignment(Qt::AlignCenter);

        // Allow label to shrink
        titleLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        mainLayout->addWidget(titleLabel);


        QLabel* logLabel = new QLabel(this); 
        logLabel->setWordWrap(true);
        logLabel->setTextFormat(Qt::RichText);
        logLabel->setOpenExternalLinks(true);
        logLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        logLabel->setFrameShape(QFrame::NoFrame);
        logLabel->setText("<div style='word-wrap: break-word; white-space: normal;'>"  + content + "</div>");
        mainLayout->addWidget(logLabel);
    }
};
