#include "token.h"
#include "utils.h"
#include <iostream>

void Token_stream::putback(Token t)
{
    if (full)
        throw std::runtime_error(color("error: putback() into a full buffer", 'r'));
    buffer = t;
    full   = true;
}

Token Token_stream::get()
{
    if (full)
    {
        full = false;
        return buffer;
    }
    char ch;
    std::cin >> ch;
    if (std::cin.eof())
    {
        std::cout << std::endl << "Exiting..." << std::endl;
        exit(0);
    }

    switch (ch)
    {
        case ';':
        case 'q':
        case '(':
        case ')':
        case '+':
        case '-':
        case '*':
        case '/':
        case '!':
        case '^':
            return Token(ch);
        case '.':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        {
            std::cin.putback(ch);
            double val;
            std::cin >> val;
            return Token('8', val);
        }
        default:
            throw std::runtime_error(color("Bad token", 'r'));
    }
}
