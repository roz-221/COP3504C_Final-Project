#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#ifndef UPGRADES_H
#define UPGRADES_H

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
      UpgradeWindow() {
        width = 450;
        height = 300;
        multiplier_cost = 100;
        multiplier = 1;
        discount = 1;
        discount = false;
        gold = false;
          std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << multiplier;
        std::string str = ss.str();
        multiplier_string = "Current multiplier: " + str + "x";

        if (!font.loadFromFile("../files/font.ttf")) {
            std::cerr << "Failed to open font file!" << std::endl;
        }
     }


      void launchUpgradeWindow() {
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
              exit(0);
            }
            if (multiplier >= 2.0) {
              multiplierPurchaseText.setStyle(sf::Text::StrikeThrough);
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
              auto multiplierbuttonbounds = multiplierPurchase.getGlobalBounds();
              if (multiplierbuttonbounds.contains(sf::Mouse::getPosition(upgradeWindow).x, sf::Mouse::getPosition(upgradeWindow).y)) {
                if (multiplier < 2 /*= && user.getBalance > multiplier_cost =*/) {
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
                if (!discount /*= && user.getBalance() > 1000000 =*/) {
                  // user.setBalance(user.getBalance() - 1000000);
                  discount = true;
                  discountPurchaseText.setStyle(sf::Text::StrikeThrough);
                }
              }
              auto goldbuttonbounds = goldPurchase.getGlobalBounds();
              if (goldbuttonbounds.contains(sf::Mouse::getPosition(upgradeWindow).x, sf::Mouse::getPosition(upgradeWindow).y)) {
                if (!gold /*= && user.getBalance() > 1000000 =*/) {
                  // user.setBalance(user.getBalance() - 1000000);
                  gold = true;
                  goldPurchaseText.setStyle(sf::Text::StrikeThrough);
                }
              }
            }
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



      }
};

#endif //UPGRADES_H
