#include <SoftwareSerial.h> 
SoftwareSerial MyBlue(2, 3); // RX TX

#define BUFF_SIZE 100

char flag = 0;
char a[BUFF_SIZE];
char got[BUFF_SIZE];
int availableBytes = 0;


void setup() {
  MyBlue.begin(9600); 
  Serial.begin(9600);
  strcpy(a, "0 22.4 45.4 9590-1 23.4 23\0");
  Serial.print(a);
}
s
void loop() 
{
  if (availableBytes = Serial.available())
  {
    for(int i=0; i<availableBytes; i++)
    {
        got[i] = Serial.read();
        got[i+1] = '\0'; // Append a null
    }

    

  }

  push(a);
  Serial.println(got);
  delay(5000);
}


void push(char *b)
{
  MyBlue.write(b);
}