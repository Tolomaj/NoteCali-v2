QT += widgets

CONFIG += c++17
CONFIG += console
QMAKE_CXXFLAGS += -Wno-enum-compare

SOURCES = main.cpp
SOURCES += view/settings/settings_window.cpp

release: DESTDIR = ../output/
debug:   DESTDIR = ../output/

OBJECTS_DIR = $$DESTDIR/tmp
MOC_DIR = $$DESTDIR/tmp
RCC_DIR = $$DESTDIR/tmp
UI_DIR = $$DESTDIR/tmp


HEADERS = view/calculator/calculator_boady.hpp
HEADERS += view/calculator/calculator_header.hpp

HEADERS += view/settings/settings_list.hpp
HEADERS += view/settings/settings_window.hpp
HEADERS += view/settings/settings_sidepanel.hpp

HEADERS += view/settings/settings_entries/bool_settings_entry.hpp
HEADERS += view/settings/settings_entries/int_settings_entry.hpp
HEADERS += view/settings/settings_entries/wstring_settings_entry.hpp
HEADERS += view/settings/settings_entries/font_string_settings_entry.hpp
HEADERS += view/settings/settings_entries/color_string_settings_entry.hpp
