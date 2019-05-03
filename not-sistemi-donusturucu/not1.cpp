#include <iostream>
#include <string>

std::string getGrade(int numberGrade)
{
    if (numberGrade >= 0 && numberGrade <= 100)
    {
        if (numberGrade > 89)
        {
            return "AA";
        }
        else if (numberGrade > 79)
        {
            return "BA";
        }
        else if (numberGrade > 69)
        {
            return "BB";
        }
        else if (numberGrade > 64)
        {
            return "CB";
        }
        else if (numberGrade > 59)
        {
            return "CC";
        }
        else if (numberGrade > 49)
        {
            return "DD";
        }
        else if (numberGrade > 29)
        {
            return "FD";
        }
        else
        {
            return "FF";
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
