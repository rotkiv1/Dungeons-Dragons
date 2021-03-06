#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <windows.h>

class Person {

    public:

        Person(std::string _name)
        : name(_name) {}

        std::string name, armor, weapon;
        int fullness = 10;
        bool isAlive = true;
        int ingredientsAmount = 0;
};

class Shop {

    public:
        Shop(std::shared_ptr<sf::RenderWindow> _screen,
             const std::vector<Person>& _companion)
        : screen(_screen), companion(_companion) {
            font.loadFromFile("gamefont.otf");

            totalCostText.setFont(font);
            totalCostText.setCharacterSize(40);
            totalCostText.setPosition(800.f, 0.f);
            totalCostText.setString("cost \t left: \t" +
                                    std::to_string(totalCost));

            foodInfo.setFont(font);
            foodInfo.setCharacterSize(0);
            foodInfo.setPosition(100.f, 30.f);
            foodInfo.setString("1kg - 1 coin \t (Already have: \t" +
                               std::to_string(currentAmountFood) + "kg)");

            image.loadFromFile("seller.png");
            image.createMaskFromColor(sf::Color::Black);
            tex.loadFromImage(image);

            creature.setTexture(tex);
            creature.setPosition(-50.f, 600.f);
            creature.setScale(1.1, 1.1);

            background.loadFromFile("shopbackground.jpg");
            backgroundSprite.setTexture(background);
            backgroundSprite.setScale(0.79, 0.79);

            foodImage.loadFromFile("ing.png");
            foodImage.createMaskFromColor(sf::Color::Black);
            foodTexture.loadFromImage(foodImage);
            foodSprite.setTexture(foodTexture);
            foodSprite.setScale(0, 0);
            foodSprite.rotate(50);
            foodSprite.setPosition(60.f, 0.f);
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
                    case sf::Event::MouseButtonPressed:
                        handlePlayerInput(event.mouseButton.button, true);
                        break;
                    case sf::Event::Closed:
                        screen->close();
                        break;
                }
            }
        }

        void handlePlayerInput(sf::Mouse::Button key, bool isPressed) {
            sf::Vector2i position = sf::Mouse::getPosition(*screen);
            sf::Vector2f mousePosition = screen->mapPixelToCoords(position);
            if (mousePosition.x >= 10.f && mousePosition.x <= 100.f) {
                totalCost--;
                totalCostText.setString("cost \t left: \t" +
                                        std::to_string(totalCost));
                currentAmountFood++;
                foodInfo.setString("1kg - 1 coin \t (Already have: \t" +
                               std::to_string(currentAmountFood) + "kg)");
            }
        }

        void update(sf::Time deltaTime) {
            if (creature.getPosition().y > 300.f && move.y < 0) {
                creature.move(move * deltaTime.asSeconds());
            } else {
                foodSprite.setScale(0.15, 0.15);
                foodInfo.setCharacterSize(35);
            }
        }

        void render() {
            screen->clear();
            screen->draw(backgroundSprite);
            screen->draw(foodSprite);
            screen->draw(foodInfo);
            screen->draw(totalCostText);
            screen->draw(creature);
            screen->display();
        }

        std::shared_ptr<sf::RenderWindow> screen;
        std::vector<Person> companion;
        sf::Time TimePerFrame = sf::seconds(1.f / 120.f);
        sf::Image image, foodImage;
        sf::Texture tex, background, foodTexture;
        sf::Sprite creature, backgroundSprite, foodSprite;
        sf::Font font;
        sf::Text totalCostText, foodInfo;
        sf::Vector2f move{0, -200.f};

        int totalCost = 100;
        int currentAmountFood = 0;
};

class MerchantScreen {

    public:

