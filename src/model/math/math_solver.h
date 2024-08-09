﻿#include <vector>
#include <string>
#include <cstdio>
#include <stddef.h>
#include "../../../include/ttmath/ttmath.h"
#include "../../link/debugger.hpp"
#include "../../link/settings_link.hpp"
#include "../../link/math_link.hpp"

using namespace std;


#define MATHERR_INVALID_NUMBER_FOR_OPERARTION 1
#define MATHERR_INVALID_VARIABLE 2
#define MATHERR_INVALID_FUNCTION 3
#define MATHERR_INVALID_SINTAX_TTMARH 3
#define MATHERR_INVALID_SINTAX 4
#define MATHERR_INVALID_VARIABLE_NAME 5
#define MATHERR_INVALID_LINE_JUMP_NUM 6

#define END_LINE_SOLVING 25

#define VARIABLE_FORBIDENT_SIMBOLS_LENGHT 8
const wchar_t forbidentVariableSimbols[VARIABLE_FORBIDENT_SIMBOLS_LENGHT] = { '[' , ']' , '{' , '}' , '=' , '&' , '@' , ' '};

#define FAST_SAME false

#define POINTER_CHAR L"@" // must be same in separator (line 58)


class MatematicalSolver {
    typedef ttmath::Big<10, 10> MyBig;
    ttmath::Parser<MyBig> parser;
    ttmath::Objects varTable;
    ttmath::Objects systemVariableTable;
    ttmath::Objects functionTable;//not used jet
    ttmath::Conv ConvertionRole;
    bool lineUsingMetrics;
    SettingsLinkAP * settings;

    vector<mline>* procesedLines;

    bool isSameLine(mline* line1, mline* line2);

    bool hasAnyVariable(mline* line);

    int findEqualition(wstring* line);// vrátí true když opsahuje samostatné = ,index je hejo pozice

    int solveLine(wstring line, wstring* solution, wstring* solutionNoRound, wstring* errorText); // vyřeší linku která neobsahuje žádné custom věci // později budwe řešit proměné a funkce

    bool isValidVariableName(wstring name);

    void creteErrorLineSolution(mline* line, wstring text, int errorCode);

    void removeBeforeAfterSpaces(wstring* line);

    bool solveVariableLine(mline* line, int eqPos);

    void executeMathComand(mline* line);

    void addMetricsToTable();

    int modifyMathRules(wstring* s);

    bool setDefaultMathRules();

    void calculateSumForLinesAbove( int lineNum);

public:
    
    MatematicalSolver(SettingsLinkAP * settings);

    void loadVariablesFromTable();

    int solve(vector<mline>* lines);

};




MatematicalSolver::MatematicalSolver(SettingsLinkAP * settings) {
    this->settings = settings;
    loadVariablesFromTable();
}

void MatematicalSolver::loadVariablesFromTable() {
    varTable.Clear();
    systemVariableTable.Clear();
    parser.SetVariables(&varTable);

/* //todo load variables from settings
    for (size_t i = 0; i < variableTable.table.size(); i++) {
        //todo dbgLog(variableTable.table.at(i).varName);
        systemVariableTable.Add(variableTable.table.at(i).varName, variableTable.table.at(i).number);
    }
*/

    varTable = systemVariableTable;
}

void MatematicalSolver::calculateSumForLinesAbove(int lineNum) {

    wstring lineFormula = L"";

    //vytvoří formulu všeho nad
    int momental = lineNum - 1;
    while (momental >= 0) {

        // sčítéme linky jen po sumbreak comand
        if (procesedLines->at(momental).isSumBrake == true) {
            break;
        }

        //pokud linka nemá číslo k řešení není možná jí sčítat takže přeskakujeme
        if (procesedLines->at(momental).solutionNoRound == L"") {
            momental--;
            continue;
        }

        // pro první číslo znaménko vynecháváme
        if (momental != lineNum) {
            lineFormula = lineFormula + L"+";
        }

        lineFormula = lineFormula + procesedLines->at(momental).solutionNoRound;


        momental--;
    }


    if (lineFormula != L"") {
        ttmath::ErrorCode err = parser.Parse(lineFormula);

        if (err == 0) {
            varTable.EditValue("sum", parser.stack[0].value.ToString());
            ////todo dbgLog("suma pro linku - " + to_string(lineNum) + " : " + parser.stack[0].value.ToString());
        } else {
            ////todo dbgLog("error sumarizace - " + to_string(lineNum) + " : ",false);
        }

    }
};

