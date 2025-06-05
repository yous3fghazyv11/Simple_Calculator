#pragma once

class Token {
  public:
    char kind;
    double value;
    Token(char ch) : kind(ch), value(0) {}
    Token(char ch, double val) : kind(ch), value(val) {}
};

class Token_stream {
  public:
    Token get();
    void putback(Token t);
    Token_stream() : full{false}, buffer{0} {}

  private:
    bool full = false;
    Token buffer;
};
