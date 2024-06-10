#include "boat2.hpp"

Boat2::Boat2():BOATCOUNT(4), HORIZONTAL(90), VERTICAL(180), MARGIN(50), boat2Texture(4)
{
	filledTexture.loadFromFile("images/Boats.png");
	filledCase.setTexture(filledTexture);
	filledCase.setTextureRect(sf::IntRect(110,13.5,25,25));
	filledCase.setOrigin(-1,-6);

	// ship1Tex.loadFromFile("images/ship1.png");
	// ship1.setTexture(ship1Tex);

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

    origin.push_back(sf::Vector2f(6,25));
    origin.push_back(sf::Vector2f(7, 40));
    origin.push_back(sf::Vector2f(7, 40));
    origin.push_back(sf::Vector2f(8, 71));
    //origin.push_back(sf::Vector2f(9, 101));

    position.x = 512;
    position.y = 200;

    canSelect = true;
    status = true;
}

void Boat2::initialize()
{
   	boat2Texture[0].loadFromFile("images/ship1_2.png");
	boat2Texture[1].loadFromFile("images/ship2_2.png");
	boat2Texture[2].loadFromFile("images/ship3_2.png");
	boat2Texture[3].loadFromFile("images/ship4_2.png");
	
    for(int i = 0; i < BOATCOUNT; i++)
    {
        boat2.push_back(Boat2());
		boat2[i].sprite.setTexture(boat2Texture[i]);
		boat2[i].sprite.setPosition(position.x,position.y + i * MARGIN);
		boat2[i].sprite.setRotation(HORIZONTAL);
		boat2[i].sprite.setOrigin(origin[i]);
		boat2[i].state = "LOCKED";
		boat2[i].rotation = "HORIZONTAL";	
    }

	//boat2[0].sprite.setTexture(ship1Tex); 

}
void Boat2::setStatus(bool value)
{ // SET IF THE BOAT CAN MOVED OR NOT MOVED IF THE GAME STARTED
	status = value;
}

void Boat2::select(sf::RenderWindow& win,sf::Vector2i cursorPosition)
{
	
	for(int i = 0;i < boat2.size();i++) {
		if(boat2[i].sprite.getGlobalBounds().contains(cursorPosition.x,cursorPosition.y))
		{

			boat2[i].state = "UNLOCKED";
			// LEFT CLICK LOCK/UNLOCK BOAT
			if(boat2[i].state == "UNLOCKED" && canSelect && status) { 
				boat2[i].move(win);
			}
			canSelect = false;
				
		}
		else { boat2[i].state = "LOCKED"; canSelect = true; }

	}
}

void Boat2::rotate(sf::Vector2i cursorPosition,sf::Event &event)
{
	for(int i = 0;i < boat2.size();i++) {
		if(boat2[i].sprite.getGlobalBounds().contains(cursorPosition.x,cursorPosition.y) && 
				boat2[i].rotation == "HORIZONTAL")	
		{
			 boat2[i].sprite.setRotation(VERTICAL); boat2[i].rotation = "VERTICAL"; 
		}
		else if (boat2[i].sprite.getGlobalBounds().contains(cursorPosition.x,cursorPosition.y)) 
		{
	       		boat2[i].sprite.setRotation(HORIZONTAL); boat2[i].rotation = "HORIZONTAL";
		}
	}
}

void Boat2::move(sf::RenderWindow& win)
{	
		sprite.setPosition(sf::Mouse::getPosition(win).x,sf::Mouse::getPosition(win).y);
}

bool Boat2::checkPositionOnGrid(sf::FloatRect& gridSquare)
{
    for (int i = 0; i < boat2.size(); i++)
    {
        // Adjusted collision detection bounds
        sf::FloatRect collisionBounds = boat2[i].sprite.getGlobalBounds();

        // Check the rotation of the ship
        if (boat2[i].rotation == "HORIZONTAL")
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

const sf::FloatRect Boat2::getBoatPosition()
{
    for(int i = 0; i < boat2.size(); i++)
    {
        return boat2[i].sprite.getGlobalBounds();
    }
        return sprite.getGlobalBounds();
}

void Boat2::filled(sf::RenderWindow& window, const int& positionX, const int& positionY)
{
	filledCase.setPosition(positionX, positionY);
	//window.draw(filledCase);
}

void Boat2::missed(sf::RenderWindow& window, const int& positionX, const int& positionY)
{
	playedCase.setPosition(positionX, positionY);
	window.draw(playedCase);
}

void Boat2::destroyed(sf::RenderWindow& window,const int& positionX,const int& positionY )
{
	explosion.setPosition(positionX,positionY);
	window.draw(explosion);		
}


void Boat2::draw(sf::RenderWindow& window)
{
	
	for(int i = 0; i < boat2.size() ; i++)
	{
		window.draw(boat2[i].sprite);
	}
	
}