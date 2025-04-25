
#include <SFML/Graphics.hpp>

std::string formatName(const std::string& input) {
    std::string formatted = input;
    formatted[0] = std::toupper(formatted[0]);
    for (size_t i = 1; i < formatted.size(); ++i) {
        formatted[i] = std::tolower(formatted[i]);
    }
    return formatted;
}

int main() {

    int welcomeWindowWidth = 800;
    int welcomeWindowHeight = 600;

    sf::RenderWindow welcomeWindow(sf::VideoMode(welcomeWindowWidth, welcomeWindowHeight), "Welcome", sf::Style::Close);

    sf::Font font;
    font.loadFromFile("../files/font.ttf");

    sf::Text welcomeText("Welcome to (game_name)!", font, 24);
    welcomeText.setPosition((welcomeWindow.getSize().x / 2) - (welcomeText.getLocalBounds().width / 2), welcomeWindow.getSize().y / 2 - 200);
    welcomeText.setFillColor(sf::Color::White);
    welcomeText.setStyle(sf::Text::Underlined | sf::Text::Bold);


    sf::Text promptText("Please enter the name of your tycoon:", font, 20);
    promptText.setPosition((welcomeWindowWidth / 2) - (promptText.getLocalBounds().width / 2), (welcomeWindowHeight / 2) - 75);
    promptText.setFillColor(sf::Color::White);
    promptText.setStyle(sf::Text::Bold);

    sf::Text userInput("|", font, 18);
    userInput.setPosition((welcomeWindowWidth / 2) - (userInput.getLocalBounds().width / 2), (welcomeWindowHeight / 2) - 45);
    userInput.setFillColor(sf::Color::White);
    std::string inputText = "";
    std::string tycoonName = "";

    sf::Sprite palmTree;
    sf::Sprite money;
    sf::Sprite ferrisWheel;

    sf::Texture palmTreeTexture;
    sf::Texture moneyTexture;
    sf::Texture ferrisWheelTexture;

    palmTreeTexture.loadFromFile("../files/palmtree.png");
    palmTree.setTexture(palmTreeTexture);
    palmTree.setPosition(sf::Vector2f(50, 50));
    palmTree.setScale(.25f, .25f);

    moneyTexture.loadFromFile("../files/moneymoney.png");
    money.setTexture(moneyTexture);
    money.setPosition(sf::Vector2f(640, 70));
    money.setScale(.05f, .05f);

    ferrisWheelTexture.loadFromFile("../files/ferriswheel.png");
    ferrisWheel.setTexture(ferrisWheelTexture);
    ferrisWheel.setPosition(sf::Vector2f(300, 300));
    ferrisWheel.setScale(.4f, .4f);

    while(welcomeWindow.isOpen()) {
        sf::Event event;
        while(welcomeWindow.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                welcomeWindow.close();
                exit(0);
            }
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == 8) {
                    if (!inputText.empty()) {
                        inputText.pop_back();
                    }
                } else if ((std::isalpha(event.text.unicode) || event.text.unicode == ' ' )&& inputText.size() < 20) {
                    inputText += static_cast<char>(event.text.unicode);
                }
                userInput.setString(formatName(inputText) + "|");
                userInput.setPosition((welcomeWindowWidth / 2) - (userInput.getLocalBounds().width / 2), (welcomeWindowHeight / 2) - 45);
            }
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Enter)) {
                if (!inputText.empty()) {
                    tycoonName = inputText;
                    welcomeWindow.close();
                }
            }
        }


        welcomeWindow.clear(sf::Color(10, 172, 96));
        welcomeWindow.draw(welcomeText);
        welcomeWindow.draw(promptText);
        welcomeWindow.draw(userInput);
        welcomeWindow.draw(palmTree);
        welcomeWindow.draw(money);
        welcomeWindow.draw(ferrisWheel);
        welcomeWindow.display();
    }


  return 0;
}
