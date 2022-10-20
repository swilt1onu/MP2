/*
*File: MP2
*Name: Selby Wilt
*Date: 10/14/22
*
*Purpose: A program that allows the user to play the game of pig against the
* computer. The rules of the game are as follows: "The game of Pig is a simple two player dice game in which
* the first player to reach 100 or more points wins. Players take turns. On each turn, a player rolls a pair of
* six-sided dice. After each roll, the individual die values are examined:
*
*If neither die shows a 1, the sum of the dice is added to the current turn total. The player can now elect to roll
* gain or to stop. If the player chooses to stop, then the sum of all of the rolls for the current turn (i.e., the
* current turn total) is added to the player’s game total. If the player rolls again, the both the current turn and
* game totals are at risk of being lost.
*
*If a single 1 is rolled, the player’s score for the current turn is lost (i.e., the current turn total is set to zero)
* and the turn ends.
*
*If two 1’s are rolled, the player’s total score for the entire game is lost (i.e., the game total is set back to zero)
* and the turn ends
*
* If a player reaches 100 or more points after stopping then that player wins.
*/

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <time.h>
#include <string>
using namespace std;

//function prototypes
int rollDie(void);
bool isTurnScoreLost(int die1value, int die2value);
bool isTotalScoreLost(int die1value, int die2value);
char getUserInput(void);
bool isWinningScore(int userTotalScore, int cpuTotalScore);


//main function
int main() {
	int cpuTotalScore = 0;      //computer players running total score
	int userTotalScore = 0;     //user player's running total score
	int userCurrentTurn = 0;    //the users turn number, should be reset to 0 after the set of turns is over
	int cpuCurrentTurn = 0;     //the computers value of their current turn, should be reset to 0 after the set of turns is over
	int die1value = 0;          //value of the first die rolled
	int die2value = 0;          //value of the second die rolled
	char input;                 // user input of s/S/r/R
	srand(time(0));

	while (isWinningScore(userTotalScore, cpuTotalScore) == false) {

		//displays the current score of the game on every turn
		cout << "The current score is - Player: " << userTotalScore << " - Computer: " << cpuTotalScore << endl;
		//prints a line to make distinguishing the turns easier to see
		cout << "---------------------------------------------------------------------" << endl;
		cout << "Users Turn" << endl;

		bool turnDone = false; //boolean value to check if the user wants to roll or stop


		//while loop for the user's turn, it is made false by having the input be s or S or not losing the turn or total
		while (turnDone == false) {

			die1value = 0;
			die2value = 0;

			//getting input from the user in order to decide if the turn will stop or roll
			input = getUserInput();

			if (input == 'r' || input == 'R') {

				//rolls the first die for the user
				die1value = rollDie();

				//rolls the second die for the user
				die2value = rollDie();

				//displays to the user the value of their dice roll
				cout << "Die 1: " << die1value << " Die 2: " << die2value << " " << endl;

				if (isTotalScoreLost(die1value, die2value)) {
					userTotalScore = 0;
					userCurrentTurn = 0;
					turnDone = true;
					cout << endl << "You rolled two 1's, total score is lost!" << endl;
				}
				else if (isTurnScoreLost(die1value, die2value)) {
					userCurrentTurn = 0;
					turnDone = true;
					cout << endl << "you rolled a 1, turn lost!" << endl;
				}
				else {
					userCurrentTurn = die1value + die2value + userCurrentTurn;
					cout << "Turn Total is: " << userCurrentTurn << endl;
				}
			}

			else {
				//computes the users total score by keeping a running total (userTotalScore) adding (userCurrentTurn) each time
				userTotalScore += userCurrentTurn;

				//displays the current score of the game on every turn
				cout << "The current score is - Player: " << userTotalScore << " - Computer: " << cpuTotalScore << endl;

				//changes the boolean value of turn done to true so the loop won't run again
				turnDone = true;

				//resets the current turn to 0 after it is done and computed
				userCurrentTurn = 0;
			}

		}

		//prints a line to make distinguishing the turns easier to see
		cout << "---------------------------------------------------------------------" << endl;


		//while loop for the computers turn / special rules apply (stated in header)
		while (cpuCurrentTurn < 20 && isWinningScore(userTotalScore, cpuTotalScore) == false) {

			cout << "Computer Roll" << endl;

			//rolls the first die for the computer
			die1value = rollDie();

			//rolls the second die for the computer
			die2value = rollDie();

			//displays to the user the value of the computers dice roll
			cout << "Computer Die 1: " << die1value << " Computer Die 2: " << die2value << " " << endl;


			if (isTotalScoreLost(die1value, die2value)) {
				cpuTotalScore = 0;
				cpuCurrentTurn = 0;
				cout << "The computer rolled two 1's, total score is lost!" << endl;
				break;
			}

			else if (isTurnScoreLost(die1value, die2value)) {
				cpuCurrentTurn = 0;
				cout << endl << "The computer rolled a 1, current turn is lost!" << endl;
				break;
			}

			else if (isWinningScore(userTotalScore, cpuTotalScore) == true) {
				cout << endl << "The computer has won!";
				return 0;
			}

			else {
				//adds the sum of each die value to find the computers current turn
				cpuCurrentTurn = die1value + die2value + cpuCurrentTurn;
			}

			if (cpuCurrentTurn >= 20) {
				cout << endl << "The computer reached a turn score greater than 20! Turn is over" << endl;
			}
		}

		//computers the computers total score by keeping a running total (cpuTotalScore) adding (cpuCurrentTurn) each time
		cpuTotalScore += cpuCurrentTurn;

		//resets the current turn to 0 after it is done and computed
		cpuCurrentTurn = 0;
	}

	if (cpuTotalScore >= 100) {
		cout << endl << "The computer has won!";
	}

	if (userTotalScore >= 100) {
		cout << endl << "You have won!";
	}
}


//function used for rolling the pair of dice
int rollDie(void) {
	int dieRollValue = 0;
	dieRollValue = (rand() % 6) + 1;
	return dieRollValue;
}

// boolean function that checks if either dice rolled is 1, if so the turn is lost
bool isTurnScoreLost(int die1value, int die2value) {
	if (die1value == 1 || die2value == 1) {
		return true;
	}
	else {
		return false;
	}
}

//boolean function that checks if both dice rolled are 1, if so total score is reset to 0
bool isTotalScoreLost(int die1value, int die2value) {
	if (die1value == 1 && die2value == 1) {
		return true;
	}
	else {
		return false;
	}
}

//prompting the user and getting the input to stop or roll using "s"/"S" and "r"/"R." If the user input fails
//because they entered something other than s/S or r/R it will repeat the prompt
char getUserInput(void) {

	//stores the character (s/S or r/R) that the user decided
	char userSelection;

	//prompts the user to input either r or s to stop or keep going
	cout << endl << "enter 's' / 'S' to stop, or enter 'r' / 'R' to roll the dice. ";
	cin >> userSelection;

	while (userSelection != 's' && userSelection != 'S' && userSelection != 'r' && userSelection != 'R') {
		cout << endl << "unrecognized input, please enter enter 's' / 'S' to stop, or enter 'r' / 'R' to roll the dice. ";
		cin >> userSelection;

	}
	return userSelection;
}

//boolean function that checks if the winning score of 100 is met by the computer or player
bool isWinningScore(int userTotalScore, int cpuTotalScore) {
	if (cpuTotalScore >= 100 || userTotalScore >= 100) {
		return true;
	}
	else {
		return false;
	}
}