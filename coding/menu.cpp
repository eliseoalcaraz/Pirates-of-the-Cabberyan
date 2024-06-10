#include "menu.hpp"

Menu::Menu(float width, float height)
{
    if (!font.loadFromFile("roman_bold.otf")) // file sa font
    {
        // handle error
    }
    backTex.loadFromFile("images/mainFinal.png");
    back.setTexture(backTex);
    

    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color(231, 223, 208));
    menu[0].setString("DULA CA?");
    menu[0].setScale(0.90, 0.90);
    menu[0].setStyle(sf::Text::Bold);
    menu[0].setPosition(sf::Vector2f(40, height / (MAX_ITEMS + 1) * 1.95));

    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color(72, 62, 103));
    menu[1].setString("GAME MECHANICS");
    menu[1].setScale(0.90, 0.90);
    menu[1].setStyle(sf::Text::Bold);
    menu[1].setPosition(sf::Vector2f(40, height / (MAX_ITEMS + 1) * 2.40));

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color(72, 62, 103));
    menu[2].setString("CREDITS");
    menu[2].setScale(0.90, 0.90);
    menu[2].setStyle(sf::Text::Bold);
    menu[2].setPosition(sf::Vector2f(40, height / (MAX_ITEMS + 1) * 2.85));

    menu[3].setFont(font);
    menu[3].setFillColor(sf::Color(72, 62, 103));
    menu[3].setString("EXIT GAME");
    menu[3].setScale(0.90, 0.90);
    menu[3].setStyle(sf::Text::Bold);
    menu[3].setPosition(sf::Vector2f(40, height / (MAX_ITEMS + 1) * 3.30));

    selectedItemIndex = 0;
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow &window)
{
    window.draw(back);
    for (int i = 0; i < MAX_ITEMS; i++)
    {
        window.draw(menu[i]);
    }
    
}

void Menu::MoveUp()
{
    if (selectedItemIndex - 1 >= 0)
    {
        menu[selectedItemIndex].setFillColor(sf::Color(72, 62, 103));
        selectedItemIndex--;
        menu[selectedItemIndex].setFillColor(sf::Color(231, 223, 208));
    }
}

void Menu::MoveDown()
{
    if (selectedItemIndex + 1 < MAX_ITEMS)
    {
        menu[selectedItemIndex].setFillColor(sf::Color(72, 62, 103));
        selectedItemIndex++;
        menu[selectedItemIndex].setFillColor(sf::Color(231, 223, 208));
    }
}