int MatematicalSolver::solve(vector<mline>* lines) { 
    procesedLines = lines;
    //nastavení pravidel pro řešení linek
    setDefaultMathRules();

    if (settings->getBool("UseMetrics")) {
        addMetricsToTable();
    }

    parser.SetDegRadGrad(settings->getBool("UseRadians"));

    //pokud se používá sum tak přidáme proměnou
    if (settings->getBool("UseSumVariable")) {
        varTable.Add("sum", "0");
    };

    for (size_t i = 0; i < lines->size(); i++) {

        // linka obsahuje příkaz co ukončí řešení momentální linky
        if (settings->getBool("UseLineModifiers") && modifyMathRules(&lines->at(i).lineModifier) == END_LINE_SOLVING) { 
            continue; 
        };

        // linka je už vyřešená nebo příkaz
        if (lines->at(i).completlySolved || lines->at(i).isComandDone) { 
            continue; 
        }  

        //linka obsahuje matematický příkaz
        if (lines->at(i).command != L"") { 
            executeMathComand(&lines->at(i));
        }
        // pokud matematický příkaz vyřešil linku
        if (lines->at(i).completlySolved ) { 
            continue; 
        }


        // pokud je zaplé používání sum proměnné tak se vypočítá
        if (settings->getBool("UseSumVariable")) {
            calculateSumForLinesAbove(i);
        }

        int eqPos = findEqualition(&lines->at(i).line);
        if (eqPos >= 0) { //is variable 
            solveVariableLine(&lines->at(i),eqPos);
        } else { // is not variable
            wstring error = L"Line Unsolvable";
            if (solveLine(lines->at(i).line, &lines->at(i).solution, &lines->at(i).solutionNoRound, &error) != 0) { //error check
                creteErrorLineSolution(&lines->at(i), error, MATHERR_INVALID_NUMBER_FOR_OPERARTION);
            }else {
                lines->at(i).completlySolved = true;
            }
        };

        // if line has 'h' modifier (hide) set paraeter
        if (lines->at(i).lineModifier.find(L'h') != string::npos) {
            lines->at(i).isHiden = true;
        }

        if (lines->at(i).lineModifier != L"") {
            setDefaultMathRules();
        }

        //todo dbgLog(L"výsledek linky - " + to_wstring(i) + L" : " + lines->at(i).solution + L"\n");

    }
    lineUsingMetrics = false;
    varTable = systemVariableTable;
   
    return 0;
}

