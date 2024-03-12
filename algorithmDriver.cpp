#include "algorithmDriver.h"

using namespace std;

// Main Driver
int main() {
    // test instructions
    Instruction I0(1, 2, 3, AddOp);
    Instruction I1(4, 1, 5, AddOp);
    Instruction I2(6, 7, 8, SubOp);
    Instruction I3(9, 4, 10, MultOp);
    Instruction I4(11, 12, 6, DivOp);
    Instruction I5(8, 1, 5, MultOp);
    Instruction I6(7, 2, 3, MultOp);

    vector<Instruction> instructions = {I0, I1, I2, I3, I4, I5, I6};

    // create reservations stations 
    ReservationStation add_rs1(AddOp, OperandInit);
    ReservationStation add_rs2(AddOp, OperandInit);
    ReservationStation add_rs3(AddOp, OperandInit);
    ReservationStation add_rs4(AddOp, OperandInit);

    ReservationStation mul_rs1(SubOp, OperandInit);
    ReservationStation mul_rs2(SubOp, OperandInit);

    ReservationStation div_rs1(MultOp, OperandInit);
    ReservationStation div_rs2(MultOp, OperandInit);
    ReservationStation div_rs3(MultOp, OperandInit);

    vector<ReservationStation> resStations = {add_rs1, add_rs2, add_rs3, add_rs4,
                                              mul_rs1, mul_rs2, 
                                              div_rs1, div_rs2, div_rs3
                                            };

    // Create 12 register objects
    RegisterStatus F0(RegStatusEmpty);
    RegisterStatus F1(RegStatusEmpty);
    RegisterStatus F2(RegStatusEmpty);
    RegisterStatus F3(RegStatusEmpty);
    RegisterStatus F4(RegStatusEmpty);
    RegisterStatus F5(RegStatusEmpty);
    RegisterStatus F6(RegStatusEmpty);
    RegisterStatus F7(RegStatusEmpty);
    RegisterStatus F8(RegStatusEmpty);
    RegisterStatus F9(RegStatusEmpty);
    RegisterStatus F10(RegStatusEmpty);
    RegisterStatus F11(RegStatusEmpty);
    RegisterStatus F12(RegStatusEmpty);

    vector<RegisterStatus> regStatus = {F0, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12};

    // Initialize register file
    vector<int> registers = {ZERO_REG, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    // Start of functionality
    while(!Done) {
        Clock++;

        ISSUE(resStations, regStatus, instructions);

        EXECUTE(resStations, regStatus, instructions);

        WRITEBACK(resStations, regStatus, registers, instructions);

        Done = false;
        
        if (total_writebacks == instructions.size()) {
            Done = true;
        }
    }


    return 0;
}