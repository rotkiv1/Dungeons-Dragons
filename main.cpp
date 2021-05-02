#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <windows.h>

class Screen2 {
    public:

        Screen2(std::shared_ptr<sf::RenderWindow> previous)
        : screen(previous) {
            if (!textureBackground.loadFromFile("background.png")) {
                //error
            }
            if (!font.loadFromFile("gamefont.otf")) {
                //error
            }

            s.setPosition(393.f, 100.f);
            s.setFillColor(sf::Color::White);
            s.setSize({5.f, 40.f});

            gameText.setFont(font);
            gameText.setPosition(230.f, 0.f);
            gameText.setString("Enter your 4 crew members names");
            gameText.setCharacterSize(60);
            gameText.setColor(sf::Color::White);

            float move = 0.f;
            for (auto& user : userNames) {
                user.setFont(font);
                user.setColor(sf::Color::White);
                user.setCharacterSize(60);
                user.setPosition(400.f, 80.f + move);
                move += 70.f;
            }

            background.setTexture(textureBackground);
            background.setPosition(-150.f, -40.f);
            background.setScale(0.6, 0.6);

            float moveNum = 0.f;
            auto number = '1';
            for (auto& numerate : counter) {
                numerate.setFont(font);
                numerate.setColor(sf::Color::White);
                numerate.setCharacterSize(60);
                numerate.setPosition(350.f, 80.f + moveNum);
                numerate.setString(number);
                numerate.setString(numerate.getString() + '.');
                moveNum += 70.f;
                number++;
            }
        }

        void run() {
            sf::Clock clock;
            sf::Time timeSinceLastUpdate = sf::Time::Zero;
            while (screen->isOpen()) {
                processEvents();
                timeSinceLastUpdate += clock.restart();
                while (timeSinceLastUpdate > TimePerFrame) {
                    timeSinceLastUpdate -= TimePerFrame;
                    processEvents();
                    update();

                }
                render();
            }
        }

    private:

        void processEvents() {
            sf::Event event;
            while (screen->pollEvent(event)) {
                switch (event.type) {
                    case sf::Event::TextEntered:
                        handlePlayerInput(event.key.code);
                        break;
                    case sf::Event::Closed:
                        screen->close();
                        break;
                }
            }
        }

        void handlePlayerInput(sf::Keyboard::Key name) {
            //check if key typed equals enter
            if (name == 13) {
                if (i < 3) {
                    i++;
                    moveCursor += 70.f;
                } else {
                    // start new screen
                }
            } else if (name == 8) /* check for backspace to delete last entered character */ {
                if (!names[i].empty()) {
                    names[i].pop_back();
                }
            } else {
                names[i] += static_cast<char>(name);
            }
            userNames[i].setString(names[i]);
            s.setPosition({403.f + userNames[i].getLocalBounds().width, 100.f + moveCursor});
        }

        void update() {
            if (count % 2 == 1) {
                s.setSize({0.f, 0.f});
            } else {
                s.setSize({5.f, 40.f});
            }
            count++;
        }

        void render() {
            screen->clear();
            screen->draw(background);
            screen->draw(gameText);
            for (const auto& numerator : counter) {
                screen->draw(numerator);
            }
            screen->draw(s);
            for (const auto& user : userNames) {
                screen->draw(user);
            }
            screen->display();
        }

        sf::Sprite background;
        sf::Texture textureBackground;
        sf::Font font;
        sf::Text gameText;
        sf::Text userName1, userName2, userName3, userName4;
        sf::Text one, two, three, four;
        sf::Time TimePerFrame = sf::seconds(1.f / 2.5);
        std::shared_ptr<sf::RenderWindow> screen;
        std::vector<sf::Text> counter{one, two, three, four};
        std::vector<std::string> names{"", "", "", ""};
        std::vector<sf::Text> userNames{userName1, userName2, userName3, userName4};
        sf::RectangleShape s;
        int i = 0;
        int count = 1;
        float moveCursor = 0.f;
};

class LoadingScreen {
    public:

        LoadingScreen()
        : mWindow(std::make_shared<sf::RenderWindow>(sf::VideoMode(1000, 600), "D&D")) {
            if (!textureBackground.loadFromFile("background.png")) {
                //error
            }
            if (!gameFont.loadFromFile("gamefont.otf")) {
                //error
            }

            gameText.setFont(gameFont);
            gameText.setPosition(385.f, 600.f);
            gameText.setString("Dungeons\n\t\t\t&\n  Dragons");
            gameText.setCharacterSize(80);
            gameText.setColor(sf::Color::White);

            beginButton.setFont(gameFont);
            beginButton.setPosition(420.f, 0.f);
            beginButton.setString("BEGIN");
            beginButton.setCharacterSize(60);
            beginButton.setColor(sf::Color::White);

            background.setTexture(textureBackground);
            background.setPosition(-150.f, -40.f);
            background.setScale(0.6, 0.6);
        }

        ~LoadingScreen() = default;

        void run() {
            sf::Clock clock;
            sf::Time timeSinceLastUpdate = sf::Time::Zero;
            while (mWindow->isOpen()) {
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
            while (mWindow->pollEvent(event)) {
                switch (event.type) {
                    case sf::Event::MouseButtonPressed:
                        handlePlayerInput(event.mouseButton.button, true);
                        break;
                    case sf::Event::Closed:
                        mWindow->close();
                        break;
                }
            }
        }

        void handlePlayerInput(sf::Mouse::Button key, bool isPressed) {
            sf::Vector2i position = sf::Mouse::getPosition(*mWindow);
            sf::Vector2f mousePosition = mWindow->mapPixelToCoords(position);
            if (isPressed &&
                mousePosition.x >= 420.f &&
                mousePosition.x <= 420.f + beginButton.getLocalBounds().width &&
                mousePosition.y >= 480.f  &&
                mousePosition.y <= 520.f + beginButton.getLocalBounds().height &&
                key == sf::Mouse::Left) {
                    Screen2 s2(mWindow);
                    s2.run();
                }
        }

        void update(sf::Time deltaTime) {
            onButton();
            updateGameText(deltaTime);
            updateButton(deltaTime);
        }

        void render() {
            mWindow->clear();
            mWindow->draw(background);
            mWindow->draw(gameText);
            mWindow->draw(beginButton);
            mWindow->display();
        }

        void onButton() {
            sf::Vector2i position = sf::Mouse::getPosition(*mWindow);
            sf::Vector2f mousePosition = mWindow->mapPixelToCoords(position);
            if (mousePosition.x >= 420.f &&
                mousePosition.x <= 420.f + beginButton.getLocalBounds().width &&
                mousePosition.y >= 480.f  &&
                mousePosition.y <= 520.f + beginButton.getLocalBounds().height) {
                beginButton.setCharacterSize(80);
                beginButton.setPosition(400.f, 460.f);
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
        std::shared_ptr<sf::RenderWindow> mWindow;
        sf::Sprite background;
        sf::Texture textureBackground;
        sf::Time TimePerFrame = sf::seconds(1.f / 120.f);

        bool isClicked = false;
};

int main() {
    LoadingScreen l;
    l.run();
}