int MatematicalSolver::solveLine(wstring line, wstring* solution, wstring* solutionNoRound,wstring * errorText) { // vyřeší linku která neobsahuje žádné custom věci // později budwe řešit proměné a funkce
    
    //převod XX:XX na sekundy
    // vždy rozdělí na dvě části podle : a ty vypočítá nezávysle to se opakuje dokud nezbyde výsledek
    if (settings->getBool("UseTimeFormat")) {
        size_t ocur2 = line.find(L":");
        while (ocur2 != wstring::npos) {

            // najdeme levou část před : dokud nenarazí na neuzavřenou ( závorku
            size_t numStart = ocur2;
            size_t lenght = 0;
            int pathcr = 0;
            while (numStart - lenght != 0 && line[numStart - lenght - 1] != ':') {
                if (line[numStart - lenght - 1] == ')') {
                    pathcr++;
                }
                if (line[numStart - lenght - 1] == '(') {
                    if (pathcr == 0) {
                        break;
                    }
                    pathcr--;
                }
                lenght++;
            }

            //najdeme pravou část za : koduk nenarazí na neuzavřenou ) závorku
            size_t secNumStart = ocur2;
            size_t secLenght = 0;
            pathcr = 0;
            while (secNumStart + secLenght != line.length() && line[secNumStart + secLenght + 1] != ':') {
                if (line[secNumStart + secLenght + 1] == '(') {
                    pathcr++;
                }
                if (line[secNumStart + secLenght + 1] == ')') {
                    if (pathcr == 0) {
                        break;
                    }
                    pathcr--;
                }

                secLenght++;
            }

            // rosekání mezi : 
            wstring fnum = line.substr(numStart - lenght, lenght);
            wstring snum = line.substr(secNumStart + 1, secLenght);

            // prevence abychom nečetli v stringu za koncem
            wstring afterstring = L"";
            if (secNumStart + secLenght + 1 <= line.length()) {
                afterstring = line.substr(secNumStart + secLenght + 1, line.length() - secNumStart + secLenght);
            }

            // prevence abychom nečetli v stringu za koncem
            wstring beforestring = L"";
            if (numStart - lenght > 0) {
                beforestring = line.substr(0, numStart - lenght);
            }

            //pokud nějaká část není definovaná potom je 0
            if (fnum == L"") { fnum = L"0"; }
            if (snum == L"") { snum = L"0"; }

            // teď je linka rozdělená na:  beforestring ( fnum : snum )?: afterstring  


            wstring lineFormula = L"(" + fnum + L")*60+" + snum;


            wstring solution = L"";
            wstring solutionNR = L"";
            wstring err = L"";

            solveLine(lineFormula, &solution, &solutionNR, &err);

            //ttmath::ErrorCode err = parser.Parse(lineFormula);

            if (err == L"") {
                line = beforestring + parser.stack[0].value.ToWString() + afterstring;
                //line.replace(numStart - lenght, lenght + secLenght + 1, parser.stack[0].value.ToWString());
            }
            else {
                *errorText = L"Cant Convert Time";
                return MATHERR_INVALID_SINTAX;
            }

            ocur2 = line.find(L":");
            dbg(
                std::wcout << L"operator : sekaná linka ->" << beforestring.c_str() << L";" <<  fnum.c_str() << L";" << snum.c_str() << L";" << afterstring.c_str() << std::endl;
                std::wcout << L"operator : sformulovaná linka->" << lineFormula.c_str() << std::endl;
                std::wcout << L"operator : poparsovaná linaka->" << line.c_str() << std::endl;
            )
        }
    }

    if (settings->getBool("UseMetrics") || lineUsingMetrics) { // check to somethink
        size_t ocur = line.find(L" to ");
        while (ocur != wstring::npos){
            line = L"(" + line;
            line.replace(ocur+1, 4, L")/");
            ocur = line.find(L"to ");
        }
    }

    // korekce neuzavřených závorek & ignorování veikosti písmen
    if (settings->getBool("IgnoreHightDiference") || settings->getBool("CorectParenthesis")) {
        size_t parCountOP = 0,parCountCL = 0;
        for (size_t i = 0; i < line.length(); i++){
            if (settings->getBool("IgnoreHightDiference")) {
                line.at(i) = towlower(line.at(i));      //set all characters to small
            }
            if (settings->getBool("CorectParenthesis")) {
                if (line.at(i) == L'(') {
                    parCountOP++;
                }else if (line.at(i) == L')') {
                    parCountCL++;
                }
            }
        }

        if (settings->getBool("CorectParenthesis")) {
            if (parCountOP > parCountCL) {
                for (size_t i = 0; i < parCountOP - parCountCL; i++){
                    line = line + L")";
                }
            }
        }
    }

    // pokud jsou zaplé ljumps anhradí skok výsledkem
    if (settings->getBool("AllowLineJump")) {
        size_t lastSeenEq = line.find(POINTER_CHAR);
        while (lastSeenEq != string::npos) {  
            for (int i = lastSeenEq; i < line.length(); i++) {
                bool isOnEnd = i == line.length() - 1;
                if (isOnEnd || !iswdigit(line.at(i + 1))) {
                    try {
                        int lineId = stoi(line.substr(lastSeenEq + 1, i - lastSeenEq));
                        if (lineId >= procesedLines->size() - 1) {
                            *errorText = L"Invalid Line Jump";
                            return MATHERR_INVALID_LINE_JUMP_NUM;
                        }
                        if (settings->getBool("UseNoRoundPointers")) {
                            line = line.substr(0, lastSeenEq) + L"(" + procesedLines->at(lineId).solutionNoRound + L")" + line.substr(i + 1, line.length() - i);
                        } else {
                            line = line.substr(0, lastSeenEq) + L"(" + procesedLines->at(lineId).solution + L")" + line.substr(i + 1, line.length() - i);
                        }
                    }
                    catch (exception& err) {
                        *errorText = L"No Line Jump Number";
                        return MATHERR_INVALID_LINE_JUMP_NUM;
                    }
                    break;
                }
            }
            lastSeenEq = line.find(POINTER_CHAR, ++lastSeenEq);
        }
    }



    // doeší linku (pokud po : zůstal jeden výsledek tak ten vyřeší též jen s ním nic neprovede)
    ttmath::ErrorCode err = parser.Parse(line); // actuali solve line


    // nastavit řešení
    if (err == 0) {
        *solution = parser.stack[0].value.ToWString(ConvertionRole);
        *solutionNoRound = parser.stack[0].value.ToWString();
    }else {
        *errorText = L"Line Unsolvable";
    }

    return err;
}

