#include "../link/math_link.hpp"
#include "../link/settings_link.hpp"
#include "../link/window_link.hpp"
#include "../view/calculator/calculator_window.hpp"
#include "../view/settings/settings_window.hpp"
#include "../model/math/line_separator.h"

class Controller : public CalculatorWindowLink , public SettingsWindowLink{
private:
    CalculatorWindow *calculator_window;
    SettingsWindow *settings_window = nullptr;
    SettingsLink * settings;
    LineSeparator * line_separator;
    //algorithm
public:
    Controller(SettingsLink * settings){
        this->settings = settings;
        calculator_window = new CalculatorWindow(settings,this);
        line_separator = new LineSeparator(settings);
    };

    /// @brief interface form CalculatorWindowLink
    void close_calculator() override {
        calculator_window->close();
        if(settings_window != nullptr){
            settings_window->close();
        }
    };
    void openSettings() override {
        if(settings_window == nullptr){
            settings_window = new SettingsWindow(settings,this);
            settings_window->loadSettings(settings);
        }else{
            delete settings_window;
            settings_window = nullptr;
        }
    };

    void solve(std::vector<std::wstring> * lines) override {
        std::wstring linesAll; 
        
        for (size_t i = 0; i < lines->size(); i++){
            linesAll += lines->at(i) + L"\n";

            std::wstring wide = lines->at(i);
            std::string str( wide.begin(), wide.end());
        }


        /*      HAZARD ZONE         */
        line_separator->procesInput(&linesAll);

        dbg(
            std::cout << CLR_BLE << "┌──────────────────────────────────────────┐" << CLR_NC << std::endl;
            std::cout << CLR_BLE << "│░░░░░░░░░░░░LINE SOLWING START░░░░░░░░░░░░│" << CLR_NC << std::endl;
            std::cout << CLR_BLE << "└──────────────────────────────────────────┘" << CLR_NC << std::endl;
            line_separator->printLines();

        )


        std::vector<MathSolutionLine> solved_lines;
        solved_lines.push_back({"solution",false,false,false});

        calculator_window->present(&solved_lines);
    };

    /// @brief interface form SettingsWindowLink
    void close_settings() override {
        //todo
    };

    void onSettingsChangeUpdate(std::string name){
        std::string cathegory = settings->get_cathegory(name);
        if(cathegory == "Style"){
            calculator_window->reloadStyles();
            settings_window->reloadStyles();
        }
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
        //todo
        std::cout << "settingWstring: " << name << std::endl;
    };

    void setSpecial(std::string name) override {
        //todo
        std::cout << "settingSpecial " << name << std::endl;
    };


};
