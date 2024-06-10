#include "boat1.hpp"

Boat1::Boat1():BOATCOUNT(4), HORIZONTAL(90), VERTICAL(180), MARGIN(50), boat1Texture(4)
{
	//fill
	filledTexture.loadFromFile("images/Boats.png");
	filledCase.setTexture(filledTexture);
	filledCase.setTextureRect(sf::IntRect(110,13.5,25,25));
	filledCase.setOrigin(-1,-6);

	//missed
	// PLAYED CASE
	playedTexture.loadFromFile("images/Boats.png");
	playedCase.setTexture(playedTexture);
	playedCase.setTextureRect(sf::IntRect(37,6,30,31));
	playedCase.setOrigin(-1,-2);

	//EXPLOSION
	explosionTexture.loadFromFile("images/Fire_Sprite.png");
	explosion.setTexture(explosionTexture);
	explosion.setTextureRect(sf::IntRect(0,0,32,32));

    origin.push_back(sf::Vector2f(6, 25));
    origin.push_back(sf::Vector2f(7, 40));
    origin.push_back(sf::Vector2f(7, 40));
    origin.push_back(sf::Vector2f(8, 71));
    //origin.push_back(sf::Vector2f(9, 101));

    position.x = 512;
    position.y = 200;

    canSelect = true;
    status = true;
}

void Boat1::initialize()
{
	boat1Texture[0].loadFromFile("images/ship1_1.png");
	boat1Texture[1].loadFromFile("images/ship2_1.png");
	boat1Texture[2].loadFromFile("images/ship3_1.png");
	boat1Texture[3].loadFromFile("images/ship4_1.png");
	
    for(int i = 0; i < BOATCOUNT; i++)
    {
        boat1.push_back(Boat1());
		boat1[i].sprite.setTexture(boat1Texture[i]);
		boat1[i].sprite.setPosition(position.x,position.y + i * MARGIN);
		boat1[i].sprite.setRotation(HORIZONTAL);
		boat1[i].sprite.setOrigin(origin[i]);
		boat1[i].state = "LOCKED";
		boat1[i].rotation = "HORIZONTAL";	
    }

}

void Boat1::setStatus(bool value)
{ // SET IF THE BOAT CAN MOVED OR NOT MOVED IF THE GAME STARTED
	status = value;
}

void Boat1::select(sf::RenderWindow& win,sf::Vector2i cursorPosition)
{
	
	for(int i = 0;i < boat1.size();i++) {
		if(boat1[i].sprite.getGlobalBounds().contains(cursorPosition.x,cursorPosition.y))
		{

			boat1[i].state = "UNLOCKED";
			// LEFT CLICK LOCK/UNLOCK BOAT
			if(boat1[i].state == "UNLOCKED" && canSelect && status) { 
				boat1[i].move(win);
			}
			canSelect = false;
				
		}
		else { boat1[i].state = "LOCKED"; canSelect = true; }

	}
}

void Boat1::rotate(sf::Vector2i cursorPosition,sf::Event &event)
{
	for(int i = 0;i < boat1.size();i++) {
		if(boat1[i].sprite.getGlobalBounds().contains(cursorPosition.x,cursorPosition.y) && 
				boat1[i].rotation == "HORIZONTAL")	
		{
			 boat1[i].sprite.setRotation(VERTICAL); boat1[i].rotation = "VERTICAL"; 
		}
		else if (boat1[i].sprite.getGlobalBounds().contains(cursorPosition.x,cursorPosition.y)) 
		{
	       		boat1[i].sprite.setRotation(HORIZONTAL); boat1[i].rotation = "HORIZONTAL";
		}
	}
}

void Boat1::move(sf::RenderWindow& win)
{	
		sprite.setPosition(sf::Mouse::getPosition(win).x,sf::Mouse::getPosition(win).y);
}


bool Boat1::checkPositionOnGrid(sf::FloatRect& gridSquare)
{
    for (int i = 0; i < boat1.size(); i++)
    {
        // Adjusted collision detection bounds
        sf::FloatRect collisionBounds = boat1[i].sprite.getGlobalBounds();

        // Check the rotation of the ship
        if (boat1[i].rotation == "HORIZONTAL")
        {
            // Adjust the collision bounds for horizontal ships
            collisionBounds.left += 16;
            collisionBounds.top += 16;
            collisionBounds.width -= 31;
            collisionBounds.height -= 31;
        }
        else
        {
            // Adjust the collision bounds for vertical ships
            collisionBounds.left += 16;
            collisionBounds.top += 16;
            collisionBounds.width -= 31;
            collisionBounds.height -= 31;
        }

        if (collisionBounds.intersects(gridSquare))
        {
            // Collision detected
            return true;
        }
    }

    return false;
}



const sf::FloatRect Boat1::getBoatPosition()
{
    for(int i = 0; i < boat1.size(); i++)
    {
        return boat1[i].sprite.getGlobalBounds();
    }
    return sprite.getGlobalBounds();
}

void Boat1::filled(sf::RenderWindow& window, const int& positionX, const int& positionY)
{
	filledCase.setPosition(positionX, positionY);
	//window.draw(filledCase);
}

void Boat1::missed(sf::RenderWindow& window, const int& positionX, const int& positionY)
{
	playedCase.setPosition(positionX, positionY);
	window.draw(playedCase);
}

void Boat1::destroyed(sf::RenderWindow& window,const int& positionX,const int& positionY )
{
	explosion.setPosition(positionX,positionY);
	window.draw(explosion);		
}


void Boat1::draw(sf::RenderWindow& window)
{
	
	for(int i = 0; i < boat1.size() ; i++)
	{
		window.draw(boat1[i].sprite);
	}
	
}


