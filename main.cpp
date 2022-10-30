#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <time.h>
#include <cstdlib>
#include <vector>

#include "includes/game/game.h"
#include "includes/constants/windowConstants.h"
#include "includes/random/random.h"

using namespace std;



int main()
{
    int framerate = 60;

    sf::FloatRect visibleArea;
    //----------S E T U P ------------------------------:

    //declare a window object:
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
                            "Proportion Game"
                            );

    window.setFramerateLimit(framerate);

    sf::Clock clock;

    sf::Font font;
    font.loadFromFile(fontPath);

    int denum = random(2, 12), num = random(1, denum-1);

    float proportion = float(num)/denum;

    float answer;

    sf::RectangleShape volume(VOLUME_SIZE);
    volume.setFillColor(SECONDARY_COLOR);
    volume.move(400, 300);

    sf::RectangleShape answerBar(sf::Vector2f(VOLUME_SIZE.x, BAR_HEIGHT));
    answerBar.setFillColor(DETAIL_COLOR);
    answerBar.setPosition(volume.getPosition());
    answerBar.setOrigin(0, BAR_HEIGHT/2);
    answerBar.setPosition(volume.getPosition().x, volume.getPosition().y+volume.getSize().y*(1-proportion));

    sf::RectangleShape answerColor(sf::Vector2f(VOLUME_SIZE.x, 0));
    answerColor.setFillColor(FILL_COLOR);
    answerColor.setSize(sf::Vector2f(volume.getSize().x, volume.getPosition().y+volume.getSize().y-answerBar.getPosition().y));
    answerColor.setPosition(answerBar.getPosition());
    
    sf::RectangleShape guessBar(sf::Vector2f(VOLUME_SIZE.x, BAR_HEIGHT));
    guessBar.setFillColor(DETAIL_COLOR);
    guessBar.setOrigin(0, BAR_HEIGHT/2);
    guessBar.setPosition(volume.getPosition());

    string txt;

    sf::Vector2f newPos;

    // run the program as long as the window is open
    // this is your main loop:
    while (window.isOpen()){
        window.setFramerateLimit(framerate);
        sf::Time elapsed = clock.restart();
        if (debug) {
            fpsCounter.setString(to_string(1000000/elapsed.asMicroseconds()));
        }
        
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        

        //go through all the pending events: keyboard, mouse, close, resize, etc.
        //pollEvent and waitEvent are the only two functions that can fill event
        while (window.pollEvent(event))//or waitEvent: EVENT LOOP
        {
            // check the type of the event...
            switch (event.type)
            {
            // window closed
            // "close requested" event: we close the window
            case sf::Event::Closed:
                cout<<"close event was encountered!"<<endl;
                window.close();
                break;

            case sf::Event::MouseMoved:
                if (guessing) {
                    newPos.x = volume.getPosition().x;
                    newPos.y = event.mouseMove.y;
                    if (newPos.y < volume.getPosition().y) newPos.y = volume.getPosition().y;
                    else if (newPos.y > volume.getPosition().y + volume.getSize().y) newPos.y = volume.getPosition().y + volume.getSize().y; 
                    guessBar.setPosition(newPos);
                }
                break;
                // key pressed
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case 87: //F3
                        debug = !debug;
                    default:
                        break;
                }
                cout << "key " << event.key.code << " was pressed..."<<endl;
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) { // MOUSE 1 PRESSED
                }

                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left) { // MOUSE 1 RELEASED
                    std::cout << event.mouseButton.x << ", " << event.mouseButton.y << std::endl;
                    if (guessing) {
                        guessing = false;
                        answer = (volume.getPosition().y+volume.getSize().y-guessBar.getPosition().y)/volume.getSize().y;
                        answerText.setString("Your guess is: " + to_string(answer) + "\nThe answer is: " + to_string(proportion));
                    } else {
                        denum = random(2, 12), num = random(1, denum-1);
                        proportion = float(num)/denum;
                        setDebugText(debugText, num, denum, proportion);
                        setPromptText(promptText, num, denum);
                        answerBar.setPosition(volume.getPosition().x, volume.getPosition().y+volume.getSize().y*(1-proportion));
                        answerColor.setSize(sf::Vector2f(volume.getSize().x, volume.getPosition().y+volume.getSize().y-answerBar.getPosition().y));
                        answerColor.setPosition(answerBar.getPosition());
                        guessing = true;
                    }
                }
                break;
            case sf::Event::Resized:
                visibleArea = sf::FloatRect(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            case sf::Event::TextEntered:
                if (event.text.unicode<128&&event.text.unicode!=8&&entering) {
                    textBox.setString(txt+=static_cast<char>(event.text.unicode));
                }
                break;
            default:
                break;
            }
        }

        // you HAVE TO clear your window on every iteration of this while.
        window.clear(BACKGROUND_COLOR);
        window.draw(volume);
        if(entering) window.draw(textBox);
        if (!guessing||debug) {
            window.draw(answerText);
            window.draw(answerColor);
            //window.draw(answerBar);
        }
        window.draw(guessBar);
        if (guessing) {
            window.draw(promptText);
        }
        if (debug) {
            window.draw(fpsCounter);
            window.draw(debugText);
        }
        window.display();

    }

    cout<<"------ NORMAL TERMINATION: WINDOW CLOSED!"<<endl;
    return 0;
}