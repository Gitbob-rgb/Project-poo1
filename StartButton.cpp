#include "StartButton.h"  

StartButton::StartButton(float x, float y, float width, float height, sf::Font& font)
    : isStarted(false), isDisabled(false) {
    button.setPosition(x, y);
    button.setSize(sf::Vector2f(width, height));
    button.setFillColor(sf::Color(23, 170, 65));

    buttonText.setFont(font);
    buttonText.setString("Démarrer");
    buttonText.setCharacterSize(16);
    buttonText.setFillColor(sf::Color::Black);
    buttonText.setPosition(x + 10, y + 5);
}

void StartButton::draw(sf::RenderWindow& window) {
    window.draw(button);
    window.draw(buttonText);
}

bool StartButton::isClicked(int mouseX, int mouseY) {
    return button.getGlobalBounds().contains(mouseX, mouseY);
}

void StartButton::startSimulation() {
    isStarted = true;
    buttonText.setString("Pause");
    button.setFillColor(sf::Color(100, 50, 50));
}

void StartButton::pauseSimulation() {
    isStarted = false;
    buttonText.setString("Reprendre");
    button.setFillColor(sf::Color(31, 144, 197));
}

void StartButton::disableButton() {
    isDisabled = true;
    buttonText.setString("Nombre d'itérations max atteint");
    button.setFillColor(sf::Color(166, 77, 255));
}

bool StartButton::getIsStarted() const {
    return isStarted;
}

bool StartButton::getIsDisabled() const {
    return isDisabled;
}