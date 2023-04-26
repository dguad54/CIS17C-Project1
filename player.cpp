#include "card.h"
#include "player.h"
#include <iostream>
using namespace std;


// Default constructor for the player class
player::player() : size(0)
{
}

// Copy constructor for the player class
player::player(const player& other)
{
	copy(other);
}

// Overloaded assignment operator for the player class
const player& player::operator= (const player& other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}

// Destructor for the player class
player::~player()
{
	clear();
}

// Add a card to the player's hand
void player::hand_add(card temp_card)
{
	hand.push_front(temp_card);
	size++;
}

card player::hand_remove(int pos)
{
	if (pos < 0 || pos >= size)
	{
		return card();
	}

	auto it = hand.begin();
	std::advance(it, pos);
	card temp_card = *it;
	hand.erase(it);
	size--;

	return temp_card;
}

void player::copy(const player& other)
{
	hand = other.hand;
	size = other.size;
}

void player::clear()
{
	hand.clear();
	size = 0;
}

// Print the cards in the player's hand
void player::print() const
{
	int i = 0;
	for (const auto& card : hand) {
		cout << i << ":  " << card << endl;
		i++;
	}
}



// Get the number of cards in the player's hand
int player::get_size() const
{
	return size;
}

// Get a copy of a card in the player's hand without removing it
card player::peek(int pos) const
{
	if (pos < 0 || pos >= size)
	{
		return card();
	}

	auto it = hand.begin();
	std::advance(it, pos);
	return *it;
}