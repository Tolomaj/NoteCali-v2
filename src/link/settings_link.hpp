#include <string>
#include <variant>
#pragma once

#define ON  true
#define OFF false

/// @brief Settings enum
enum ThemeType{ AUTO, LIGHT, DARK, CUSTOM };

enum StringType{ PLAIN ,COMBO, FONT, COLOR };


/// @brief Settings entry (way to get all settings)
struct SettingsEntryBool{ std::string name; std::string category; bool defaultValue; std::wstring desription = L"";};
struct SettingsEntryInt{ std::string name; std::string category; int defaultValue;std::wstring desription = L""; std::vector<int> options = {};};
struct SettingsEntryWString{ std::string name; std::string category; std::wstring defaultValue;std::wstring desription  = L""; StringType type = PLAIN; std::vector<std::wstring> options = {};};

/// @brief template for settings acess point passed to all classes to have acces to them
class SettingsLinkAP{
    public: virtual bool getBool(std::string name) = 0;
    public: virtual int getInt(std::string name) = 0;
    public: virtual std::wstring getWString(std::string name) = 0;
};

/// @brief template for settings getter poin, provide function to get all settings used in app 
class SettingsLinkGP{
    public: virtual SettingsEntryBool getBoolEntry(size_t i) = 0;
    public: virtual SettingsEntryInt getIntEntry(size_t i) = 0;
    public: virtual SettingsEntryWString getWStringEntry(size_t i) = 0;
};

/// @brief template for settings
class SettingsLink : public SettingsLinkAP, public SettingsLinkGP{
    public: virtual void createBoolEntry(std::string name,std::string category,bool defaultValue,std::wstring desription) = 0;
    public: virtual void createIntEntry(std::string name,std::string category,int defaultValue,std::wstring desription,std::vector<int> options = {} ) = 0;
    public: virtual void createWStringEntry(std::string name,std::string category,std::wstring defaultValue,std::wstring desription,StringType type = PLAIN ,std::vector<std::wstring> options = {}) = 0;

    public: virtual void save() = 0;

    public: virtual void setBool(std::string name,bool value) = 0;
    public: virtual void setInt(std::string name,int value) = 0;
    public: virtual void setWString(std::string name,std::wstring value) = 0;

    public: virtual std::string get_cathegory(std::string name) = 0;

};
