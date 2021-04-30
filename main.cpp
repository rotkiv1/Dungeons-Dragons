#include <SFML/Graphics.hpp>
#include <iostream>

class LoadingScreen {
    public:

        LoadingScreen() : mWindow(sf::VideoMode(1000, 600), "D&D") {
            if (!textureBackground.loadFromFile("image.png")) {
                //error
            }
            if (!gameFont.loadFromFile("gamefont.otf")) {
                //error
            }

            gameText.setFont(gameFont);
            gameText.setPosition(420.f, 600.f);
            gameText.setString("Dungeons\n\t\t\t&\n  Dragons");
            gameText.setCharacterSize(60);
            gameText.setColor(sf::Color::White);

            beginButton.setFont(gameFont);
            beginButton.setPosition(420.f, 0.f);
            beginButton.setString("BEGIN");
            beginButton.setCharacterSize(60);
            beginButton.setColor(sf::Color::White);

            background.setTexture(textureBackground);
            background.setPosition(-150.f, -40.f);
            background.setScale(0.6, 0.6);

            std::cout << beginButton.getPosition().x;
        }

        ~LoadingScreen() = default;

        void run() {
            sf::Clock clock;
            sf::Time timeSinceLastUpdate = sf::Time::Zero;
            while (mWindow.isOpen()) {
                processEvents();
                timeSinceLastUpdate += clock.restart();
                while (timeSinceLastUpdate > TimePerFrame) {
                    timeSinceLastUpdate -= TimePerFrame;
                    processEvents();
                    update(TimePerFrame);

                }
                render();
            }
        }

    private:

        void processEvents() {
            sf::Event event;
            while (mWindow.pollEvent(event)) {
                switch (event.type) {
                    case sf::Event::MouseButtonPressed:
                        handlePlayerInput(event.key.code, true);
                        break;
                    case sf::Event::Closed:
                        mWindow.close();
                        break;
                }
            }
        }

        void handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
            if(isPressed)std:: cout <<5;
        }

        void update(sf::Time deltaTime) {
            onButton();
            updateGameText(deltaTime);
            updateButton(deltaTime);
        }

        void render() {
            mWindow.clear();
            mWindow.draw(background);
            mWindow.draw(gameText);
            mWindow.draw(beginButton);
            mWindow.display();
        }

        void onButton() {
            sf::Vector2i position = sf::Mouse::getPosition(mWindow);
            sf::Vector2f mousePosition = mWindow.mapPixelToCoords(position);
            if (mousePosition.x >= 420.f &&
                mousePosition.x <= 420.f + beginButton.getLocalBounds().width &&
                mousePosition.y >= 480.f  &&
                mousePosition.y <= 520.f + beginButton.getLocalBounds().height) {
                beginButton.setCharacterSize(80);
                beginButton.setPosition(400.f, 460.f);
                std::cout << mousePosition.x << ' ' << mousePosition.y << '\n';
            } else {
                beginButton.setPosition(420.f, beginButton.getPosition().y);
                beginButton.setCharacterSize(60);
            }
        }

        void updateGameText(sf::Time deltaTime) noexcept {
            sf::Vector2f moveGameText{0.f, -350.f};
            if (gameText.getPosition().y <= 0.f) {
                moveGameText.y = 0.f;
            }
            gameText.move(moveGameText * deltaTime.asSeconds());
        }

        void updateButton(sf::Time deltaTime) noexcept {
            sf::Vector2f moveButton{0, 350.f};
            if (beginButton.getPosition().y >= 480.f) {
                moveButton.y = 0.f;
            }
            beginButton.move(moveButton * deltaTime.asSeconds());
        }

        sf::Font gameFont;
        sf::Text gameText;
        sf::Text beginButton;
        sf::RenderWindow mWindow;
        sf::Sprite background;
        sf::Texture textureBackground;
        sf::Time TimePerFrame = sf::seconds(1.f / 120.f);

        bool isClicked = false;
};


int main() {
    LoadingScreen l;
    l.run();
}
