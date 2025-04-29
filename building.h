#include <SFML/Graphics.hpp>
#include <string>

#ifndef BUILDING_H
#define BUILDING_H

class Building {
  std::string name;
  int building_count;
  int building_price;
  sf::Sprite building_sprite;
  sf::Texture building_texture;
  int earn_rate;
  bool unlocked;

  public:
    Building(): building_count(0), building_price(0), earn_rate(0), unlocked(false) {}

    Building(int building_count, int building_price, int earn_rate, sf::Sprite sprite) {
      this->building_count = building_count;
      this->building_price = building_price;
      this->earn_rate = earn_rate;
      this->building_sprite = sprite;
    }

    int purchaseBuilding() {
      int original_price = building_price;
      building_count +=1;
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

#endif //BUILDING_H
