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
#include <iostream>
#include <QFontDialog>


#define DEBUG 2

#include "link/debugger.hpp"
#include "link/math_link.hpp"
#include "model/settings/settings.hpp"

#include "controler/controller.hpp"


int main(int argc, char **argv) {
    //dbgInfo("App Starting");
    QApplication app(argc, argv);

    Settings * settings = new Settings("setings.ini");

    /* test area */

    settings->createBoolEntry("NativeTitleBar","Style",false,L"Use System Native Window Title Bar");
    settings->createBoolEntry("FloatingDivider","Style",false,L"");
    settings->createIntEntry("LineDefaultPosition","Style",70,L"",{0,2,100});
    settings->createWStringEntry("Theme","Style",L"Auto",L"",COMBO,{L"Dark",L"Light",L"Manual"});
    settings->createIntEntry("FontSize","Style",0,L"",{0,40});
    settings->createWStringEntry("Font","Style",L"Helvetica",L"",FONT);


    settings->createBoolEntry("UseLineModifiers","Calculation",true,L"");
    settings->createBoolEntry("UseMetrics","Calculation",false,L"");
    settings->createBoolEntry("UseRadians","Calculation",false,L"");
    settings->createBoolEntry("UseSumVariable","Calculation",true,L"");


    settings->createBoolEntry("separated_lines","Calculation",true,L"");
    settings->createBoolEntry("UseTimeFormat","Calculation",false,L"");
    settings->createBoolEntry("CorectParenthesis","Calculation",false,L"When expresion is not properly ended with ( the ')' will by addet to end of solution.\nFor example '(2)*(5+5' is 20");
    settings->createBoolEntry("IgnoreHightDiference","Calculation",true,L"Dont make diference between Ab+C+2 & ab+C+6");
    settings->createBoolEntry("UseSientific","Calculation",false,L"");

    settings->createIntEntry("NumberGrouping","Calculation",0,L"Group numbers to groups of N. For Exmaple 3 -> (100 000 000)");
    settings->createIntEntry("RoundToDec","Calculation",0,L"Round solution to N decimal places");
    
    settings->createBoolEntry("ClickToCopy","Calculation",true,L"on Click solution is saved to clipboard.\n Otherwise text become selectable and you must select & press ctrl+C to copy solution");
    settings->createBoolEntry("CopyRounded","Calculation",false,L"When copying by clcking copy rounded solution (exact what is shownd). \nOtherwise use more acurate value");


    Controller * controller = new Controller(settings);




    return app.exec(); 
}