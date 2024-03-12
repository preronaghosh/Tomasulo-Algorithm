#include "reservationStation.h"

ReservationStation::ReservationStation() {
    busy = false;
    op = 0;
    lat = 0;
    result = 0;
    resultReady = false;
    Qj = 1;
    Qk = 1;
    Vj = 0;
    Vk = 0;
    instNum = 100000;
    ISSUE_lat = 0;
    WRITEBACK_lat = 0;
}

ReservationStation::ReservationStation(int OP, int RSoperandAvailable) {
    busy = false;
    op = OP;
    lat = 0;
    result = 0;
    resultReady = false;
    Qj = RSoperandAvailable;
    Qk = RSoperandAvailable;
    Vj = 0;
    Vk = 0;
    instNum = 100000;
    ISSUE_lat = 0;
    WRITEBACK_lat = 0;
}