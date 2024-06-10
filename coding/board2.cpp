#include "board2.hpp"

Board2::Board2():PLAYER2GRID_X(645), PLAYER2GRID_Y(150), PLAYER2GRID_OFFSET_X(650), PLAYER2GRID_OFFSET_Y(155), GAMESPEED(1.00), GRID_SIZE(320), TILESIZE(32), EMPTY(0), FILLED(1), DESTROYED(2), PLAYED(3)
{
    squarePositionX = PLAYER2GRID_OFFSET_X;
    squarePositionY = PLAYER2GRID_OFFSET_Y;

    ships2 = 13;

    attack.openFromFile("audio/Boom_panes.ogg");
    attackMissed.openFromFile("audio/Boom_panot.ogg");
    attack.setVolume(50);
    font.loadFromFile("roman_normal.ttf");
    text.setFont(font);
}



void Board2::init()
{
    //add the texture of the grid here
    gridTexture.loadFromFile("images/Grid.png");
    player2Grid.setTexture(gridTexture);
    player2Grid.setPosition(PLAYER2GRID_X, PLAYER2GRID_Y);

    grid.left = PLAYER2GRID_X;
    grid.top = PLAYER2GRID_Y;
    grid.width = GRID_SIZE;

}
void Board2::setPlayer2Grid()
{
    for(int line= 0; line < player2GridArray.size(); line++)
    {
        for(int row=0; row<player2GridArray.size(); row++)
            player2GridArray[line][row] = EMPTY;
    }
}

void Board2::readPlayer2GridInfo(sf::RenderWindow& window,Boat2& boat2)
{
    for(int line=0; line < player2GridArray.size(); line++)
    {
        for(int row=0; row < player2GridArray.size(); row++)
        {
            if(player2GridArray[line][row] == FILLED){
                positionX = row * TILESIZE + PLAYER2GRID_OFFSET_X;
                positionY = line * TILESIZE + PLAYER2GRID_OFFSET_Y;
                boat2.filled(window,positionX,positionY);
            }
            else if(player2GridArray[line][row] == PLAYED)
			{
				positionX = row * TILESIZE + PLAYER2GRID_OFFSET_X; 
				positionY = line * TILESIZE + PLAYER2GRID_OFFSET_Y;			
				boat2.missed(window,positionX,positionY);
			}
			else if(player2GridArray[line][row] == DESTROYED)
			{
				positionX = row * TILESIZE + PLAYER2GRID_OFFSET_X; 
				positionY = line * TILESIZE + PLAYER2GRID_OFFSET_Y;			
				boat2.destroyed(window,positionX,positionY);
			}
        }
    }

}


void Board2::addSensorsToGrid()
{
    for (int row = 0; row < 10; ++row) {
        for (int col = 0; col < 10; ++col) {
            gridSquare.emplace_back(
                sf::FloatRect(
                    PLAYER2GRID_OFFSET_X + col * TILESIZE,
                    PLAYER2GRID_OFFSET_Y + row * TILESIZE,
                    TILESIZE,
                    TILESIZE
                )
            );
        }
    }
}

int Board2::getAttackedSquare(sf::RenderWindow& win)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(win);
    for (int i = 0; i < gridSquare.size(); ++i) {
        if (gridSquare[i].contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            return i;
        }
    }
    return -1; // No square was clicked
}

void Board2::detectBoat2OnGrid(Boat2& boat2)
{
    for( int i = 0; i < gridSquare.size(); i++)
	{
			if(boat2.checkPositionOnGrid(gridSquare[i]))
			{
				setBoat2OnGrid(i,FILLED);
			}
		else 
			{
				setBoat2OnGrid(i,EMPTY);
			}
	}
}

void Board2::setBoat2OnGrid(int& idx, const int& status)
{
    x = 0;
    y = idx;
    if(idx > 10)
    {
        x = std::abs(idx/10);
        y = idx % 10;
    }
    if(player2GridArray[x][y] != DESTROYED){
        if(status == EMPTY && player2GridArray[x][y] == FILLED){
            player2GridArray[x][y] = status;
        }
        else if(status == FILLED){
            player2GridArray[x][y] = status;
        }
    }

}


std::vector<sf::RectangleShape> coloredBox2;
void Board2::addBoxtoSquare(sf::RenderWindow& win)
{
    for(int i=0; i < gridSquare.size(); i++)
    {
        coloredBox2.push_back(sf::RectangleShape(sf::Vector2f(16, 16)));
        coloredBox2.back().setPosition(gridSquare[i].left, gridSquare[i].top);
        coloredBox2.back().setFillColor(sf::Color::Red);
    }
   
    for(int i=0; i<coloredBox2.size(); i++)
    {
        win.draw(coloredBox2[i]);
    }
}

void Board2::updateEvent(sf::RenderWindow& win,sf::Event &event,Boat2& boat2)
{
	// MOUSE EVENT TO SELECT AND MOVE BOARD
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		boat2.select(win,sf::Mouse::getPosition(win));
	}

	if(clock.getElapsedTime().asSeconds() >= GAMESPEED) 
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::R) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			boat2.rotate(sf::Mouse::getPosition(win),event);
			clock.restart();		
		}
	}
}

int Board2::player1AttackEvent(sf::RenderWindow& win, bool& hasAttacked)
{
    if (!hasAttacked && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        int attackedSquare = getAttackedSquare(win);
        if (attackedSquare >= 0) {
            play1_x = 0;
            play1_y = attackedSquare;

            if (attackedSquare > 10) {
                play1_x = std::abs(attackedSquare / 10);
                play1_y = attackedSquare % 10;
            }

            if (player2GridArray[play1_x][play1_y] != FILLED && player2GridArray[play1_x][play1_y] != PLAYED && player2GridArray[play1_x][play1_y] != DESTROYED ) {
                player2GridArray[play1_x][play1_y] = PLAYED;
                hasAttacked = true;
                attackMissed.play();
                text.setString("Oh naurrr!");
                text.setPosition(sf::Vector2f(150, 530));
                win.draw(text);
            } else if (player2GridArray[play1_x][play1_y] == FILLED) {
                player2GridArray[play1_x][play1_y] = DESTROYED;
                ships2--;
                hasAttacked = true;
                attack.play();
                std::stringstream ss;
                ss << ships2 << " hits to go!";
                text.setString(ss.str());
                text.setPosition(sf::Vector2f(150, 530));
                win.draw(text);
            }
        }
    }
    return ships2;
}

void Board2::draw(sf::RenderWindow& window)
{
    window.draw(player2Grid);
}
