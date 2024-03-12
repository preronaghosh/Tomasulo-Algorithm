#include "instruction.h"

Instruction::Instruction() {
    rs = 0;
    rt = 0;
    rd = 0;
    op = 0;
    issueClk = 0;
    executeClkBegin = 0;
    executeClkEnd = 0;
    writebackClk = 0;
}

Instruction::Instruction(int RD, int RS, int RT, int OP) {
    rs = RS;
    rt = RT;
    rd = RD;
    op = OP;
    issueClk = 0;
    executeClkBegin = 0;
    executeClkEnd = 0;
    writebackClk = 0;
}

