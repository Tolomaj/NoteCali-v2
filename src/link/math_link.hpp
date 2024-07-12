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

/// @brief struct that define solved line vith all data that is created in solving process
struct mline { 
	bool isEnded = true;	
	bool isSumBrake = false;
	bool isComandDone = false;	// comand on this line is done
	bool completlySolved = false;	// if is there any solution and is proceed
	bool isHiden = false;       // if its comment it hides solution
	bool isError = false;

	std::wstring command = L"";
	std::wstring lineModifier = L""; // comand for program or comand that modify line behavior
	std::wstring line = L"";		// line to solve

	std::wstring localVariableName = L""; // if line defines variable, the name is stored here (for presenting)
	std::wstring solution = L""; // copiable solution to line
	std::wstring solutionNoRound = L""; // copiable solution to line
	std::wstring solutionModifier = L""; // not copiable coment to solution
};

/// @brief struct that defines part in text hat is defined [//todo]
enum HightlightType{ RED, BLUE, RED_BOLD};
struct MathHighlite{
    HightlightType type;
    int start, stop;
};