wstring getNumFrom(wstring * s,int index) {
    wstring num = L"";
    for (int i = index; i < s->length();i++) {
        if (iswdigit(s->at(i))) {
            num = num + s->at(i);
        } else {
            return num;
        }
    }
    return num;
}

int MatematicalSolver::modifyMathRules(wstring * rules){
    size_t rulePos = rules->find_last_of(L'r');
    if (rulePos != string::npos) {
        try {
            ConvertionRole.round = std::stoi(getNumFrom(rules, rulePos + 1));
        }
        catch (std::exception const& e) {
            dbg(
                std::cout << "error modifier INT r" << std::endl;
            )
        }
    }


    rulePos = rules->find_last_of(L'b');
    if (rulePos != string::npos) {
        try {
            ConvertionRole.base = std::stoi(getNumFrom(rules, rulePos + 1));
        }
        catch (std::exception const& e) {
            dbg(
                std::cout << "error modifier INT b" << std::endl;
            )
        }
    }

    rulePos = rules->find(L'c');
    if (rulePos != string::npos) {
        return END_LINE_SOLVING;
    }

    


    //chceck for Coment


    return 0;
};

bool MatematicalSolver::setDefaultMathRules() {
    ConvertionRole.round = settings->getInt("RoundToDec");
    ConvertionRole.group = ' ' * (bool)settings->getInt("NumberGrouping");
    ConvertionRole.group_digits = settings->getInt("NumberGrouping");
    ConvertionRole.scient = settings->getBool("UseSientific");
    ConvertionRole.base_round = false;
    ConvertionRole.scient_from = 100; //pokud je nad 100 míst použije se sience number i když je vyplé (kvuli tomu aby se nepoužívalo dřív)
    ConvertionRole.base = 10;
    return true;
};


void MatematicalSolver::addMetricsToTable() { // zkontrolovat převod (:
    if (!(varTable.IsDefined("km") || varTable.IsDefined("den") || varTable.IsDefined("mg"))) {
        varTable.Add("km", "1000");
        varTable.Add("m", "1");
        varTable.Add("dm", "0.1");
        varTable.Add("cm", "0.01");
        varTable.Add("mm", "0.001");

        varTable.Add("den", "86400");
        varTable.Add("day", "86400");
        varTable.Add("h", "3600");
        varTable.Add("min", "60");
        varTable.Add("s", "1");

        varTable.Add("mg", "0.001");
        varTable.Add("g", "1");
        varTable.Add("dag", "10");
        varTable.Add("kg", "1000");
        varTable.Add("t", "1000000");


        //přidat měny


    }
    
}


