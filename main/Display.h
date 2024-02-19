class Display
{
  
    public:      
      LiquidCrystal_I2C *lcd;
      
      void initializeDisp()
      {
        lcd = new LiquidCrystal_I2C(0x27, 20, 4);
        lcd -> init();   
        lcd -> backlight();
        lcd -> setCursor(2,0);
        lcd -> print(F("Weather  Station"));
        lcd -> setCursor(8,1);
        lcd -> print(F("V2.0"));
        lcd -> setCursor(5,3);
        lcd -> print(F("Booting..."));
        createCustomChar();
        delay(1000);
        lcd -> clear();
      }

      void displayMainScreen(Main *m)
      {
        lcd -> setCursor(0,0); // Printing Dallas Temperature
        lcd -> write(0);
        lcd -> print(" ");
        lcd -> print((int)round(m->getDallasTemp()/10.0));  
        lcd -> print("   ");
      
        lcd -> setCursor(8,0);
        lcd -> print("Home");

        lcdPrintInverse((int)round(m->getDhtHumidity()),17,0);
        lcd -> setCursor(18,0);
        lcd -> print(" ");
        lcd -> write(1);

        lcd -> setCursor(0,1); // Printing Bmp Pressure Temperature
        lcd -> write(2);
        lcd -> print(" ");
        lcd -> print((int) m->getBmpPressure());  
        lcd -> print("    ");
      
        lcdPrintInverse((int) m->getBmpAlt(),17,1);

        lcd -> setCursor(18,1);
        lcd -> print(" ");
        lcd -> write(3);
      }

    void updateSecondariesScreen(Secondary *sec)
    {

        int temp =  round(sec[0].getDallasTemp()/10.0);
        int hum =  sec[0].getDhtHumidity();
        int dew = calculateDewPoint(temp,hum);
        int frost = calculateFrostPoint(temp,dew);
        int hid = computeHeatIndex(temp,hum);

        lcd -> setCursor(0,2);
        lcd -> write(0);
        lcd -> print(" ");
        lcd -> print(temp);
        
        lcd -> setCursor(6,2);
        lcd -> print("Balcony");

        lcdPrintInverse(hum,17,2);
        lcd -> setCursor(18,2);
        lcd -> print(" ");
        lcd -> write(1);

        lcd -> setCursor(0,3);
        lcd -> write(4);
        lcd -> print(" ");
        lcd -> print(hid);

        lcdPrintInverse(dew,10,3);
        lcd -> setCursor(11,3);
        lcd -> print(" ");
        lcd -> write(5);

        lcdPrintInverse(frost,17,3);
        lcd -> setCursor(18,3);
        lcd -> print(" ");
        lcd -> write(6);
        
    }
    void clearScreen()
    {
      lcd -> clear();
    }
    void clearLine(int line)
    {
      for(int i=0; i<=19; i++)
      {
        lcd -> setCursor(i,line);
        lcd -> print(" ");
      }
    }

     private:
      void createCustomChar()
      {
        lcd -> createChar(0,tempChar);
        lcd -> createChar(1,humChar);
        lcd -> createChar(2,pressChar);
        lcd -> createChar(3,altChar);
        lcd -> createChar(4, HidChar);
        lcd -> createChar(5, DewChar);
        lcd -> createChar(6, frostChar);
      }

      void lcdPrintInverse(int num, int column, int line)
      {
        int k;
        bool isNeg = num >= 0 ? false : true;
        num = abs(num);

        do{
          k = num % 10;
          lcd -> setCursor(column,line);
          lcd -> print(k);
          num /= 10;
          k = num % 10;
          column--;
        }while(num > 0);

        if(isNeg)
        {
          lcd -> setCursor(column,line);
          lcd -> print("-");
        }

        lcd -> setCursor(--column,line);
        lcd -> print("  ");

      }
      
        
};
