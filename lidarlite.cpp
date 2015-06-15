#include "lidarlite.h"
#include <I2C.h>

/*
	A tidy little package to use the PulsedLight3D LIDAR-Lite through the I2C interface.

	Most of the code here is a direct copy from the PulsedLight3D State Machine sample:
	https://github.com/PulsedLight3D/LIDARLite_StateMachine
*/

//constructor
LIDARLite::LIDARLite() {
	I2c.begin(); // Opens & joins the irc bus as master
	delay(100); // Waits to make sure everything is powered up before sending or receiving data  
	I2c.timeOut(50); // Sets a timeout to ensure no locking up of sketch if I2C communication fails
}

//destructor
//additionally stops reading
LIDARLite::~LIDARLite() {
	reset();
	I2c.end();
}

int LIDARLite::distance() {
	write_register(RegisterMeasure, ReadDistanceCmd); // Write 0x04 to register 0x00 to start getting distance readings
	byte data[2]; // array to store bytes from read function
	read_registers(RegisterDistance, 2, data); // Read 2 bytes from 0x8f
	int distance = (data[0] << 8) + data[1];  // Shift high byte [0] 8 to the left and add low byte [1] to create 16-bit int
	return distance;
}

int LIDARLite::velocity() {
	write_register(RegisterMeasure, ReadDistanceCmd); // Write 0x04 to register 0x00 to start getting distance readings
	write_register(ReadDistanceCmd, ReadVelocityCmd); // Write 0x80 to 0x04 to switch on velocity mode 
	byte data[1]; // Array to store bytes from read function
	read_registers(RegisterVelocity, 1, data); // Read 1 byte from register 0x09 to get velocity measurement 
	return (int)((char)data[0]); // Convert 1 byte to char and then to int to get signed int value for velocity measurement
}

double LIDARLite::mean_distance(int readings = 2) {
	if (readings < 2)
		readings = 2;
	int sum = 0;
	for(int i = 0; i < readings; i++)
		sum = sum + distance(); // Add up all of the readings
	return sum / readings; // Divide the total by the number of readings to get the average
}

double LIDARLite::mean_velocity(int readings = 2) {
	if (readings < 2)
		readings = 2;
	int sum = 0;
	for(int i = 0; i < readings; i++)
		sum = sum + velocity(); // Add up all of the readings
	return sum / readings; // Divide the total by the number of readings to get the average
}

void LIDARLite::scale_velocity(VelocityScale scale) {
	write_register(RegisterVeloScale, (unsigned char)scale);
}

void LIDARLite::reset() {
	write_register(RegisterMeasure, ResetCmd);
}

void calibrate(byte offset) {
	write_register(RegisterCalibrate, offset);
}
	
byte LIDARLite::read_registers(char address, int numBytes, byte data[2]) {
	uint8_t nackack = 100; // Setup variable to hold ACK/NACK resopnses     
	while (nackack != 0){ // While NACK keep going (i.e. continue polling until sucess message (ACK) is received )
		nackack = I2c.read(LIDARLite_ADDRESS, address, numBytes, data); // Read 1-2 Bytes from LIDAR-Lite Address and store in array
		delay(2); // Wait 2 ms to prevent overpolling
	}
	return data; // Return array for use in other functions
}

// Write a register and wait until it responds with success
void LIDARLite::write_register(char address, char val) {
	uint8_t nackack = 100; // Setup variable to hold ACK/NACK resopnses     
	while (nackack != 0){ // While NACK keep going (i.e. continue polling until sucess message (ACK) is received )
		nackack = I2c.write(LIDARLite_ADDRESS, address, val); // Write to LIDAR-Lite Address with Value
		delay(2); // Wait 2 ms to prevent overpolling
	}
}