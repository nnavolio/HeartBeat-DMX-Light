  /* HeartBeat DMX Light
  Nicole Navolio - 3/1/2015
  Testing a DMX light so that it pulses like a human heartbeat.
  Preprocessing: I took audio of a heartbeat and took the "lub dub" sound.  
  I downsampled the audio to 8kHz to save space.  Then, I read in the audio 
  using matlab to downsample further.
  I got the amplitude values over time (-1 to 1), took the absolute value, 
  multiplied by 255, and then rounded to the nearest integer.
  I took this matrix of int amplitudes and pasted it below.
  The amplitude corresponds to the brightness using DmxSimple.write
 */
 
 #include <DmxSimple.h>

const byte amountOfLights = 8;
byte Sound[] = {0, 0, 0, 1, 2, 3, 1, 7, 24, 46, 64, 67, 58, 39, 13, 31, 113, 202, 251, 231, 151, 43, 62, 147, 208, 239, 243, 220, 176, 119, 56, 6, 63, 107, 134, 141, 126, 90, 39, 19, 74, 114, 134, 133, 114, 79, 33, 34, 118, 197, 248, 255, 217, 146, 59, 25, 96, 148, 181, 197, 200, 189, 166, 134, 96, 56, 16, 22, 55, 81, 99, 107, 107, 97, 80, 58, 32, 7, 17, 38, 53, 62, 65, 62, 54, 42, 28, 13, 2, 16, 27, 35, 39, 40, 37, 32, 24, 15, 6, 1, 5, 7, 6, 6, 5, 4, 3, 2, 2, 1, 0, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3, 3, 1, 9, 26, 48, 65, 67, 57, 37, 10, 38, 123, 211, 252, 224, 139, 30, 72, 155, 212, 241, 241, 216, 171, 112, 49, 13, 68, 111, 136, 140, 123, 85, 33, 26, 80, 118, 135, 132, 111, 75, 27, 43, 127, 205, 251, 253, 211, 137, 49, 34, 102, 152, 184, 198, 199, 187, 163, 130, 92, 51, 11, 26, 58, 83, 100, 108, 106, 95, 78, 55, 30, 4, 20, 40, 54, 63, 65, 61, 53, 41, 26, 11, 4, 17, 28, 35, 39, 40, 37, 31, 23, 14, 5, 1, 5, 7, 6, 5, 4, 4, 3, 2, 1, 1};
const int lengthOfSound = sizeof(Sound);

void setup(){
  Serial.begin(9600);
}

void loop(){   
  int audiosample=0;  
  int brightness=0;
    
  for (audiosample = 0; audiosample < lengthOfSound; audiosample++) {
        brightness=Sound[audiosample];

   Serial.println(brightness);
   for(byte i=0;i<amountOfLights;i++)
   {

     DmxSimple.write(i+1, brightness);
   }
   delay(2);

 }
  for(byte i=0;i<amountOfLights;i++){
    DmxSimple.write(i+1, 0);
 }
  delay(3000);
}

