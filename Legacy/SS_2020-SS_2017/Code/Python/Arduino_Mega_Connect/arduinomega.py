##################################################
## (Python 2.7) *arduinomega.py					##
## Soft Robotics Pneumatic Platform Controller	##
## Developed by Thassyo Pinto					##
## All rights reserved							##
##################################################

import serial
import time

class ArduinoMega:
	HIGH = 1
	LOW = 0
	timeUnit = 1000.0 # milliseconds
	## Arduino Serial ##
	data = ""
	packet = ""
	waitTime = 25 # Send and receive wait time (milliseconds)
	arduinoPort = serial.Serial()
	## Arduino Parameters ##
	const_ADCPinCount = 10
	const_GPIOPinCount = 32
	const_GPIOPinStart = 22
	const_GPIOPinEnd = 53
	const_ParameterDelimiterString = ","
	const_PacketTerminatorString = "\n"
	## Arduino Commands ##
	const_GetADCValuesString = "ADC"
	const_GetGPIOValuesString = "DIG"
	const_SetGPIODirectionString = "PIN"
	const_SetGPIODirectionInString = "IN"
	const_SetGPIODirectionOutString = "OUT"
	const_SetPWMDutyCyleString = "PWM"
	const_SetFullStopString = "STP"

	def millis(self):
		return int(round(time.time() * self.timeUnit))

	def setupSerial(self, portName, baudRate):
		self.arduinoPort.port = portName
		self.arduinoPort.baudrate = baudRate
		self.arduinoPort.open()
		self.data = self.arduinoPort.readline()
		#print "Received: " + self.data.rstrip()

	def closeSerial(self):
		self.arduinoPort.close()

	def createPacket(self, command, parameters = []):
		message = []
		message.append(command)
		if parameters:
			for i in range(len(parameters)):
				message.append(self.const_ParameterDelimiterString)
				message.append(parameters[i])
		message.append(self.const_PacketTerminatorString)
		return ''.join(message)

	def getADC(self):
		self.packet = self.createPacket(self.const_GetADCValuesString)
		self.arduinoPort.write(self.packet)
		#print "Sent: " + self.packet.rstrip()
		time.sleep(self.waitTime / self.timeUnit)
		self.data = self.arduinoPort.readline()
		#print "Received: " + self.data.rstrip()
		return self.data.rstrip()

	def getGPIO(self):
		self.packet = self.createPacket(self.const_GetGPIOValuesString)
		self.arduinoPort.write(self.packet)
		time.sleep(self.waitTime / self.timeUnit)
		self.data = self.arduinoPort.readline()
		return self.data.rstrip()

	def setPWM(self, dutyCycles):
		self.packet = self.createPacket(self.const_SetPWMDutyCyleString, dutyCycles)
		self.arduinoPort.write(self.packet)
		#print "Sent: " + self.packet.rstrip()
		time.sleep(self.waitTime / self.timeUnit)
		self.data = self.arduinoPort.readline()
		#print "Received: " + self.data.rstrip()

	def setGPIO(self, pinNumber, pinState):
		self.packet = self.createPacket(self.const_SetGPIODirectionString, [pinNumber, pinState])
		self.arduinoPort.write(self.packet)
		print "Sent: " + self.packet.rstrip()
		time.sleep(self.waitTime / self.timeUnit)
		self.data = self.arduinoPort.readline()
		print "Received: " + self.data.rstrip()

	def sendSTOP(self):
		self.packet = self.createPacket(self.const_SetFullStopString)
		self.arduinoPort.write(message)
		print "Sent: " + self.packet.rstrip()
		time.sleep(self.waitTime / self.timeUnit)
		self.data = self.arduinoPort.readline()
		print "Received: " + self.data.rstrip()
