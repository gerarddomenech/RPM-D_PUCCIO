# RPM3D_PUCCIO
Prototype of the wearable device
 This folder contain two files:
 - Arduino file ".ino": contains the code that you have to upload to your Arduino. The code reads the MPU6050 (Accelerometter+Gyroscope+Magnetometter) and process the raw data to obtain pitch and roll angles that are sended by Serial.  The file is located inside GetData_v5
 - Processing file ".pde": contains the code that you have to upload to your Processing IDLE. Allows to get the data from Arduino, via Serial, and makes a 3D representation of the movement. The file is located inside GetData_v5 --> visual_movement.
 
 
WARNING!: Check the port 'COM' assoiciated to the arduino, should be the same in both files (modify the files if it is necessary)
