#include "main.hpp"

void displayStoryline(sf::RenderWindow& window) {
    sf::Music story;
    story.openFromFile("audio/stry_music.ogg");
    story.setVolume(85);
    story.setLoop(true);
    story.play();
    const int numImages = 20;
    sf::Sprite images[numImages];
    sf::Texture textures[numImages];
    std::string fileNames[numImages] = {
        "images/storyline/storyline1.png",
        "images/storyline/storyline2.png",
        "images/storyline/storyline3.png",
        "images/storyline/storyline4.png",
        "images/storyline/storyline5.png",
        "images/storyline/storyline6.png",
        "images/storyline/storyline7.png",
        "images/storyline/storyline8.png",
        "images/storyline/storyline9.png",
        "images/storyline/storyline10.png",
        "images/storyline/storyline11.png",
        "images/storyline/storyline12.png",
        "images/storyline/storyline13.png",
        "images/storyline/storyline14.png",
        "images/storyline/storyline15.png",
        "images/storyline/storyline16.png",
        "images/storyline/storyline17.png",
        "images/storyline/storyline18.png",
        "images/storyline/storyline19.png",
        "images/storyline/storyline20.png",
    };

    for (int i = 0; i < numImages; ++i) {
        if (!textures[i].loadFromFile(fileNames[i])) {
            std::cerr << "Error loading " << fileNames[i] << std::endl;
            return;
        }
        images[i].setTexture(textures[i]);
        images[i].setPosition(
            (window.getSize().x - textures[i].getSize().x) / 2,
            (window.getSize().y - textures[i].getSize().y) / 2
        );
        images[i].setColor(sf::Color(255, 255, 255, i == 0 ? 255 : 0)); // Only the first image is visible initially
    }

    int currentImage = 0; //keeps track of the currently displayed image
    bool transitioning = false; //indidcates if a transition between images is happening
    bool exitToGame = false; //if mo skip nalang
    sf::Clock clock; //meausres elapsed time for transitions
    float transitionTime = 0.5f; // 0.5 seconds for transition
    float elapsedTransitionTime = 0.0f; //tracks the time during a transition

    while (window.isOpen() && !exitToGame) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Escape) {
                    return; // Exit the function //skip the story line
                } else if (event.key.code == sf::Keyboard::Space && currentImage < numImages - 1) {
                    transitioning = true; 
                    elapsedTransitionTime = 0.0f;
                    clock.restart();
                } else if (event.key.code == sf::Keyboard::Return && currentImage == numImages - 1) {
                    exitToGame = true; //mo exit na siya if last image na
                }
            }
        }

        if (transitioning) {
            elapsedTransitionTime = clock.getElapsedTime().asSeconds();
            if (elapsedTransitionTime >= transitionTime) {
                transitioning = false;
                elapsedTransitionTime = transitionTime;
                images[currentImage].setColor(sf::Color(255, 255, 255, 0)); // Fully transparent
                currentImage++;
                images[currentImage].setColor(sf::Color(255, 255, 255, 255)); // Fully opaque
            } else {
                float alpha = (elapsedTransitionTime / transitionTime) * 255;
                images[currentImage].setColor(sf::Color(255, 255, 255, 255 - alpha));
                images[currentImage + 1].setColor(sf::Color(255, 255, 255, alpha));
            }
        }

        window.clear(sf::Color::Black);
        for (int i = 0; i <= currentImage; ++i) {
            window.draw(images[i]);
        }
        window.display();
    }
    story.stop();
}

