#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <random>
#include <cmath>

static void setText(sf::Text& text, float x, float y)
{
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

class WelcomeWindow
{
private:
	unsigned int width;
	unsigned int height;
	sf::Font font;

public:
	WelcomeWindow()
	{
		width = 800;
		height = 600;

		//Load Font
		if (!font.loadFromFile("font.ttf"))
		{
			std::cerr << "Failed to open font file!" << std::endl;
		}
	}

    void launchWelcomeWindow()
    {
        //Create Welcome Window
        sf::RenderWindow welcomeWindow(sf::VideoMode({ width, height }), "Welcome", sf::Style::Default);
        welcomeWindow.setFramerateLimit(60);

        //Set Background
        sf::RectangleShape background(sf::Vector2f(width, height));
        background.setFillColor(sf::Color::Blue);

        sf::Text welcomeText("Welcome to (game_name)!", font, 24);
        welcomeText.setPosition((welcomeWindow.getSize().x / 2) - (welcomeText.getLocalBounds().width / 2), welcomeWindow.getSize().y / 2 - 200);
        welcomeText.setFillColor(sf::Color::White);
        welcomeText.setStyle(sf::Text::Underlined | sf::Text::Bold);


        sf::Text promptText("Please enter the name of your tycoon:", font, 20);
        promptText.setPosition((width / 2) - (promptText.getLocalBounds().width / 2), (height / 2) - 75);
        promptText.setFillColor(sf::Color::White);
        promptText.setStyle(sf::Text::Bold);

        std::string playerName;
        sf::Text inputText("", font, 18);
        inputText.setStyle(sf::Text::Bold);
        inputText.setFillColor(sf::Color::White);
        setText(inputText, width / 2.0f, height / 2.0f - 25);

        sf::Sprite palmTree;
        sf::Sprite money;
        sf::Sprite ferrisWheel;

        sf::Texture palmTreeTexture;
        sf::Texture moneyTexture;
        sf::Texture ferrisWheelTexture;

        palmTreeTexture.loadFromFile("images/palmtree.png");
        palmTree.setTexture(palmTreeTexture);
        palmTree.setPosition(sf::Vector2f(50, 50));
        palmTree.setScale(.25f, .25f);

        moneyTexture.loadFromFile("images/moneymoney.png");
        money.setTexture(moneyTexture);
        money.setPosition(sf::Vector2f(640, 70));
        money.setScale(.05f, .05f);

        ferrisWheelTexture.loadFromFile("images/ferriswheel.png");
        ferrisWheel.setTexture(ferrisWheelTexture);
        ferrisWheel.setPosition(sf::Vector2f(300, 300));
        ferrisWheel.setScale(.4f, .4f);

        sf::Text cursor("|", font, 20);
        cursor.setFillColor(sf::Color::Yellow);
        bool showCursor = true;

        while (welcomeWindow.isOpen()) {
            sf::Event event;
            while (welcomeWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    welcomeWindow.close();
                    exit(0);
                }
                if (event.type == sf::Event::TextEntered)
                {
                    //Backspace
                    if (event.text.unicode == '\b')
                    {
                        if (!playerName.empty())
                        {
                            playerName.pop_back();
                        }
                    }
                    //Alphabet Check
                    else if (isalpha(static_cast<char>(event.text.unicode)) && playerName.size() < 10)
                    {
                        char input = static_cast<char>(event.text.unicode);

                        if (playerName.empty())
                        {
                            playerName += toupper(input);
                        }
                        else
                        {
                            playerName += tolower(input);
                        }
                    }

                    inputText.setString(playerName);
                    setText(inputText, width / 2.0f, height / 2.0f - 25);
                }
                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Enter)) {
                    if (!playerName.empty())
                    {
                        welcomeWindow.close();
                        //GameWindow Opens
                    }
                }
                if (!playerName.empty())
                {
                    sf::FloatRect bounds = inputText.getLocalBounds();
                    cursor.setPosition(inputText.getPosition().x + bounds.width / 2.0f + 2, inputText.getPosition().y);
                }
                else
                {
                    setText(cursor, width / 2.0f, inputText.getPosition().y);
                }
            }


            welcomeWindow.clear();
            welcomeWindow.draw(background);
            welcomeWindow.draw(welcomeText);
            welcomeWindow.draw(promptText);
            welcomeWindow.draw(inputText);
            welcomeWindow.draw(palmTree);
            welcomeWindow.draw(money);
            welcomeWindow.draw(ferrisWheel);
            if (showCursor)
            {
                welcomeWindow.draw(cursor);
            }
            welcomeWindow.display();
        }
    }
};

int main() 
{
    WelcomeWindow ww;

    ww.launchWelcomeWindow();

    return 0;
}
