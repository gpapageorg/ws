SoftwareSerial MyBlue(2, 3); // RX TX
class Bluetooth
{
  private:
    //static String ssend;
    static char got[10];
    
    public:
      static bool readBlue(Main *m , Secondary *s)
      {
        int availableBytes;
        if (availableBytes = MyBlue.available())
        {
          for(int i = 0; i< availableBytes; i++)
          { 
            got[i] = MyBlue.read();
            got[i+1] = '\0'; // Append a null
            
          }
          Serial.println(got);
        }
        
       
        if(strcmp(got, BRING_KEYWORD) == 0)
        {
          sendString(m, s);
          got[0] = '\0';
          Serial.println(F("Debug: Send All Sensors Data Via Bluetooth"));
          return true;
        }
        else
        {
          got[0] = '\0';
          return false;
        }

      }

  public:
    static void sendString(Main *m, Secondary *s)
    {
      const char format[] PROGMEM = "%1d %3d %3d %4d %4d";
      char send[BUFF_SIZE];

      sprintf(send, format, 0, m -> getDallasTemp(), m -> getDhtHumidity(), m -> getBmpPressure(), m -> getBmpAlt());

      
        for(int i = 0; i < MAX_STATIONS; i++)
          sprintf(&send[19 + 10*i], "|%1d %3d %3d", s[i].getId() + 1, s[i].getDallasTemp(), s[i].getDhtHumidity());

      send[20+10*MAX_STATIONS] = '\n';
      
      Serial.println(send);
      MyBlue.write(send);      
    }

};
char Bluetooth::got[10];
