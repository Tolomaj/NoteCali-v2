#include "../link/math_link.hpp"
#include "../link/settings_link.hpp"
#include "../link/window_link.hpp"
#include "../view/calculator/calculator_window.hpp"
#include "../view/settings/settings_window.hpp"

class Controller : public CalculatorWindowLink , public SettingsWindowLink{
private:

    CalculatorWindow *main_win;
    SettingsWindow *settings_window = nullptr;
    //settings
    //algorithm
public:
    Controller(SettingsLink * settings){
        main_win = new CalculatorWindow(settings,this);
    };

    /// @brief interface form CalculatorWindowLink
    void close_calculator() override {
        main_win->close();
        if(settings_window != nullptr){
            settings_window->close();
        }
    };
    void openSettings() override {
        if(settings_window == nullptr){
            settings_window = new SettingsWindow(this);
        }else{
            delete settings_window;
            settings_window = nullptr;
        }
    };

    void solve(std::vector<std::wstring> * lines) override {
        for (size_t i = 0; i < lines->size(); i++){
            std::wstring wide = lines->at(i);
            std::string str( wide.begin(), wide.end());
            dbgInfo(str);
        }
        
        //todo
    };

    /// @brief interface form SettingsWindowLink
    void close_settings() override {
        //todo
    };

    void setBool(std::string name,bool value) override {
        //todo
    };
    void setInt(std::string name,int value) override {
        //todo
    };
    void setWString(std::string name,std::wstring value) override {
        //todo
    };


};
