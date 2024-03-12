#ifndef RESERVATION_STATION_H
#define RESERVATION_STATION_H


class ReservationStation {
public:
    bool busy;
    int Qj; // holds value of the reservation station currently updating rs
    int Qk; // holds value of the reservation station currently updating rs
    int Vj; 
    int Vk;
    int lat;
    int op; // opcode of curr instruction in ResStation
    int result; // stores result of execute stage 
    bool resultReady; // says if we have a result in the execute stage which can go to writeback stage
    int instNum;    // holds the curr instruction index from the vector of all instructions
    int ISSUE_lat; // set to 0 once issue for an inst has been done (counter to see how long it takes to issue an inst when reservation station is busy)
    int WRITEBACK_lat;

    ReservationStation();
    ReservationStation(int, int);
};

#endif // RESERVATION_STATION_H