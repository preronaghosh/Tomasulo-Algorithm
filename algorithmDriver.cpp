#include "algorithmDriver.h"

using namespace std;

// -----------------------------------------------------------------------------------------------------


// Will dispatch an instruction to the appropriate reservation station
int ISSUE(std::vector<ReservationStation>& reservationStations,
          std::vector<RegisterStatus>& regStatus,
          std::vector<Instruction>& Inst) {

    // Boundaries of functional units for easier indexing holistically
    // since they are not defined as vector here
    int RSAddStart = 0;
    int RSAddEnd = num_add_rs;
    int RSSubStart = 0;
    int RSSubEnd = num_add_rs;
    int RSMultStart = num_add_rs; // starts at index 4
    int RSMultEnd = num_add_rs + num_mul_rs;
    int RSDivStart = num_add_rs + num_mul_rs; // starts at index 6
    int RSDivEnd = num_add_rs + num_mul_rs + num_div_rs; // ends at index 8 

    int curr_rs = 0;
    int curr_inst_op = 0;
    bool rsAssigned = false;

    if (currentInst_ISSUE >= Inst.size())
        return 0;

    curr_inst_op = Inst[currentInst_ISSUE].op;
    switch(curr_inst_op) {
        case AddOp:
            for(int i = RSAddStart; i < RSAddEnd; i++) {
                if (!reservationStations[i].busy) {
                    curr_rs = i;
                    reservationStations[i].op = AddOp;
                    
                    currentInst_ISSUE++;  // go to next instruction
                    rsAssigned = true;
                    break; // got a resStation, so no need to loop on to the next one
                }
            }

            if (!rsAssigned) 
                return 1;

            break;

        case SubOp:
            for(int i = RSSubStart; i < RSSubEnd; i++) {
                if (!reservationStations[i].busy) {
                    curr_rs = i;
                    reservationStations[i].op = SubOp;
                    
                    currentInst_ISSUE++;  // go to next instruction
                    rsAssigned = true;
                    break; // got a resStation, so no need to loop on to the next one
                }
            }

            if (!rsAssigned) 
                return 1;

            break;


        case MultOp:
            for(int i = RSMultStart; i < RSMultEnd; i++) {
                if (!reservationStations[i].busy) {
                    curr_rs = i;
                    reservationStations[i].op = MultOp;
                    
                    currentInst_ISSUE++;  // go to next instruction
                    rsAssigned = true;
                    break; // got a resStation, so no need to loop on to the next one
                }
            }

            if (!rsAssigned) 
                return 1;

            break;


        case DivOp:
            for(int i = RSDivStart; i < RSDivEnd; i++) {
                if (!reservationStations[i].busy) {
                    curr_rs = i;
                    reservationStations[i].op = DivOp;
                    
                    currentInst_ISSUE++;  // go to next instruction
                    rsAssigned = true;
                    break; // got a resStation, so no need to loop on to the next one
                }
            }

            if (!rsAssigned) 
                return 1;

            break;

        default:
            break;
    } // end of switch case

    // set source operand value if available
    // or set it to the res station currently working with it
    if (regStatus[Inst[currentInst_ISSUE-1].rs].Qi == RegStatusEmpty) {
        reservationStations[curr_rs].Vj = Inst[currentInst_ISSUE-1].rs;
        reservationStations[curr_rs].Qj = OperandAvailable;
    } else {
        reservationStations[curr_rs].Qj = regStatus[Inst[currentInst_ISSUE-1].rs].Qi;
    }

    if (regStatus[Inst[currentInst_ISSUE-1].rt].Qi == RegStatusEmpty) {
        reservationStations[curr_rs].Vk = Inst[currentInst_ISSUE-1].rt;
        reservationStations[curr_rs].Qk = OperandAvailable;
    } else {
        reservationStations[curr_rs].Qk = regStatus[Inst[currentInst_ISSUE-1].rt].Qi;
    }

    // set resStation characteristics since a dispatch was done
    reservationStations[curr_rs].busy = true;
    reservationStations[curr_rs].ISSUE_lat = 0;
    reservationStations[curr_rs].instNum = currentInst_ISSUE - 1;

    Inst[currentInst_ISSUE-1].issueClk = Clock;

    // update the destination register status
    regStatus[Inst[currentInst_ISSUE-1].rd].Qi = curr_rs;

    return 2;

}

