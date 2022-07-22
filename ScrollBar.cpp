#include "ScrollBar.hpp"
#include <cmath>

ScrollBar::ScrollBar(sf::Vector2f position, sf::Vector2f size, sf::RenderWindow &window) {
    bar.setPosition(position);
    bar.setSize(size);
    bar.setFillColor(sf::Color(50, 50, 50));
    bar.setOutlineThickness(1);
    bar.setOutlineColor(sf::Color::White);

    dot.setRadius(20);
    dot.setPosition(bar.getPosition().x - dot.getRadius(), bar.getPosition().y - dot.getRadius() + bar.getSize().y / 2);
    this->window = &window;
}
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void ScrollBar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if(hasFocus && (sf::Mouse::getPosition().x - window->getPosition().x) > bar.getPosition().x &&
            (sf::Mouse::getPosition().x - window->getPosition().x) < bar.getPosition().x + bar.getSize().x)
        dot.setPosition(sf::Mouse::getPosition().x - window->getPosition().x - dot.getRadius(), dot.getPosition().y);
    target.draw(bar);
    target.draw(dot);
}

#pragma GCC diagnostic pop

void ScrollBar::events() {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
            (bar.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition() - window->getPosition())) ||
             dot.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition() - window->getPosition())))) {
        hasFocus = true;
    }
    if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        hasFocus = false;
    }
}

float ScrollBar::getProcent() {
    return std::round(((dot.getPosition().x - bar.getPosition().x + dot.getRadius()) / bar.getSize().x) * 100) / 100.f;
}