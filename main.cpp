#include <iostream>
#include <stdexcept>
#include <cassert>

double expression();
double term();
double primary();

// clang-format off
class Token
{
public:
	char kind;	   // what kind of token
	double value;  // for numbers: a value
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
    Token get(); // get a Token
    void putback(Token t); // put a Token back
    Token_stream() : full{false}, buffer{0} {}
private:
	bool full = false;
    Token buffer;
};
// clang-format on

void Token_stream::putback(Token t)
{
	if (full) {
		throw std::runtime_error("error: putback() into a full buffer");
	}
	buffer = t;
	full = true;
}

Token Token_stream::get()
{
	if (full) {
		full = false;
		return buffer;
	}
	char ch;
	std::cin >> ch;	 // note that >> skips whitespace (space, newline, tab, etc.)

	switch (ch) {
		case ';':
		case 'q':
		case '(':
		case ')':
		case '+':
		case '-':
		case '*':
		case '/':
			return Token(ch);  // let each character represent itself
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
		case '9': {
			std::cin.putback(ch);  // put digit back into the input stream
			double val;
			std::cin >> val;		 // read a floating-point number
			return Token('8', val);	 // let '8' represent "a number"
		}
		default:
			throw std::runtime_error("Bad token");
	}
}

Token_stream ts;

double expression()
{
	double left = term();
	Token next = ts.get();
	while (true) {
		switch (next.kind) {
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
	Token next = ts.get();
	while (true) {
		switch (next.kind) {
			case '*':
				left *= primary();
				next = ts.get();
				break;
			case '/': {
				double d = primary();
				if (d == 0) throw std::runtime_error("error: devision by zero");
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
	switch (next.kind) {
		case '(': {
			double d = expression();
			next = ts.get();
			if (next.kind != ')') throw std::runtime_error("error: ')' expected");
			return d;
			break;
		}
		case '8':
			return next.value;
			break;
		default:
			throw std::runtime_error("error: primary expected");
			break;
	}
}

int main()
{
	std::cout << "Welcome to my calculator app" << std::endl;
	while (std::cout << "> ") {
		try {
			double val = expression();
			Token t = ts.get();
			if (t.kind == 'q') {
				std::cout << "Exiting..." << std::endl;
				break;
			} else if (t.kind == ';') {
				std::cout << "= " << val << std::endl;
			}
		} catch (std::exception& e) {
			std::cerr << e.what() << std::endl;
		} catch (...) {
			std::cerr << "unknown error happend" << std::endl;
		}
	}
	return 0;
}
