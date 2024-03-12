#include "algorithmDriver.h"

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