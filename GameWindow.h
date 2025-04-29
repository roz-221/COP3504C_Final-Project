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

    sf::Sprite backdrop;
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
        
        // Set Textures
        sf::Texture background;
        background.loadFromFile("images/background_screen.png")''
        backdrop.setTexture(background);
        
        sf::Texture pausebutton;
        pausebutton.loadFromFile("images/pause.png");
        pause.setTexture(pausebutton);

        sf::Texture resetbutton;
        resetbutton.loadFromFile("images/reset.png");
        reset.setTexture(resetbutton);

        buildings.loadTextures();

        // Set Positions
        pause.setPosition({200.f, 100.f});
        reset.setPosition({1200.f, 100.f});
        title.setPosition({700.f, 80.f});
        
        // Run Game Window
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

            // Draw Everything
            gameWindow.draw(backdrop);
            gameWindow.draw(title);
            gameWindow.draw(pause);
            gameWindow.draw(reset);

            sf::Vector2f topBuildingPosition(300.f, 200.f);
            for (size_t i = 0; i < ; i++) {
                sf::Sprite building = buildings.at(i).getBuildingSprite();
                building.setPosition(topBuildingPosition());
                gameWindow.draw(building);
                topBuildingPosition.x += 50.f;
            }

            sf::Vector2f bottomBuildingPosition(300.f, 600.f);
            for (size_t j = 4; j < buildings.size(); j++) {
                sf::Sprite building = buildings.at(j).getBuildingSprite();
                building.setPosition(topBuildingPosition());
                gameWindow.draw(building);
                bottomBuildingPosition.x += 50.f;
            }

            gameWindow.display();
        }
    }
}  
