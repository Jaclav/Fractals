


#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>

#include "ScrollBar.hpp"

typedef unsigned int uint;

int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Fractals", sf::Style::Fullscreen);
    sf::Event event;

    std::vector<sf::Vector3f> squares;
    squares.push_back(sf::Vector3f(333, 333, 333));
    std::vector<sf::Vector3f> sqrsTmp;

    sf::RectangleShape rs;
    ScrollBar maxSquares(sf::Vector2f(1100, 400), sf::Vector2f(200, 30), window);
    float maxSquaresOld = maxSquares.getProcent();

    while(window.isOpen()) {
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }
        maxSquares.events();
        if(maxSquares.getProcent() != maxSquaresOld) {
            sqrsTmp.clear();
            squares.clear();
            squares.push_back(sf::Vector3f(333, 333, 333));
            maxSquaresOld = maxSquares.getProcent();
        }

        window.clear();
        rs.setPosition(0, 0);
        rs.setSize(sf::Vector2f(1000, 1000));
        rs.setFillColor(sf::Color(100, 100, 100));
        window.draw(rs);
        rs.setFillColor(sf::Color::White);

        for(uint i = 0; i < squares.size(); i++) {
            rs.setSize(sf::Vector2f(squares[i].z, squares[i].z));
            rs.setPosition(squares[i].x, squares[i].y);
            window.draw(rs);

            //upper
            sqrsTmp.push_back(sf::Vector3f(squares[i].x - squares[i].z * 2.f / 3.f, squares[i].y - squares[i].z * 2.f / 3.f, squares[i].z / 3.f));
            sqrsTmp.push_back(sf::Vector3f(squares[i].x + squares[i].z * 1.f / 3.f, squares[i].y - squares[i].z * 2.f / 3.f, squares[i].z / 3.f));
            sqrsTmp.push_back(sf::Vector3f(squares[i].x + squares[i].z * 4.f / 3.f, squares[i].y - squares[i].z * 2.f / 3.f, squares[i].z / 3.f));

            //middle

            sqrsTmp.push_back(sf::Vector3f(squares[i].x - squares[i].z * 2.f / 3.f, squares[i].y + squares[i].z * 1.f / 3.f, squares[i].z / 3.f));
            sqrsTmp.push_back(sf::Vector3f(squares[i].x + squares[i].z * 1.f / 3.f, squares[i].y + squares[i].z * 1.f / 3.f, squares[i].z / 3.f));
            sqrsTmp.push_back(sf::Vector3f(squares[i].x + squares[i].z * 4.f / 3.f, squares[i].y + squares[i].z * 1.f / 3.f, squares[i].z / 3.f));

            //bottom
            sqrsTmp.push_back(sf::Vector3f(squares[i].x - squares[i].z * 2.f / 3.f, squares[i].y + squares[i].z * 4.f / 3.f, squares[i].z / 3.f));
            sqrsTmp.push_back(sf::Vector3f(squares[i].x + squares[i].z * 1.f / 3.f, squares[i].y + squares[i].z * 4.f / 3.f, squares[i].z / 3.f));
            sqrsTmp.push_back(sf::Vector3f(squares[i].x + squares[i].z * 4.f / 3.f, squares[i].y + squares[i].z * 4.f / 3.f, squares[i].z / 3.f));
        }

        while(!sqrsTmp.empty() && squares.size() < std::pow(10, 6 * maxSquares.getProcent())) {
            squares.push_back(sqrsTmp.back());
            sqrsTmp.pop_back();
        }
        sqrsTmp.clear();

        window.draw(maxSquares);

        window.display();
    }
}