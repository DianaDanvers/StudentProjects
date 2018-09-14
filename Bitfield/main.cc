#include <iostream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <stdint.h>
#include <cmath>
using namespace std;

//This final homework assignment will teach you:
//Inheritance (polymorphism)
//Bit fields
//Refresher on overloading operators
//Three different ways of doing constants
//A bit of exceptions

//These constants can either be accessed by name "orange" or by "key_colors::orange" for clarity
enum key_colors {
	red = 1,
	yellow = 2,
	green = 4,
	blue = 8,
	orange = 16,
	ultraviolet = 32,
	brown = 64,
	black = 128
};

//The player can only have one of this list of bits set between JOB_THIEF and JOB_PSION
//Setting another bit in this range will clear all the other bits in the range set
const int JOB_THIEF  = 1;
const int JOB_RUNNER = 2;
const int JOB_WARLOCK = 4;
const int JOB_CHAPLAN = 8;
const int JOB_BERSERKER = 16;
const int JOB_GUERILLA = 32;
const int JOB_JUDOKA = 64;
const int JOB_ARMY = 128;
const int JOB_HACKER = 256;
const int JOB_MARTYR = 512;
const int JOB_CRUSADER = 1024;
const int JOB_TKD = 262144;
const int JOB_PSION = 524288;

const int JOB_ALL = 788479; //The sum of all bits above, for easy math

//Any or all of these can be set in addition to the above
const int JOB_ACTIVE = 2048;
const int JOB_FULL_HIDE = 4096;
const int JOB_TIRED = 8192;
const int JOB_BLOODY_KNIFE = 16384;
const int JOB_EXTRA1 =		65536;
const int JOB_EXTRA2 =		131072;

//This is the C way of doing constants
#define WEAP_HOOK				1
#define WEAP_THE_NAVARRO        2
#define WEAP_MEDIKIT			4
#define WEAP_SPANNER			8
#define WEAP_AXE				16
#define WEAP_SNIPER_RIFLE		32
#define WEAP_AUTO_RIFLE 		64
#define WEAP_SHOTGUN			128
#define WEAP_SUPER_SHOTGUN		256
#define WEAP_NAILGUN			512
#define WEAP_LIGHT_ASSAULT		1024
#define WEAP_GRENADE_LAUNCHER	2048
#define WEAP_FLAMETHROWER		4096
#define WEAP_ROCKET_LAUNCHER	8192
#define WEAP_INCENDIARY 		16384
#define WEAP_ASSAULT_CANNON 	32768
#define WEAP_LIGHTNING			65536
#define WEAP_DAEDALUS			131072
#define WEAP_TRANQ				262144
#define WEAP_RAILGUN			524288
#define WEAP_MAUSER 			1048576
#define WEAP_AIRFIST			2097152 
#define WEAP_LASERCANNON		4194304
#define WEAP_SNG				8388608

typedef int64_t int64; //Here's an example of how to do a typedef

class Bitfield {
	protected: //Protected, not private!!
		int64 datafield;
	public:
		Bitfield() : datafield(0) {}

		//YOU: Make this function virtual and see what happens in print_message...
		virtual void foo() { cout << "My datafield is: " << datafield << "\n"; }

		//YOU: Set the passed in flag on datafield
		void operator+=(const int64 flag) {
			datafield = datafield | flag;
		}

		//YOU: This function will clear the passed in flag
		void operator-=(const int64 flag) {
			datafield = datafield & ~flag; 
		}

		//YOU: This function will return true if the passed in flag is set
		bool operator==(const int64 flag) {
			return (datafield & flag);
		}
};

class Job_Bitfield : public Bitfield {
	public:
		Job_Bitfield() : Bitfield() {}
		void foo() {
			if (datafield)
				cout << "I have a job!\n";
			else
				cout << "I do not have a job.\n";
		}

