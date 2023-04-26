#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "card.h"
#include <list>
using namespace std;
class player
{
public:
	player();
	player(const player& other);
	const player& operator= (const player& other);
	~player();
	void hand_add(card temp);
	card hand_remove(int pos);
	void uno();
	void print() const;
	int get_size() const;
	card peek(int pos) const;
private:
	//use of list as sequence requirment
	list<card> hand;
	int size;
	void copy(const player& other);
	void clear();


};

#endif 

