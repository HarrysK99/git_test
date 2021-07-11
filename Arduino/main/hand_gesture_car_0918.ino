#include <Wire.h>
#include <SoftwareSerial.h> // 시리얼 통신 라이브러리 호출

const int MPU = 0x68;  //MPU 6050 의 I2C 기본 주소
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ; //AcX~ GyX 변수 설정

int blueTx=4;  //Tx (보내는 핀 설정) at
int blueRx=2;  //Rx (받는 핀 설정)

char Go = 'G';
char Back = 'B';
char Right = 'R';
char Left = 'L';
char Quit = 'Q';
SoftwareSerial mySerial(blueTx, blutRx);  //시리얼 통신을 위한 객체선언

void setup() {

  Wire.begin();       //Wire 라이브러리 초기화
  Wire.beginTransmission(MPU);  //MPU로 데이터 전송 시작
  Wire.write(0x68);  //PWR_MGMT_1 register
  Wire.write(0);     //MPU-6050 시작 모드로
  Wire.endTransmission(true);

  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop(){
  Wire.beginTransmission(MPU);  //데이터 전송 시작
  Wire.write(0x3B);             // reister 0x3B (ACCEL_XOUT_H), 큐에 데이터 기록
  Wire.endTransmission(false);  //연결 유지
  Wire.requestFrom(mpu,6,true); //MPU에 데이터 요청

  //데이터 한 바이트씩 읽어서 반환
  AcX = Wire.read() << 8 | Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  AcY = Wire.read() << 8 | Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ = Wire.read() << 8 | Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  //Tmp = Wire.read() << 8 | Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  //GyX = Wire.read() << 8 | Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  //GyY = Wire.read() << 8 | Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  //GyZ = Wire.read() << 8 | Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  float RADIAN_TO_DEGREES = 180/3.14139;
  float val_y = atan(AcX/sqrt(pow(AcY,2) + pow(AcZ,2))) * RADIAN_TO_DEGREES;
  float val_x = atan(AcY/sqrt(pow(AcX,2) + pow(AcZ,2))) * RADIAN_TO_DEGREES;

    if(val_x > 15){
      mySerial.write(Go);     //BTserial 로 Front 'G' 송신
    }
    else if(val_x < -15){
      mySerial.write(Back);   //BTserial 로 back 'B' 송신
    }
    else if(val_y > 15){
      mySerial.write(Right);
      //BTserial 로 right 'R' 송신
    }
    else if(val_y < -15){
      mySerial.write(Left);
    }
    else{
    mySerial.write(Quit);   //BTserial 로 Quit 'Q' 송신
    }
}
