#include "algorithmDriver.h"

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