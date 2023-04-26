#pragma once
#include <iostream>
#include <stack>
#include <string>
#include <random>
#include "displaycard.h"
class displayStack {
public:
    displayStack() {}
    ~displayStack() {}

    void displayRandomCards(int numCards) {
        std::cout << "Random UNO Cards:" << std::endl;

        std::string colors[] = { "Red", "Green", "Blue", "Yellow" };
        std::string actions[] = { "Skip", "Reverse", "Draw Two", "Wild", "Wild Draw Four" };

        // Create a random number generator
        std::random_device rd;
        std::mt19937 gen(rd());

        // Create a stack of randomly generated cards
        std::stack<displaycard> cardStack;
        for (int i = 0; i < numCards; i++) {
            int colorIndex = std::uniform_int_distribution<>(0, 3)(gen);
            int actionIndex = std::uniform_int_distribution<>(0, 4)(gen);
            int number = (actions[actionIndex] == "Number") ? std::uniform_int_distribution<>(1, 9)(gen) : 0;

            cardStack.push(displaycard(colors[colorIndex], actions[actionIndex], number));
        }

        while (!cardStack.empty()) {
            displaycard card = cardStack.top();
            cardStack.pop();

            std::cout << "- ";
            if (card.getColor() != "") {
                std::cout << card.getColor() << " ";
            }
            if (card.getNumber() != 0) {
                std::cout << card.getNumber() << " ";
            }
            if (card.getAction() != "") {
                std::cout << card.getAction() << " ";
            }
            std::cout << std::endl;
        }
    }

    void displaySortedStacks() {
            cout << "Random UNO Cards:" << endl;

            string colors[] = { "Red", "Green", "Blue", "Yellow" };
            string actions[] = { "Skip", "Reverse", "Draw Two", "Wild", "Wild Draw Four" };

            // Create a random number generator
            random_device rd;
            mt19937 gen(rd());
            const int  numCards = 7;
            // Create an array of randomly generated cards
            displaycard cardArray[numCards];
            for (int i = 0; i < numCards; i++) {
                int colorIndex = uniform_int_distribution<>(0, 3)(gen);
                int actionIndex = uniform_int_distribution<>(0, 4)(gen);
                int number = (actions[actionIndex] == "Number") ? uniform_int_distribution<>(1, 9)(gen) : 0;

                cardArray[i] = displaycard(colors[colorIndex], actions[actionIndex], number);
            }

            // Sort the cards in the array
            sort(cardArray, cardArray + numCards, [](const displaycard& a, const displaycard& b) {
                // Sort by color, then by action, then by number
                if (a.getColor() != b.getColor()) {
                    return a.getColor() < b.getColor();
                }
                if (a.getAction() != b.getAction()) {
                    return a.getAction() < b.getAction();
                }
                return a.getNumber() < b.getNumber();
                });

            // Print out the sorted cards from the array
            for (int i = 0; i < numCards; i++) {
                displaycard card = cardArray[i];

                cout << "- ";
                if (card.getColor() != "") {
                    cout << card.getColor() << " ";
                }
                if (card.getNumber() != 0) {
                    cout << card.getNumber() << " ";
                }
                if (card.getAction() != "") {
                    cout << card.getAction() << " ";
                }
                cout << endl;
            }
        }
};