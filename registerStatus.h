#ifndef REGISTER_STATUS_H
#define REGISTER_STATUS_H

// states for every register supprted
class RegisterStatus {
public:
    bool busy;
    int Qi; // holds the status of the respective register (OperandInit, OperandAvailable, ResStation number)

    RegisterStatus();
    RegisterStatus(int); // initially register will have no status
};


#endif // REGISTER_STATUS_H