        MerchantScreen(std::shared_ptr<sf::RenderWindow> previous,
                       const std::vector<Person>& _companion)
        : screen(previous), companion(_companion) {
            font.loadFromFile("gamefont.otf");

            image.loadFromFile("seller.png");
            image.createMaskFromColor(sf::Color::Black);
            tex.loadFromImage(image);

            armorSwordImage.loadFromFile("eq.png");
            armorSwordImage.createMaskFromColor(sf::Color::Black);
            armorSwordTexture.loadFromImage(armorSwordImage);
            armorSwordSprite.setTexture(armorSwordTexture);
            armorSwordSprite.setScale(0, 0);
            armorSwordSprite.setPosition(400.f, 200.f);

            creature.setTexture(tex);
            creature.setPosition(-50.f, 600.f);
            creature.setScale(1.1, 1.1);

            merchant.loadFromFile("background.png");
            merchantSprite.setTexture(merchant);
            merchantSprite.setPosition(-150.f, -40.f);
            merchantSprite.setScale(0.65, 0.65);

            introduce.setFont(font);
            introduce.setColor(sf::Color::Black);
            introduce.setCharacterSize(40);
            introduce.setPosition(230.f, 70.f);

            warning.setFont(font);
            warning.setColor(sf::Color::Black);
            warning.setCharacterSize(35);
            warning.setPosition(230.f, 70.f);

            cloud.loadFromFile("text.png");
            cloud.createMaskFromColor(sf::Color::Black);
            cloudTex.loadFromImage(cloud);

            textCloud.setTexture(cloudTex);
            textCloud.setPosition(80.f, -20.f);
            textCloud.setScale(0.f, 0.f);
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
                    case sf::Event::Closed:
                        screen->close();
                        break;
                }
            }
        }

        void update(sf::Time deltaTime) {
            if (creature.getPosition().y > 300.f && move.y < 0) {
                creature.move(move * deltaTime.asSeconds());
            } else {
                textCloud.setScale(1.3, 1.f);
                TimePerFrame = sf::seconds(1.f / 200.f);
                if (iText < strlen(text)) {
                    introduce.setString(introduce.getString() + text[iText++]);
                    if (text[iText - 1] == '\n' && text[iText - 2] == '.') {
                        introduce.setString("");
                    }
                } else {
                    if (iWarning < strlen(text2)) {
                        warning.setString(warning.getString() + text2[iWarning++]);
                    } else {
                        warning.setString("");
                        textCloud.setScale(0.f, 0.f);
                        TimePerFrame = sf::seconds(1.f / 120.f);
                        move.y = 200.f;
                        if (creature.getPosition().y <= 600.f) {
                            creature.move(move * deltaTime.asSeconds());
                        } else {
                            armorSwordSprite.setScale(0.3, 0.3);
                            sf::Vector2i position = sf::Mouse::getPosition(*screen);
                            sf::Vector2f worldPosition = screen->mapPixelToCoords(position);
                            auto x = worldPosition.x;
                            auto y = worldPosition.y;
                            if (x >= 400.f && x <= 200.f + armorSwordSprite.getPosition().x &&
                                y >= 200.f && y <= 200.f + armorSwordSprite.getPosition().y) {
                                armorSwordSprite.setScale(0.4, 0.4);
                                armorSwordSprite.setPosition(380.f, 180.f);
                                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                                    Shop s(screen, companion);
                                    s.run();
                                }
                            } else {
                                armorSwordSprite.setPosition(400.f, 200.f);
                                armorSwordSprite.setScale(0.3, 0.3);
                            }
                        }
                    }
                }
            }
        }

        void render() {
            screen->clear();
            screen->draw(merchantSprite);
            screen->draw(textCloud);
            screen->draw(introduce);
            screen->draw(warning);
            screen->draw(creature);
            screen->draw(armorSwordSprite);
            screen->display();
        }

        std::shared_ptr<sf::RenderWindow> screen;
        std::vector<Person> companion;
        sf::Time TimePerFrame = sf::seconds(1.f / 120.f); /* 1 / 30.f is fine */
        sf::Sprite background, creature, textCloud, merchantSprite, armorSwordSprite;
        sf::Texture textureBackground, merchant, tex, cloudTex, armorSwordTexture;
        sf::Text introduce, warning;
        sf::Image image, cloud, armorSwordImage;
        sf::Font font;
        int iText = 0;
        int iWarning = 0;
        sf::Vector2f move{0.f, -200.f};
        char* text{"\t\tBetween the 4 of you, you have 100 gold  \n\t\t coins."
                   "You will need to spend the rest of your \n\t\t money on the"
                   "following items.\n"
                   "\t\t\t\t\t\t\t\tINGREDIENTS\n To make food, you have to cook"
                   "raw ingredients.\n\t\t"
                   "\t\t\t\t\t\tCOOKWARE\n If you want to cook, you have to have"
                   "cookware first.\n\t\t"
                   "\t\t\t\t\t\t\t\tWEAPONS\n You will want at least one weapon"
                   "per party\n member to fend off monsters.\n\t\t"
                   "\t\t\t\t\t\t\t\tARMOR\n Armor increases the chances of"
                   "surviving\n a monster attack.\n\t\t"};
        char* text2{"\t\tYou can spend all of your money here before\n you start"
                    "your journey, or you can save some to\n spend on merchants"
                    "along the way. But beware, some of the\n merchants in this"
                    "dungeon are shady characters, and they will\n\t\t not always"
                    "give you a fair price...\n"};
};

class Screen2 {

    public:

