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
    Player()
    {
        time = 0;
        name = "";
    }

    Player(std::string name, unsigned int time)
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
    unsigned int building_count;
    float original_building_price;
    float current_building_price;
    sf::Sprite building_sprite;
    sf::Texture building_texture;
    int earn_rate;

public:
    Building() : building_count(0), original_building_price(0), earn_rate(0) {}

    Building(std::string name) {
        this->name = name;
    }

    void setAllPrice()
    {
        if (name == "concessions")
        {
            original_building_price = 50;
            earn_rate = 10;
        }

        else if (name == "bull")
        {
            original_building_price = 400;
            earn_rate = 100;
        }

        else if (name == "coaster")
        {
            original_building_price = 2500;
            earn_rate = 250;
        }

        else if (name == "ferriswheel")
        {
            original_building_price = 15000;
            earn_rate = 1500;
        }

        else if (name == "teacups")
        {
            original_building_price = 100000;
            earn_rate = 8000;
        }

        else if (name == "bumper cars")
        {
            original_building_price = 500000;
            earn_rate = 40000;
        }

        else if (name == "gokarts")
        {
            original_building_price = 2500000;
            earn_rate = 200000;
        }

        else if (name == "droptower")
        {
            original_building_price = 15000000;
            earn_rate = 1500000;
        }
    }

    int purchaseBuilding() {
        current_building_price = original_building_price;
        building_count += 1;
        current_building_price *= 1.08;
        return (current_building_price / 1.08);
    }

    int getEarnRate() {
        return earn_rate;
    }
    int getBuildingCount() {
        return building_count;
    }
    int getBuildingPrice() {
        return current_building_price;
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
        original_building_price = price;
    }
    void setBuildingSprite(sf::Sprite sprite) {
        building_sprite = sprite;
    }

    void setBuildingTexture()
    {
        if (!building_texture.loadFromFile("images/" + name + ".png"))
        {
            std::cerr << "Failed to load hidden tile!" << std::endl;
        }
        building_sprite.setTexture(building_texture);
        building_sprite.setTextureRect(sf::IntRect(0, 0, 200, 200));
    }
};

struct Leaderboard{
    unsigned int width;
    unsigned int height;
    sf::Font font;
    std::vector<Player> players;

    Leaderboard(){
        width = 600;
        height = 800;
        if (!font.loadFromFile("font.ttf"))
        {
            std::cout << "Failed to open font file!" << std::endl;
        }
        std::ifstream file("leaderboard.txt");
        std::vector<Player> players;
        if (file.is_open()){
            std::string line;
            while(std::getline(file, line)){
                unsigned int time = std::stoi(line);
                std::getline(file, line);
                std::string name = line;
                players.push_back(Player(name, time));
            }
        }
        int n = players.size();
        for(int i = 0; i < n - 1; i++){
            for (int j = 0; j < n - i - 1; j++){
                if (players.at(j).getTime() > players.at(j+1).getTime()){
                    Player temp = players[j];
                    players[j] = players[j+1];
                    players[j+1] = temp;
                }
            }
        }
    }

    void launchLeaderboard(){
        sf::RenderWindow leaderBoardWindow(sf::VideoMode({ width, height }), "Welcome", sf::Style::Default);
        while(leaderBoardWindow.isOpen()){
            sf::Event event;
            while(leaderBoardWindow.pollEvent(event)){
                if(event.type == sf::Event::Closed){
                    leaderBoardWindow.close();
                    exit(0);
                }

                leaderBoardWindow.setFramerateLimit(60);

                //draw background
                sf::RectangleShape background(sf::Vector2f(width, height));
                background.setFillColor(sf::Color::Blue);

                //create title text
                sf::Text mainText("User Leaderboard", font);
                mainText.setPosition(sf::Vector2f(width/4, 0));
                mainText.setColor(sf::Color::Black);

                leaderBoardWindow.draw(background);
                //draw player list
                for(int i = 0; i < players.size(); i++){
                    std::cout << players.at(i).getName();
                    sf::Text playerText((players.at(i).getName() + " : " + std::to_string(players.at(i).getTime())) + " seconds", font);
                    playerText.setColor(sf::Color::Black);
                    sf::Vector2f center = playerText.getLocalBounds().getSize() / 2.f;
                    playerText.setOrigin(center.x, center.y);
                    playerText.setPosition(sf::Vector2f(leaderBoardWindow.getSize().x / 2.f, 50 + (i * 50))) ;
                    leaderBoardWindow.draw(playerText);
                }
                leaderBoardWindow.draw(mainText);
                leaderBoardWindow.display();
            }
        }
    }

