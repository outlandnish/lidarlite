# LIDAR-Lite Library

This tidy little Arduino package gives you access to the basic functions provided by PulsedLight3D's LIDAR-Lite device.

With this, you'll be able to:

 * Get individual distance and velocity readings
 * Get smoothed (averaged) distance and velocity readings
 * Set the [velocity scaling](http://kb.pulsedlight3d.com/support/solutions/articles/5000549527-velocity-measurement)
 * Reset and calibrate the LIDAR-Lite
 * File contents are saved in the URL so you can share files

### Setup
1. Download and copy the DSS Circuits [Arduino I2C Master Library](http://www.dsscircuits.com/index.php/articles/66-arduino-i2c-master-library) to your Arduino > libraries folder.
2. Copy this library to your Arduino > libraries folder.

### Usage

```c++
<include I2C.h>
<include lidarlite.h>
<include velocityscale.h>

LIDARLite lidar;	

void setup() {
	// reset the device
	lidar.reset();
}

void loop() {
	// read distance
	int dist = lidar.distance();
	
	// read velocity
	int velo = lidar.velocity();
		
}
```

You can find additional samples in the examples folder.

### Credits

 * [PulsedLight3D](http://pulsedlight3d.com) for making an awesome, affordable LIDAR unit.
 * [State Machine Sample](https://github.com/PulsedLight3D/LIDARLite_StateMachine) for a good portion of the code in this library.
 * [DSS Circuits](http://www.dsscircuits.com) for the Arduino I2C Master library.
