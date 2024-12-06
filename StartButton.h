#ifndef STARTBUTTON_H  
#define STARTBUTTON_H  

#include <SFML/Graphics.hpp>  

class StartButton {
private:
    sf::RectangleShape button;
    sf::Text buttonText;
    bool isStarted;
    bool isDisabled;

public:
    StartButton(float x, float y, float width, float height, sf::Font& font);
    void draw(sf::RenderWindow& window);
    bool isClicked(int mouseX, int mouseY);
    void startSimulation();
    void pauseSimulation();
    void disableButton();
    bool getIsStarted() const;
    bool getIsDisabled() const;
};

#endif // STARTBUTTON_H
