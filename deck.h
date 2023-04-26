#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <map>
#include <list>
using namespace std;
class deck : public card {
public:
    deck();
    deck(const deck& other);
    const deck& operator= (const deck& other);
    ~deck();
    void shuffle();
    card draw();
    void create();
    int add_card(card temp_card);
    void quick_shuffle();
    void print_deck();
    int get_size();
    void print_values();
    void copy(const deck& other);
    void print_values_helper(pair<card, int> p);
    int add_count(card temp_card);
    int cout_draw();
    void display_setDeck();
private:
    card* ptr_deck;
    //use of map for Associaitve containers
    map<int, int> card_counts;
    //set<card> display_deck;
    int size;
    void clear();
    card maximum();
    card minimum();
};

#endif

