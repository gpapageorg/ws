#include "RH_ASK.h"
RH_ASK driver(1000, 10, 9, 8);

struct IncomingData
{
  int id;
  float temp;
  float humidity;
} data;
class Receiver
{

  static int time;
  static IncomingData received[MAX_STATIONS];

  unsigned char buf[BUFF_SIZE];

  protected:
    static char bufc[BUFF_SIZE];
  
  public:
    bool get()
    {
  
        unsigned char buflen = sizeof(buf);
        
        if (driver.recv(buf, &buflen))
        {
          time = seconds();
          buf[buflen] = 0;
          strcpy(bufc, (char *) buf);
          clear_buff(buf);
          return true;
        }
        else
        {
          clear_buff(buf);
          return false;
        }
     }
      
      static void getReceivedData(int *id, float *temp, float *humidity)
      {
         split();
         *id = data.id;
         *temp = received[data.id].temp;
         *humidity = received[data.id].humidity;
         //Serial.print("Id from fun: ");
         //Serial.println(*id);

      }
  

    private:
      void clear_buff(uint8_t *buff)
      {

        for (int i = 0; i < BUFF_SIZE; i++)
          buff[i] = 0;
      }
          
    int seconds()
    {
      return millis() / 1000;
    }

    static void split()
    {
      int ttemp, thumidity;

      sscanf(bufc, "%d %d %d", &data.id, &ttemp, &thumidity);
      data.temp = ttemp;
      data.humidity = thumidity;
      Serial.println((char *) bufc);
      received[data.id] = data;
    }
  public:
  static void initializeReceived()
  {
    IncomingData d;
    d.humidity = -300;
    d.temp = -300;
    d.id = -3;
    for (int i = 0; i < MAX_STATIONS; i++)
    { 
      received[i] = d;
    }
    //Serial.print(received[0].temp);
  }
};

char Receiver::bufc[BUFF_SIZE];
IncomingData Receiver::received[MAX_STATIONS];
int Receiver::time;