        Screen2(std::shared_ptr<sf::RenderWindow> previous)
        : screen(previous) {
            font.loadFromFile("gamefont.otf");

            /* button | */
            s.setPosition(393.f, 100.f);
            s.setFillColor(sf::Color(204, 102, 0));
            s.setSize({5.f, 40.f});

            gameText.setFont(font);
            gameText.setPosition(230.f, 0.f);
            gameText.setString("Enter your 4 crew members names");
            gameText.setCharacterSize(60);
            gameText.setColor(sf::Color(204, 102, 0));

            /* create user names templates at certain position */
            auto move = 0.f;
            for (auto& user : userNames) {
                user.setFont(font);
                user.setColor(sf::Color(204, 102, 0));
                user.setCharacterSize(60);
                user.setPosition(400.f, 80.f + move);
                move += 70.f;
            }

            textureBackground.loadFromFile("background.png");
            background.setTexture(textureBackground);
            background.setPosition(-150.f, -40.f);
            background.setScale(0.65, 0.65);

            /* create and set number at certain position */
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
            } else if (name == 8) /* check for backspace to delete
                                     last entered character */ {
                if (!names[i].empty()) {
                    names[i].pop_back();
                }
            } else {
                names[i] += static_cast<char>(name);
            }
            userNames[i].setString(names[i]);
            s.setPosition({403.f + userNames[i].getLocalBounds().width,
                          100.f + moveCursor});
        }

        /* texture | showing -> hiding */
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
            /* display 1. / 2. / 3. /4. on screen */
            for (const auto& numerator : counter) {
                screen->draw(numerator);
            }
            screen->draw(s);
            /* live display chars that user is entering */
            for (const auto& user : userNames) {
                screen->draw(user);
            }
            screen->display();
        }

        sf::Sprite background;
        sf::Texture textureBackground;
        sf::Font font;
        sf::Text userName1, userName2, userName3, userName4,
                 gameText, one, two, three, four;
        sf::Time TimePerFrame = sf::seconds(1.f / 2.5);
        sf::RectangleShape s;
        std::shared_ptr<sf::RenderWindow> screen;
        std::vector<sf::Text> counter{one, two, three, four};
        std::vector<std::string> names{"", "", "", ""};
        std::vector<sf::Text> userNames{userName1, userName2, userName3, userName4};
        std::vector<Person> companion;
        int i = 0;
        int count = 1;
        float moveCursor = 0.f;
};

class LoadingScreen {

    public:

        LoadingScreen()
        : mWindow(std::make_shared<sf::RenderWindow>(sf::VideoMode(1000, 600), "D&D")) {
            gameFont.loadFromFile("gamefont.otf");

            image.loadFromFile("dd.png");
            image.createMaskFromColor(sf::Color::Black);
            tex.loadFromImage(image);

            s.setTexture(tex);
            s.setPosition(195.f, -100.f);
            s.setScale(0.9, 0.9);

            beginButton.setFont(gameFont);
            beginButton.setPosition(420.f, 0.f);
            beginButton.setString("BEGIN");
            beginButton.setCharacterSize(60);
            beginButton.setColor(sf::Color(204, 102, 0));

            textureBackground.loadFromFile("background.png");
            background.setTexture(textureBackground);
            background.setPosition(-150.f, -40.f);
            background.setScale(0.65, 0.65);

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
            /* if we click on the button, go to next screen */
            if (isPressed && checkMousePosition(mousePosition) &&
                key == sf::Mouse::Left) {
                Screen2 s2(mWindow);
                s2.run();
            }
        }

        /* moving button from bottom to certain spot */
        void update(sf::Time deltaTime) {
            onButton();
            updateButton(deltaTime);
        }

        void render() {
            mWindow->clear();
            mWindow->draw(background);
            mWindow->draw(s);
            mWindow->draw(beginButton);
            mWindow->display();
        }

        void onButton() {
            sf::Vector2i position = sf::Mouse::getPosition(*mWindow);
            sf::Vector2f mousePosition = mWindow->mapPixelToCoords(position);
            if (checkMousePosition(mousePosition)) {
                beginButton.setCharacterSize(80);
                beginButton.setPosition(400.f, 460.f);
            } else {
                beginButton.setPosition(420.f, beginButton.getPosition().y);
                beginButton.setCharacterSize(60);
            }
        }

        bool checkMousePosition(const sf::Vector2f& mousePosition) {
            auto width =  beginButton.getLocalBounds().width;
            auto height = beginButton.getLocalBounds().height;
            return mousePosition.x >= 420.f && mousePosition.x <= 420.f + width &&
                   mousePosition.y >= 480.f && mousePosition.y <= 520.f + height;
        }

        void updateButton(sf::Time deltaTime) {
            sf::Vector2f moveButton{0, 350.f};
            if (beginButton.getPosition().y >= 480.f) {
                moveButton.y = 0.f;
            }
            beginButton.move(moveButton * deltaTime.asSeconds());
        }

        sf::Font gameFont;
        sf::Text gameText, beginButton;
        std::shared_ptr<sf::RenderWindow> mWindow;
        sf::Sprite background, s;
        sf::Texture textureBackground, tex;
        sf::Image image;
        sf::Time TimePerFrame = sf::seconds(1.f / 120.f);
        bool isClicked = false;
};

int main() {


    auto p = std::make_shared<sf::RenderWindow>(sf::VideoMode(1000, 600), "D&D");
    std::vector<Person> w;

    Shop s(p, w);
    s.run();



    //LoadingScreen l;
    //l.run();
}
