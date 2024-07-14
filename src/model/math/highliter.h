#pragma once

#include <vector>
#include <string>
#include "../../link/debugger.hpp"
#include "../../link/settings_link.hpp"
#include "../../link/math_link.hpp"

using namespace std;

class MathHighliter {

    SettingsLinkAP * settings;
    std::vector<MathHighlite> highlites;

public:
    MathHighliter(SettingsLinkAP * settings);

    std::vector<MathHighlite>* procesHighlite(wstring* str);
};


MathHighliter::MathHighliter(SettingsLinkAP * settings){
    this->settings = settings;
}

std::vector<MathHighlite>* MathHighliter::procesHighlite(wstring* text) {
        
        highlites.clear();
        MathHighlite highlite;

        enum eat_state { consume, after_comment, consume_a_modi,  is_comment};
        eat_state state;

        int line_start = 0;

        //highlite comments and modifiers
        for (size_t i = 0; i < text->size(); i++){
            switch (state){
            case consume:
                if(text->at(i) == 'c'){
                    state = is_comment;
                }else if(text->at(i) == ';'){
                    highlite.start = line_start;
                    highlite.stop = i+1;
                    highlite.type = MODIFIER;
                    highlites.push_back(highlite);
                    state = consume_a_modi;
                }else if(text->at(i) == '('){
                    state = consume_a_modi;
                }else if(text->at(i) == '\n'){
                    line_start = i;
                }
                break;
            case consume_a_modi:
                if(text->at(i) == '\n'){
                    line_start = i;
                    state = consume;
                }
                break;
            case is_comment:
                if(text->at(i) == ';'){
                    highlite.start = line_start;
                    highlite.stop = i+1;
                    highlite.type = MODIFIER;
                    highlites.push_back(highlite);
                    line_start = i+1;
                    state = after_comment;
                }
                break;
            case after_comment:
                if(text->at(i) == '\n' || i == text->size() ){
                    highlite.start = line_start;
                    highlite.stop = i;
                    highlite.type = COMMNET;
                    highlites.push_back(highlite);
                    line_start = i;
                    state = consume;
                }
                break;
            }
        }
        
        line_start = 0;
        std::wstring list_of_chars = std::wstring(L" +-*/%^<>=!&|()123456890@\n");
        std::wstring list_of_nums = std::wstring(L"123456890");
        enum eat_cmd_state { start, command, not_command, jump};
        eat_cmd_state state_cmd;

        // highlite commands
        for (size_t i = 0; i < text->size(); i++){
            switch (state_cmd){
            case start:
                if(text->at(i) == ';'){
                    state_cmd = command;
                }else if(text->at(i) == '\n'){
                }else if(text->at(i) == '@'){
                    line_start = i;
                    state_cmd = jump;
                }else{
                    state_cmd = not_command;
                }
                break;
            case command:
                if(list_of_chars.find(text->at(i)) != std::string::npos || i == text->size()){
                    highlite.start = line_start;
                    highlite.stop = i;
                    highlite.type = COMMAND;
                    highlites.push_back(highlite);

                    line_start = i;
                    state_cmd = not_command;
                    if(text->at(i) == '@'){
                       line_start = i;
                       state_cmd = jump;
                   }
                }
                break;
            case not_command:
                if(text->at(i) == '\n'){
                    line_start = i;
                    state_cmd = start;
                }
                if(text->at(i) == '@'){
                    line_start = i;
                    state_cmd = jump;
                }
                break;
            case jump:
                if(list_of_nums.find(text->at(i)) == std::string::npos || i == text->size()){
                    if(line_start + 1 != i){
                       highlite.start = line_start;
                       highlite.stop = i;
                       highlite.type = JUMP;
                       highlites.push_back(highlite);
                    }

                    line_start = i;
                    state_cmd = start;
                }
                break;
            }
        }

        return &highlites;
}
