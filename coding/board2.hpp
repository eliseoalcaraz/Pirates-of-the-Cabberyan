#ifndef BOARD2_HPP
#define BOARD2_HPP

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <sstream>
#include <vector>
#include <array>
#include "boat2.hpp"

class Boat2;

class Board2
{
    private: 
    //for displaying, the sensor, the squares
        const int TILESIZE;
        const int GRID_SIZE;
        sf::FloatRect grid;
        const int PLAYER2GRID_X;
        const int PLAYER2GRID_Y;
        const int PLAYER2GRID_OFFSET_X;
        const int PLAYER2GRID_OFFSET_Y;
        int squarePositionX;
        int squarePositionY;
        sf::Font font;
        sf::Text text;
        std::vector<sf::FloatRect> gridSquare;

        const int EMPTY;
        sf::Texture gridTexture;
        sf::Sprite player2Grid;
    //
        sf::Clock clock;
        const int GAMESPEED;
    
    //fill
        const int FILLED;
        int positionX;
        int positionY;
    //set
        int x, y;
    
    //destroy
        const int DESTROYED;

     //playing
        bool isPressed;
        bool touched;
        int play1_x;
        int play1_y;
        const int PLAYED;

        int ships2;
        
        sf::Music attack;
        sf::Music attackMissed;

    public:
        Board2();
        void init();
        void setPlayer2Grid();
        void addSensorsToGrid();
        void addBoxtoSquare(sf::RenderWindow&);
        void draw(sf::RenderWindow&);

    //
        void updateEvent(sf::RenderWindow&, sf::Event&,Boat2& boat2);

    //set
        void detectBoat2OnGrid(Boat2&);
        void setBoat2OnGrid(int&, const int&);
        void readPlayer2GridInfo(sf::RenderWindow&,Boat2&);

    //playing
         int player1AttackEvent(sf::RenderWindow&, bool& hasAttacked); 
         std::array<std::array<int,10>,10> player2GridArray;
         int getAttackedSquare(sf::RenderWindow& win);
    
};

#endif