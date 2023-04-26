#pragma once
#include <set>
#include <iostream>
#include"displaycard.h"
class displaySet {
public:
    displaySet() {}
    ~displaySet() {}

    void displayCardSet(std::set<displaycard> cardSet) {
        std::cout << "UNO Set:" << std::endl;
        for (auto const& card : cardSet) {
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
};
