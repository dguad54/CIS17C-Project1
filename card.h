#pragma once
#pragma once
#ifndef _CARD_H_
#define _CARD_H_
#include <set>
#include <ostream>
using namespace std;

enum COLOR { wild, red, green, blue, yellow };

class card
{
private:
public:
	int number; // 0-9 numbers, +2, skip, reverse, all color, +4 (all color) 
	COLOR color; // 5 colors: red, green, blue, yellow, and no color 

	bool operator==(card const& other) const;

	bool operator!=(card const& other) const;

	card();
	card(int num, COLOR col);

};


std::ostream& operator<<(std::ostream& out, card const& temp_card);


#endif // _CARD_H_
