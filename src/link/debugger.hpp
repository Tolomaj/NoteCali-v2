#include <iostream>
#pragma once


#define CLR_NC "\e[0m"
#define CLR_RED "\e[0;31m"
#define CLR_GRN "\e[0;32m"
#define CLR_YEL "\e[0;33m"
#define CLR_BLE "\e[0;34m"
#define CLR_MAG "\e[0;35m"
#define CLR_CYN "\e[0;36m"
#define CLR_REDB "\e[41m"


#if DEBUG == 2
#define dbgLog(str) std::cout << __FILE__ << "/" << __LINE__ << ": " << str << std::endl;
#define dbgErr(str) std::cout << __FILE__ << "/" << __LINE__ << ": " << "\x1B[31m" << str << "\033[0m" << std::endl;
#define dbgInfo(str)std::cout << __FILE__ << "/" << __LINE__ << ": " << "\x1B[34m" << str << "\033[0m" <<  std::endl;
#define dbg(x) x


#elif DEBUG == 1
#define dbgLog(str) std::cout << str << std::endl;
#define dbgErr(str) std::cout << "\x1B[31m" << str << "\033[0m" << std::endl;
#define dbgInfo(str) std::cout << "\x1B[34m" << str << "\033[0m" <<  std::endl;
#define dbg(x) x

#else
#define dbgLog(...)
#define dbgErr(...)
#define dbgInfo(...)
#define dbg(...)
#endif

