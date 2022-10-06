#ifndef TEMPERATURE_H
#define TEMPERATURE_H

// Data wire is connected to GPIO15
#define ONE_WIRE_BUS 7
#define TEMPERATURE_PRECISION 9

void init_temp_sensors(void);
//void PrintAddress(DeviceAddress deviceAddress);
//void printData(DeviceAddress deviceAddress);
void temp_request(void);

#endif