void MatematicalSolver::removeBeforeAfterSpaces(wstring* line) {
    size_t start = 0;
    for (size_t i = 0; i < line->length(); i++) {
        if (line->at(i) != L' ') {
            start = i;
            break;
        }
    }
    for (int i = line->length() - 1; i >= 0; i--) {
        if (line->at(i) != L' ') {
            *line = line->substr(start, i - start + 1);
            return;
        }
    }
}



bool MatematicalSolver::solveVariableLine(mline* line, int eqPos) {

    wstring beforeEQ = line->line.substr(0, eqPos);

    if (settings->getBool("IgnoreHightDiference")) {
        size_t parCountOP = 0, parCountCL = 0;
        for (size_t i = 0; i < beforeEQ.length(); i++) {
            beforeEQ.at(i) = towlower(beforeEQ.at(i));      //set all characters to small
        }
    }

    if (settings->getBool("UseSumVariable") && beforeEQ == L"sum") {
        creteErrorLineSolution(line, L"Redefintion of system Sum variable", MATHERR_INVALID_VARIABLE_NAME);
        return false;
    }
    

    removeBeforeAfterSpaces(&beforeEQ);

    wstring afterEQ = line->line.substr(eqPos + 1, line->line.length());

    if (!isValidVariableName(beforeEQ)) { //ošetření neplatného jména
        creteErrorLineSolution(line, L"Variable Name contains Forbident simbols", MATHERR_INVALID_VARIABLE_NAME);
        return false;
    }

    // if use metrics disalow variables named to. (it calls error but )
    if (settings->getBool("UseMetrics") && beforeEQ == L"to") {
        creteErrorLineSolution(line, L"Variable name conflicts with to operator", MATHERR_INVALID_VARIABLE_NAME);
        return false;
    }

    wstring errorText = L"Math Err";

    if (solveLine(afterEQ, &line->solution,&line->solutionNoRound, &errorText) != 0) { // is is error
        creteErrorLineSolution(line, errorText, MATHERR_INVALID_NUMBER_FOR_OPERARTION);
        return false;
    }
    else {
        line->completlySolved = true;
        line->localVariableName = beforeEQ;

        wstring solutionVtext;
        if (settings->getBool("UseNoRoundPointers")) {
            solutionVtext = line->solutionNoRound;
        }else {
            solutionVtext = line->solution;
        }

        if (varTable.IsDefined(beforeEQ)) {
            varTable.EditValue(beforeEQ, solutionVtext);
        } else {
            varTable.Add(beforeEQ, solutionVtext);
        };
    }
    return true;
}



