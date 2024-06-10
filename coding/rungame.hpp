#ifndef RUNGAME_HPP
#define RUNGAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include "board1.hpp"
#include "board2.hpp"
#include "boat1.hpp"
#include "boat2.hpp"

class Battleship
{
private:
    sf::Music gameFinish;
    sf::Music inGameMusic;
    sf::Sprite Winner1;
    sf::Texture Winner1Tex;
    sf::Sprite Winner2;
    sf::Texture Winner2Tex;
    sf::Font font;
    sf::Text text;
    sf::Text text1;
    sf::Text missedText1;
    sf::Text missedText2;
    sf::Sprite background;
    sf::Texture backTex;
    Board1 board1;
    Board2 board2;
    int filled1, filled2;
    sf::Sprite cloud1;
    sf::Texture cloudTex1;
    sf::Sprite cloud2;
    sf::Texture cloudTex2;
public:
    void loop(sf::RenderWindow& window);
    void init();

};

#endif