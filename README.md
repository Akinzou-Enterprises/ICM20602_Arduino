# ICM20602_Arduino
ICM20602 only in I2C mode

ICM20602 ICM(true); TRUE - 0x69 (SA0 VCC) false - 0x68 (SA0 GND)

ICM.Init(CLKSEL CLK, bool EnableTemp, bool GryroStandby, bool Cycle);
ICM.GyroS(bool X, bool Y, bool Z);

you can also change one gyro at time:
ICM.GyroX/Y/Z(bool Enable); //true - enabled

Same with accels

To read use 

ICM.ReadGyroX/Y/Z();
ICM.ReadAccelX/Y/Z();

It's returning 16bit varibale
