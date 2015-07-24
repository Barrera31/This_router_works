// Router!
int flexSensorPin1 = A0;
int flexSensorPin2 = A1;
int flexSensorPin3 = A2;
int flexSensorPin4 = A4;
int ledPin=13;
int button=10;
int button_read=0;
int b=0;
int k=0;
char s_str1[2];
char s_str2[2];
char s_str3[2];
char s_str4[2];
char command='e';
String str1,str2,str3,str4;

void setup(){
  pinMode(button,INPUT);  // The button is going to control if we are going to control either the robot arm or the motors.
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop(){
  
  if (digitalRead(button) == LOW)    // check if button was pressed
  {
    b++;
    b=b%2;                            
    delay(250);
      if (b==0){
        command='s';
        digitalWrite(ledPin,HIGH); // indicator on the hand to know if the motors is going to be controlled or the robot arm
      }
       else {
        command='e';
        digitalWrite(ledPin,LOW); 
      }    
  }
  
// Read the values
int flexS1 = analogRead(flexSensorPin1);
int flexS2 = analogRead(flexSensorPin2);
int flexS3 = analogRead(flexSensorPin3);
int flexS4 = analogRead(flexSensorPin4);

// Numbers below is individual for each of the flex sensors
if (flexS1 < 503) flexS1 = 503;         
else if (flexS1 > 660) flexS1 = 660;
if (flexS2 < 490) flexS2 = 490;
else if (flexS2 > 728) flexS2 = 728;
if (flexS3 < 495) flexS3 = 495;
else if (flexS3 > 724) flexS3 = 724;
if (flexS4 < 500) flexS4 = 500;
else if (flexS4 > 700) flexS4 = 700;

 // Mapping all the sensor values down between 0-9. (0 = full bent, 9 = unbent)
  int flex_1_0to100 = map(flexS1, 660, 503, 9, 0);
  int flex_2_0to100 = map(flexS2, 728, 490, 9, 0);
  int flex_3_0to100 = map(flexS3, 724, 495, 9, 0);
  int flex_4_0to100 = map(flexS4, 700, 500, 9, 0);
  
 // Converting all strings to a single char
  str1=String(flex_1_0to100);
  str1.toCharArray(s_str1,2);
 
  str2=String(flex_2_0to100);
  str2.toCharArray(s_str2,2);
  
  str3=String(flex_3_0to100);
  str3.toCharArray(s_str3,2);
  
  str4=String(flex_4_0to100);
  str4.toCharArray(s_str4,2);

 if (command=='e'){
  // Send all values to coordinator
  Serial1.print("e"); // Indicates the start of the message (e=motors, s=robot arm)
  Serial1.print(s_str4); // Thumb
  Serial1.print(s_str2);  // Index-finger
  Serial1.print(s_str3); // Middle-finger
  Serial1.print(s_str1);  // Pinky
  Serial.print("e"); // Indicates the start of the message (e=motors, s=robot arm)
  Serial.print(s_str4); // Thumb
  Serial.print(s_str2);  // Index-finger
  Serial.print(s_str3); // Middle-finger
  Serial.print(s_str1);  // Pinky
  delay(50);
 }
 else if (command=='s'){
  //Send all values to coordinator
  Serial1.print("s"); // Indicates the start of the message (e=motors, s=robot arm)
  Serial1.print(s_str4); // Thumb
  Serial1.print(s_str2);  // Index finger
  Serial1.print(s_str3); // Middle finger
  Serial1.print(s_str1);  // Pinky
  Serial.print("s"); // Indicates the start of the message (e=motors, s=robot arm)
  Serial.print(s_str4); // Thumb
  Serial.print(s_str2);  // Index finger
  Serial.print(s_str3); // Middle finger
  Serial.print(s_str1);  // Pinky
  delay(50); 
 }
}
