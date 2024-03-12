#ifndef INSTRUCTION_H
#define INSTRUCTION_H

class Instruction {
public: 
    int rs, rt;  // source registers
    int rd;      // dest register
    int op;      // opcode
    int issueClk; 
    int executeClkBegin;
    int executeClkEnd;
    int writebackClk;

public:
    Instruction();  // default constructor
    Instruction(int RD, int RS, int RT, int OP);
};


#endif // INSTRUCTION_H