#include <vector>
#include <string>

struct MathLine{
    int height;
    std::wstring line;
};

struct MathSolutionLine{
    std::string solution;
    bool isVariable = false;
    bool isError = false;
};

//std::vector <MathLine> lines;

