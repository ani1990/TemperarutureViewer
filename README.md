# Real-Time Measurement of Temperature on a System on Chip with Consideration of Ambient Temperature


## Description 
* Reading temperature of panStamp nodes using onboard SI7021 temperature and humidity sensor. 
* Developing an Android application to display real-time data.
* Firebase cloud database is used to store data from panStamp nodes, which ultimately read by Android application in real-time to plot real-time graph.
* Comparison of sensitivity between SI7021 and DHT11 external temperature sensor using Arduino UNO.



## Arduino

* Modem code used for a base station.
* Beacon code used for temperature nodes.
* Temperature nodes will be sending temperature data to the base station in below format

  ``` <Base Station ID> <Node ID> <Tempearture Value>```
  
  Ex: 211345
  
 * Data is reached to the modem, python script will read data from the serial port and upload it to firebase cloud.
 
 * Andoird application reads data from cloud and plots temperature values over the graph. 

## MIT app inventor for android application
* MIT App inventor uses block-based coding method.
* It uses a graphical interface to drag and drop visual objects.
* Integrated with Firebase for cloud services.
* Please follow this [link](https://appinventor.mit.edu/) to develop android applications using MIT app inventor.


## Read serial data and upload to Firebase 
* SerialReadPythonScript.py reads serial data given by the modem and uploads data to firebase cloud and modem should be connected to a computer USB port. 
* Python packages like Pyrebase and pySerial are required to be installed. Link for installing packages [Pyrebase](https://pypi.org/project/Pyrebase/) and [pySerial](https://pypi.org/project/pyserial/)
 
## Firebase cloud service
* Firebase is the real-time cloud services provided by Google to read and write data in real-time in Cloud
* Please follow this [link](https://firebase.google.com/) to create firebase database.

## Authors
* Animesh Mukherjee
* Sharad Sirsat
* Giriaj Pawar
