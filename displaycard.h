#pragma once
#include <iostream>
#include <set>
#include <string>
class displaycard {
public:
    displaycard(std::string color, std::string action, int number = 0)
        : m_color(color), m_action(action), m_number(number) {}
    ~displaycard() {}

    std::string getColor() const { return m_color; }
    std::string getAction() const { return m_action; }
    int getNumber() const { return m_number; }

private:
    std::string m_color;
    std::string m_action;
    int m_number;
};