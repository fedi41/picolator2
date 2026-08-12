
#include <string> 
#include <vector>

namespace TextUtils
{
    

    static std::vector<std::string> stringFit(std::string str, int lenght) {
        std::vector<std::string> lines = {};
        
        int i = 0;

        while (i+lenght < str.size()) {
            lines.push_back(str.substr(i,lenght));
            i += lenght;
        } 
        lines.push_back(str.substr(i,lenght));


        return lines;
    }


}



