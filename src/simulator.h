#include "status.h"

#ifndef __SIMULATOR_H_
#    define __SIMULATOR_H_

struct Num {
    bool type;
    // `true` means immediate number or line_to_jump (line to exec)
    // `false` means register
    //   (depend on the instruction)
    unsigned int val;
    // if `val` means register, we will use 0 to 31 to represent it
    Num(bool _type, unsigned int _val);
    ~Num();
};

class Line {
  private:
#    define UNDEF       -10
#    define DRAW        -2
#    define END         -1
#    define LINE_SYMBOL 0
#    define LOAD        1
#    define STORE       2
#    define PUSH        3
#    define POP         4
#    define MOV         10
#    define ADD         20
#    define SUB         21
#    define MUL         22
#    define DIV         23
#    define REM         24
#    define AND         25
#    define OR          26
#    define JAL         30
#    define BEQ         31
#    define BNE         32
#    define BLT         33
#    define BGE         34
#    define CALL        41
#    define RET         42

    short type;
    Num   arg[3];

  public:
    Line();
    Line(const short &t, const Num *args, const int &arg_n);
    ~Line();
    short get_type() {
        return type;
    }
    Num get_arg(unsigned int i) {
        return arg[i];
    }
};

class Simulator {
  private:
    static const int MAX_INSTRUCTION = 10000;
    static const int MAX_LINE_COL    = 100;
    Line             lines[MAX_INSTRUCTION];
    Status           status;
    unsigned int     now_line;
    unsigned int     lines_num;
    void parse(const char *script, Line &line, const int current_line);
    void do_line(unsigned int &now_line, Line line);

  public:
    Simulator(/* args */);
    ~Simulator();
    void parse_file(const char *FILENAME);
    void execute(unsigned int stop_line = -1);
};

#endif