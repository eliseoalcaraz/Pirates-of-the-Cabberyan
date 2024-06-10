#ifndef BOAT2_HPP
#define BOAT2_HPP

#include <SFML\Graphics.hpp>
#include <vector>
#include "board2.hpp"

class Boat2
{
    private:
    //display
        sf::Sprite sprite;
        sf::Vector2f position;
        std::vector<sf::Texture> boat2Texture;
        std::vector<Boat2> boat2;
        std::vector<sf::Vector2f> origin;
        std::string rotation;
        const int BOATCOUNT;
        const int VERTICAL;
        const int HORIZONTAL;
        const int MARGIN;
    //c
    //realdeal
        std::string state;
        bool canSelect;
        bool status;

    //set
        sf::Sprite filledCase;
        sf::Texture filledTexture;

    //missed
        sf::Sprite playedCase;
        sf::Texture playedTexture;

    //destroyed
        sf::Sprite explosion;
        sf::Texture explosionTexture;

        sf::Sprite ship1;
        sf::Texture ship1Tex;


    public:
    //display
        Boat2();
        void initialize();
        void draw(sf::RenderWindow&);
    //
    //real, movement of the boat
    	void select(sf::RenderWindow&,sf::Vector2i);					
		void rotate(sf::Vector2i,sf::Event&);			
		void move(sf::RenderWindow&);
        void setStatus(bool);
    
    //set
        const sf::FloatRect getBoatPosition();
        void filled(sf::RenderWindow&, const int&, const int&);
        bool checkPositionOnGrid(sf::FloatRect& );
    
    //missed
        void missed(sf::RenderWindow& window, const int&,const int&);    
        void destroyed(sf::RenderWindow&,const int&, const int&);	
    
};





#endif