
import pyrebase
import time
import re
import io
import serial
config = {
  "apiKey": "apiKey",
  "authDomain": "projectId.firebaseapp.com",
  "databaseURL": "https://temperaturedatabase-47c41.firebaseio.com/",
  "storageBucket": "projectId.appspot.com"
}

firebase = pyrebase.initialize_app(config)

db = firebase.database()
#current time and date

ser = serial.Serial('/dev/ttyUSB1', 38400, timeout=0)

interval = 1
while 1:
  try:
   
    temperature_c = ser.readline()    
    #print(temperature_c)

    #only read integer
    temperature_c = [int(i) for i in temperature_c.split() if i.isdigit()]
    
    # Avoid empty list 
    if not temperature_c:
    	continue
    # print only first element
    #print (temperature_c[0])
    
    sensorData = str(temperature_c[0])
    #print (sensorData)

    time_hhmmss = time.strftime('%H:%M:%S')
    date_mmddyyyy = time.strftime('%d-%m-%Y')



    if len(sensorData) != 6:
       continue
 
    print(sensorData)

    NodeID = sensorData[2] + sensorData[3]
    temperature = sensorData[4] + sensorData[5]

    #print (NodeID)
    #print (temperature) 
    
    if(NodeID == '13'):
        node = "Node 13/"
    if(NodeID == '16'):
        node = "Node 16/"
    if(NodeID == '17'):
        node = "Node 17/"


    tempViewverDB = "TemperatureViewerDB/"
    data = {time_hhmmss: str(temperature)}
    db.child(tempViewverDB + node + date_mmddyyyy).update(data)

    ser.flushInput()
    ser.flushOutput()


  except IOError:
    print('Error! Something went wrong.')
  time.sleep(interval)









