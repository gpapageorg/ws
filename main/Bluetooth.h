SoftwareSerial MyBlue(2, 3); // RX TX
class Bluetooth
{

  private:
    //static String ssend;
    static int i;
    static char got[10];
    public:
      static bool readBlue(Main *m , Secondary *s)
      {

          while(MyBlue.available())
          { 
            got[i] = MyBlue.read();
            Serial.print("Avail");
            if (i < 9 && got[i] == '\n')
            {
              got[i + 1] = '\0';
              Serial.println("IN1");
              break;
              
            }
            else if (i >= 9)
            {
              Serial.println("IN2");
              //got[0] = '\0';
              i = 0;
              return false;  
            }
            i++;
            
          }
        
       
        if(got[i] == '\n')
        {
          if (strcmp(got, BRING_KEYWORD) == 0)
          {
              Serial.println("IN3");

            i = 0;
            Serial.print(got);
            got[0] = '\0';
            sendString(m, s);
            Serial.println(F("Debug: Send All Sensors Data Via Bluetooth"));
            return true;
          }
          else
          {
              Serial.println("IN4");

           i = 0;
           //got[0] = '\0';
           return false;
          }
        }

        else
          return false;
        
      }

    static void printgot()
    {
      for (int i = 0; i < 10; i++)
        Serial.print(got[i]);
    }
      

  public:
    static void sendString(Main *m, Secondary *s)
    {
      const char format[] PROGMEM = "%1d %3d %3d %4d %4d";
      char send[BUFF_SIZE];

      sprintf(send, format, 0, m -> getDallasTemp(), m -> getDhtHumidity(), m -> getBmpPressure(), m -> getBmpAlt());

      
        for(int i = 0; i < MAX_STATIONS; i++)
          sprintf(&send[19 + 14*i], "|%3d %4d %4d", s[i].getId() + 1, s[i].getDallasTemp(), s[i].getDhtHumidity());

      send[20 + 14*MAX_STATIONS] = '\n';
      
      Serial.print(send);
      MyBlue.write(send);      
    }

};
char Bluetooth::got[10];
int Bluetooth::i = 0;
