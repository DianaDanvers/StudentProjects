import RPi.GPIO as GPIO
import subprocess
import os
import time
import pylirc
#GPIO.setmode(GPIO.BOARD)
blocking = 0
def setup():
	GPIO.setmode(GPIO.BOARD)
	#GPIO.setmode(GPIO.BCM)
	GPIO.setup(7,GPIO.OUT)
	GPIO.setup(11,GPIO.OUT)
	GPIO.setup(22, GPIO.OUT)
	GPIO.output(22, GPIO.LOW)
	pylirc.init("pylirc", "./conf", blocking)
        
        
feedtime = subprocess.check_output(["date"]);
#print(feedtime);


feed = feedtime[11:16];


feedBreakfast = "06:00"
feedDinner    = "18:00"
def foodmix():
	print("din din")
	os.system("omxplayer -o local /home/pi/Desktop/Dinner_OhWow.mp3")
	#GPIO.setup(7,GPIO.OUT)
	food = GPIO.PWM(7,50)
	food.start(7.5)
	food.ChangeDutyCycle(10)
	time.sleep(5)
	food.ChangeDutyCycle(1.75)
	time.sleep(5)

def treatmix():
	print 'treat pressed'
	#GPIO.setup(11,GPIO.OUT)
	os.system("omxplayer -o local /home/pi/Desktop/MuchSkill_SucculentTreat.mp3")
	treat = GPIO.PWM(11,50)
	treat.start(7.5)	
	treat.ChangeDutyCycle(10.5)
	time.sleep(5)
	treat.ChangeDutyCycle(2)
	time.sleep(5)
	
def ball(config):
		if config == 'KEY_NUMERIC_1':
			foodmix()
			print 'You pressed button number 1'

		if config == 'KEY_NUMERIC_2':
			treatmix()
			print 'You pressed button number 2'

		if config == 'KEY_NUMERIC_3':
			os.system("omxplayer -o local /home/pi/Desktop/GreatSpeed_Fun_OhJoy.mp3")
			GPIO.output(22, GPIO.HIGH)
			time.sleep(0.5)
			print ("You pressed button number 3")
			GPIO.output(22, GPIO.LOW)

def feeder():
	while True:
		s = pylirc.nextcode(1)
		while (s):
			for (code) in s:
				 ball(code["config"])
			if (not blocking):
				s = pylirc.nextcode(1)
			else:
				s = []
		
#should feed				
		if feed == feedBreakfast or feed == feedDinner:
			foodmix()
		#elif feed != feedBreakfast or feed != feedDinner:
			#print("too early")
			
try:
	setup()
	feeder()
	
except KeyboardInterrupt:
        food.stop()
        treat.stop()
	GPIO.output(22, GPIO.LOW)
        GPIO.cleanup()
        pylirc.exit()