		//YOU: Override the += operator for this class so that it clears any existing jobs between 
		// JOB_THIEF and JOB_PSION if a new bit in that range is set.
		//You can use JOB_ALL to quickly test to see if a bit is in that range, and clear all such bits
		// if you do get a match
		//The other bits (JOB_ACTIVE through JOB_EXTRA2) should be left alone and can be independently set
		//JOB_ALL cannot be set by the user. If he tries to, throw a runtime_exception with the string:
		// "Cannot set flag JOB_ALL"

		void operator+=(const int64 flag) {
			bool extraJobs [6] = {false}; // Remembering the extra jobs
			if(datafield == JOB_ACTIVE)			extraJobs[0] = true;
			if(datafield == JOB_FULL_HIDE)		extraJobs[1] = true;
			if(datafield == JOB_TIRED)			extraJobs[2] = true;
			if(datafield == JOB_BLOODY_KNIFE)	extraJobs[3] = true;
			if(datafield == JOB_EXTRA1)			extraJobs[4] = true;
			if(datafield == JOB_EXTRA2)			extraJobs[5] = true;

			datafield = datafield & ~ JOB_ALL;	// Remove all previous jobs

			if(extraJobs[0]) datafield = datafield | JOB_ACTIVE;	// Check to see if job was previously held
			if(extraJobs[1]) datafield = datafield | JOB_FULL_HIDE;
			if(extraJobs[2]) datafield = datafield | JOB_TIRED;
			if(extraJobs[3]) datafield = datafield | JOB_BLOODY_KNIFE;
			if(extraJobs[4]) datafield = datafield | JOB_EXTRA1;
			if(extraJobs[5]) datafield = datafield | JOB_EXTRA2;

			datafield = datafield | flag;	// Replace (1) only job
		}

};

class Weapon_Bitfield : public Bitfield {
	public:
		Weapon_Bitfield() : Bitfield() {}
		int64 select_best_weapon() {
			//YOU: Return the highest bit set
			if(datafield & WEAP_SNG){		 			cout << "WEAP_SNG" << endl;}
			else if(datafield & WEAP_LASERCANNON){ 		cout << "WEAP_LASERCANNON" << endl;}
			else if(datafield & WEAP_AIRFIST){ 			cout << "WEAP_AIRFIST" << endl;}
			else if(datafield & WEAP_MAUSER){ 			cout << "WEAP_MAUSER" << endl;}
			else if(datafield & WEAP_RAILGUN){ 			cout << "WEAP_RAILGUN" << endl;}
			else if(datafield & WEAP_TRANQ){ 			cout << "WEAP_TRANQ" << endl;}
			else if(datafield & WEAP_DAEDALUS){ 		cout << "WEAP_DAEDALUS" << endl;}
			else if(datafield & WEAP_LIGHTNING){ 		cout << "WEAP_LIGHTNING" << endl;}
			else if(datafield & WEAP_ASSAULT_CANNON){ 	cout << "WEAP_ASSAULT_CANNON" << endl;}
			else if(datafield & WEAP_INCENDIARY){ 		cout << "WEAP_INCENDIARY" << endl;}
			else if(datafield & WEAP_ROCKET_LAUNCHER){ 	cout << "WEAP_ROCKET_LAUNCHER" << endl;}
			else if(datafield & WEAP_FLAMETHROWER){ 	cout << "WEAP_FLAMETHROWER" << endl;}
			else if(datafield & WEAP_GRENADE_LAUNCHER){	cout << "WEAP_GRENADE_LAUNCHER" << endl;}
			else if(datafield & WEAP_LIGHT_ASSAULT){ 	cout << "WEAP_LIGHT_ASSAULT" << endl;}
			else if(datafield & WEAP_NAILGUN){ 			cout << "WEAP_NAILGUN" << endl;}
			else if(datafield & WEAP_SUPER_SHOTGUN){ 	cout << "WEAP_SUPER_SHOTGUN" << endl;}
			else if(datafield & WEAP_SHOTGUN){ 			cout << "WEAP_SHOTGUN" << endl;}
			else if(datafield & WEAP_AUTO_RIFLE){  		cout << "WEAP_AUTO_RIFLE" << endl;}
			else if(datafield & WEAP_SNIPER_RIFLE){ 	cout << "WEAP_SNIPER_RIFLE" << endl;}
			else if(datafield & WEAP_AXE){ 				cout << "WEAP_AXE" << endl;}
			else if(datafield & WEAP_SPANNER){ 			cout << "WEAP_SPANNER" << endl;}
			else if(datafield & WEAP_MEDIKIT){ 			cout << "WEAP_MEDIKIT" << endl;}
			else if(datafield & WEAP_THE_NAVARRO){ 		cout << "WEAP_THE_NAVARRO" << endl;}
			else if(datafield & WEAP_HOOK){ 			cout << "WEAP_HOOK" << endl;}
	
			//If we have no weapon at all, throw an exception
			//Don't bother catching it, we'll let it kill the program
			if (!datafield)
				throw runtime_error("Cannot select best weapon when we don't have one!");
		}
		void foo() {
			if (datafield >= WEAP_SNIPER_RIFLE) 
				cout << "I haz ranged weapon.\n";
			else if (datafield)
				cout << "I haz melee weapon.\n";
			else
				cout << "I no haz weapon.\n";
		}
};

