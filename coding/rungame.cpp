#include "rungame.hpp"

void Battleship::init()
{
    font.loadFromFile("roman_normal.ttf");

    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setScale(0.75, 0.75);

    text1.setFont(font);
    text1.setFillColor(sf::Color::Black);
    text1.setScale(0.75, 0.75);

    missedText1.setFont(font);
    missedText1.setString("Atoiii ya uyy!");
    missedText1.setFillColor(sf::Color::Black);
    missedText1.setPosition(sf::Vector2f(150, 530));
    missedText1.setScale(0.75, 0.75);

    missedText2.setFont(font);
    missedText2.setString("Oh nauurrr!");
    missedText2.setFillColor(sf::Color::Black);
    missedText2.setPosition(sf::Vector2f(750, 530));
    missedText2.setScale(0.75, 0.75);

    inGameMusic.openFromFile("audio/ingame_sfx.ogg");
    inGameMusic.setVolume(85);

    gameFinish.openFromFile("audio/gameFinish.ogg");
    gameFinish.setVolume(85);

    Winner1Tex.loadFromFile("images/winner1.png"); // to be replaced
    Winner1.setTexture(Winner1Tex);
    Winner1.setPosition(0, 0);

    Winner2Tex.loadFromFile("images/winner2.png");
    Winner2.setTexture(Winner2Tex);
    Winner2.setPosition(0, 0);

    backTex.loadFromFile("images/game_bg.png");
    background.setTexture(backTex);
    background.setPosition(0, 0);

    board1.setPlayer1Grid();
    board2.setPlayer2Grid();
    board2.init();
    board2.addSensorsToGrid();
    board1.init();
    board1.addSensorsToGrid();

    cloudTex1.loadFromFile("images/cloud.png");
    cloud1.setTexture(cloudTex1);
    cloud1.setPosition(sf::Vector2f(0, 50));

    cloudTex2.loadFromFile("images/cloud.png");
    cloud2.setTexture(cloudTex2);
    cloud2.setPosition(sf::Vector2f(560, 50));

    filled1 = 0;
    filled2 = 0;
}

