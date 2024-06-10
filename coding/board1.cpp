#include "board1.hpp"

Board1::Board1():PLAYER1GRID_X(50), PLAYER1GRID_Y(150), PLAYER1GRID_OFFSET_X(50), PLAYER1GRID_OFFSET_Y(155), GRID_SIZE(320), GAMESPEED(1.00), TILESIZE(32), EMPTY(0), FILLED(1), DESTROYED(2), PLAYED(3)
{
    squarePositionX = PLAYER1GRID_OFFSET_X;
    squarePositionY = PLAYER1GRID_OFFSET_Y;

    isPressed = false;
    ships1 = 13;

    attack.openFromFile("audio/Boom_panes.ogg");
    attackMissed.openFromFile("audio/Boom_panot.ogg");
    attack.setVolume(50);

}



void Board1::init()
{
    //add the texture of the grid here
    gridTexture.loadFromFile("images/Grid.png");
    player1Grid.setTexture(gridTexture);
    player1Grid.setPosition(PLAYER1GRID_X, PLAYER1GRID_Y);

    grid.left = PLAYER1GRID_X;
    grid.top = PLAYER1GRID_Y;
    grid.width = GRID_SIZE;

}
void Board1::setPlayer1Grid()
{
    for(int line= 0; line < player1GridArray.size(); line++)
    {
        for(int row=0; row<player1GridArray.size(); row++)
            player1GridArray[line][row] = EMPTY;
    }
}

void Board1::readPlayer1GridInfo(sf::RenderWindow& window,Boat1& boat1)
{
    for(int line=0; line < player1GridArray.size(); line++)
    {
        for(int row=0; row < player1GridArray.size(); row++)
        {
            if(player1GridArray[line][row] == FILLED){
                positionX = row * TILESIZE + PLAYER1GRID_OFFSET_X;
                positionY = line * TILESIZE + PLAYER1GRID_OFFSET_Y;
                boat1.filled(window,positionX,positionY);
            }
            else if(player1GridArray[line][row] == PLAYED)
			{
				positionX = row * TILESIZE + PLAYER1GRID_OFFSET_X; 
				positionY = line * TILESIZE + PLAYER1GRID_OFFSET_Y;			
				boat1.missed(window,positionX,positionY);
			}
			else if(player1GridArray[line][row] == DESTROYED)
			{
				positionX = row * TILESIZE + PLAYER1GRID_OFFSET_X; 
				positionY = line * TILESIZE + PLAYER1GRID_OFFSET_Y;			
				boat1.destroyed(window,positionX,positionY);
			}

        }
    }

}

void Board1::addSensorsToGrid()
{
    for (int row = 0; row < 10; ++row) {
        for (int col = 0; col < 10; ++col) {
            gridSquare.emplace_back(
                sf::FloatRect(
                    PLAYER1GRID_OFFSET_X + col * TILESIZE,
                    PLAYER1GRID_OFFSET_Y + row * TILESIZE,
                    TILESIZE,
                    TILESIZE
                )
            );
        }
    }
}

void Board1::detectBoat1OnGrid(Boat1& boat1)
{
    for( int i = 0; i < gridSquare.size(); i++)
	{
			if(boat1.checkPositionOnGrid(gridSquare[i]))
			{
				setBoat1OnGrid(i,FILLED);
			}
		else 
			{
				setBoat1OnGrid(i,EMPTY);
			}
	}
}

void Board1::setBoat1OnGrid(int& idx, const int& status)
{
    x = 0;
    y = idx;
    if(idx > 10)
    {
        x = std::abs(idx/10);
        y = idx % 10;
    }
    if(player1GridArray[x][y] != DESTROYED){
        if(status == EMPTY && player1GridArray[x][y] == FILLED){
            player1GridArray[x][y] = status;
        }
        else if(status == FILLED){
            player1GridArray[x][y] = status;
        }
    }

}



std::vector<sf::RectangleShape> coloredBox1;
void Board1::addBoxtoSquare(sf::RenderWindow& win)
{
    for(int i=0; i < gridSquare.size(); i++)
    {
        coloredBox1.push_back(sf::RectangleShape(sf::Vector2f(16, 16)));
        coloredBox1.back().setPosition(gridSquare[i].left, gridSquare[i].top);
        coloredBox1.back().setFillColor(sf::Color::Red);
    }

    for(int i=0; i<coloredBox1.size(); i++)
    {
        win.draw(coloredBox1[i]);
    }
}

void Board1::updateEvent(sf::RenderWindow& win,sf::Event &event,Boat1& boat1)
{
	// MOUSE EVENT TO SELECT AND MOVE BOARD
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		boat1.select(win,sf::Mouse::getPosition(win));
	}

	if(clock.getElapsedTime().asSeconds() >= GAMESPEED) 
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::R) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			boat1.rotate(sf::Mouse::getPosition(win),event);
			clock.restart();		
		}
	}
}

int Board1::getAttackedSquare(sf::RenderWindow& win)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(win);
    for (int i = 0; i < gridSquare.size(); ++i) {
        if (gridSquare[i].contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            return i;
        }
    }
    return -1; // No square was clicked
}


int Board1::player2AttackEvent(sf::RenderWindow& win, bool& hasAttacked)
{
    if (!hasAttacked && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        int attackedSquare = getAttackedSquare(win);
        if (attackedSquare >= 0) {
            play2_x = 0;
            play2_y = attackedSquare;

            if (attackedSquare > 10) {
                play2_x = std::abs(attackedSquare / 10);
                play2_y = attackedSquare % 10;
            }

            if (player1GridArray[play2_x][play2_y] != FILLED && player1GridArray[play2_x][play2_y] != PLAYED && player1GridArray[play2_x][play2_y] != DESTROYED) {
                player1GridArray[play2_x][play2_y] = PLAYED;
                hasAttacked = true;
                attackMissed.play();
            } else if (player1GridArray[play2_x][play2_y] == FILLED) {
                player1GridArray[play2_x][play2_y] = DESTROYED;
                ships1--;
                hasAttacked = true;
                attack.play();
            }
        }
    }
    return ships1;
}



void Board1::draw(sf::RenderWindow& window)
{
    window.draw(player1Grid);
}