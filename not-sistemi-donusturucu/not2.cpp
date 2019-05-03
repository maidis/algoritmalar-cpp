#include <iostream>
#include <string>

std::string getGrade(int numberGrade)
{
    unsigned int quotient = numberGrade / 10;
    unsigned int remainder = numberGrade % 10;

    std::string letterGrade = "";

    switch (quotient)
    {
        case 10:
            letterGrade = "AA";
            break;
        case 9:
            letterGrade = "AA";
            break;
        case 8:
            letterGrade = "BA";
            break;
        case 7:
            letterGrade = "BB";
            break;
        case 6:
            letterGrade = "C";
            switch (remainder)
            {
                case 9:
                case 8:
                case 7:
                case 6:
                case 5:
                    letterGrade += "B";
                    break;
                case 4:
                case 3:
                case 2:
                case 1:
                case 0:
                    letterGrade += "C";
                    break;
            }
            break;
        case 5:
            letterGrade = "DD";
            break;
        case 4:
        case 3:
            letterGrade = "FD";
            break;
        case 2:
        case 1:
        case 0:
            letterGrade = "FF";
            break;
    }
    return letterGrade;
}

int main()
{
    for (int i = 100; i >= 0; --i)
    {
        std::cout << i << " = " << getGrade(i) << std::endl;
    }

    return 0;
}
