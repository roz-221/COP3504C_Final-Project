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
#include <sstream>
#include <iomanip>

class UpgradeWindow {
    int multiplier_cost;
    float multiplier;
    bool discount;
    bool gold;
    unsigned int width;
    unsigned int height;
    sf::Font font;
    std::string multiplier_string;

    public:

      void setDiscount(bool other) {
          this->discount = other;
      }
      void resetUpgradeWindow() {
          multiplier_cost = 100;
          multiplier = 1.0;
          discount = false;
          gold = false;
          std::stringstream ss;
          ss << std::fixed << std::setprecision(2) << multiplier;
          std::string str = ss.str();
          multiplier_string = "Current multiplier: " + str + "x";
      }    
      float getMultiplier() {
          return this->multiplier;
      }

      bool getDiscount() {
          return this->discount;
      }

      bool getGold() {
          return this->gold;
      }

      UpgradeWindow() {
        width = 450;
        height = 300;
        multiplier_cost = 100;
        multiplier = 1;
        discount = false;
        gold = false;
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << multiplier;
        std::string str = ss.str();
        multiplier_string = "Current multiplier: " + str + "x";

        if (!font.loadFromFile("font.ttf")) {
            std::cerr << "Failed to open font file!" << std::endl;
        }
     }


      unsigned int launchUpgradeWindow(unsigned int balance) {
        int money_spent = 0;
        sf::Color textColor = sf::Color(10, 172, 96);
        sf::RenderWindow upgradeWindow(sf::VideoMode(width, height), "Upgrades", sf::Style::Default);
        upgradeWindow.setFramerateLimit(60);

        sf::RectangleShape background(sf::Vector2f(width, height));
        background.setFillColor(sf::Color::Blue);

        sf::Text headerText("Upgrades", font, 20);
        headerText.setStyle(sf::Text::Bold | sf::Text::Underlined);
        sf::FloatRect headerTextRect = headerText.getLocalBounds();
        headerText.setOrigin(headerTextRect.left + headerTextRect.width / 2.0f, headerTextRect.top + headerTextRect.height / 2.0f);
        headerText.setPosition(sf::Vector2f(width / 2, 35));
        headerText.setFillColor(sf::Color::White);

        sf::RectangleShape multiplierPurchase(sf::Vector2f(130, 30));
        multiplierPurchase.setFillColor(sf::Color::White);
        multiplierPurchase.setOutlineColor(sf::Color::Black);
        multiplierPurchase.setOutlineThickness(3.0f);
        multiplierPurchase.setPosition(sf::Vector2f(275, 100));
        sf::Text multiplierPurchaseText("$" + std::to_string(multiplier_cost), font, 15);
        sf::FloatRect multiplierPurchaseTextRect = multiplierPurchaseText.getLocalBounds();
        multiplierPurchaseText.setOrigin(multiplierPurchaseTextRect.left + multiplierPurchaseTextRect.width / 2.0f, multiplierPurchaseTextRect.top + multiplierPurchaseTextRect.height / 2.0f);
        multiplierPurchaseText.setPosition(sf::Vector2f(340, 115));
        multiplierPurchaseText.setFillColor(textColor);
        sf::Text multiplierText(multiplier_string, font, 15);
        multiplierText.setFillColor(sf::Color::White);
        multiplierText.setPosition(sf::Vector2f(35, 105));


        sf::RectangleShape discountPurchase(sf::Vector2f(130, 30));
        discountPurchase.setFillColor(sf::Color::White);
        discountPurchase.setOutlineColor(sf::Color::Black);
        discountPurchase.setOutlineThickness(3.0f);
        discountPurchase.setPosition(sf::Vector2f(275, 160));
        sf::Text discountPurchaseText("$1000000", font, 15);
        sf::FloatRect discountPurchaseTextRect = discountPurchaseText.getLocalBounds();
        discountPurchaseText.setOrigin(discountPurchaseTextRect.left + discountPurchaseTextRect.width / 2.0f, discountPurchaseTextRect.top + discountPurchaseTextRect.height / 2.0f);
        discountPurchaseText.setPosition(sf::Vector2f(340, 175));
        discountPurchaseText.setFillColor(textColor);
        sf::Text discountText("10% Discount!", font, 15);
        discountText.setFillColor(sf::Color::White);
        discountText.setPosition(sf::Vector2f(90, 165));

        sf::RectangleShape goldPurchase(sf::Vector2f(130, 30));
        goldPurchase.setFillColor(sf::Color::White);
        goldPurchase.setOutlineColor(sf::Color::Black);
        goldPurchase.setOutlineThickness(3.0f);
        goldPurchase.setPosition(sf::Vector2f(275, 220));
        sf::Text goldPurchaseText("$1000000", font, 15);
        sf::FloatRect goldPurchaseTextRect = goldPurchaseText.getLocalBounds();
        goldPurchaseText.setOrigin(goldPurchaseTextRect.left + goldPurchaseTextRect.width / 2.0f, goldPurchaseTextRect.top + goldPurchaseTextRect.height / 2.0f);
        goldPurchaseText.setPosition(sf::Vector2f(340, 235));
        goldPurchaseText.setFillColor(textColor);
        sf::Text goldText("Gold Background!", font, 15);
        goldText.setFillColor(sf::Color::White);
        goldText.setPosition(sf::Vector2f(85, 225));

        while (upgradeWindow.isOpen()) {
          sf::Event event;
          while (upgradeWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
              upgradeWindow.close();
            }
            if (multiplier >= 2.0) {
              multiplierPurchaseText.setStyle(sf::Text::StrikeThrough);
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
              auto multiplierbuttonbounds = multiplierPurchase.getGlobalBounds();
              if (multiplierbuttonbounds.contains(sf::Mouse::getPosition(upgradeWindow).x, sf::Mouse::getPosition(upgradeWindow).y)) {
                if (multiplier < 2 && (balance - money_spent) >= multiplier_cost) {
                  money_spent += multiplier_cost;
                  // user.setBalance(user.getBalance() - multiplier_cost);
                  multiplier += .1;
                  multiplier_cost *= 4;
                  std::stringstream ss;
                  ss << std::fixed << std::setprecision(2) << multiplier;
                  std::string str = ss.str();
                  multiplier_string = "Current multiplier: " + str + "x";
                  multiplierText.setString(multiplier_string);
                  multiplierPurchaseText.setString("$" + std::to_string(multiplier_cost));
                  multiplierPurchaseTextRect = multiplierPurchaseText.getLocalBounds();
                  multiplierPurchaseText.setOrigin(multiplierPurchaseTextRect.left + multiplierPurchaseTextRect.width / 2.0f, multiplierPurchaseTextRect.top + multiplierPurchaseTextRect.height / 2.0f);
                  multiplierPurchaseText.setPosition(sf::Vector2f(340, 115));
                }
              }
              auto discountbuttonbounds = discountPurchase.getGlobalBounds();
              if (discountbuttonbounds.contains(sf::Mouse::getPosition(upgradeWindow).x, sf::Mouse::getPosition(upgradeWindow).y)) {
                if (!discount && (balance - money_spent) >= 1000000) {
                  money_spent += 1000000;
                  // user.setBalance(user.getBalance() - 1000000);
                  discount = true;
                  discountPurchaseText.setStyle(sf::Text::StrikeThrough);
                }
              }
              auto goldbuttonbounds = goldPurchase.getGlobalBounds();
              if (goldbuttonbounds.contains(sf::Mouse::getPosition(upgradeWindow).x, sf::Mouse::getPosition(upgradeWindow).y)) {
                if (!gold && (balance - money_spent) >= 1000000) {
                  money_spent += 1000000;
                  // user.setBalance(user.getBalance() - 1000000);
                  gold = true;
                  goldPurchaseText.setStyle(sf::Text::StrikeThrough);
                }
              }
            }
          }

          if (gold) {
              goldPurchaseText.setStyle(sf::Text::StrikeThrough);
          }
          if (discount) {
              discountPurchaseText.setStyle(sf::Text::StrikeThrough);
          }
            
          upgradeWindow.clear();
          upgradeWindow.draw(background);
          upgradeWindow.draw(multiplierPurchase);
          upgradeWindow.draw(multiplierPurchaseText);
          upgradeWindow.draw(multiplierText);
          upgradeWindow.draw(discountPurchase);
          upgradeWindow.draw(discountPurchaseText);
          upgradeWindow.draw(discountText);
          upgradeWindow.draw(goldPurchase);
          upgradeWindow.draw(goldPurchaseText);
          upgradeWindow.draw(goldText);
          upgradeWindow.draw(headerText);
          upgradeWindow.display();
        }


