#include "card.h"
#include "deck.h"
#include "player.h"
#include <iostream>
#include <string> 
#include <cstdlib> 
#include <limits>
#include "displaySet.h"
#include "displaycard.h"
#include "displayStack.h"
using namespace std;

constexpr int PRINT_ALL_PLAYERS = 0;
constexpr int TEMP_DECK = 1;
constexpr int TURN = 2;
constexpr int TEST = -1;

void display_intro();
void card_display();
void confirm_turn(int);
COLOR FromString(const string&);


int main()
{

	system("clear");
	display_intro();
	card_display();
	//inputs amount of players
	int amount_players;
	int flag = 0;
	while (flag == 0)
	{
		cout << "Please enter amount of players: ";
		cin >> amount_players;
		if (amount_players >= 2 && amount_players <= 4)
		{
			cout << amount_players << " players entering game .... " << endl;
			flag = 1;
			break;
		}
		else
		{
			cout << "invalid amount of players" << endl;
		}
	}

	deck gameDeck;
	gameDeck.create();
	gameDeck.quick_shuffle();
	player* play_array;
	play_array = new player[amount_players];
	for (int i = 0; i < amount_players; i++)
	{
		for (int k = 0; k < 7; k++)
		{
			card temp_card;
			temp_card = gameDeck.draw();
			play_array[i].hand_add(temp_card);
		}
	}
	deck temp_deck;
	card played_card;
	card temp_card;
	int card_flag = 0;
	while (card_flag == 0)
	{
		temp_card = gameDeck.draw();
		if (temp_card.color != wild)
		{
			card_flag = 1;
			played_card = temp_card;
		}
		else
		{
			temp_deck.add_card(temp_card);
		}
	}


#if TEST == PRINT_ALL_PLAYERS
	/*print out testing */
	for (int i = 0; i < amount_players; i++)
	{
		cout << "player: " << i << endl;
		play_array[i].print();
	}
#endif

	srand(time(NULL));
	int turn = rand() % amount_players;
	cout << "PLAYER " << turn << " is randomly selected to play first" << endl;
	confirm_turn(turn);

	bool force_draw_bool = false;
	int turn_flag = 1;
	int win = 0;
	while (win == 0)
	{
		// clear screen
		system("clear");




		player* curr_player = &play_array[turn % amount_players];


		cout << "PLAYER " << turn % amount_players << endl;

		if (force_draw_bool)
		{
			// checked for Draw-2
			if (played_card.number == 10)
			{
				cout << "Forced Draw-2" << endl;
				card draw_2;
				for (int i = 0; i < 2; i++)
				{
					draw_2 = gameDeck.draw();
					curr_player->hand_add(draw_2);
				}
			}

			// check for Draw-4 
			if (played_card.number == 14)
			{
				cout << "Forced Draw-4" << endl;
				card draw_4;
				for (int i = 0; i < 4; i++)
				{
					draw_4 = gameDeck.draw();
					curr_player->hand_add(draw_4);
				}

			}
			force_draw_bool = false;
		}


		// print out the cards remaining for each player
		cout << "Cards remaining for each player: " << endl;
		for (int i = 0; i < amount_players; i++)
		{
			cout << "PLAYER " << i << ": " << play_array[i].get_size() << "   ";
		}
		cout << endl;
		// print out the temporary card 
		cout << "Played Card: " << played_card << endl;
		// print out cards in player's hand
		cout << "PLAYER " << turn % amount_players << endl;

		curr_player->print();
		int check_flag = 0;
		int index;
		int size = curr_player->get_size();
		// ask for which card to play into middle
		while (check_flag == 0)
		{
			cout << "which card do you want to play? " << endl;
			cout << "If you want to draw a card please enter '-1' " << endl;


			return 0;
			cout << "Type the index of the card and press enter: ";
			cin >> index;
			//check if index is to draw a card
			if (index == -1)
			{
				card draw_temp;
				draw_temp = gameDeck.draw();
				cout << "DRAWN CARD: " << draw_temp << endl;
				if (draw_temp == played_card && draw_temp.color != wild)
				{

					int play_draw_flag = 0;
					while (play_draw_flag == 0)
					{

						string temp_play;
						cout << "Do you want to play the drawn card [y/n] : ";
						cin >> temp_play;
						if (temp_play == "y")
						{
							played_card = draw_temp;
							temp_deck.add_card(draw_temp);
							if (played_card.number >= 10 && played_card.number <= 14)
							{
								force_draw_bool = true;
							}
							play_draw_flag = 1;
						}
						if (temp_play == "n")
						{
							curr_player->hand_add(draw_temp);
							play_draw_flag = 1;
						}


					}

				}
				else
				{
					curr_player->hand_add(draw_temp);
				}
				check_flag = 1;

			}
			//check if index is valid
			if (index >= 0 && index < size)
			{
				// check if card is compatilbe with played card
				card temp = curr_player->peek(index);
				if (temp == played_card)
				{
					//remove from player's hand
					curr_player->hand_remove(index);
					// add to the discarded pile
					temp_deck.add_card(temp);
					// change the played card
					played_card = temp;
					// check if card is a wild card 
					if (played_card.color == wild)
					{
						int check_color = 0;
						COLOR temp_color;
						string str_color;
						while (check_color == 0)
						{
							// ask for new color
							cout << "Please choose a color (red , green, blue, yellow) :";
							cin >> str_color;
							// change string to enum type COLOR
							temp_color = FromString(str_color);
							// check if valid color
							if (temp_color != wild)
							{
								played_card.color = temp_color;
								check_color = 1;
							}
							else
							{
								cout << "invalid color" << endl;
							}

						}
					}
					if (played_card.number >= 10 && played_card.number <= 14)
					{
						force_draw_bool = true;
					}
					check_flag = 1;
				}
				else
				{
					cout << "card cannot be played " << endl;
				}
			}
			else
			{
				cout << "invalid index " << endl;
			}
		}

		// check if there is a winner, and break while loop 
		if (curr_player->get_size() == 0)
		{
			win = 1;
			cout << "PLAYER " << turn % amount_players << " has won the game." << endl;
			break;
		}


		if (played_card.number == 11 && force_draw_bool == true)
		{
			if (turn_flag == 1)
				turn = turn + 2;
			else
				turn = turn - 2;
		}
		// reverse case 
		else if (played_card.number == 12 && force_draw_bool == true)
		{

			if (amount_players == 2)
			{
				turn = turn + 2;
			}
			else
			{
				// changes the rotation
				if (turn_flag == 1)
				{
					turn_flag = -1;
					turn--;
				}
				else
				{
					turn_flag = 1;
					turn++;
				}

			}
		}

		else
		{
			//Clockwise or CounterClockwise
			if (turn_flag == 1)
				turn++;
			else
				turn--;
		}


		system("clear");
		// print out the cards remaining for each player
		cout << "Cards remaining for each player: " << endl;
		for (int i = 0; i < amount_players; i++)
		{
			cout << "PLAYER " << i << ": " << play_array[i].get_size() << "   ";
		}
		cout << endl;

		// print out the temporary card 
		cout << "Played Card: " << played_card << endl;
		confirm_turn(turn % amount_players);


	}



	return 0;
}

