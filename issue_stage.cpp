#include "algorithmDriver.h"

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