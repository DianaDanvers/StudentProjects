#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <pcf8591.h>
#include <math.h>
#define uchar unsigned char
/*  ************************
	*Set all pin locations *
	************************ */
// LED Pin Locations
#define RightLedPinRed 	1	
#define RightLedPinGreen 4
#define RightLedPinBlue 5
//#define LeftLedPinRed 0
//#define LeftLedPinGreen 1
//#define LeftLedPinBlue 2

// PCF8591 Pin Location
#define PCFPin 120

// Flame Sensor Pin Locations
#define FlameDigitalPin 2
int 	FlameAnalogState = 0;
int 	FlameDigitalState = 0;

// Hall Sensor Pin Locations
#define HallPin 3 		// The SIG of hall sensor attach to 
int 	HallState = 0; 	// The variable to store the value read from Hall Switch

// Raindrop Sensor Pin Locations
#define RainDigitalPin 0 	//D0 attach to pin 
int 	RainAnalogState=0; 	//store the value of A0
int	RainDigitalState=0; 	//store the value of D0


void SystemSetup(void){
	// Right eye colors created
	softPwmCreate(RightLedPinRed, 0, 100);
	softPwmCreate(RightLedPinGreen,0, 100);
	softPwmCreate(RightLedPinBlue,0, 100);
	
	// Left eye colors created
//	softPwmCreate(LeftLedPinRed,0, 100);
//	softPwmCreate(LeftLedPinGreen,0, 100);
//	softPwmCreate(LeftLedPinBlue, 0, 100);
	
	pinMode(HallPin, INPUT);			// Ininitialize Hall Digital
	pinMode(PCFPin, INPUT);			// Ininitialize PCF
	pinMode(RainDigitalPin, INPUT);		// Ininitialize Raindrop Digital
	pinMode(FlameDigitalPin, INPUT);	// Ininitialize Flame Digital
	
	pcf8591Setup(PCFPin, 0x48);	// Initialize PCF8591 on base pin A0 and address 0x48

}
void EyesColorChange(uchar r_val, uchar g_val, uchar b_val){
	
	// Right eye
	softPwmWrite(RightLedPinRed, r_val);
	softPwmWrite(RightLedPinGreen, g_val);
	softPwmWrite(RightLedPinBlue, b_val);
	
	// Left eye
//	softPwmWrite(LeftLedPinRed, r_val);
//	softPwmWrite(LeftLedPinGreen, g_val);
//	softPwmWrite(LeftLedPinBlue, b_val);
	
}

int main(){
	
	if(wiringPiSetup() == -1){ // When initialize wiring failed, print message to screen
		printf("Setup wiringPi failed!");
		return 1; 
	}
	
	//printf("linker LedPin : GPIO %d(wiringPi pin)\n",LedPin); //when initialize wiring successfully,print message to screen
	
	SystemSetup();
	system("omxplayer -o local /home/pi/CSCI45/P1-Sentinel/lbp.mp3"); // Audio "Loading Battle Protocols"
	
	while(1){ //Full loop
	
		// Begin in Passive Mode
//		EyesColorChange(0xff,0xff,0x00); // Yellow eyes by default
		EyesColorChange(0x00,0x00,0xff); // Yellow eyes by default
		
		// Sensing w/Flame Analog - Pyro
		FlameAnalogState = analogRead(PCFPin + 0); // Read value from PCF
		FlameDigitalState = digitalRead(FlameDigitalPin);
		printf("Flame Analog: ");
		printf("%d\n", FlameAnalogState);  			// Print value
		
		// Sensing w/Hall - Magneto
		HallState = digitalRead(HallPin);  // Read value from Hall
		printf("Hall Digital: ");
		printf("%d\n", HallState);		
	
		// Sensing w/Raindrop - Storm
//		RainAnalogState = analogRead(RainAnalogPin); // Read value of A0
		RainDigitalState = digitalRead(RainDigitalPin); // Read value of D0
		printf("Raindrop State: ");
		printf("%d\n", RainDigitalState);

		// Mutant Detected
		if(RainDigitalState != HIGH || HallState != HIGH || FlameDigitalState != HIGH){
			printf("Mutant\n");
			system("omxplayer -o local /home/pi/CSCI45/P1-Sentinel/med.mp3");	// Audio "Mutant Entity Detected"
			delay(500);
			system("omxplayer -o local /home/pi/CSCI45/P1-Sentinel/tpe.mp3"); // Audio "Termination program engage"
			if(HallState != HIGH){				 // Magneto 
				printf("Magneto!");
//				EyesColorChange(0xff,0x00,0xff); // Purple eyes
				EyesColorChange(0x00,0xff,0x00); // Purple eyes
			}
			else if(FlameDigitalState != HIGH){		 // Pyro
				printf("Pyro!");
//				EyesColorChange(0xff,0x00,0x00); // Red eyes
				EyesColorChange(0x00,0xff,0xff); // Red eyes
			}
			else if(RainDigitalState != HIGH){		 // Storm
				printf("Storm!");
//				EyesColorChange(0x00,0x00,0xff); // Blue Eyes	
				EyesColorChange(0xff,0xff,0x00); // Blue Eyes	
			}
			delay(1500);
			
			// Returning to Passive Mode
			printf("Return to Passive");
			system("omxplayer -o local /home/pi/CSCI45/P1-Sentinel/me.mp3"); // Audio "Mutant Entity Elmited. Operations Successful"
//			EyesColorChange(0x00,0xff,0x00); // Status GREEN Eyes
			EyesColorChange(0xff,0x00,0xff); // Status GREEN Eyes
			delay(4000);
	
		
			// Return to default states
			RainDigitalState = digitalRead(RainDigitalPin); // Read value of D0
			HallState = digitalRead(HallPin);  // Read value from Hall
			FlameDigitalState = digitalRead(FlameDigitalPin);
			
			}
	}
	
	return 0;
}
