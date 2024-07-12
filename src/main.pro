QT += widgets

CONFIG += c++17
CONFIG += console
QMAKE_CXXFLAGS += -Wno-enum-compare

SOURCES = main.cpp
SOURCES += view/settings/settings_window.cpp

HEADERS = view/calculator/calculator_boady.hpp
HEADERS += view/calculator/calculator_header.hpp
HEADERS += view/calculator/solution_box.hpp

HEADERS += view/settings/settings_list.hpp
HEADERS += view/settings/settings_window.hpp
HEADERS += view/settings/bool_settings_entry.hpp
HEADERS += view/settings/int_settings_entry.hpp
HEADERS += view/settings/wstring_settings_entry.hpp
HEADERS += view/settings/font_string_settings_entry.hpp
