#include "registerStatus.h"

RegisterStatus::RegisterStatus() {
    busy = false;
    Qi = 0; // indicated the reservation station currently working with this register
}

RegisterStatus::RegisterStatus(int RegStatusEmpty) {
    Qi = RegStatusEmpty;
}