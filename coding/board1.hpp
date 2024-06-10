#ifndef BOARD1_HPP
#define BOARD1_HPP

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>
#include <array>
#include "boat1.hpp"

class Boat1;

class Board1
{
    private: 
    //for displaying, the sensor, the squares
        const int TILESIZE;
        const int GRID_SIZE;
        sf::FloatRect grid;
        const int PLAYER1GRID_X;
        const int PLAYER1GRID_Y;
        const int PLAYER1GRID_OFFSET_X;
        const int PLAYER1GRID_OFFSET_Y;
        int squarePositionX;
        int squarePositionY;
        std::vector<sf::FloatRect> gridSquare;
        const int EMPTY;
        sf::Texture gridTexture;
        sf::Sprite player1Grid;
        int ships1;
    //
    //started integrating the boat
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
    //missed
        const int PLAYED;
    
    //playing
        bool isPressed;
        bool touched;
        int play2_x;
        int play2_y;


    //sound
        sf::Music attack;
        sf::Music attackMissed;
    public:
        Board1();
        void init();
        void setPlayer1Grid();
        void addSensorsToGrid();
        void addBoxtoSquare(sf::RenderWindow&);
        void draw(sf::RenderWindow&);

    //started integrating the boat
        void updateEvent(sf::RenderWindow&, sf::Event&,Boat1& boat1);	 

    //set
        void detectBoat1OnGrid(Boat1&);
        void setBoat1OnGrid(int&, const int&);
        void readPlayer1GridInfo(sf::RenderWindow&,Boat1&);

    //playing
        int player2AttackEvent(sf::RenderWindow&, bool &hasAttacked);
        //bool hitBoat1(int&, const int&);
        std::array<std::array<int,10>,10> player1GridArray;

        int getAttackedSquare(sf::RenderWindow& win);
};

#endif