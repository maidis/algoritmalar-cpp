#include <iostream>
#include <string>
#include <map>

std::string getGrade(int numberGrade)
{
    if (numberGrade >= 0 && numberGrade <= 100)
    {
        std::map<int, std::string> score = {
            { 30, "FF" },
            { 50, "FD" },
            { 60, "DD" },
            { 65, "CC" },
            { 70, "CB" },
            { 80, "BB" },
            { 90, "BA" },
            { 101, "AA" }
        };

        for (const auto& i : score)
        {
            if (numberGrade < i.first)
            {
                return i.second;
            }
        }
    }
    return "";
}

int main()
{
    for (int i = 100; i >= 0; --i)
    {
        std::cout << i << " = " << getGrade(i) << std::endl;
    }

    return 0;
}
