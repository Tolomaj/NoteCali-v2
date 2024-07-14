#include "../link/math_link.hpp"
#include "../link/settings_link.hpp"
#include "../link/math_link.hpp"
#include "../link/window_link.hpp"
#include "../view/calculator/calculator_window.hpp"
#include "../view/settings/settings_window.hpp"

#include "../model/math/line_separator.h"
#include "../model/math/math_solver.h"
#include "../model/math/highliter.h"



class Controller : public CalculatorWindowLink , public SettingsWindowLink{
private:
    CalculatorWindow *calculator_window;
    SettingsWindow *settings_window = nullptr;
    SettingsLink * settings;
    LineSeparator * line_separator;
    MatematicalSolver * math_solver;
    MathHighliter *math_highliter;
    //algorithm
public:
    Controller(SettingsLink * settings){
        this->settings = settings;
        calculator_window = new CalculatorWindow(settings,this);
        line_separator = new LineSeparator(settings);
        math_solver = new MatematicalSolver(settings);
        math_highliter = new MathHighliter(settings);
    };

    /// @brief interface form CalculatorWindowLink
    void close_calculator() override {
        calculator_window->close();
        if(settings_window != nullptr){
            settings_window->close();
        }
    };

    void toggleSettings() override {

        if(settings_window == nullptr){
            settings_window = new SettingsWindow(settings,this);
            settings_window->loadSettings(settings);
        }else{
            delete settings_window;
            settings_window = nullptr;
        }
    };


    /// @brief interface form SettingsWindowLink
    void close_settings() override {
        toggleSettings();
    };

    void solve(std::vector<std::wstring> * lines) override {

        std::wstring linesAll; 
        
        for (size_t i = 0; i < lines->size(); i++){
            linesAll += lines->at(i) + L"\n";

            std::wstring wide = lines->at(i);
            std::string str( wide.begin(), wide.end());
        }

        vector<mline> * separated_lines = line_separator->procesInput(&linesAll);

        dbg(
            system(CLEAR);
            std::cout << CLR_BLE << "┌──────────────────────────────────────────┐" << CLR_NC << std::endl;
            std::cout << CLR_BLE << "│░░░░░░░░░░░░LINE SOLWING START░░░░░░░░░░░░│" << CLR_NC << std::endl;
            std::cout << CLR_BLE << "└──────────────────────────────────────────┘" << CLR_NC << std::endl;
            line_separator->printLines();
        )


        math_solver->solve(separated_lines);

        dbg(
            std::cout << CLR_YEL << "VYŘEŠENÉ LINKY:" << std::endl;
            for (size_t i = 0; i < separated_lines->size(); i++) {
                std::cout << "╠═╦line(" << i << ")»";
                std::wcout << L" mod:[" << separated_lines->at(i).lineModifier 
                           << L"] cmd:[" << separated_lines->at(i).command 
                           << L"] solved:[" << separated_lines->at(i).completlySolved 
                           << L"] line:[" << separated_lines->at(i).line << L"]" << std::endl;
                std::cout << "║ ╚line(" << i << ")»";
                std::wcout << L"var:[" << separated_lines->at(i).localVariableName << L"]" 
                        << L" mod:[" << separated_lines->at(i).solutionModifier 
                        //<< L"] unit:[" << separated_lines->at(i).solutionUnits
                        << L"] noRound:[" << separated_lines->at(i).solutionNoRound
                        << L"] solution:[" << separated_lines->at(i).solution << L"]" << std::endl;
            };
            std::cout << "╚END" << CLR_NC << std::endl;
        )

        calculator_window->present(separated_lines);

        if(settings->getBool("UseHighliting")){
            std::vector<MathHighlite> * highlites = math_highliter->procesHighlite(&linesAll);
            calculator_window->highlite(highlites);
        };

    };


    void onSettingsChangeUpdate(std::string name){
        //std::string cathegory = settings->get_cathegory(name);
        //if(cathegory == "Style"){
            calculator_window->reloadStyles();
            settings_window->reloadStyles();
        //}
    }

    void setBool(std::string name,bool value) override {
        settings->setBool(name,value);
        this->onSettingsChangeUpdate(name);
        
        std::cout << "settingBool: " << name << std::endl;
    };
    void setInt(std::string name,int value) override {
        settings->setInt(name,value);
        this->onSettingsChangeUpdate(name);

        std::cout << "settingInt: " << name << std::endl;
    };
    void setWString(std::string name,std::wstring value) override {
        settings->setWString(name,value);
        this->onSettingsChangeUpdate(name);

        std::cout << "settingWstring: " << name << std::endl;
    };

    void setSpecial(std::string name) override {
        //todo
        std::cout << "settingSpecial " << name << std::endl;
    };


};
