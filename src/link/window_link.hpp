/// obsahuje callbcky na controller

#include <string>
#include <vector>
#pragma once

class CalculatorWindowLink{
    public: virtual void close_calculator() = 0;
    public: virtual void openSettings() = 0;
    public: virtual void solve(std::vector<std::wstring> * lines) = 0;
};

class SettingsWindowLink{
    public: virtual void close_settings() = 0;
    public: virtual void setBool(std::string name,bool value) = 0;
    public: virtual void setInt(std::string name,int value) = 0;
    public: virtual void setWString(std::string name,std::wstring value) = 0;
    public: virtual void setSpecial(std::string name) = 0;
};