#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>

struct Player{
    std::string name;
    std::chrono::duration<int> total_time;
    Player(std::string _name, std::chrono::duration<int> _total_time){
        name = _name;
        total_time = _total_time;
    }
};

struct Leaderboard{
    int width;
    int height;
    sf::Font font;
    std::vector<Player> players;

    Leaderboard(){
        width = 600;
        height = 800;
        if (!font.loadFromFile("font.ttf"))
        {
            std::cout << "Failed to open font file!" << std::endl;
        }
        players = {Player("Monish", std::chrono::seconds(5)), Player("Joe", std::chrono::seconds(6)), Player("Bill", std::chrono::seconds(7))};
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
                    std::cout << players.at(i).name;
                    sf::Text playerText((players.at(i).name + " : " + std::to_string(players.at(i).total_time.count())) + " minutes", font);
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
};
