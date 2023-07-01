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
        delay(1500);
        lcd -> clear();
      }

      void displayMainScreen(Main *m, Secondary *sec)
      { 
        lcd-> clear();
        lcd -> setCursor(0,0);
        lcd -> write(0);
        lcd -> print((int)round(m->getDallasTemp()/10.0));
        lcd -> print("C");
        lcd -> print((char)223);
        lcd -> setCursor(0,1);
        lcd -> write(1);
        lcd -> print((int) m->getDhtHumidity());
        lcd -> print("%");
        lcd -> setCursor(15,0);
        lcd -> write(2);
        lcd -> print((int) m->getBmpPressure());
        lcd -> setCursor(15,1);
        lcd -> write(3);
        lcd -> print((int) m->getBmpAlt());

        
        lcd -> setCursor(0,3);
        lcd -> write(0);
        lcd -> print((int)round(sec[0].getDallasTemp()/10.0));
        lcd -> print("C");
        lcd -> print((char)223);
        lcd -> setCursor(15,3);
        lcd -> write(1);
        lcd -> print(sec[0].getDhtHumidity());
        lcd -> print("%");
        
        lcd -> setCursor(8,0);
        lcd -> print("Home");
        lcd -> setCursor(6,2);
        lcd -> print("Balcony");
      }

      void clearDisp()
      {
        lcd->clear();
      }

     private:
      void createCustomChar()
      {
        lcd -> createChar(0,tempChar);
        lcd -> createChar(1,humChar);
        lcd -> createChar(2,pressChar);
        lcd -> createChar(3,altChar);
      }
      
        
};
