#ifndef SCROLLBAR_HPP
#define SCROLLBAR_HPP

#include <SFML/Graphics.hpp>

class ScrollBar : public sf::Drawable {
public:
    ScrollBar(sf::Vector2f position, sf::Vector2f size, sf::RenderWindow &window);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void events();
    float getProcent();

private:
    sf::RectangleShape bar;
    mutable sf::CircleShape dot;
    bool hasFocus = false;
    sf::RenderWindow *window;
};

#endif //SCROLLBAR_HPP