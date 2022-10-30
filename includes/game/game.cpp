#include "game.h"

game::game(sf::Font& font, bool& debug) {
    
    fpsCounter.setFont(font);
    promptText.setFont(font);
    answerText.setFont(font);
    debugText.setFont(font);
    promptText.move(100, 50);
    answerText.move(100, 100);
    debugText.move(0,120);

    _debug = debug;

}