void Battleship::loop(sf::RenderWindow& win)
{
    int ships1 = 13, ships2 = 13;
    int winner = 0;
    bool gameOverSoundPlayed = false;

    Boat1 boat1;
    boat1.initialize();
    Boat2 boat2;
    boat2.initialize();

    bool placingShipsPlayer1 = true;
    bool placingShipsPlayer2 = false;

    bool isPlayer1Turn = true;
    bool gameStarted = false;
    bool hasAttacked = false;  // Flag to track if the current player has attacked

    bool exitToMenu = false;

    inGameMusic.setLoop(true); // Loop the music
    inGameMusic.play();

    int temp1 = ships1;
    int temp2 = ships2;
    int firstTurn = 1;

    while (win.isOpen() && !exitToMenu)
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                win.close();
            else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
                exitToMenu = true;
            else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {
                int filledCount1 = 0;
                int filledCount2 = 0;

                // Count the number of filled spaces for Player 1
                for (int line = 0; line < 10; line++) {
                    for (int row = 0; row < 10; row++) {
                        if (board1.player1GridArray[line][row] == 1) {
                            filledCount1++;
                        }
                    }
                }

                // Count the number of filled spaces for Player 2
                for (int line = 0; line < 10; line++) {
                    for (int row = 0; row < 10; row++) {
                        if (board2.player2GridArray[line][row] == 1) {
                            filledCount2++;
                        }
                    }
                }

                if (placingShipsPlayer1 && filledCount1 == 13) {
                    placingShipsPlayer1 = false;
                    placingShipsPlayer2 = true;
                    filled1 = filledCount1;
                }
                else if (placingShipsPlayer2 && filledCount2 == 13) {
                    placingShipsPlayer2 = false;
                    gameStarted = true;
                    filled2 = filledCount2;
                }
            }
        }

        win.clear(sf::Color::White);

        if (placingShipsPlayer1)
        {
            win.draw(background);
            for (int line = 0; line < 10; line++) {
                for (int row = 0; row < 10; row++) {
                    if (board1.player1GridArray[line][row] == 1) {
                        filled1++;
                    }
                }
            }
            if (filled1 == 13) {
                text.setString("READY");
                text.setPosition(sf::Vector2f(170, 530));
            }
            else {
                text.setString("Place your ships");
                text.setPosition(sf::Vector2f(130, 530));
            }
            filled1 = 0;
            text1.setString("Look sa far away!");
            text1.setPosition(sf::Vector2f(730, 530));
            win.draw(text1);
            win.draw(text);
            board1.draw(win);
            board1.updateEvent(win, event, boat1);
            board1.detectBoat1OnGrid(boat1);
            board1.readPlayer1GridInfo(win, boat1);
            boat1.draw(win);
        }
        else if (placingShipsPlayer2)
        {
            win.draw(background);
            for (int line = 0; line < 10; line++) {
                for (int row = 0; row < 10; row++) {
                    if (board2.player2GridArray[line][row] == 1) {
                        filled2++;
                    }
                }
            }
            if (filled2 == 13) {
                text.setString("READY");
                text.setPosition(sf::Vector2f(770, 530));
            }
            else {
                text.setString("Place your ships");
                text.setPosition(sf::Vector2f(730, 530));
            }
            filled2 = 0;
            text1.setString("Sleep ka muna!");
            text1.setPosition(sf::Vector2f(130, 530));
            win.draw(text1);
            win.draw(text);
            win.draw(cloud1);
            board2.draw(win);
            board2.updateEvent(win, event, boat2);
            board2.detectBoat2OnGrid(boat2);
            board2.readPlayer2GridInfo(win, boat2);
            boat2.draw(win);
        }
        else if (gameStarted)
        {
            if (isPlayer1Turn)
            {
                // Player 1's turn
                text.setString("Attack!");
                text.setPosition(sf::Vector2f(170, 530));
                temp2 = ships2;
                ships2 = board2.player1AttackEvent(win, hasAttacked);
                if (ships2 <= 0)
                {
                    winner = 1;// Player 1 wins
                }
                else if (hasAttacked)
                {
                    isPlayer1Turn = false;
                    hasAttacked = false;  // Reset the attack flag for the next turn
                }
            }
            else
            {
                // Player 2's turn
                text.setString("Attack!");
                text.setPosition(sf::Vector2f(770, 530));
                temp1 = ships1;
                ships1 = board1.player2AttackEvent(win, hasAttacked);
                if (ships1 <= 0)
                {
                    winner = 2; /// Player 2 wins
                }
                else if (hasAttacked)
                {
                    isPlayer1Turn = true;
                    hasAttacked = false;  // Reset the attack flag for the next turn
                }
                firstTurn = 0;
            }
            if (winner == 0) {
                win.draw(background);
                win.draw(text);

                if (firstTurn == 0) {
                    if (!isPlayer1Turn) {
                        if (temp2 > ships2) {
                            std::stringstream ss;
                            ss << ships2 << " hits to go!";
                            text1.setString(ss.str());
                            text1.setPosition(sf::Vector2f(150, 530));
                            win.draw(text1);
                        }
                        else
                            win.draw(missedText1);
                    }
                    else {
                                                if (temp1 > ships1) {
                            std::stringstream ss;
                            ss << ships1 << " hits to go!";
                            text1.setString(ss.str());
                            text1.setPosition(sf::Vector2f(750, 530));
                            win.draw(text1);
                        }
                        else
                            win.draw(missedText2);
                    }
                }
                else {
                    text1.setString("Hmmm...");
                    text1.setPosition(sf::Vector2f(750, 530));
                    win.draw(text1);
                }
                board1.draw(win);
                board1.readPlayer1GridInfo(win, boat1);
                board2.draw(win);
                board2.readPlayer2GridInfo(win, boat2);
                win.draw(cloud2);
                win.draw(cloud1);
            }
            else {
                inGameMusic.stop();
                if (!gameOverSoundPlayed) {
                    gameFinish.setLoop(false); // Do not loop the game finish sound
                    gameFinish.play();
                    gameOverSoundPlayed = true;
                }
                if (winner == 1) {
                    win.draw(Winner1);
                }
                else {
                    win.draw(Winner2);
                }
            }
        }

        win.display();
    }
    gameFinish.stop();
    inGameMusic.stop(); // Stop the in-game music when exiting to the menu
}

