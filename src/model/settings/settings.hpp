/*********************************************************************
 * @file  settings.hpp
 * @author tolomaj
 *
 * @brief setting objects
 * Qt inplementation of Settings (using interface defined in controler/settings_link.hpp)
 *********************************************************************/


#include <QSettings>
#include <vector>
#include <QVariant>
#include "../../link/settings_link.hpp"

class Settings : public SettingsLink {
    QSettings *settings;
    std::vector<SettingsEntryBool> boolSettngsList;
    std::vector<SettingsEntryWString> wstringSettngsList;
    std::vector<SettingsEntryInt> intSettngsList;
    

public:

    Settings(QString file){
        settings = new QSettings(file,QSettings::NativeFormat);
    }

    void save() override {
        // for this inlementation saving settings is not needed
    };

    bool getBool(std::string name) override {
        QVariant val = settings->value(name);
        if(val.isNull()){
           for (SettingsEntryBool & entry : boolSettngsList) {
                if(entry.name == name){
                    return entry.defaultValue;
                }
            } 
            //todo dbgErr("no entry found for: " + name);
        }
        return val.toBool();
    };

    int getInt(std::string name) override {
        QVariant val = settings->value(name);
        if(val.isNull()){
           for (SettingsEntryInt & entry : intSettngsList) {
                if(entry.name == name){
                    return entry.defaultValue;
                }
            } 
            //todo dbgErr("no entry found for: " + name);
        }
        return val.toInt();
    };

    std::wstring getWString(std::string name) override{
        QVariant val = settings->value(name);
        if(val.isNull()){
           for (SettingsEntryWString & entry : wstringSettngsList) {
                if(entry.name == name){
                    return entry.defaultValue;
                }
            } 
            //todo dbgErr("no entry found for: " + name);
        }
        return val.toString().toStdWString();
    };


    void createBoolEntry(std::string name,std::string category,bool defaultValue,std::wstring desription) override {
        boolSettngsList.push_back({name,category,defaultValue,desription});
    };

    // option is [1,2] (min,max) [3](step)
    void createIntEntry(std::string name,std::string category,int defaultValue,std::wstring desription,std::vector<int> options  = {}) override{
        intSettngsList.push_back({name,category,defaultValue,desription,options});
    };
    
    void createWStringEntry(std::string name,std::string category,std::wstring defaultValue,std::wstring desription, StringType type = PLAIN,std::vector<std::wstring> options  = {}) override {
        wstringSettngsList.push_back({name,category,defaultValue,desription,type,options});
    };

    SettingsEntryBool getBoolEntry(int i) override {
        if(i >= boolSettngsList.size()){
            return {"","",false};
        }
        return boolSettngsList.at(i);
    };
    SettingsEntryInt getIntEntry(int i) override {
        if(i >= intSettngsList.size()){
            return {"","",0};
        }
        return intSettngsList.at(i);
    };
    SettingsEntryWString getWStringEntry(int i) override {
        if(i >= wstringSettngsList.size()){
            return {"","",L""};
        }
        return wstringSettngsList.at(i);
    };

    void setBool(std::string name,bool value) override {
        settings->setValue(name,value);
    };

    void setInt(std::string name,int value) override {
        settings->setValue(name,value);
    };

    void setWString(std::string name,std::wstring value) override {
        settings->setValue(name,QString::fromWCharArray(value.c_str()));
    };

    std::string get_cathegory(std::string name){
        for (SettingsEntryBool & entry : boolSettngsList) {
            if(entry.name == name){
                return entry.category;
            }
        } 
        for (SettingsEntryInt & entry : intSettngsList) {
            if(entry.name == name){
                return entry.category;
            }
        } 
        for (SettingsEntryWString & entry : wstringSettngsList) {
            if(entry.name == name){
                return entry.category;
            }
        } 
        
        //todo dbgErr("no entry found for: " + name);
        return "";
    }
};

