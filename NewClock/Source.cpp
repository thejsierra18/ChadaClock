/*SNHU - CS 210
  ChadaTech_Clock
  Jorge Sierra Alzaga
*/


#include <ctime>                                                                                                              //This header file contains definitions of functions to get and manipulate date and time information.
#include <string>                                                                                                             
#include <iostream>                                                                                                           
#include<iomanip>                                                                                                             
#include <conio.h>                                                                                                            //Next two headers used with function to register any type of keyboard hit.
#include <Windows.h>                                                                                                          
                                                                                                                              
using namespace std;                                                                                                          
																										                      
void displayTime(int twelveHour, int hour, int min, int sec, string am_pm) {                                                  //Function used to display time as requested. Setfill used to always show two digits.
	cout << "**************************    **************************" << endl;
	cout << "*     12- Hour Clock     *    *     24- Hour Clock     *" << endl;
	cout << "*       " << setw(2) << setfill('0') << twelveHour << ":";
	cout << setw(2) << setfill('0') << min << ":";
	cout << setw(2) << setfill('0') << sec << " ";
	cout << am_pm << "     *    *         ";
	cout << setw(2) << setfill('0') << hour << ":";
	cout << setw(2) << setfill('0') << min << ":";
	cout << setw(2) << setfill('0') << sec << " ";
	cout << "      *" << endl;
	cout << "**************************    **************************" << endl;
}

void displayMenu() {                                                                                                          //Function used to display menu as requested.
	cout << "**************************" << endl;
	cout << "* 1 - Add One Hour       *" << endl;
	cout << "* 2 - Add One Minute     *" << endl;
	cout << "* 3 - Add One Second     *" << endl;
	cout << "* 4 - Exit Program       *" << endl;
	cout << "**************************" << endl;
}


string am_pm(int hour) {                                                                                                      //Function used to determine when to display A M or P M depending on the time.
	string status;

	if (hour >= 12) {
		status = "P M";
	}
	else {
		status = "A M";
	}
	return status;
}

int twelveHour(int hour) {                                                                                                    //Function used to convert time from 24 hours to 12 hours.
	int formattedHour;
	if (hour > 12) {
		formattedHour = hour - 12;
	}
	else {
		formattedHour = hour;
	}
	return formattedHour;
}

void addHour(int& currentHour) {                                                                                              //Function to add 1 hour to the current time.
	if (currentHour == 23){
		currentHour = 0;
	}
	else {
		currentHour += 1;
	}
}

void addMinute(int& currentMin, int& currentHour) {                                                                          //Function to add 1 minute to the current time.
	if (currentMin == 59) {
		currentMin = 0;
		addHour(currentHour);                                                                                                //Using addHour() in case minute is at the top of the hour.
	}
	else {
		currentMin += 1;
	}
}

void addSecond(int& currentSec, int& currentMin, int& currentHour) {                                                         //Function to add 1 second to the current time.
	if (currentSec == 59) {
		currentSec = 0;
		addMinute(currentMin, currentHour);                                                                                  //Using addMinute() in case second is at the top of the minute.
	}
	else {
		currentSec += 1;
	}
}




int main() {

	time_t now = time(0);                                                                                                   
	tm* ltm = localtime(&now);                                                                                              //Statements used to get time from the system.


	int currentHour = ltm->tm_hour;                                                                                         
	int currentMin = ltm->tm_min;
	int currentSec = ltm->tm_sec;                                                                                           //Statements to get each element from the time and assign it to each corresponding variable.
																															//It is used outside while loop in order to manipulate the time as requested by the user.


	while (1) {                                                                                                             //Loop to keep the program running.

		displayTime(twelveHour(currentHour), currentHour, currentMin, currentSec, am_pm(currentHour));                      //Using function displayTime() and assigning each argument
		Sleep(960);																											//Used to call displayTime() every a certain time.
		system("CLS");																										//Clearing screen.
		addSecond(currentSec, currentMin, currentHour);																		//Adding second to simulate the pass of time while still being able to manipulate it.

		if (_kbhit()) {																										//Stopping loop if a keyboard hit is register.
			
			displayMenu();																									//Displaying menu.
			
			int command;
			cin >> command;																									//Getting input from user, which has a function as assigned by switch statement.

			switch (command) {
			case 1:
				addHour(currentHour);
				break;
			case 2:
				addMinute(currentMin, currentHour);
				break;
			case 3:
				addSecond(currentSec, currentMin, currentHour);
				break;
			case 4:
				cout << "Goodbye";
				exit(1);
				break;
			default:
				cout << "Invalid choice!" << endl;
				break;
			}
			continue;																										//Resuming loop.
		}
		
	}

}