void showGameMechanics(sf::RenderWindow &window)
{
    sf::Sprite gameMecha1, gameMecha2, gameMecha3;
    sf::Texture gameMechaTex1, gameMechaTex2, gameMechaTex3;

    if (!gameMechaTex1.loadFromFile("images/gamemechanics1.png")) {
        // Handle error
    }
    if (!gameMechaTex2.loadFromFile("images/gamemechanics2.png")) {
        // Handle error
    }
    if (!gameMechaTex3.loadFromFile("images/gamemechanics3.png")) {
        // Handle error
    }

    gameMecha1.setTexture(gameMechaTex1);
    gameMecha2.setTexture(gameMechaTex2);
    gameMecha3.setTexture(gameMechaTex3);

    gameMecha1.setColor(sf::Color(255, 255, 255, 255)); // Fully opaque
    gameMecha2.setColor(sf::Color(255, 255, 255, 0));   // Fully transparent
    gameMecha3.setColor(sf::Color(255, 255, 255, 0));   // Fully transparent

    int currentImage = 0; // 0 for gameMecha1, 1 for gameMecha2, 2 for gameMecha3
    bool exitToMenu = false;
    sf::Clock clock;
    float transitionTime = 0.5f; // 0.5 seconds for transition
    bool transitioning = false;
    float elapsedTransitionTime = 0.0f;

    while (window.isOpen() && !exitToMenu)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Escape)
                    exitToMenu = true;
                else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left) {
                    transitioning = true;
                    elapsedTransitionTime = 0.0f;
                    clock.restart();
                }
            }
        }

        if (transitioning) {
            elapsedTransitionTime = clock.getElapsedTime().asSeconds();
            if (elapsedTransitionTime >= transitionTime) {
                transitioning = false;
                elapsedTransitionTime = transitionTime;
                currentImage = (currentImage + 1) % 3; // Cycle through the images
                gameMecha1.setColor(sf::Color(255, 255, 255, currentImage == 0 ? 255 : 0));
                gameMecha2.setColor(sf::Color(255, 255, 255, currentImage == 1 ? 255 : 0));
                gameMecha3.setColor(sf::Color(255, 255, 255, currentImage == 2 ? 255 : 0));
            } else {
                float alpha = (elapsedTransitionTime / transitionTime) * 255;
                if (currentImage == 0) {
                    gameMecha1.setColor(sf::Color(255, 255, 255, 255 - alpha));
                    gameMecha2.setColor(sf::Color(255, 255, 255, alpha));
                    gameMecha3.setColor(sf::Color(255, 255, 255, 0));
                } else if (currentImage == 1) {
                    gameMecha1.setColor(sf::Color(255, 255, 255, 0));
                    gameMecha2.setColor(sf::Color(255, 255, 255, 255 - alpha));
                    gameMecha3.setColor(sf::Color(255, 255, 255, alpha));
                } else {
                    gameMecha1.setColor(sf::Color(255, 255, 255, alpha));
                    gameMecha2.setColor(sf::Color(255, 255, 255, 0));
                    gameMecha3.setColor(sf::Color(255, 255, 255, 255 - alpha));
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(gameMecha1);
        window.draw(gameMecha2);
        window.draw(gameMecha3);
        window.display();
    }
}

void showCredits(sf::RenderWindow &window)
{
    sf::Sprite credits1, credits2, credits3;
    sf::Texture creditsTex1, creditsTex2, creditsTex3;

    if (!creditsTex1.loadFromFile("images/credits1.png")) {
        // Handle error
    }
    if (!creditsTex2.loadFromFile("images/credits2.png")) {
        // Handle error
    }
    if (!creditsTex3.loadFromFile("images/credits3.png")) {
        // Handle error
    }

    credits1.setTexture(creditsTex1);
    credits2.setTexture(creditsTex2);
    credits3.setTexture(creditsTex3);

    credits1.setColor(sf::Color(255, 255, 255, 255)); // Fully opaque
    credits2.setColor(sf::Color(255, 255, 255, 0));   // Fully transparent
    credits3.setColor(sf::Color(255, 255, 255, 0));   // Fully transparent

    int currentImage = 0; // 0 for gameMecha1, 1 for gameMecha2, 2 for gameMecha3
    bool exitToMenu = false;
    sf::Clock clock;
    float transitionTime = 0.5f; // 0.5 seconds for transition
    bool transitioning = false;
    float elapsedTransitionTime = 0.0f;

    while (window.isOpen() && !exitToMenu)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Escape)
                    exitToMenu = true;
                else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left) {
                    transitioning = true;
                    elapsedTransitionTime = 0.0f;
                    clock.restart();
                }
            }
        }

        if (transitioning) {
            elapsedTransitionTime = clock.getElapsedTime().asSeconds();
            if (elapsedTransitionTime >= transitionTime) {
                transitioning = false;
                elapsedTransitionTime = transitionTime;
                currentImage = (currentImage + 1) % 3; // Cycle through the images
                credits1.setColor(sf::Color(255, 255, 255, currentImage == 0 ? 255 : 0));
                credits2.setColor(sf::Color(255, 255, 255, currentImage == 1 ? 255 : 0));
                credits3.setColor(sf::Color(255, 255, 255, currentImage == 2 ? 255 : 0));
            } else {
                float alpha = (elapsedTransitionTime / transitionTime) * 255;
                if (currentImage == 0) {
                    credits1.setColor(sf::Color(255, 255, 255, 255 - alpha));
                    credits2.setColor(sf::Color(255, 255, 255, alpha));
                    credits3.setColor(sf::Color(255, 255, 255, 0));
                } else if (currentImage == 1) {
                    credits1.setColor(sf::Color(255, 255, 255, 0));
                    credits2.setColor(sf::Color(255, 255, 255, 255 - alpha));
                    credits3.setColor(sf::Color(255, 255, 255, alpha));
                } else {
                    credits1.setColor(sf::Color(255, 255, 255, alpha));
                    credits2.setColor(sf::Color(255, 255, 255, 0));
                    credits3.setColor(sf::Color(255, 255, 255, 255 - alpha));
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(credits1);
        window.draw(credits2);
        window.draw(credits3);
        window.display();
    }
}






int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 610), "Pirates of the Cabberyan", sf::Style::Titlebar | sf::Style::Close);
    Menu mainMenu(window.getSize().x, window.getSize().y);

    Battleship battleship;
    sf::Music backgroundMusic;
    
    if (!backgroundMusic.openFromFile("audio/Menu_Music_loop.ogg")) {
        // Error handling for loading music file
    }
    backgroundMusic.setLoop(true); // Loop the music
    backgroundMusic.play();

 
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        mainMenu.MoveUp();
                        break;
                    case sf::Keyboard::Down:
                        mainMenu.MoveDown();
                        break;
                    case sf::Keyboard::Return:
                        switch (mainMenu.getPressedItem()) {
                            case 0:
                                backgroundMusic.stop();
                                displayStoryline(window);
                                battleship.init();
                                battleship.loop(window);
                                backgroundMusic.play();
                                break;
                            case 1:
                                showGameMechanics(window);
                                break;
                            case 2:
                                showCredits(window);
                                break;
                            case 3:
                                std::cout << "Exit selected" << std::endl;
                                window.close();
                                break;
                        }
                }
            }
        }
       

        window.clear();
        mainMenu.draw(window);
        window.display();
    }

    return 0;
}