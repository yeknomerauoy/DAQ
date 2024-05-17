#include <SPI.h>
#include <SD.h>
#include <Wire.h>

File myFile;
int c[32];

void setup() {
  Serial.begin(9600);
  Wire.begin(4);
  Wire.onReceive(receiveEvent);
  
  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  
}

void loop() {
  Wire.begin(4);

  myFile = SD.open("test2.txt", FILE_WRITE);
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.println("Writing...");
    int x=6;
    while(x--)
    {
      myFile.print(c[x]); 
    }
    myFile.println();
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

}


void receiveEvent(int howMany)
{  
  int cnt=0;
  while(1< Wire.available()) // loop through all but the last
  {
    c[cnt]= Wire.read()-'0'; // receive byte as a character
    
    cnt++;
  }
}