    void writeStats(std::string name, unsigned int time){
        std::ofstream log("leaderboard.txt", std::ios_base::app | std::ios_base::out);
        log << time << "\n" << name;
    }
};


class GameWindow {
    float balance;
    sf::Sprite avatar; // Winning & Normal

    // Buttons
    bool isPaused;
    unsigned int timeElapsed = 0;
    sf::Time pausedTime;
    sf::Time pauseStartTime;
    sf::Clock gameClock;
    sf::Sprite pausePlayButton;
    sf::Texture pauseTexture;
    sf::Texture playTexture;

    sf::Sprite reset;
    sf::Texture resetTexture;

    sf::Sprite leaderboard;
    sf::Texture leaderboardTexture;
    Leaderboard lb;

    sf::Sprite upgrade;
    sf::Texture upgradeTexture;

    std::vector<Building> buildings;
    unsigned int height;
    unsigned int width;
    
    bool gameWon;
    Player p1;

public:
    GameWindow() : balance(50), width(1500), height(1200) {}
    
    void loadTextures()
    {

    }

    void handleClick(int x, int y, sf::Mouse::Button){

    }
  
    void togglePause() 
    {
        isPaused = !isPaused;

        if (isPaused) {
            pauseStartTime = gameClock.getElapsedTime();
            pausePlayButton.setTexture(playTexture);
        }
        else {
            pausedTime += gameClock.getElapsedTime() - pauseStartTime;
            pausePlayButton.setTexture(pauseTexture);
        }
    }
    void toggleReset() 
    {
        gameClock.restart();

        balance = 50;

        for (size_t i = 0; i < buildings.size(); i++)
        {
            buildings[i].setBuildingCount(0);
        }
    }

    void toggleLeaderboard() 
    {
        lb.players.push_back(p1);
        lb.launchLeaderboard();
    }
    
    void run(std::string name) {
        sf::Font font;
        if (!font.loadFromFile("font.ttf")) {
            std::cout << "Failed to read font file." << std::endl;
            return;
        }

        sf::RenderWindow gameWindow(sf::VideoMode({ width, height }), "Game Window");
        sf::Text title(name + "'s Tycoon", font, 30);
        title.setColor(sf::Color::Black);
        sf::Vector2f center = title.getLocalBounds().getSize() / 2.f;
        title.setOrigin(center.x, center.y);
        title.setPosition(sf::Vector2f(gameWindow.getSize().x / 2.f, 10));

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
            gameWindow.clear(sf::Color::Blue);
            sf::Texture money_background;
            money_background.loadFromFile("images/background_screen.png");
            sf::Sprite bg(money_background);
            gameWindow.draw(bg);

            //draw title
            gameWindow.draw(title);

            //draw buildings 
            for (size_t i = 0; i < buildings.size(); ++i) {
                gameWindow.draw(buildings.at(i).getBuildingSprite());
            }
            gameWindow.display();

        }
    }
};

class WelcomeWindow
{
private:
    unsigned int width;
    unsigned int height;
    sf::Font font;
    Player p;

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

    std::string launchWelcomeWindow()
    {
        //Create Welcome Window
        sf::RenderWindow welcomeWindow(sf::VideoMode({ width, height }), "Welcome", sf::Style::Default);
        welcomeWindow.setFramerateLimit(60);

        //Set Background
        sf::RectangleShape background(sf::Vector2f(width, height));
        background.setFillColor(sf::Color::Blue);

        sf::Text welcomeText("Welcome to Tycoon Simulator!", font, 24);
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
        return playerName;
    }
};

int main()
{
    WelcomeWindow ww;

    std::string userName = ww.launchWelcomeWindow();

    GameWindow gw;
    gw.run(userName);

    return 0;
}
