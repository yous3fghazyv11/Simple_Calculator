// basic calculator app
// author: yousef ghazy

/*
 * parsing grammar:
 * Expression: 
 *   Term + Term
 *   Term - Term
 *   Let var_name = Expression
 * Term:
 *   Power * Power
 *   Power / Power
 * power:
 *   Primary ^ Primary
 * Primary:
 *   Number
 *   Number!
 *   (Expression)
 *   (Expression)!
 */

#include <cassert>
#include <format>
#include <iostream>
#include <stdexcept>
#include <string>
#include "token.h"
#include "utils.h"

double expression();
double term();
double primary();
double power();

Token_stream ts;

double expression()
{
    double left = term();
    Token  next = ts.get();
    while (true)
    {
        switch (next.kind)
        {
            case '+':
                left += term();
                next = ts.get();
                break;
            case '-':
                left -= term();
                next = ts.get();
                break;
            default:
                ts.putback(next);
                return left;
        }
    }
}

double term()
{
    double left = power();
    Token  next = ts.get();
    while (true)
    {
        switch (next.kind)
        {
            case '*':
                left *= power();
                next = ts.get();
                break;
            case '/':
            {
                double d = power();
                if (d == 0)
                    throw std::runtime_error(color("error: devision by zero", 'r'));
                left /= d;
                next = ts.get();
                break;
            }
            default:
                ts.putback(next);
                return left;
        }
    }
}

double power()
{
    double left = primary();
    Token  next = ts.get();
    while (true)
    {
        if (next.kind == '^')
        {
            return std::pow(left, primary());
            next = ts.get();
        }
        else
        {
            ts.putback(next);
            return left;
        }
    }
}

double primary()
{
    Token next = ts.get();
    switch (next.kind)
    {
        case '(':
        {
            double d = expression();
            next     = ts.get();
            if (next.kind != ')')
                throw std::runtime_error(color("error: ')' expected", 'r'));
            Token is_fac = ts.get();
            if (is_fac.kind == '!')
            {
                return factorial(d);
            }
            else
            {
                ts.putback(is_fac);
            }
            return d;
            break;
        }
        case '8':
        {
            Token is_fac = ts.get();
            if (is_fac.kind == '!')
            {
                return factorial(next.value);
            }
            else
            {
                ts.putback(is_fac);
            }
            return next.value;
            break;
        }
        case 'q':
            std::cout << "Exiting...\n";
            exit(0);
        default:
            throw std::runtime_error(color("error: primary expected", 'r'));
            break;
    }
}

int main()
{
    while (std::cout << "> ")
    {
        try
        {
            double val = expression();
            Token  t   = ts.get();
            if (t.kind == ';')
            {
                std::cout << "= " << color(std::format("{}", val), 'g') << std::endl;
            }
            else
            {
                std::cout << "';' expected" << std::endl;
            }
        }
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;
        }
        catch (...)
        {
            std::cerr << "unknown error happend" << std::endl;
        }
    }
    return 0;
}
