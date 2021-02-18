#include <Arduino.h>
#include "LCDActuator.h"

bool LCDBigNumber_Setup();

void LCDBigNumber_Print_Height2_Right(int row, String number);
void LCDBigNumber_Print_Height2_Center(int row, String number);
void LCDBigNumber_Print_Height2_Left(int row, String number);

void LCDBigNumber_Print_Height4_Right(String number);
void LCDBigNumber_Print_Height4_Center(String number);
void LCDBigNumber_Print_Height4_Left(String number);
