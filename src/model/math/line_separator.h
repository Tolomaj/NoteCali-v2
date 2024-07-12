#pragma once

#include <vector>
#include <string>
#include "../../link/debugger.hpp"
#include "../../link/settings_link.hpp"
#include "../../link/math_link.hpp"

using namespace std;

class LineSeparator {

    SettingsLinkAP * settings;

    vector<mline> lines;

    void registerLine(wstring* iline, bool isCompleted = true);

public:
    LineSeparator(SettingsLinkAP * settings);

    void printLines();

    vector<mline> * procesInput(wstring* str);

};


LineSeparator::LineSeparator(SettingsLinkAP * settings){
    this->settings = settings;
}

void LineSeparator::registerLine(wstring* iline, bool isCompleted) {
    mline separatedLine;
    separatedLine.isEnded = isCompleted;
    if ((iline->size() > 0 && iline->at(0) != L';') || iline->size() == 0) { // neobsahuje ; na prvn�m a nen� tud� command
        if (settings->getBool("UseLineModifiers")) {
            size_t modificator = iline->find(L";");
            size_t modifcorection = iline->find(L"(");


            bool modificationIsvalid = (modificator != string::npos) && ((modifcorection == string::npos) || (modificator < modifcorection));//aby se nepo��taly ; v z�vork�ch

            if (modificationIsvalid) {
                separatedLine.lineModifier = iline->substr(0, modificator);
                separatedLine.line = iline->substr(modificator + 1, iline->length());
                lines.push_back(separatedLine);
                return;
            }
        }


        separatedLine.line = *iline;
        lines.push_back(separatedLine);
        return;
    }

    size_t space = iline->find_first_of(L" +-*/%^<>=!&|");

    if (space == string::npos) {
        separatedLine.command = iline->substr(1, iline->length());
        lines.push_back(separatedLine);
        return;
    };


    separatedLine.command = iline->substr(1, space - 1);
    separatedLine.line = iline->substr(space + (iline->at(space) == L' '), iline->size() - 1);
    lines.push_back(separatedLine);
}

void LineSeparator::printLines() {
    std::cout << CLR_GRN << "╔SEPAROVANÉ LINKY:" << std::endl;

    for (size_t i = 0; i < lines.size(); i++) {
        std::cout << "╠═ line(" << i << ")»";

        std::wcout << L" mod:[" << lines.at(i).lineModifier 
                   << L"] cmd:[" << lines.at(i).command 
                   << L"] line:[" << lines.at(i).line << L"]" << std::endl;
    };

    std::cout << "╚END" << CLR_NC << std::endl;
};

vector<mline> * LineSeparator::procesInput(wstring* str) { //used from stackowerflow https://stackoverflow.com/questions/13172158/c-split-string-by-line
    lines.clear();

    size_t pos = 0;
    size_t prev = 0;
    wstring a = L"";
    while ((pos = str->find(L"\n", prev)) != string::npos) {
        long long posN = pos - prev - 1;
        if (posN < 0) {
            mline l;
            l.isComandDone = true;
            lines.push_back(l);
            prev = pos + 1;
            continue;
        }
        a = str->substr(prev, pos - prev - (str->at(posN) == L'\r'));
        registerLine(&a);
        prev = pos + 1;
    }

    if (prev < str->length()) {
        a = str->substr(prev);
        registerLine(&a, false);
    }

    return &lines;
};