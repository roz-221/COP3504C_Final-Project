#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <ios>
#include <fstream>
#include "main.cpp"

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
        std::ifstream file("leaderboard.txt");
        std::vector<Player> players;
        if (file.is_open()){
            std::string line;
            while(std::getline(file, line)){
                unsigned int time = std::stoi(line);
                std::getline(file, line);
                std::string name = line;
                players.push_back(Player(time, name));
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
