#include <cassert>
#include <iostream>
#include <stdexcept>

double expression();
double term(); double primary();

class Token
{
public:
	char kind;
	double value;
	Token(char ch)
		: kind(ch), value(0)
	{
	}
	Token(char ch, double val)
		: kind(ch), value(val)
	{
	}
};

class Token_stream
{
public:
    Token get();
    void putback(Token t);
    Token_stream() : full{false}, buffer{0} {}
private:
	bool full = false;
    Token buffer;
};

void Token_stream::putback(Token t)
{
    if (full)
    {
        throw std::runtime_error("error: putback() into a full buffer");
    }
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
            throw std::runtime_error("Bad token");
    }
}

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
    double left = primary();
    Token  next = ts.get();
    while (true)
    {
        switch (next.kind)
        {
            case '*':
                left *= primary();
                next = ts.get();
                break;
            case '/':
            {
                double d = primary();
                if (d == 0)
                    throw std::runtime_error("error: devision by zero");
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
                throw std::runtime_error("error: ')' expected");
            return d;
            break;
        }
        case '8':
            return next.value;
            break;
		case 'q':
			std::cout << "Exiting...\n";
			exit(0);
        default:
            throw std::runtime_error("error: primary expected");
            break;
    }
}

int main()
{
    std::cout << "Welcome to my calculator app" << std::endl;
    while (std::cout << "> ")
    {
        try
        {
            double val = expression();
            Token  t   = ts.get();
            if (t.kind == ';')
            {
                std::cout << "= " << val << std::endl;
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
