#include <iostream>
#pragma once

#if DEBUG == 2
#define dbgLog(str) std::cout << __FILE__ << "/" << __LINE__ << ": " << str << std::endl;
#define dbgErr(str) std::cout << __FILE__ << "/" << __LINE__ << ": " << "\x1B[31m" << str << "\033[0m" << std::endl;
#define dbgInfo(str)std::cout << __FILE__ << "/" << __LINE__ << ": " << "\x1B[34m" << str << "\033[0m" <<  std::endl;

#elif DEBUG == 1
#define dbgLog(str) std::cout << str << std::endl;
#define dbgErr(str) std::cout << "\x1B[31m" << str << "\033[0m" << std::endl;
#define dbgInfo(str) std::cout << "\x1B[34m" << str << "\033[0m" <<  std::endl;

#else
#define dbgLog(...)
#define dbgErr(...)
#define dbgInfo(...)
#endif