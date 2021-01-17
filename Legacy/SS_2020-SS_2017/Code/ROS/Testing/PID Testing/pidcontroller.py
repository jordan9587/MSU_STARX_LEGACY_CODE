##################################################
## (Python 2.7) *pidcontroller.py				##
## Soft Robotics Pneumatic Platform Controller	##
## Developed by Thassyo Pinto					##
## All rights reserved							##
##################################################

import time

class PID:
	MANUAL = 0
	AUTOMATIC = 1
	DIRECT = 0
	REVERSE = 1
	
	lastTime = 0
	inputValue = 0.0
	outputValue = 0.0
	setPoint = 0.0
	iTerm = 0.0
	lastInput = 0.0
	kpGain = 0.0
	kiGain = 0.0
	kdGain = 0.0
	outMin = 0.0
	outMax = 0.0
	sampleTime = 1000 # milliseconds
	inAuto = False
	controllerDirection = DIRECT
	
	def millis(self):
		return int(round(time.time() * 1000))

	def computeValues(self):
		if not self.inAuto: return
		currentTime = self.millis()
		elapsedTime = (currentTime - self.lastTime)
		if elapsedTime >= self.sampleTime:
			self.errorValue = self.setPoint - self.inputValue
			self.iTerm += self.kiGain * self.errorValue
			if self.iTerm > self.outMax:
				self.iTerm = self.outMax
			elif self.iTerm < self.outMin:
				self.iTerm = self.outMin
			dInput = self.inputValue - self.lastInput
			## PID Equation ##
			self.outputValue = self.kpGain * self.errorValue + self.iTerm - self.kdGain * dInput
			##################
			if self.outputValue > self.outMax:
				self.outputValue = self.outMax
			elif self.outputValue < self.outMin:
				self.outputValue = self.outMin
			self.lastInput = self.inputValue
			self.lastTime = currentTime

	def setTunings(self,kP, kI, kD):
		if (kP < 0) or (kI < 0) or (kD < 0): return
		sampleTimeInSec = self.sampleTime / 1000.0;
		self.kpGain = kP
		self.kiGain = kI * sampleTimeInSec
		self.kdGain = kD / sampleTimeInSec
		if self.controllerDirection == self.REVERSE:
			self.kpGain = (0 - self.kpGain)
			self.kiGain = (0 - self.kiGain)
			self.kdGain = (0 - self.kdGain)

	def setSampleTime(self, newSampleTime):
		if newSampleTime > 0:
			ratio = newSampleTime / self.sampleTime;
			self.kiGain *= ratio
			self.kdGain /= ratio
			self.sampleTime = newSampleTime

	def setOutputLimits(self, Min, Max):
		if Min > Max: return
		self.outMin = Min
		self.outMax = Max
		if self.outputValue > self.outMax:
			self.outputValue = self.outMax
		elif self.outputValue < self.outMin:
			self.outputValue = self.outMin
		if self.iTerm > self.outMax:
			self.iTerm = self.outMax
		elif self.iTerm < self.outMin:
			self.iTerm = self.outMin

	def setMode(self, Mode):
		newAuto = (Mode == self.AUTOMATIC)
		if not newAuto == self.inAuto:
			self.initialize();
		self.inAuto = newAuto

	def initialize(self):
		self.lastInput = self.inputValue
		self.iTerm = self.outputValue
		if self.iTerm > self.outMax:
			self.iTerm = self.outMax
		elif self.iTerm < self.outMin:
			self.iTerm = self.outMin

	def setControllerDirection(self, Direction):
		self.controllerDirection = Direction


	
