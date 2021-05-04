#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <windows.h>


class Person {
    public:

        Person(std::string _name) : name(_name) {}

        std::string name;
        int fullness = 10;
        bool isAlive = true;
        std::string armor;
        std::string weapon;
        int ingredientsAmount = 0;
};

class MerchantScreen {
    public:

        MerchantScreen(std::shared_ptr<sf::RenderWindow> previous,
                       const std::vector<Person>& _companion)
        : screen(previous), companion(_companion) {
            if (!merchant.loadFromFile("background.png")) {
                /* error */
            }
            if (!font.loadFromFile("gamefont.otf")) {
                /* error */
            }

            image.loadFromFile("test.png");
            image.createMaskFromColor(sf::Color::White);
            tex.loadFromImage(image);

            creature.setTexture(tex);
            creature.setPosition(-75.f, 600.f);
            creature.setScale(0.6, 0.6);

            merchantSprite.setTexture(merchant);
            merchantSprite.setPosition(-150.f, -40.f);
            merchantSprite.setScale(0.6, 0.6);

            introduce.setFont(font);
            introduce.setColor(sf::Color(204, 102, 0));
            introduce.setCharacterSize(40);
            introduce.setPosition(0.f, 70.f);

            warning.setFont(font);
            warning.setColor(sf::Color(204, 102, 0));
            warning.setCharacterSize(40);
            warning.setPosition(300.f, 400.f);
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
                    update(TimePerFrame);

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

        }

        void update(sf::Time deltaTime) {
            if (creature.getPosition().y > 280.f) {
                creature.move(move * deltaTime.asSeconds());
            } else {
                TimePerFrame = sf::seconds(1.f / 130.f);
                if (iText < strlen(text)) {
                    introduce.setString(introduce.getString() + text[iText++]);
                    if (text[iText - 1] == '\n' && iText < 150) {
                        introduce.setString("");
                    }
                } else {
                    if (iWarning < strlen(text2)) {
                        warning.setString(warning.getString() + text2[iWarning++]);
                    } else {
                        warning.setString("");
                        introduce.setString("");
                        TimePerFrame = sf::seconds(1.f / 120.f);
                        move.y = 200.f;
                        if (creature.getPosition().y <= 1200.f) {
                            creature.move(move * deltaTime.asSeconds());
                        }
                        if (!merchant.loadFromFile("background.png")) {
                            /* error */
                        }
                    }
                }
            }
        }

        void render() {
            screen->clear();
            screen->draw(merchantSprite);
            screen->draw(introduce);
            screen->draw(warning);
            screen->draw(creature);
            screen->display();
        }

        std::shared_ptr<sf::RenderWindow> screen;
        std::vector<Person> companion;
        sf::Time TimePerFrame = sf::seconds(1.f / 120.f); /* 1 / 30.f is fine */
        sf::Sprite background;
        sf::Texture textureBackground;
        sf::Texture merchant;
        sf::Sprite merchantSprite;
        sf::Text introduce, warning;
        sf::Font font;
        char* text{"\t\tBetween the 4 of you, you have 100 gold coins. \n\t\t"
                   "You will need to spend the rest of your money \n\t\t on the following items: \n\t\t"
                   "- INGREDIENTS. To make food, you have to cook raw ingredients.\n\t\t"
                   "- COOKWARE. If you want to cook, you have to have cookware first.\n\t\t"
                   "- WEAPONS. You will want at least one weapon per party member to fend off monsters.\n\t\t"
                   "- ARMOR. Armor increases the chances of surviving a monster attack.\n\t\t"};
        char* text2{"You can spend all of your money here before you start your\n"
                    "journey, or you can save some to spend on merchants along the\n"
                    "way. But beware, some of the merchants in this dungeon are\n"
                    "shady characters, and they will not always give you a fair price...\n"};
        int iText = 0;
        int iWarning = 0;
        sf::Image image;
        sf::Texture tex;
        sf::Sprite creature;
        sf::Vector2f move{0.f, -200.f};
};


class Screen2 {
    public:

        Screen2(std::shared_ptr<sf::RenderWindow> previous)
        : screen(previous) {
            if (!textureBackground.loadFromFile("background.png")) {
                /* error */
            }
            if (!font.loadFromFile("gamefont.otf")) {
                /* error */
            }

            s.setPosition(393.f, 100.f);
            s.setFillColor(sf::Color(204, 102, 0));
            s.setSize({5.f, 40.f});

            gameText.setFont(font);
            gameText.setPosition(230.f, 0.f);
            gameText.setString("Enter your 4 crew members names");
            gameText.setCharacterSize(60);
            gameText.setColor(sf::Color(204, 102, 0));

            auto move = 0.f;
            for (auto& user : userNames) {
                user.setFont(font);
                user.setColor(sf::Color(204, 102, 0));
                user.setCharacterSize(60);
                user.setPosition(400.f, 80.f + move);
                move += 70.f;
            }

            background.setTexture(textureBackground);
            background.setPosition(-150.f, -40.f);
            background.setScale(0.6, 0.6);

            auto moveNum = 0.f;
            auto number = '1';
            for (auto& numerate : counter) {
                numerate.setFont(font);
                numerate.setColor(sf::Color(204, 102, 0));
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
            /* check if key typed equals enter */
            if (name == 13) {
                if (i < 3) {
                    i++;
                    moveCursor += 70.f;
                } else {
                    /* start new screen and create company */
                    for (auto& person : names) {
                        companion.push_back(Person(person));
                    }
                    MerchantScreen ms(screen, companion);
                    ms.run();
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
        std::vector<Person> companion;
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
            gameText.setColor(sf::Color(204, 102, 0));

            beginButton.setFont(gameFont);
            beginButton.setPosition(420.f, 0.f);
            beginButton.setString("BEGIN");
            beginButton.setCharacterSize(60);
            beginButton.setColor(sf::Color(204, 102, 0));

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
    /*
    auto p = std::make_shared<sf::RenderWindow>(sf::VideoMode(1000, 600), "D&D");
    std::vector<Person> w;

    MerchantScreen s(p, w);
    s.run();
    */
    LoadingScreen s;
    s.run();


}
