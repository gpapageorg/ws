class Secondary : private Station
{
  int id;


  public:

    int getId()
    {
      return id;
    }
    int getDallasTemp()
    {
      return temp;
    }

    int getDhtHumidity()
    {
      return round(humidity);

    }

    void setTemp(float temp)
    {
      this -> temp = temp;
    }

    void setHumidity(float humidity)
    {
      this -> humidity = humidity;
    }
    void setId(int id)
    {
      this -> id = id;
    }

    bool areOutdated(int currentTime, int lastDataTime)
    {
      if(currentTime>=lastDataTime + OUTDATED_INTERVAL)
        return true;
      else
        return false;
    }
  
};