        return money_spent;
      }
};

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
    sf::Text buildingCount;
    sf::RectangleShape countRectangle;

    int original_building_price;
    int current_building_price;
    sf::Text currentBuildingPrice;
    sf::RectangleShape buildingPriceButton;

    sf::Sprite building_sprite;
    sf::Texture building_texture;
    sf::RectangleShape outline_rectangle;

    int earn_rate;
    sf::Text earnRate;

    sf::Font font;

    bool discount;

public:
    Building() : building_count(0), original_building_price(0), earn_rate(0), discount(false)
    {
        if (!font.loadFromFile("font.ttf"))
        {
            std::cerr << "Failed to open font file!" << std::endl;
        }
    }

    Building(std::string name) {
        this->name = name;
    }

    void setName(std::string name)
    {
        this->name = name;
    }
    void setDiscount(bool discount) {
        this->discount = discount;
    }
    void setCurrentPrice(int curprice) {
        this->current_building_price = curprice;
    }


    void setAllPriceAndText()
    {
        if (name == "concessions")
        {
            
            original_building_price = 50;
            if (current_building_price == 0) {
                current_building_price = original_building_price;
            }
            if (discount) {
                current_building_price *= .9;
                discount = false;
            }
            earn_rate = 10;
        }

        else if (name == "bull")
        {
            original_building_price = 400;
            if (current_building_price == 0) {
                current_building_price = original_building_price;
            }
            if (discount) {
                current_building_price *= .9;
                discount = false;
            }
            earn_rate = 100;
        }

        else if (name == "coaster")
        {
            original_building_price = 2500;
            if (current_building_price == 0) {
                current_building_price = original_building_price;
            }
            if (discount) {
                current_building_price *= .9;
                discount = false;
            }
            earn_rate = 250;
        }

        else if (name == "ferriswheel")
        {
            original_building_price = 15000;
            if (current_building_price == 0) {
                current_building_price = original_building_price;
            }
            if (discount) {
                current_building_price *= .9;
                discount = false;
            }
            earn_rate = 1500;
        }

        else if (name == "teacups")
        {
            original_building_price = 100000;
            if (current_building_price == 0) {
                current_building_price = original_building_price;
            }
            if (discount) {
                current_building_price *= .9;
                discount = false;
            }
            earn_rate = 8000;
        }

        else if (name == "bumper cars")
        {
            original_building_price = 500000;
            if (current_building_price == 0) {
                current_building_price = original_building_price;
            }
            if (discount) {
                current_building_price *= .9;
                discount = false;
            }
            earn_rate = 40000;
        }

        else if (name == "gokarts")
        {
            original_building_price = 2500000;
            if (current_building_price == 0) {
                current_building_price = original_building_price;
            }
            if (discount) {
                current_building_price *= .9;
                discount = false;
            }
            earn_rate = 200000;
        }

        else if (name == "droptower")
        {
            original_building_price = 15000000;
            if (current_building_price == 0) {
                current_building_price = original_building_price;
            }
            if (discount) {
                current_building_price *= .9;
                discount = false;
            }
            earn_rate = 1500000;
        }
    }

    int purchaseBuilding() {
        currentBuildingPrice = sf::Text("$" + std::to_string(current_building_price), font, 10);
        buildingCount = sf::Text(std::to_string(building_count), font, 10);
        earnRate = sf::Text(std::to_string(earn_rate), font, 10);
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
    sf::RectangleShape getOutlineRectangle() {
        return outline_rectangle;
    }
    sf::RectangleShape getBuildingPriceButton() {
        return buildingPriceButton;
    }
    sf::Text getBuildingPriceText() {
        return currentBuildingPrice;
    }
    sf::RectangleShape getCountRectangle() {
        return countRectangle;
    }
    sf::Text getCountText() {
        return buildingCount;
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
    // sf::Text buildingCount;
    //sf::RectangleShape countRectangle;

    void setBuildingTexture()
    {
        if (!building_texture.loadFromFile("images/" + name + ".png"))
        {
            std::cerr << "Failed to load " + name + " image!" << std::endl;
        }

        building_sprite.setTexture(building_texture);
        building_sprite.setScale(200.0f/(building_texture.getSize().x), 200.0f/(building_texture.getSize().y));
        building_sprite.setPosition(100,100);
        outline_rectangle.setSize(sf::Vector2f(200, 200));
        outline_rectangle.setOutlineColor(sf::Color::Black);
        outline_rectangle.setOutlineThickness(3.0f);
        buildingPriceButton.setSize(sf::Vector2f(150, 50));
        buildingPriceButton.setOutlineColor(sf::Color::Black);
        buildingPriceButton.setOutlineThickness(3.0f);
        currentBuildingPrice.setString("$" + std::to_string(current_building_price));
        sf::FloatRect costTextRect = currentBuildingPrice.getLocalBounds();
        currentBuildingPrice.setOrigin(costTextRect.left + costTextRect.width / 2.0f, costTextRect.top + costTextRect.height / 2.0f);
        currentBuildingPrice.setFont(font);
        currentBuildingPrice.setCharacterSize(15);
        currentBuildingPrice.setFillColor(sf::Color(0, 100, 0));
        countRectangle.setSize(sf::Vector2f(50, 50));
        countRectangle.setOutlineColor(sf::Color::Black);
        countRectangle.setOutlineThickness(3.0f);
        buildingCount.setString(std::to_string(building_count) + "x");
        sf::FloatRect countTextRect = buildingCount.getLocalBounds();
        buildingCount.setOrigin(countTextRect.left + countTextRect.width / 2.0f, countTextRect.top + countTextRect.height / 2.0f);
        buildingCount.setFont(font);
        buildingCount.setCharacterSize(18);
        buildingCount.setFillColor(sf::Color::Black);

        if (name == "concessions") {
            building_sprite.setPosition(sf::Vector2f(275, 200));
            outline_rectangle.setPosition(sf::Vector2f(275, 200));
            buildingPriceButton.setPosition(sf::Vector2f(275, 403));
            currentBuildingPrice.setPosition(sf::Vector2f(350, 428));
            countRectangle.setPosition(sf::Vector2f(425, 403));
            buildingCount.setPosition(sf::Vector2f(450, 428));
        } else if (name == "bull") {
            building_sprite.setPosition(sf::Vector2f(275, 600));
            outline_rectangle.setPosition(sf::Vector2f(275, 600));
            buildingPriceButton.setPosition(sf::Vector2f(275, 803));
            currentBuildingPrice.setPosition(sf::Vector2f(350, 828));
            countRectangle.setPosition(sf::Vector2f(425, 803));
            buildingCount.setPosition(sf::Vector2f(450, 828));
        } else if (name == "coaster") {
            building_sprite.setPosition(sf::Vector2f(525, 200));
            outline_rectangle.setPosition(sf::Vector2f(525, 200));
            buildingPriceButton.setPosition(sf::Vector2f(525, 403));
            currentBuildingPrice.setPosition(sf::Vector2f(600, 428));
            countRectangle.setPosition(sf::Vector2f(675, 403));
            buildingCount.setPosition(sf::Vector2f(700, 428));
        } else if (name == "ferriswheel") {
            building_sprite.setPosition(sf::Vector2f(525, 600));
            outline_rectangle.setPosition(sf::Vector2f(525, 600));
            buildingPriceButton.setPosition(sf::Vector2f(525, 803));
            currentBuildingPrice.setPosition(sf::Vector2f(600, 828));
            countRectangle.setPosition(sf::Vector2f(675, 803));
            buildingCount.setPosition(sf::Vector2f(700, 828));
        } else if (name == "teacups") {
            building_sprite.setPosition(sf::Vector2f(775, 200));
            outline_rectangle.setPosition(sf::Vector2f(775, 200));
            buildingPriceButton.setPosition(sf::Vector2f(775, 403));
            currentBuildingPrice.setPosition(sf::Vector2f(850, 428));
            countRectangle.setPosition(sf::Vector2f(925, 403));
            buildingCount.setPosition(sf::Vector2f(950, 428));
        } else if (name == "bumper cars") {
            building_sprite.setPosition(sf::Vector2f(775, 600));
            outline_rectangle.setPosition(sf::Vector2f(775, 600));
            buildingPriceButton.setPosition(sf::Vector2f(775, 803));
            currentBuildingPrice.setPosition(sf::Vector2f(850, 828));
            countRectangle.setPosition(sf::Vector2f(925, 803));
            buildingCount.setPosition(sf::Vector2f(950, 828));
        } else if (name == "gokarts") {
            building_sprite.setPosition(sf::Vector2f(1025, 200));
            outline_rectangle.setPosition(sf::Vector2f(1025, 200));
            buildingPriceButton.setPosition(sf::Vector2f(1025, 403));
            currentBuildingPrice.setPosition(sf::Vector2f(1100, 428));
            countRectangle.setPosition(sf::Vector2f(1175, 403));
            buildingCount.setPosition(sf::Vector2f(1200, 428));
        } else if (name == "droptower") {
            building_sprite.setPosition(sf::Vector2f(1025, 600));
            outline_rectangle.setPosition(sf::Vector2f(1025, 600));
            buildingPriceButton.setPosition(sf::Vector2f(1025, 803));
            currentBuildingPrice.setPosition(sf::Vector2f(1100, 828));
            countRectangle.setPosition(sf::Vector2f(1175, 803));
            buildingCount.setPosition(sf::Vector2f(1200, 828));
        }
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
                }

                leaderBoardWindow.setFramerateLimit(60);

                //draw background
                sf::RectangleShape background(sf::Vector2f(width, height));
                background.setFillColor(sf::Color::Blue);

                //create title text
                sf::Text mainText("User Leaderboard", font);
                mainText.setPosition(sf::Vector2f(width/4, 0));
                mainText.setFillColor(sf::Color::Black);

                leaderBoardWindow.draw(background);
                //draw player list
                for(int i = 0; i < players.size(); i++){
                    sf::Text playerText((players.at(i).getName() + " : " + std::to_string(players.at(i).getTime())) + " seconds", font);
                    playerText.setFillColor(sf::Color::Black);
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
    unsigned int balance;
    sf::Text totalBalance;

    sf::Font font;

    sf::Texture digits;

    sf::Sprite avatar; // Winning & Normal
    sf::Texture avatarTexture;

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

    std::vector<Building> buildings = std::vector<Building>(8);
    unsigned int height;
    unsigned int width;
    UpgradeWindow uw;

    bool gameWon = false;
    Player p1;

    sf::Clock earningsClock;

public:
    GameWindow() : balance(50), width(1500), height(1000)
    {
        if (!font.loadFromFile("font.ttf"))
        {
            std::cerr << "Failed to open font file!" << std::endl;
        }
    }
    void wonGame() {
        if (balance >= 2000000000) {
            gameWon = true;
        }
    }
    void drawTimer(sf::RenderWindow& window)
    {
        if (!gameWon)
        {
            if (!isPaused)
            {
                timeElapsed = static_cast<int>((gameClock.getElapsedTime() - pausedTime).asSeconds());
            }
        }

        if (timeElapsed > 3599)
        {
            timeElapsed = 3599;
        }

        int minutes = timeElapsed / 60;
        int seconds = timeElapsed % 60;

        int mDigit1 = minutes / 10;
        int mDigit2 = minutes % 10;

        int sDigit1 = seconds / 10;
        int sDigit2 = seconds % 10;

        // Draw minutes
        sf::Sprite mDigit1Sprite(digits);
        mDigit1Sprite.setTextureRect(sf::IntRect(21 * mDigit1, 0, 21, 32));
        mDigit1Sprite.setPosition(width - 102, height - 50);
        window.draw(mDigit1Sprite);

        sf::Sprite mDigit2Sprite(digits);
        mDigit2Sprite.setTextureRect(sf::IntRect(21 * mDigit2, 0, 21, 32));
        mDigit2Sprite.setPosition(width - 81, height - 50);
        window.draw(mDigit2Sprite);

        // Draw seconds
        sf::Sprite sDigit1Sprite(digits);
        sDigit1Sprite.setTextureRect(sf::IntRect(21 * sDigit1, 0, 21, 32));
        sDigit1Sprite.setPosition(width - 55, height - 50);
        window.draw(sDigit1Sprite);

        sf::Sprite sDigit2Sprite(digits);
        sDigit2Sprite.setTextureRect(sf::IntRect(21 * sDigit2, 0, 21, 32));
        sDigit2Sprite.setPosition(width - 34, height - 50);
        window.draw(sDigit2Sprite);
    }

    void loadTextures()
    {
        if (!digits.loadFromFile("images/digits.png"))
        {
            std::cerr << "Failed to load digits!" << std::endl;
        }

        if (!avatarTexture.loadFromFile("images/avatar.png"))
        {
            std::cerr << "Failed to load avatar!" << std::endl;
        }

        avatar.setTexture(avatarTexture);
        avatar.setTextureRect(sf::IntRect(0, 55, 500, 500));
        avatar.setScale(100 / 400.0, 100 / 400.0);
        avatar.setPosition(0, 0);

        if (!pauseTexture.loadFromFile("images/pause.png"))
        {
            std::cerr << "Failed to load pause!" << std::endl;
        }

        if (!playTexture.loadFromFile("images/play.png"))
        {
            std::cerr << "Failed to load play!" << std::endl;
        }

        if (!resetTexture.loadFromFile("images/reset.png"))
        {
            std::cerr << "Failed to load reset!" << std::endl;
        }

        reset.setTexture(resetTexture);
        reset.setTextureRect(sf::IntRect(0, 0, 106, 106));
        reset.setScale(100 / 106.0, 100 / 106.0);
        reset.setPosition(1400, 0);

        if (!leaderboardTexture.loadFromFile("images/leaderboard.png"))
        {
            std::cerr << "Failed to load leaderboard!" << std::endl;
        }

        leaderboard.setTexture(leaderboardTexture);
        leaderboard.setTextureRect(sf::IntRect(0, 0, 64, 64));
        leaderboard.setScale(100 / 64.0, 100 / 64.0);
        leaderboard.setPosition(40, 860);

        buildings[0].setName("concessions");
        buildings[1].setName("bull");
        buildings[2].setName("coaster");
        buildings[3].setName("ferriswheel");
        buildings[4].setName("teacups");
        buildings[5].setName("bumper cars");
        buildings[6].setName("gokarts");
        buildings[7].setName("droptower");

        for (size_t i = 0; i < buildings.size(); i++)
        {
            buildings[i].setAllPriceAndText();
            buildings[i].setBuildingTexture();
        }
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
            buildings[i].setCurrentPrice(0);
        }
        uw.resetUpgradeWindow();
    }


    void toggleLeaderboard()
    {
        lb.players.push_back(p1);
        lb.launchLeaderboard();
    }

    void handleClick(sf::Vector2i mousePos)
    {
        if(upgrade.getGlobalBounds().contains(mousePos.x, mousePos.y)){
            int money_spent = uw.launchUpgradeWindow(balance);
            balance -= money_spent;
        }

        //reset check
        else if (reset.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            toggleReset();
        }

        //Leaderboard Check
        else if (leaderboard.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            toggleLeaderboard();
        }

        else if (pausePlayButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            togglePause();
        }

        else {
            for (size_t i = 0; i < buildings.size(); ++i) {
                if (buildings[i].getBuildingSprite().getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    if (balance >= buildings[i].getBuildingPrice()) {
                        balance -= buildings[i].purchaseBuilding();
                    }
                }
            }
        }
    }

    int getEarnings() {
        int total_earn_rate = 0;
        for (Building b : buildings) {
            total_earn_rate += (b.getEarnRate() * b.getBuildingCount());
        }
        total_earn_rate *= uw.getMultiplier();

        return total_earn_rate;
    }
    void updateEarnings() {
        float earningsTime = earningsClock.getElapsedTime().asSeconds();
        if (earningsTime >= 1.0f) {
            balance += getEarnings();
            earningsClock.restart();
        }
    }
    void run(std::string name) {
        p1 = Player(name, timeElapsed);
        sf::Font font;
        if (!font.loadFromFile("font.ttf")) {
            std::cout << "Failed to read font file." << std::endl;
            return;
        }
        sf::RenderWindow gameWindow(sf::VideoMode({ width, height }), "Game Window");
        sf::Text title(name + "'s Tycoon", font, 30);
        title.setFillColor(sf::Color::Black);
        sf::Vector2f center = title.getLocalBounds().getSize() / 2.f;
        title.setOrigin(center.x, center.y);
        title.setPosition(sf::Vector2f(gameWindow.getSize().x / 2.f, 15));

        bool discount_applied = false;

        while (gameWindow.isOpen()) {
            sf::Event event;
            while (gameWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    gameWindow.close();
                }
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(gameWindow);

                        handleClick(mousePos);
                    }
                }
            }
            // Change background to money picture or gold picture depending on upgrades
            if (!uw.getGold()) {
                gameWindow.clear(sf::Color::Blue);
                sf::Texture money_background;
                money_background.loadFromFile("images/background_screen.png");
                sf::Sprite bg(money_background);
                gameWindow.draw(bg);
            } else {
                gameWindow.clear(sf::Color::Blue);
                sf::Texture gold_background;
                gold_background.loadFromFile("images/goldbackground.png");
                sf::Sprite gold(gold_background);
                gold.setScale(1.5f, 1.5f);
                gameWindow.draw(gold);
            }

            if (uw.getDiscount() && !discount_applied) {
                for (int i = 0; i < buildings.size(); ++i) {
                    buildings[i].setDiscount(true);
                }
                discount_applied = true;
            }

            loadTextures();
            //draw title
            gameWindow.draw(title);
            //draw balance
            sf::Text balanceText("Balance: $" + std::to_string(balance), font);
            sf::Vector2f balanceCenter = balanceText.getLocalBounds().getSize() / 2.f;
            balanceText.setOrigin(balanceCenter);
            balanceText.setPosition(sf::Vector2f(title.getPosition().x + 400, 10));
            balanceText.setColor(sf::Color::Black);
            gameWindow.draw(balanceText);
            //draw buttons
            upgradeTexture.loadFromFile("images/upgradebutton.png");
            upgrade.setTexture(upgradeTexture);
            upgrade.setPosition(160, 850);
            upgrade.setScale(sf::Vector2f(0.2, 0.2));
            gameWindow.draw(upgrade);
            gameWindow.draw(leaderboard);
            gameWindow.draw(avatar);
            gameWindow.draw(pausePlayButton);
            gameWindow.draw(reset);
            gameWindow.draw(totalBalance);
            drawTimer(gameWindow);
            //draw buildings
            for (size_t i = 0; i < buildings.size(); ++i) {
                gameWindow.draw(buildings.at(i).getOutlineRectangle());
                gameWindow.draw(buildings.at(i).getBuildingSprite());
                gameWindow.draw(buildings.at(i).getBuildingPriceButton());
                gameWindow.draw(buildings.at(i).getBuildingPriceText());
                gameWindow.draw(buildings.at(i).getCountRectangle());
                gameWindow.draw(buildings.at(i).getCountText());
            }
            //Update Earnings
            updateEarnings();

            //Check if game won
            if (!gameWon) {
                wonGame();
            }
            if (gameWon) {
                p1.setTime(gameClock.getElapsedTime().asSeconds());
                std::cout << p1.getName() << " " << p1.getTime();
                lb.players.push_back(p1);
                toggleReset();
                gameWon = false;
                lb.launchLeaderboard();
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
