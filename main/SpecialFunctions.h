float convertFtoC(float f) { return (f - 32) * 0.55555; }
float convertCtoF(float c) { return c * 1.8 + 32; }

int computeHeatIndex(int temperature, int percentHumidity) {
  float hi;

  temperature = convertCtoF(temperature);

  hi = 0.5 * (temperature + 61.0 + ((temperature - 68.0) * 1.2) +
              (percentHumidity * 0.094));

  if (hi > 79) {
    hi = -42.379 + 2.04901523 * temperature + 10.14333127 * percentHumidity +
         -0.22475541 * temperature * percentHumidity +
         -0.00683783 * pow(temperature, 2) +
         -0.05481717 * pow(percentHumidity, 2) +
         0.00122874 * pow(temperature, 2) * percentHumidity +
         0.00085282 * temperature * pow(percentHumidity, 2) + 
         -0.00000199 * pow(temperature, 2) * pow(percentHumidity, 2);

    if ((percentHumidity < 13) && (temperature >= 80.0) &&
        (temperature <= 112.0))
        hi -= ((13.0 - percentHumidity) * 0.25) *
            sqrt((17.0 - abs(temperature - 95.0)) * 0.05882);

    else if ((percentHumidity > 85.0) && (temperature >= 80.0) &&
                (temperature <= 87.0))
          hi += ((percentHumidity - 85.0) * 0.1) * ((87.0 - temperature) * 0.2);
  }
  return round(convertFtoC(hi));
}

int calculateDewPoint(int temperature, int humidity)
{
  float td;
  float A = 17.27;
  float B = 237.7;

  float alpha = ((A * temperature) / (B + temperature)) + log(humidity / 100.0);

  td = (B * alpha) / (A - alpha);


  return round(td);
}

int calculateFrostPoint(float temperature, float dew)
{
  float fp;
  temperature += 273.15;
  dew += 273.15;


  fp = dew - temperature + 2671.02 / ((2954.61 / temperature) + 2.193665 * log(temperature) - 13.3448);

  return round(fp - 273.15);
}




                                                                         