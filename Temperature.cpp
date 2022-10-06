#include <OneWire.h>
#include <DallasTemperature.h>
#include "Temperature.h"

OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);

int deviceCount = 0;

//DeviceAddress sensor1 = { 0x28, 0xFF, 0x10, 0x19, 0xA4, 0x16, 0x5, 0x8E };
//DeviceAddress sensor2 = { 0x28, 0xFF, 0xD6, 0x22, 0xA4, 0x16, 0x5, 0xEC };
//DeviceAddress sensor3 = { 0x28, 0xFF, 0x33, 0x24, 0xA4, 0x16, 0x4, 0xB3 };

// arrays to hold device addresses
DeviceAddress sensor1, sensor2, sensor3, dummy;

float sensor_array[3];
char sensor_status[3] = {0, 0, 0};

void init_temp_sensors(void)
{
  // Start up the library
  sensors.begin();
 
  // locate devices on the bus
  Serial.print("Locating devices...");
  Serial.print("Found ");
  deviceCount = sensors.getDeviceCount();
  Serial.print(deviceCount, DEC);
  Serial.println(" sensors.");

  delay(1000);

  // report parasite power requirements
  Serial.print("Parasite power is: ");
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");
  Serial.println();

  if (!sensors.getAddress(sensor1, 0)) Serial.println("Unable to find address for Device 0");
  if (!sensors.getAddress(sensor2, 1)) Serial.println("Unable to find address for Device 1");
  if (!sensors.getAddress(sensor3, 2)) Serial.println("Unable to find address for Device 2");
  Serial.println();

  // set the resolution to 9 bit
  sensors.setResolution(sensor1, TEMPERATURE_PRECISION);
  sensors.setResolution(sensor2, TEMPERATURE_PRECISION);
  sensors.setResolution(sensor3, TEMPERATURE_PRECISION);

  Serial.print("Device 0 Resolution: ");
  Serial.print(sensors.getResolution(sensor1), DEC);
  Serial.println();

  Serial.print("Device 1 Resolution: ");
  Serial.print(sensors.getResolution(sensor2), DEC);
  Serial.println();

  Serial.print("Device 2 Resolution: ");
  Serial.println(sensors.getResolution(sensor3), DEC);
  Serial.println();
}

// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // zero pad the address if necessary
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

// function to print the temperature for a device
void printTemperature(DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  Serial.print("Temp C: ");
  Serial.print(tempC);
  Serial.print(" Temp F: ");
  Serial.print(DallasTemperature::toFahrenheit(tempC));
}

// function to print a device's resolution
void printResolution(DeviceAddress deviceAddress)
{
  Serial.print("Resolution: ");
  Serial.print(sensors.getResolution(deviceAddress));
  Serial.println();   
}

// main function to print information about a device
void printData(DeviceAddress deviceAddress)
{
  Serial.print("Device Address: ");
  printAddress(deviceAddress);
  Serial.print(" ");
  printTemperature(deviceAddress);
  Serial.println();
}

void temp_request(void)
{
  Serial.println("Requesting temperatures...");
//    SerialBT.print("Requesting temperatures...");

  if (!sensors.getAddress(sensor1, 0))
  {
    Serial.println("Unable to find address for Device 1");
    sensor_status[0] = 0;    
  }else sensor_status[0] = 1;
  
    if (!sensors.getAddress(sensor2, 1))
    {
      Serial.println("Unable to find address for Device 2");
      sensor_status[1] = 0;
    }else sensor_status[1] = 1;
    
  if (!sensors.getAddress(sensor3, 2))
  {
    Serial.println("Unable to find address for Device 3");
    sensor_status[2] = 0;
  }else sensor_status[2] = 1;
  
  Serial.println();
    
  delay(1000);
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
//    SerialBT.println("DONE");
  Serial.println();
//    SerialBT.println();

  sensor_array[0] = sensors.getTempC(sensor1);
  if(sensor_array[0] == -127) sensor_array[0] = 0;
  Serial.println(sensors.getTempC(sensor1));
//    SerialBT.println(sensors.getTempC(sensor1));
  sensor_array[1] = sensors.getTempC(sensor2);
  if(sensor_array[1] == -127) sensor_array[1] = 0;
  Serial.println(sensors.getTempC(sensor2));
//    SerialBT.println(sensors.getTempC(sensor2));
  sensor_array[2] = sensors.getTempC(sensor3);
  if(sensor_array[2] == -127) sensor_array[2] = 0;
  Serial.println(sensors.getTempC(sensor3));
//    SerialBT.println(sensors.getTempC(sensor3));
  Serial.println();
//    SerialBT.println();
  
  // print the device information in C and F
  printData(sensor1);
  printData(sensor2);
  printData(sensor3);

  Serial.println();
}