void display_intro() {
	// Welcome the user to UNO.
	cout << "Welcome to UNO! Select any information you may need:" << endl;

	// Get the user's input.
	int user_choice;
	cout << "1. View Rules" << endl;
	cout << "2. General Advice" << endl;
	cout << "3. Exit Intro Menu" << endl;
	cin >> user_choice;

	// Check for invalid input.
	if (user_choice < 1 || user_choice > 3) {
		cout << "Invalid input. Please enter a valid number." << endl;
		return;
	}

	// Display the appropriate information.
	switch (user_choice) {
	case 1:
		cout << "Here are the rules of UNO:" << endl;
		cout << "- The goal of UNO is to be the first player to get rid of all of your cards." << endl;
		cout << "- You can play a card if it matches the color or number of the top card of the discard pile." << endl;
		cout << "- If you don't have a playable card, you must draw a card from the draw pile." << endl;
		cout << "- If you draw a Wild card, you can choose any color to play it as." << endl;
		cout << "- If you draw a Draw Four card, you must draw four cards from the draw pile and your turn is skipped." << endl;
		break;
	case 2:
		cout << "Here are some general tips for playing UNO:" << endl;
		cout << "- Try to keep track of the cards that have been played." << endl;
		cout << "- If you have a Wild card, save it for when you need it." << endl;
		cout << "- If you have a Draw Four card, don't be afraid to use it." << endl;

		break;
	case 3:
		cout << "Have fun!" << endl;
		break;
	}
}

void card_display()
{
	int input;
	cout << "Get familiar with UNO cards and Decks" << endl;
	cout << "Choose how you want to you would wish to see the deck" << endl;
	cout << "1. Display a stacked set of cards: " << endl;
	cout << "2. Display a sorted deck: " << endl;
	cout << "3. Display a example set of cards: " << endl;
	cout << "4. Exit deck display menu" << endl;
	cin >> input;
	switch (input)
	{
	case 1:
	{
		displayStack stack;
		stack.displayRandomCards(7);
	}

	break;
	case 2:
	{
		displayStack stack;
		stack.displaySortedStacks();
	}
		break;

	case 3:
	{
		std::set<displaycard> unoSet{
		displaycard("Red", "Number", 1),
		displaycard("Red", "Number", 2),
		displaycard("Red", "Skip"),
		displaycard("Green", "Reverse"),
		displaycard("Blue", "Draw Two"),
		displaycard("", "Wild"),
		displaycard("", "Wild Draw Four")
		};
		displaySet mySet;
		mySet.displayCardSet(unoSet);
		break;
	
	}
	case 4:
	{
		cout << "Exiting deck display menu." << endl;
		break;
	}
	default:
	{
		cout << "Invalid input. Please enter a number between 1 and 4." << endl;
		break;
	}
  }
}


	void confirm_turn(int x)
	{
		cout << "Confirm Player " << x << " by typing " << "'" << x << "'" << " and pressing enter" << ": ";
		int temp = 0;
		while (temp != x) {
			cin >> temp;
		}
	}

	COLOR FromString(const string & str) {
		if (str == "red") return red;
		if (str == "green") return green;
		if (str == "blue") return blue;
		if (str == "yellow") return yellow;
		return wild;
	}
	
