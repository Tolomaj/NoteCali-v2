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

#include "base_entry.hpp"
#pragma once

class ComboStringEntry : public EntryTemplate {
    QComboBox *combo;

public:
    ComboStringEntry(
        SettingsWindowLink *settings_link,
        SettingsLinkAP *settings,
        std::string name,
        std::wstring description,
        std::vector<std::wstring> options
    ) : EntryTemplate(settings_link, settings, name, description) {
        combo = new QComboBox();
        combo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

        for (const std::wstring &option : options) {
            combo->addItem(QString::fromStdWString(option));
        }

        QString current = QString::fromStdWString(settings->getWString(name));
        int idx = combo->findText(current);
        if (idx < 0) {
            combo->addItem(current);
            idx = combo->findText(current);
        }
        combo->setCurrentIndex(idx);

        layout->addWidget(combo);

        connect(combo, &QComboBox::currentTextChanged, this, [this](const QString &txt) {
            this->settings_link->setWString(this->name, txt.toStdWString());
        });
    }
};