//What will this print?
void print_message(Bitfield& b) {
	b.foo();
}

void uppercaseify(string& mystr){
	for(auto& c: mystr)
		c = toupper(c);
}

void fact(bool query){
	if(query) cout << "TRUE\n";
	else 	  cout << "FALSE\n";
}
int main() {
	Bitfield keys;
	Job_Bitfield jobs;
	Weapon_Bitfield weapons;

	while(cin){	
		string command = "", taskObject = "";
		cin >> command >> taskObject;
		uppercaseify(command);
		uppercaseify(taskObject);
		
		if(command == "QUERY"){
			if(taskObject.at(0) == 'J'){			// Job Query
				if(taskObject == "JOB_THIEF")		fact(jobs == JOB_THIEF); 
				if(taskObject == "JOB_RUNNER")		fact(jobs == JOB_RUNNER);
				if(taskObject == "JOB_WARLOCK")		fact(jobs == JOB_WARLOCK);
				if(taskObject == "JOB_CHAPLAN")		fact(jobs == JOB_CHAPLAN);
				if(taskObject == "JOB_BERSERKER")	fact(jobs == JOB_BERSERKER);
				if(taskObject == "JOB_GUERILLA")	fact(jobs == JOB_GUERILLA);
				if(taskObject == "JOB_JUDOKA")		fact(jobs == JOB_JUDOKA);
				if(taskObject == "JOB_ARMY")		fact(jobs == JOB_ARMY);
				if(taskObject == "JOB_HACKER")		fact(jobs == JOB_HACKER);
				if(taskObject == "JOB_MARTYR")		fact(jobs == JOB_MARTYR);
				if(taskObject == "JOB_CRUSADER")	fact(jobs == JOB_CRUSADER);
				if(taskObject == "JOB_TKD")			fact(jobs == JOB_TKD);
				if(taskObject == "JOB_PSION")		fact(jobs == JOB_PSION);
				if(taskObject == "JOB_ACTIVE")		fact(jobs == JOB_ACTIVE);
				if(taskObject == "JOB_FULL_HIDE")	fact(jobs == JOB_FULL_HIDE);
				if(taskObject == "JOB_TIRED")		fact(jobs == JOB_TIRED);
				if(taskObject == "JOB_BLOODY_KNIFE")fact(jobs == JOB_BLOODY_KNIFE);
				if(taskObject == "JOB_EXTRA1")		fact(jobs == JOB_EXTRA1);
				if(taskObject == "JOB_EXTRA2")		fact(jobs == JOB_EXTRA2);
			}
			if(taskObject.at(0) == 'W'){					// Weapon Query
				if(taskObject == "WEAP_HOOK")				fact(weapons == WEAP_HOOK);			
				if(taskObject == "WEAP_THE_NAVARRO")		fact(weapons == WEAP_THE_NAVARRO);
				if(taskObject == "WEAP_MEDIKIT")			fact(weapons == WEAP_MEDIKIT);
				if(taskObject == "WEAP_SPANNER")			fact(weapons == WEAP_SPANNER);
				if(taskObject == "WEAP_AXE")				fact(weapons == WEAP_AXE);			
				if(taskObject == "WEAP_SNIPER_RIFLE")		fact(weapons == WEAP_SNIPER_RIFLE);
				if(taskObject == "WEAP_AUTO_RIFLE")			fact(weapons == WEAP_AUTO_RIFLE);
				if(taskObject == "WEAP_SHOTGUN")			fact(weapons == WEAP_SHOTGUN);
				if(taskObject == "WEAP_SUPER_SHOTGUN")		fact(weapons == WEAP_SUPER_SHOTGUN);
				if(taskObject == "WEAP_NAILGUN")			fact(weapons == WEAP_NAILGUN);
				if(taskObject == "WEAP_LIGHT_ASSAULT")		fact(weapons == WEAP_LIGHT_ASSAULT);
				if(taskObject == "WEAP_GRENADE_LAUNCHER")	fact(weapons == WEAP_GRENADE_LAUNCHER);
				if(taskObject == "WEAP_FLAMEHTROWER")		fact(weapons == WEAP_FLAMETHROWER);
				if(taskObject == "WEAP_ROCKET_LAUNCHER")	fact(weapons == WEAP_ROCKET_LAUNCHER);
				if(taskObject == "WEAP_INCENDINARY")		fact(weapons == WEAP_INCENDIARY);
				if(taskObject == "WEAP_ASSUALT_CANNON")		fact(weapons == WEAP_ASSAULT_CANNON);
				if(taskObject == "WEAP_LIGHTNING")			fact(weapons == WEAP_LIGHTNING);
				if(taskObject == "WEAP_DAEDALUS")			fact(weapons == WEAP_DAEDALUS);
				if(taskObject == "WEAP_TRANQ")				fact(weapons == WEAP_TRANQ);
				if(taskObject == "WEAP_RAILGUN")			fact(weapons == WEAP_RAILGUN);
				if(taskObject == "WEAP_MAUSER")				fact(weapons == WEAP_MAUSER);
				if(taskObject == "WEAP_AIRFIST")			fact(weapons == WEAP_AIRFIST);
				if(taskObject == "WEAP_ASSAULT_CANNON")		fact(weapons == WEAP_ASSAULT_CANNON);
				if(taskObject == "WEAP_LASERCANNON")		fact(weapons == WEAP_LASERCANNON);
				if(taskObject == "WEAP_SNG")				fact(weapons == WEAP_SNG);
			}
			
			else{								// Key Query
				if(taskObject == "RED") 		fact(keys == red); 	
				if(taskObject == "YELLOW") 		fact(keys == yellow);
				if(taskObject == "GREEN") 		fact(keys == green);
				if(taskObject == "BLUE") 		fact(keys == blue);
				if(taskObject == "ORANGE") 		fact(keys == orange);
				if(taskObject == "ULTRAVIOLET") fact(keys == ultraviolet);
				if(taskObject == "BROWN") 		fact(keys == brown);	
				if(taskObject == "BLACK")	 	fact(keys == black);
			}
			
		}
		if(command == "ADD" ){
			if(taskObject.at(0) == 'J'){			// Job Add
				if(taskObject == "JOB_THIEF")		jobs += (JOB_THIEF);
				if(taskObject == "JOB_RUNNER")		jobs += (JOB_RUNNER);
				if(taskObject == "JOB_WARLOCK")		jobs += (JOB_WARLOCK);
				if(taskObject == "JOB_CHAPLAN")		jobs += (JOB_CHAPLAN);
				if(taskObject == "JOB_BERSERKER")	jobs += (JOB_BERSERKER);
				if(taskObject == "JOB_GUERILLA")	jobs += (JOB_GUERILLA);
				if(taskObject == "JOB_JUDOKA")		jobs += (JOB_JUDOKA);
				if(taskObject == "JOB_ARMY")		jobs += (JOB_ARMY);
				if(taskObject == "JOB_HACKER")		jobs += (JOB_HACKER);
				if(taskObject == "JOB_MARTYR")		jobs += (JOB_MARTYR);
				if(taskObject == "JOB_CRUSADER")	jobs += (JOB_CRUSADER);
				if(taskObject == "JOB_TKD")			jobs += (JOB_TKD);
				if(taskObject == "JOB_PSION")		jobs += (JOB_PSION);
				if(taskObject == "JOB_ACTIVE")		jobs += (JOB_ACTIVE);
				if(taskObject == "JOB_FULL_HIDE")	jobs += (JOB_FULL_HIDE);
				if(taskObject == "JOB_TIRED")		jobs += (JOB_TIRED);
				if(taskObject == "JOB_BLOODY_KNIFE")jobs += (JOB_BLOODY_KNIFE);
				if(taskObject == "JOB_EXTRA1")		jobs += (JOB_EXTRA1);
				if(taskObject == "JOB_EXTRA2")		jobs += (JOB_EXTRA2);
			}
			if(taskObject.at(0) == 'W'){					// Weapon Add
				if(taskObject == "WEAP_HOOK")				weapons += (WEAP_HOOK);
				if(taskObject == "WEAP_THE_NAVARRO")		weapons += (WEAP_THE_NAVARRO);
				if(taskObject == "WEAP_MEDIKIT")			weapons += (WEAP_MEDIKIT);
				if(taskObject == "WEAP_SPANNER")			weapons += (WEAP_SPANNER);
				if(taskObject == "WEAP_AXE")				weapons += (WEAP_AXE);
				if(taskObject == "WEAP_SNIPER_RIFLE")		weapons += (WEAP_SNIPER_RIFLE);
				if(taskObject == "WEAP_AUTO_RIFLE")			weapons += (WEAP_AUTO_RIFLE);
				if(taskObject == "WEAP_SHOTGUN")			weapons += (WEAP_SHOTGUN);
				if(taskObject == "WEAP_SUPER_SHOTGUN")		weapons += (WEAP_SUPER_SHOTGUN);
				if(taskObject == "WEAP_NAILGUN")			weapons += (WEAP_NAILGUN);
				if(taskObject == "WEAP_LIGHT_ASSAULT")		weapons += (WEAP_LIGHT_ASSAULT);
				if(taskObject == "WEAP_GRENADE_LAUNCHER")	weapons += (WEAP_GRENADE_LAUNCHER);
				if(taskObject == "WEAP_FLAMEHTROWER")		weapons += (WEAP_FLAMETHROWER);
				if(taskObject == "WEAP_ROCKET_LAUNCHER")	weapons += (WEAP_ROCKET_LAUNCHER);
				if(taskObject == "WEAP_INCENDINARY")		weapons += (WEAP_INCENDIARY);
				if(taskObject == "WEAP_ASSUALT_CANNON")		weapons += (WEAP_ASSAULT_CANNON);
				if(taskObject == "WEAP_LIGHTNING")			weapons += (WEAP_LIGHTNING);
				if(taskObject == "WEAP_DAEDALUS")			weapons += (WEAP_DAEDALUS);
				if(taskObject == "WEAP_TRANQ")				weapons += (WEAP_TRANQ);
				if(taskObject == "WEAP_RAILGUN")			weapons += (WEAP_RAILGUN);
				if(taskObject == "WEAP_MAUSER")				weapons += (WEAP_MAUSER);
				if(taskObject == "WEAP_AIRFIST")			weapons += (WEAP_AIRFIST);
				if(taskObject == "WEAP_ASSAULT_CANNON")		weapons += (WEAP_ASSAULT_CANNON);
				if(taskObject == "WEAP_LASERCANNON")		weapons += (WEAP_LASERCANNON);
				if(taskObject == "WEAP_SNG")				weapons += (WEAP_SNG);

			}
			else{								// Key Add
				if(taskObject == "RED") 		keys += (key_colors::red);
				if(taskObject == "YELLOW") 		keys += (key_colors::yellow);
				if(taskObject == "GREEN") 		keys += (key_colors::green);
				if(taskObject == "BLUE") 		keys += (key_colors::blue);
				if(taskObject == "ORANGE") 		keys += (key_colors::orange);
				if(taskObject == "ULTRAVIOLET") keys += (key_colors::ultraviolet);
				if(taskObject == "BROWN") 		keys += (key_colors::brown);
				if(taskObject == "BLACK")	 	keys += (key_colors::black);
			}

		}

		if(command == "SELECT"){
			weapons.select_best_weapon();
		}

		if(command == "DELETE"){
			if(taskObject.at(0) == 'J'){			// Job Delete
				if(taskObject == "JOB_THIEFF")		jobs -= (JOB_THIEF);
				if(taskObject == "JOB_RUNNER")		jobs -= (JOB_RUNNER);
				if(taskObject == "JOB_WARLOCK")		jobs -= (JOB_WARLOCK);
				if(taskObject == "JOB_CHAPLAN")		jobs -= (JOB_CHAPLAN);
				if(taskObject == "JOB_BERSERKER")	jobs -= (JOB_BERSERKER);
				if(taskObject == "JOB_GUERILLA")	jobs -= (JOB_GUERILLA);
				if(taskObject == "JOB_JUDOKA")		jobs -= (JOB_JUDOKA);
				if(taskObject == "JOB_ARMY")		jobs -= (JOB_ARMY);
				if(taskObject == "JOB_HACKER")		jobs -= (JOB_HACKER);
				if(taskObject == "JOB_MARTYR")		jobs -= (JOB_MARTYR);
				if(taskObject == "JOB_CRUSADER")	jobs -= (JOB_CRUSADER);
				if(taskObject == "JOB_TKD")			jobs -= (JOB_TKD);
				if(taskObject == "JOB_ACTIVE")		jobs -= (JOB_ACTIVE);
				if(taskObject == "JOB_FULL_HIDE")	jobs -= (JOB_FULL_HIDE);
				if(taskObject == "JOB_TIRED")		jobs -= (JOB_TIRED);
				if(taskObject == "JOB_BLOODY_KNIFE")jobs -= (JOB_BLOODY_KNIFE);
				if(taskObject == "JOB_EXTRA1")		jobs -= (JOB_EXTRA1);
				if(taskObject == "JOB_EXTRA2")		jobs -= (JOB_EXTRA2);
			}
			if(taskObject.at(0) == 'W'){					// Weapon Delete
				if(taskObject == "WEAP_HOOK")				weapons -= (WEAP_HOOK);
				if(taskObject == "WEAP_THE_NAVARRO")		weapons -= (WEAP_THE_NAVARRO);
				if(taskObject == "WEAP_MEDIKIT")			weapons -= (WEAP_MEDIKIT);
				if(taskObject == "WEAP_SPANNER")			weapons -= (WEAP_SPANNER);
				if(taskObject == "WEAP_AXE")				weapons -= (WEAP_AXE);
				if(taskObject == "WEAP_SNIPER_RIFLE")		weapons -= (WEAP_SNIPER_RIFLE);
				if(taskObject == "WEAP_AUTO_RIFLE")			weapons -= (WEAP_AUTO_RIFLE);
				if(taskObject == "WEAP_SHOTGUN")			weapons -= (WEAP_SHOTGUN);
				if(taskObject == "WEAP_SUPER_SHOTGUN")		weapons -= (WEAP_SUPER_SHOTGUN);
				if(taskObject == "WEAP_NAILGUN")			weapons -= (WEAP_NAILGUN);
				if(taskObject == "WEAP_LIGHT_ASSAULT")		weapons -= (WEAP_LIGHT_ASSAULT);
				if(taskObject == "WEAP_GRENADE_LAUNCHER")	weapons -= (WEAP_GRENADE_LAUNCHER);
				if(taskObject == "WEAP_FLAMEHTROWER")		weapons -= (WEAP_FLAMETHROWER);
				if(taskObject == "WEAP_ROCKET_LAUNCHER")	weapons -= (WEAP_ROCKET_LAUNCHER);
				if(taskObject == "WEAP_INCENDINARY")		weapons -= (WEAP_INCENDIARY);
				if(taskObject == "WEAP_ASSUALT_CANNON")		weapons -= (WEAP_ASSAULT_CANNON);
				if(taskObject == "WEAP_LIGHTNING")			weapons -= (WEAP_LIGHTNING);
				if(taskObject == "WEAP_DAEDALUS")			weapons -= (WEAP_DAEDALUS);
				if(taskObject == "WEAP_TRANQ")				weapons -= (WEAP_TRANQ);
				if(taskObject == "WEAP_RAILGUN")			weapons -= (WEAP_RAILGUN);
				if(taskObject == "WEAP_MAUSER")				weapons -= (WEAP_MAUSER);
				if(taskObject == "WEAP_AIRFIST")			weapons -= (WEAP_AIRFIST);
				if(taskObject == "WEAP_ASSAULT_CANNON")		weapons -= (WEAP_ASSAULT_CANNON);
				if(taskObject == "WEAP_LASERCANNON")		weapons -= (WEAP_LASERCANNON);
				if(taskObject == "WEAP_SNG")				weapons -= (WEAP_SNG);
			}
			else{								// Key Delete
				if(taskObject == "RED") 		keys -=(key_colors::red);
				if(taskObject == "YELLOW") 		keys -=(key_colors::yellow);
				if(taskObject == "GREEN") 		keys -=(key_colors::green);
				if(taskObject == "BLUE") 		keys -=(key_colors::blue);
				if(taskObject == "ORANGE") 		keys -=(key_colors::orange);
				if(taskObject == "ULTRAVIOLET") keys -=(key_colors::ultraviolet);
				if(taskObject == "BROWN") 		keys -=(key_colors::brown);
				if(taskObject == "BLACK")	 	keys -=(key_colors::black);
			}

		}
/*
		//Example code, can delete...
		keys.foo();
		jobs.foo();
		weapons += (WEAP_AXE);
		weapons.foo();
		print_message(keys);
		print_message(jobs);
		print_message(weapons);
		keys+=(key_colors::red);
		keys-=(green);
		if (keys == red) cout << "Haz red.\n";
		weapons.select_best_weapon();
*/
	}


	//YOU: Write a main loop that will allow the user to set, clear, and test to see if certain flags are set
	// within the bitfields declared above. You'll need to keep track of three:
	//1) keys, which will hold the values from key_colors::red through black. 
	//2) jobs, which will hold the const ints for jobs, with special rules (you can only have one job)
	//3) weapons, which will allow the user to query what the best weapon he has is.

	//SYNTAX: 
	//"ADD <flagname>" will add the flag to the appropriate bitfield. (Example: "ADD RED" or "ADD WEAP_ROCKET_LAUNCHER" or "ADD JOB_PSION") (JOB_ALL cannot be set by the user)
	//"DELETE <flagname>" removes the flag from the appropriate bitfield. (Example: "REMOVE ORANGE" will clear the orange flag from the keys bitfield.
	//"QUERY <flagname>" will cout "TRUE" if the flag is set in the appropriate bitfield, or "FALSE" otherwise. (Example: "ADD JOB_PSION", "QUERY JOB_PSION" will print "TRUE" to the screen.) 
	//"SELECT BEST WEAPON will cout the name of the highest bit set (Example: If the bits for the axe and rocket launcher have been set, it will print to the screen "WEAP_ROCKET_LAUNCHER".)
	//On an invalid command (i.e. not one of the four possibilities above), throw a runtime_error with the string "Invalid Input", and let it kill the program
}