void EXECUTE(std::vector<ReservationStation>& reservationStations,
          std::vector<RegisterStatus>& regStatus,
          std::vector<Instruction>& Inst) {

    for(int rs = 0; rs < reservationStations.size(); rs++) {
        // if both operands are available, execute given instructions operation
        // and set resultReady flag to true so that result can be written back to CDB

        // first check if instruction has been issued
        if (reservationStations[rs].busy) {
            if (reservationStations[rs].ISSUE_lat == issue_lat) {       // at least 1 cycle of ISSUE latency

                if ((reservationStations[rs].Qj == OperandAvailable) && (reservationStations[rs].Qk == OperandAvailable)) {
                    // start execute
                    if (Inst[reservationStations[rs].instNum].executeClkBegin == 0) 
                        Inst[reservationStations[rs].instNum].executeClkBegin = Clock;

                    reservationStations[rs].lat++;

                    switch (reservationStations[rs].op) {
                        case AddOp:
                            // add operations take 4 clock cycles
                            if (reservationStations[rs].lat == add_lat) {
                                reservationStations[rs].result = reservationStations[rs].Vj + reservationStations[rs].Vk;
                                // ready for WB stage
                                reservationStations[rs].resultReady= true;

                                reservationStations[rs].lat = 0;
                                Inst[reservationStations[rs].instNum].executeClkEnd = Clock;
                                reservationStations[rs].ISSUE_lat = 0;
                            } 
                        
                            break;

                        case SubOp:
                            // sub operations take 4 clock cycles
                            if (reservationStations[rs].lat == add_lat) {
                                reservationStations[rs].result = reservationStations[rs].Vj - reservationStations[rs].Vk;
                                // ready for WB stage
                                reservationStations[rs].resultReady= true;

                                reservationStations[rs].lat = 0;
                                Inst[reservationStations[rs].instNum].executeClkEnd = Clock;
                                reservationStations[rs].ISSUE_lat = 0;
                            } 
                        
                            break;

                        case MultOp:
                            // multiplication operations take 12 clock cycles
                            if (reservationStations[rs].lat == mult_lat) {
                                reservationStations[rs].result = reservationStations[rs].Vj * reservationStations[rs].Vk;
                                // ready for WB stage
                                reservationStations[rs].resultReady= true;

                                reservationStations[rs].lat = 0;
                                Inst[reservationStations[rs].instNum].executeClkEnd = Clock;
                                reservationStations[rs].ISSUE_lat = 0;
                            }
                            break;

                        case DivOp:
                            // division operations take 38 clock cycles
                            if (reservationStations[rs].lat == mult_lat) {
                                reservationStations[rs].result = reservationStations[rs].Vj / reservationStations[rs].Vk;
                                // ready for WB stage
                                reservationStations[rs].resultReady= true;

                                reservationStations[rs].lat = 0;
                                Inst[reservationStations[rs].instNum].executeClkEnd = Clock;
                                reservationStations[rs].ISSUE_lat = 0;
                            }
                            break;
                        default:
                            break;
                    }
                }
            } else {
                reservationStations[rs].ISSUE_lat++;
            }
        }
    }
}


void WRITEBACK(std::vector<ReservationStation>& reservationStations,
          std::vector<RegisterStatus>& regStatus,
          std::vector<int> Registers,
          std::vector<Instruction>& Inst) {

    for(int rs = 0; rs < reservationStations.size(); rs++) {
        // check if result is ready for WB stage
        if (reservationStations[rs].resultReady) {
            // min 1 cycle of WB stage
            if (reservationStations[rs].WRITEBACK_lat == writeback_lat) {
                Inst[reservationStations[rs].instNum].writebackClk = Clock;
                
                // check if any register is waiting for result from current reservStation
                for (int reg = 0; reg < Registers.size(); reg++) {
                    if (regStatus[reg].Qi == rs) {
                        // write back to registers and update status
                        Registers[reg] = reservationStations[rs].result;
                        regStatus[reg].Qi = RegStatusEmpty;
                    }
                }

                // check if any resStations are waiting on result
                for(int resStn = 0; resStn < reservationStations.size(); resStn++) {
                    if (reservationStations[resStn].Qj == rs) {
                        reservationStations[resStn].Vj = reservationStations[resStn].result;    
                        reservationStations[resStn].Qj = OperandAvailable;
                    }

                    if (reservationStations[resStn].Qk == rs) {
                        reservationStations[resStn].Vk = reservationStations[resStn].result;    
                        reservationStations[resStn].Qk = OperandAvailable;
                    }
                }
                // The given reservation station can now be used again
                // Reset all ResStn paramaters
                reservationStations[rs].WRITEBACK_lat = 0;
                reservationStations[rs].busy = false;
                reservationStations[rs].resultReady = false;
                reservationStations[rs].Qj = OperandInit;
                reservationStations[rs].Qk = OperandInit;
                reservationStations[rs].Vj = 0;
                reservationStations[rs].Vk = 0;

                total_writebacks++;

            } else {
                reservationStations[rs].WRITEBACK_lat++;
            }
        }
    }
}



// -----------------------------------------------------------------------------------------------------

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