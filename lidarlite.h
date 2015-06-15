#ifdef LIDARLITE_H
#define LIDARLITE_H

#define		LIDARLite_ADDRESS	0x62		// Default I2C Address of LIDAR-Lite

#define		RegisterMeasure		0x00		// Register to write to initiate ranging
#define		RegisterDistance	0x8f		// Register that stores distance
#define		RegisterVelocity	0x09		// Register that stores velocity
#define		RegisterVeloScale	0x68		// Register that stores velocity scaling
#define		RegisterCalibrate	0x13		// Register that stores calibration value

#define		ResetCmd			0x00		// Value to reset register
#define		ReadDistanceCmd		0x04		// Value to initiate ranging
#define		ReadVelocityCmd		0x80		// Value to initiate velocity measurement

#include <WProgram.h>
#include "velocityscale.h"

class LIDARLite {
public:
	//default constructor + destructor
	LIDARLite();
	~LIDARLite();
	
	// single readings
	int distance();	
	int velocity();
	
	// mean readings
	double mean_distance(int readings = 2);
	double mean_velocity(int readings = 2);
	
	// set the velocity scaling
	void scale_velocity(VelocityScale scale);
	
	void calibrate(byte offset);
	
	// reset the LIDAR-Lite
	void reset();
	
private:	
	// Read 1-2 bytes from a register and wait until it responds with success
	byte read_registers(char address, int numBytes, byte data[2]);
	
	// Write a register and wait until it responds with success
	void write_register(char address, char val);
}

#endif