#include "deck.h"
#include "card.h"
#include <iostream> // std:: cout
#include <cstdlib> // std::rand, std::srand
#include <algorithm> // std::for_each
#include <random>
#define DECK_SIZE 108

using namespace std;

deck::deck()
{
    ptr_deck = new card[DECK_SIZE];
    size = 0;
    for (int i = 0; i <= 14; i++) {
        card_counts[i] = 0;
    }

}

void deck::copy(const deck& other)
{
    size = other.size;
    ptr_deck = new card[size];
    for (int i = 0; i < size; i++)
    {
        ptr_deck[i] = other.ptr_deck[i];
    }
}

const deck& deck::operator= (const deck& other)
{
    if (this != &other)
    {
        clear();
        copy(other);
    }
    return *this;
}

void deck::create()
{
    int num = 0;


    // card rank 0
    for (int col = 1; col <= 4; col++)
    {
        ptr_deck[size].number = num;
        ptr_deck[size].color = static_cast<COLOR>(col);
        size++;
    }

    // card rank 1 till 9 , "draw-two", "skip", "reverse"
    for (num = 1; num <= 12; num++)
    {
        for (int x = 0; x < 2; x++)
        {
            for (int col = 1; col <= 4; col++)
            {
                ptr_deck[size].number = num;
                ptr_deck[size].color = static_cast<COLOR>(col);
                size++;
            }
        }

    }

    // card "wild", "wild-draw-four"
    for (num = 13; num <= 14; num++)
    {
        for (int x = 0; x < 4; x++)
        {
            ptr_deck[size].number = num;
            ptr_deck[size].color = wild;
            size++;
        }
    }


}

deck::deck(const deck& other)
{
    copy(other);
}


card deck::maximum()
{
    if (size == 0)
    {
        // If the deck is empty, return a default-constructed card.
        return card();
    }


    return *std::max_element(ptr_deck, ptr_deck + size, [](const card& c1, const card& c2) {
        if (c1.number != c2.number)
            return c1.number < c2.number;
        else
            return c1.color < c2.color;
        });
}

card deck::minimum()
{
    if (size == 0)
    {
        return card();
    }


    return *min_element(ptr_deck, ptr_deck + size, [](const card& c1, const card& c2) {
        if (c1.number != c2.number)
            return c1.number < c2.number;
        else
            return c1.color < c2.color;
        });
}


deck::~deck()
{
    clear();
}




void deck::shuffle()
{
    // Create a random number generator.
    random_device rd;
    mt19937 gen(rd());

    // Shuffle the cards in the deck.
    for (int i = 0; i < size; i++) {
        // Generate a random index between 0 and i.
        int random_index = gen() % (i + 1);

        // Swap the cards at the current index and the random index.
        //Use of swap for Mutating algorithm
        swap(ptr_deck[i], ptr_deck[random_index]);
    }
}

card deck::draw()
{
    if (size <= 0)
    {

        return card();
    }
    card temp_card = ptr_deck[size - 1];
    size--;
    return temp_card;
}


int deck::add_card(card temp_card)
{
    if (size < DECK_SIZE)
    {
        ptr_deck[size] = temp_card;
        size++;
        return 0;
    }
    else
        return -1;
}
int deck::add_count(card temp_card)
{
    if (size < DECK_SIZE)
    {
        ptr_deck[size] = temp_card;
        size++;
        card_counts[temp_card.number]++;
        return 0;
    }
    else
        return -1;
}

int deck::cout_draw()
{
    card temp_card = ptr_deck[size - 1];
    size--;
    card_counts[temp_card.number]--;
    return temp_card.number;

}

void deck::quick_shuffle()
{

    int pos;
    int temp_size = size - 1;
    card temp_card;
    while (temp_size > 0)
    {
        srand(time(NULL));
        pos = rand() % temp_size;
        // swap elements
        temp_card = ptr_deck[temp_size];
        ptr_deck[temp_size] = ptr_deck[pos];
        ptr_deck[pos] = temp_card;
        // reduce size by 1
        temp_size--;
    }

}



void deck::print_deck()
{
    for (int i = 0; i < size; i++)
    {
        cout << i << ": " << ptr_deck[i] << " count: " << card_counts[ptr_deck[i].number] << endl;
    }
}

void deck::clear()
{
    delete[]ptr_deck;
    ptr_deck = NULL;
    size = 0;
}


int deck::get_size()
{
    return size;
}

void deck::print_values()
{
    // Create a function object that prints the value of a card.
    struct print_value {
        void operator()(const card& c) const {
            cout << c.number << endl;
        }
    };

    // Iterate over the cards in the deck and call the print_value function on each card.\
    //Use of Non-Mutating Algorithm
    for_each(ptr_deck, ptr_deck + size, print_value());
}
