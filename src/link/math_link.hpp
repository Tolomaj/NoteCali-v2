/*********************************************************************
 * @file  math_link.hpp
 * @author Ondřej Gross (xgross13)
 *
 * @brief comunication between objects
 * Platform independent way to comunicate between math solver and math presenter
 *********************************************************************/

#include <string>
#include <vector>
#pragma once

/// @brief struct that define solved line
struct MathSolutionLine{
    std::string solution;
    bool isVariable = false;
    bool isError = false;
    bool isInformation = false;
};

/// @brief struct that defines part in text hat is defined [//todo]
enum HightlightType{ RED, BLUE, RED_BOLD};
struct MathHighlite{
    HightlightType type;
    int start, stop;
};
