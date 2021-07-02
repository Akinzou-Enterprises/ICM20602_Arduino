#include <ICM20602.h>
#include <Wire.h>

ICM20602::ICM20602(bool ADR)
{ 
    Wire.begin();

    if(ADR)
    {
        Addr = 0x69;
    }
    
    else
    {
        Addr = 0x68;
    }
}

void ICM20602::Restart()
{
    write8(PWR_MGMT_1, 0x80);
    delay(10);
}

void::ICM20602::Init(CLKSEL CLK, bool EnableTemp, bool GryroStandby, bool Cycle)
{
    uint8_t ConfigToSend = 0b00000000;
    switch (CLK)
    {
    case Internal20MHz:
        ConfigToSend |= Internal20MHz;
        break;
    
    case AutoSelect:
        ConfigToSend |= AutoSelect;
        break;

    case StopClock:
        ConfigToSend |= StopClock;
    }

    if(EnableTemp)
    {
        ConfigToSend |= 0x8;
    }

    if(GryroStandby)
    {
        ConfigToSend |= 0x10;
    }

    if(Cycle)
    {
        ConfigToSend |= 0x20;
    }
    
    write8(PWR_MGMT_1, ConfigToSend);
}

int ICM20602::ReadAngleX()
{

}


void ICM20602::GyroStandby(bool On)
{
    uint8_t ConfigToSend = read8(PWR_MGMT_1);
    if(On)
    {
        ConfigToSend |= 0x10;
    }

    else
    {
        ConfigToSend &= ~(0x10);
    }
    write8(PWR_MGMT_1, ConfigToSend);
}

bool ICM20602::Test()
{
    if (read8(WHO_AM_I) == 0x12)
    {
        return true;
    }
    
    else
    {
        return false;
    }
}

void ICM20602::Sleep(bool On)
{
    uint8_t ConfigToSend = read8(PWR_MGMT_1);
    if(On)
    {
        ConfigToSend |= 0x40;
    }
    
    else
    {
        ConfigToSend &= ~(0x40);
    }
    write8(PWR_MGMT_1, ConfigToSend);
}

void ICM20602::SetOffsetGyroX(int offset)
{
    uint8_t RegL =| offset;
    uint8_t RegH =| offset >> 8;
    write8(XG_OFFS_TC_L, RegL);
    write8(XG_OFFS_TC_H, RegH);
}

void ICM20602::SetOffsetGyroY(int offset)
{
    uint8_t RegL =| offset;
    uint8_t RegH =| offset >> 8;
    write8(YG_OFFS_TC_L, RegL);
    write8(YG_OFFS_TC_H, RegH);
}


void ICM20602::SetOffsetGyroZ(int offset)
{
    uint8_t RegL =| offset;
    uint8_t RegH =| offset >> 8;
    write8(ZG_OFFS_TC_L, RegL);
    write8(ZG_OFFS_TC_H, RegH);
}


void ICM20602::GyroPrecision(GyroPrec dps)
{
    write8(GYRO_CONFIG, dps<<2);
}

void ICM20602::GyroS(bool X, bool Y, bool Z)
{
    GyroX(X);
    GyroY(Y);
    GyroZ(Z);
}

void ICM20602::GyroX(bool On)
{  
    uint8_t ConfigToSend = read8(PWR_MGMT_2);
    if(On)
    {
        ConfigToSend &= ~(4);
    }

    else
    {
        ConfigToSend |= 4;
    }
    write8(PWR_MGMT_2, ConfigToSend);
}

void ICM20602::GyroY(bool On)
{  
    uint8_t ConfigToSend = read8(PWR_MGMT_2);
    if(On)
    {
        ConfigToSend &= ~(2);
    }

    else
    {
        ConfigToSend |= 2;
    }
    write8(PWR_MGMT_2, ConfigToSend);
}

