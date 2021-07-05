#include <ICM20602.h>

ICM20602 ICM(true);


void setup() 
{
  ICM.Restart();
  ICM.Init(AutoSelect, false, false, false);
  ICM.GyroS(true, true, true);
  Serial.begin(9600);
  ICM.GyroPrecision(dps250);
  ICM.SetOffsetGyroX(308);

}

float angle;

void loop() 
{ 
  int Gyro = ICM.ReadGyroX();
  if(Gyro >= 100 && Gyro < 32768)
  {
	//https://dronebotworkshop.com/mpu-6050-level/
	//Gyro angle calculations . Note 0.0000611 = 1 / (250Hz x 65.5)
    angle += Gyro * 0.0000611;
  }
  else if (Gyro >= 32768)
  {
    angle -= (65600 - Gyro) * 0.0000611;
  }
  
  Serial.println(angle);
	//1:0.004 gives 250Hz
  delay(4);

}
