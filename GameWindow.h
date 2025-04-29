#include <vector>
#include "building.h"

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

        sf::RenderWindow gameWindow(sf::VideoMode({width, height}), "Game Window");
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
