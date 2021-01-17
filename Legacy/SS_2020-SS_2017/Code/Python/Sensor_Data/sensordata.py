import arduinomega as mcu
import csv
import sys

board = mcu.ArduinoMega()
portName = '/dev/ttyACM0'
baudRate = 115200

## Sensor Pins
sensorList = [0, 1, 2, 3]
## A0 = Force Sensor Right Leg
## A1 = Force Sensor Left Leg
## A2 = EMG Right Leg
## A3 = EMG Left Leg

lastTime = 0
timeStamp = 0

def main():
	global lastTime
	global timeStamp
	initialize()
	myFile = open('sensors_data.csv', 'w')
	with myFile:
		writer = csv.writer(myFile)
		writer.writerows([['Timestamp [ms]','Force Sensor (RL) [V]','Force Sensor (LL) [V]','EMG (RL) [V]','EMG (LL) [V]']])
		lastTime = board.millis()
		while True:
			currentTime = board.millis()
			elapsedTime = (currentTime - lastTime)
			timeStamp = timeStamp + elapsedTime
			adcStates = updateADC()
			sensorReadings = updateSensors(adcStates)
			sensorData = [[timeStamp, sensorReadings[0], sensorReadings[1], sensorReadings[2], sensorReadings[3]]]
			writer = csv.writer(myFile)
			writer.writerows(sensorData)
			lastTime = currentTime

def updateADC():
	adcList = []
	adcValues = []
	adcList = board.getADC().split(board.const_ParameterDelimiterString)
	for i in range(board.const_ADCPinCount):
		adcValues.append(int(adcList[i]))
	return adcValues

def updateSensors(adcValues):
	sensorValues = []
	for i in range(len(sensorList)):
		sensorValues.append(convertToVoltage(adcValues[sensorList[i]]))
	return sensorValues

def convertToVoltage(adcValue):
	voltageValue = adcValue * (5.0 / 1023.0)
	return voltageValue

def initialize():
	board.setupSerial(portName, baudRate)

if __name__ == "__main__":
	main()
