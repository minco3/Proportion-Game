#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class game {

    void setDebugText(int num, int denum, float proportion) {
    debugText.setString("Target = " + to_string(num) + "/" + to_string(denum) + "\nProportion = " + to_string(proportion));
    }
    void setPromptText(int num, int denum) {
    promptText.setString("Try to guess where " + to_string(num) + "/" + to_string(denum) + " would be on this rectangle");
    }

    sf::Text fpsCounter;
    sf::Text debugText;
    sf::Text promptText;
    sf::Text answerText;

    sf::Font font;

    bool _debug;
    bool guessing = true;

    game::game(sf::Font& font, bool& debug);
    
    void draw(sf::RenderWindow& window);
};

#endif //GAME_H