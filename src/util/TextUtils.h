
#include <string> 
#include <vector>

namespace TextUtils
{
    

    static std::vector<std::string> stringFit(std::string str, int lenght) {
        std::vector<std::string> lines = {};
        
        int charsInLine = 0;
        for (int i = 0; i < str.size(); i++) {
            charsInLine += 1;
            if (charsInLine >= lenght) {
                lines.push_back(str.substr(i-charsInLine, i));
                charsInLine = 0;
            }
        }

        return lines;
    }


}



