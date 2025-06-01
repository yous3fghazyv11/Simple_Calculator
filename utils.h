#pragma once
#include <cassert>
#include <cmath>
#include <stdexcept>
#include <string>

inline std::string color(std::string text, char color)
{
    std::string green = "\033[32m";
    std::string red   = "\033[31m";
    std::string white = "\033[0m";
    switch (color)
    {
        case 'r':
            return red + text + white;
            break;
        case 'g':
            return green + text + white;
            break;
        default:
            return "";
    }
}

inline double factorial(double num)
{
    if (num < 0 || std::floor(num) != num)
        throw std::runtime_error(color("Factorial of negative/non-integer", 'r'));
    if (num == 1 || num == 0)
        return 1;
    return num * (factorial(num - 1));
}
