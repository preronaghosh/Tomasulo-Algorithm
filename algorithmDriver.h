#ifndef ALGORITHM_DRIVER_H
#define ALGORITHM_DRIVER_H


#include "reservationStation.h"
#include "instruction.h"
#include "registerStatus.h"
#include <vector>
#include <iostream>

// Opcode Values
constexpr int AddOp = 0;
constexpr int SubOp = 1;
constexpr int MultOp = 2;
constexpr int DivOp = 3;

// number of reservation stations
constexpr int num_add_rs = 4;
constexpr int num_mul_rs = 2;
constexpr int num_div_rs = 3;

// RESERVATION STATION LATENCY
constexpr int add_lat = 4;
constexpr int mult_lat = 12;
constexpr int div_lat = 38;

// Datapath Latency
constexpr int issue_lat = 1;    // min 1 cycle latency
constexpr int writeback_lat = 1; // min 1 cycle latency

int currentInst_ISSUE = 0;

constexpr int ZERO_REG = 5000;
constexpr int RegStatusEmpty = 1000;
constexpr int OperandAvailable = 1001;
constexpr int OperandInit  = 1002;

bool Done = false; // true -> all instructions have been executed
int total_writebacks = 0; // counter to track if all instructions have been executed and set above flag

int Clock = 0; // Global Clock

// driver functions
int ISSUE(std::vector<ReservationStation>& reservationStations,
          std::vector<RegisterStatus>& regStatus,
          std::vector<Instruction>& Inst
);

void EXECUTE(std::vector<ReservationStation>& reservationStations,
          std::vector<RegisterStatus>& regStatus,
          std::vector<Instruction>& Inst);

void WRITEBACK(std::vector<ReservationStation>& reservationStations,
          std::vector<RegisterStatus>& regStatus,
          std::vector<int> Registers,
          std::vector<Instruction>& Inst);

#endif // ALGORITHM_DRIVER_H