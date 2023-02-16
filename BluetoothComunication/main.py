import serial
import time
import re

PORT = '/dev/rfcomm0'

class Data:
    def __init__(self, string):
        self.__id = string[0]
        self.__temp = string[1] / 10
        self.__humidity = string[2] 
        self.__pressure = string[3] if len(string) >= 4 else -300
        self.__alt = string[4] if len(string) >= 5 else -300


    def getId(self):
        return self.__id
    
    def getTemp(self):
        return self.__temp
    
    def getHumidity(self):
        return self.__humidity
    
    def getPressure(self):
        return self.__pressure
    def getAlt(self):
        return self.__alt    
    
class Device:
    def __init__(self,port):
        self.port = port

        try:
            self.device = serial.Serial(self.port, 9600, timeout = 1)
        except:
            print("Error, Probably Adapter Not Connected")
            exit()
                
    def make_query(self):
        try:
            #self.device.write('trash\n'.encode('utf-8'))
            self.device.write('fetch\n'.encode('utf-8'))
            print("Debug: Query Made, Awaiting Response")
        except:
            print("Error, Can't Make Query")
    
    def get_text(self):
        self.inc = ''
        if(self.device.in_waiting != 0):
            self.inc = str(self.device.readline().decode('utf-8'))
            print("Debug: Response Arrived")

        #if(re.match('^[0-9]\s',self.inc) == None):
        #    print("None Arrived Trying Again In 3s")
        #    self.inc = ''
        #    time.sleep(3)
        #    self.make_query()
        #    time.sleep(1)
        #    self.get_text()
        #else:
        #print(len(self.inc))
        return self.inc

    def __del__(self):
        pass
       # self.device.close()

                    
def split_string(inc):
    start = 0
    end = 0
    data = []
    strings = []
    finValues = []
    
    print(inc)

    try:
        inc = re.sub(" +", " ", inc)
    except:
        print("Error In Splitting")

    for x in inc:
        if (x == "|" or x == "\n"):
            data.append(inc[start:end])
            start = end + 1
        end+=1 

    for x in range(len(data)):
        strings.append(data[x].split(' '))

    for x in range(len(strings)):
        strings[x] = [int(y) for y in strings[x]]
        #strings[x][0] = int(strings[x][0])

    for x in strings:
        finValues.append(Data(x))
    

    return finValues;


def main():

    ble = Device(PORT) 

    ble.make_query()
    time.sleep(1)
    data = ble.get_text()
    t = time.localtime()
    print(time.strftime("%H:%M:%S", t))


    receivedData = split_string(data)

    #print(len(receivedData))

    #printData(receivedData)
    
    del ble
    #exit()


def printData(values):
    for x in range(len(values)):
        print("Got From: ", end = '')
        print(values[x].getId())
        print(values[x].getTemp())
        print(values[x].getHumidity())
        print(values[x].getPressure())
        print(values[x].getAlt())

     
# Call Main Function
while(True):
    main()
    time.sleep(10)
