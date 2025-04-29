#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include <random>
#include <cmath>
#include <vector>

static void setText(sf::Text& text, float x, float y)
{
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

class Player
{
private:
    unsigned int time;
    std::string name;
public:
    User()
    {
        time = 0;
        name = "";
    }

    Player(unsigned int time, std::string name)
    {
        this->time = time;
        this->name = name;
    }

    std::string getName()
    {
        return name;
    }

    int getTime()
    {
        return time;
    }

    void setTime(int time)
    {
        this->time = time;
    }

    void setName(std::string name)
    {
        this->name = name;
    }
};

class Building {
    std::string name;
    int building_count;
    int building_price;
    sf::Sprite building_sprite;
    sf::Texture building_texture
        int earn_rate;
    bool unlocked;

public:
    Building() : building_count(0), building_price(0), earn_rate(0), unlocked(false) {}

    Building(int building_count, int building_price, int earn_rate, sf::Sprite sprite) {
        this->building_count = building_count;
        this->building_price = building_price;
        this->earn_rate = earn_rate;
        this->building_sprite = sprite;
    }

    int purchaseBuilding() {
        int original_price = building_price;
        building_count += 1;
        building_price *= 1.08;
        return original_price;
    }

    int getEarnRate() {
        return earn_rate;
    }
    int getBuildingCount() {
        return building_count;
    }
    int getBuildingPrice() {
        return building_price;
    }
    int getUnlocked() {
        return unlocked;
    }
    std::string getName() {
        return name;
    }
    sf::Sprite getBuildingSprite() {
        return building_sprite;
    }
    void setEarnRate(int rate) {
        earn_rate = rate;
    }
    void setBuildingCount(int count) {
        building_count = count;
    }
    void setBuildingPrice(int price) {
        building_price = price;
    }
    void setBuildingSprite(sf::Sprite sprite) {
        building_sprite = sprite;
    }

    void setBuildingTexture()
    {
        if (!building_texture.loadFromFile("images/" + name + ".png"))
        {
            std::cerr << "Failed to load hidden tile!" << std::endl;
            return false;
        }
        building_sprite.setTexture(building_texture);
        building_sprite.setTextureRect(sf::IntRect(0, 0, 200, 200))
    }
};

class GameWindow {
    float balance;
    sf::Sprite avatar; // Winning & Normal

    // Buttons
    sf::Sprite pause;
    sf::Sprite reset;
    sf::Sprite leaderboard;
    sf::Sprite upgrade;

    std::vector<Building> buildings;
    int height;
    int width;
    bool paused;
    bool reset;

public:
    GameWindow() : balance(50), width(1500), height(1200), {}
        void loadTextures() {
        for (size_t i = 0; i < buildings.size(); ++i) {
            std::string filename = "images/";
            filename += buildings.at(i).getName();
            buildings.at(i).setTexture(filename);
        }
    }
    void togglePause() {
        if (paused) {

        }
    }
    void toggleReset() {
        // Set everything to default
        if (reset) {

        }
    }
    void toggleLeaderboard() {
        // load leaderboard
    }
    void handleClick(int x, int y, sf::Mouse::button button) {
        // IDK
    }
    void run() {
        sf::Font font;
        if (!font.loadFromFile("font.ttf")) {
            std::cout << "Failed to read font file." << std::endl;
            return;
        }

        sf::RenderWindow gameWindow(sf::VideoMode({ width, height }), "Game Window");
        sf::Text title(font, "Testing's Tycoon", 30);

        while (gameWindow.isOpen()) {
            sf::Event event;
            while (gameWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    gameWindow.close();
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    handleClick(event.mouseButton.x, event.mouseButton.y, event.mouseButton.button);
                }
            }
            // Change to money picture
            gameWindow.clear(sf::Color::White);

            gameWindow.draw(title);
            for (size_t i = 0; i < buildings.size(); ++i) {
                gameWindow.draw(buildings.at(i).getBuildingSprite());
            }

        }
    }
}

class WelcomeWindow
{
private:
    unsigned int width;
    unsigned int height;
    sf::Font font;
    Player p

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

            p.setName(playerName);
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