void MatematicalSolver::executeMathComand(mline* line) {


    if (line->command == L"sumbrake" || line->command == L"rstsum") {
        line->solution = L"SUM_BREAK";
        line->isComandDone = true;
        line->completlySolved = true;
        line->isSumBrake = true;
    }else if (line->command == L"sum") {
        wstring textnumber = L"";
        for (size_t i = 0; i < procesedLines->size(); i++) {
            if (&procesedLines->at(i) == line) { break; } // sum only lines abo;
            if (procesedLines->at(i).isSumBrake == true) { textnumber = L""; }
            if (procesedLines->at(i).completlySolved && procesedLines->at(i).localVariableName == L"") {
                textnumber.append(procesedLines->at(i).solution + L" + ");
            }
            //todo dbgLog(textnumber);
        }

        textnumber.append(L"0");
        ttmath::ErrorCode err = parser.Parse(textnumber);
        if (err == 0) {
            //line->solution = parser.stack[0].value.ToWString();
            line->line = parser.stack[0].value.ToWString() + L" " + line->line;
            line->isComandDone = true;
            line->completlySolved = false;
        }
        else {
            line->solution = L"countingProblem";
            line->isComandDone = true;
            line->completlySolved = true;
        }
    }
    else if (line->command == L"sumV") {
        wstring textnumber = L"";
        for (size_t i = 0; i < procesedLines->size(); i++) {
            if (&procesedLines->at(i) == line) { break; } // sum only lines abo;
            if (procesedLines->at(i).command == L"rstsum") { textnumber = L""; }
            if (procesedLines->at(i).completlySolved) {
                textnumber.append(procesedLines->at(i).solution + L" + ");
            }
            //todo dbgLog(textnumber);
        }

        textnumber.append(L"0");
        ttmath::ErrorCode err = parser.Parse(textnumber);
        if (err == 0) {
            line->line = parser.stack[0].value.ToWString() + L" " + line->line;
            line->isComandDone = true;
            line->completlySolved = false;
        }
        else {
            line->solution = L"countingProblem";
            line->completlySolved = true;
        }
    }
    else if (line->command == L"rand") {
        double i = (float)rand() / (RAND_MAX);
        line->line = to_wstring(i) + L" " + line->line;
        line->isComandDone = true;
        line->completlySolved = false;
    }
    else if (line->command == L"randi") {
        int i = rand();
        line->line = to_wstring(i) + L" " + line->line;
        line->isComandDone = true;
        line->completlySolved = false;
    }
    else if (line->command == L"randn") {
        float i = ((float)rand() / (RAND_MAX) - 0.5)*2;
        line->line = to_wstring(i) + L" " + line->line;
        line->isComandDone = true;
        line->completlySolved = false;
    }
    else if (line->command == L"metrics") {
        addMetricsToTable();
        lineUsingMetrics = true;
        line->solution = L"Metrics Added";
        line->isComandDone = true;
        line->completlySolved = true;
    }
}



bool MatematicalSolver::isSameLine(mline* line1, mline* line2) {
    size_t lineSize1 = line1->line.size();
    size_t lineSize2 = line2->line.size();

    if (line1->line.size() != line2->line.size() || line1->command.size() != line2->command.size()) {
        return false;
    }
    else if (FAST_SAME) {
        return true;
    }

    return line1->line.compare(line2->line) && line1->command.compare(line2->command);

}



bool MatematicalSolver::hasAnyVariable(mline* line) {
    return false;
}



int MatematicalSolver::findEqualition(wstring* line) { // vrátí true když opsahuje samostatné = ,index je hejo pozice
    size_t lastSeenEq = line->find(L"=");

    while (lastSeenEq != string::npos) {

        // line contains -> (  line->at(lastSeenEq + 1) == L'=' ||  )
        //test = behind
        // test alos before

        if (lastSeenEq + 1 < line->length() && line->at(lastSeenEq + 1) != L'=') {
            if (lastSeenEq >= 1 && line->at(lastSeenEq - 1) != L'<' && line->at(lastSeenEq - 1) != L'<' && line->at(lastSeenEq - 1) != L'!') { // check if = is not operation
                return lastSeenEq;  // vrtí pozici =
            }

        }
        lastSeenEq = line->find(L"=", ++lastSeenEq);
    }
    return -1;
};




bool MatematicalSolver::isValidVariableName(wstring name) { // var neobsahuje []{}=&@ a ani číslo // mabey rerete variableTable.IsNameCorrect
    if (iswdigit(name.at(0))) { return false; }

    for (size_t i = 0; i < name.length(); i++) {
        wchar_t simbol = name.at(i);
        for (size_t c = 0; c < VARIABLE_FORBIDENT_SIMBOLS_LENGHT; c++) {
            if (simbol == forbidentVariableSimbols[c]) {
                return false;
            }
        }
    }

    return true;
}



void MatematicalSolver::creteErrorLineSolution(mline* line, wstring text, int errorCode) {
    line->completlySolved = false;
    line->isError = true;
    line->solutionModifier = L"ERROR";
    line->solution = text;
    //line->error.type = errorCode;
}