void ICM20602::GyroZ(bool On)
{  
    uint8_t ConfigToSend = read8(PWR_MGMT_2);
    if(On)
    {
        ConfigToSend &= ~(1);
    }

    else
    {
        ConfigToSend |= 1;
    }
    write8(PWR_MGMT_2, ConfigToSend);
}

void ICM20602::AccelPrecision(AccelPrec g)
{
    write8(GYRO_CONFIG, g<<2);
}

void ICM20602::AccelS(bool X, bool Y, bool Z)
{
    AccelX(X);
    AccelY(Y);
    AccelZ(Z);
}

void ICM20602::SetOffsetGyroX(int offset)
{
    uint8_t RegL =| offset;
    uint8_t RegH =| offset >> 8;
    write8(XA_OFFSET_H, RegL);
    write8(XA_OFFSET_L, RegH);
}


void ICM20602::SetOffsetGyroY(int offset)
{
    uint8_t RegL =| offset;
    uint8_t RegH =| offset >> 8;
    write8(YA_OFFSET_H, RegL);
    write8(YA_OFFSET_H, RegH);
}


void ICM20602::SetOffsetGyroZ(int offset)
{
    uint8_t RegL =| offset;
    uint8_t RegH =| offset >> 8;
    write8(ZA_OFFSET_H, RegL);
    write8(ZA_OFFSET_H, RegH);
}


void ICM20602::AccelZ(bool On)
{
    uint8_t ConfigToSend = read8(PWR_MGMT_2);

    if(On)
    {
        ConfigToSend &= ~(8);
    }

    else
    {
        ConfigToSend |= 8;
    }
    write8(PWR_MGMT_2, ConfigToSend);
}

void ICM20602::AccelY(bool On)
{
    uint8_t ConfigToSend = read8(PWR_MGMT_2);

    if(On)
    {
        ConfigToSend &= ~(16);
    }

    else
    {
        ConfigToSend |= 16;
    }
    write8(PWR_MGMT_2, ConfigToSend);
}

void ICM20602::AccelX(bool On)
{
    uint8_t ConfigToSend = read8(PWR_MGMT_2);

    if(On)
    {
        ConfigToSend &= ~(32);
    }

    else
    {
        ConfigToSend |= 32;
    }
    write8(PWR_MGMT_2, ConfigToSend);
}


int ICM20602::ReadAccelX()
{
    return ReturnData(read8(ACCEL_XOUT_H), read8(ACCEL_XOUT_L));
}

int ICM20602::ReadAccelY()
{
    return ReturnData(read8(ACCEL_YOUT_H), read8(ACCEL_YOUT_L));
}

int ICM20602::ReadAccelZ()
{
    return ReturnData(read8(ACCEL_ZOUT_H), read8(ACCEL_ZOUT_L));
}

int ICM20602::ReadGyroX()
{
    return ReturnData(read8(GYRO_XOUT_H), read8(GYRO_XOUT_L));
}

int ICM20602::ReadGyroY()
{
    return ReturnData(read8(GYRO_YOUT_H), read8(GYRO_YOUT_L));
}

int ICM20602::ReadGyroZ()
{
    return ReturnData(read8(GYRO_ZOUT_H), read8(GYRO_ZOUT_L));
}


int ICM20602::ReturnData(uint8_t RegH, uint8_t RegL)
{  
    uint16_t Data = RegH << 8;
    Data |= RegL;
    return Data;
}

void ICM20602::write8(byte reg, byte value) 
{
  Wire.beginTransmission((uint8_t)Addr);
  Wire.write((uint8_t)reg);
  Wire.write((uint8_t)value);
  Wire.endTransmission();
}

uint8_t ICM20602::read8(byte reg) 
{
    uint8_t value;
    Wire.beginTransmission((uint8_t)Addr);
    Wire.write((uint8_t)reg);
    Wire.endTransmission(false);
    Wire.requestFrom((uint8_t)Addr, (byte)1);
    value = Wire.read();
    return value;
}
