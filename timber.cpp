#include <SFML/Graphics.hpp>
#include <sstream> //standrard in/op librery

using namespace sf;
// function declaration
void updateBranches(int seed);

const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

// position of branches left or right
enum class side
{
    LEFT,
    RIGHT,
    NONE
};
side branchPosition[NUM_BRANCHES];

int main()
{
    srand(time(0)); // Seed random once at the beginning

    VideoMode vm(1920, 1080);
    RenderWindow window(vm, "timber");

    Texture backgroundTexture;
    backgroundTexture.loadFromFile("graphics/background.png");
    Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(-100, -250);

    // Cloud texture
    Texture cloudTexture;
    cloudTexture.loadFromFile("graphics/cloud.png");
    Sprite cloudSprite1, cloudSprite2, cloudSprite3;
    cloudSprite1.setTexture(cloudTexture);
    cloudSprite1.setPosition(100, 50);
    cloudSprite1.scale(0.5f, 0.5f);

    cloudSprite2.setTexture(cloudTexture);
    cloudSprite2.setPosition(800, 50);
    cloudSprite2.scale(0.5f, 0.5f);

    cloudSprite3.setTexture(cloudTexture);
    cloudSprite3.setPosition(300, 50);
    cloudSprite3.scale(0.5f, 0.5f);

    bool cloudActive1 = false, cloudActive2 = false, cloudActive3 = false;
    float cloudSpeed1 = 0.0f, cloudSpeed2 = 0.0f, cloudSpeed3 = 0.0f;
    Clock cloudClock1, cloudClock2, cloudClock3;

    // Tree texture
    Texture treeTexture;
    treeTexture.loadFromFile("graphics/tree.png");
    Sprite treeSprite;
    treeSprite.setTexture(treeTexture);
    treeSprite.setPosition(570, 0);
    treeSprite.scale(0.5f, 1);

    // Bee texture
    Texture beeTexture;
    beeTexture.loadFromFile("graphics/bee.png");
    Sprite beeSprite;
    beeSprite.setTexture(beeTexture);
    beeSprite.setPosition(200, 400);

    bool beeActive = false;
    float beeSpeed = 0.0f;
    float beeHeight = 0.0f;

    //load the playes
    Texture textureplayer;
    textureplayer.loadFromFile("graphics/player.png");
    Sprite spriteplayer;
    spriteplayer.setTexture(textureplayer);
    spriteplayer.setPosition(500,720);

    Texture texturerip;
    texturerip.loadFromFile("graphics/rip.png");
    Sprite spriterip;
    spriterip.setTexture(texturerip);
    spriterip.setPosition(600,800);

    Texture textureaxe;
    textureaxe.loadFromFile("graphics/axe.png");
    Sprite spriteaxe;
    spriteaxe.setTexture(textureaxe);
    spriteaxe.setPosition(700,630);

    Texture texturelog;
    texturelog.loadFromFile("graphics/log.png");
    Sprite spritelog;
    spritelog.setTexture(texturelog);
    spritelog.setPosition(100,0);

    Clock clock;

    // Time Bar
    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 40;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((1250 / 2) - timeBarStartWidth / 2, 600);

    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

    bool paused = true;
    // Draw score
    int score = 0;
    sf::Text messageText;
    sf::Text scoreText;

    // we ne to choose a font from file
    sf::Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");

    // set the font to our message
    messageText.setFont(font);
    scoreText.setFont(font);

    // set specific message
    messageText.setString("press enter to Start");
    scoreText.setString("score=0");

    // set the character size
    messageText.setCharacterSize(200);
    scoreText.setCharacterSize(100);
    // set colour
    messageText.setFillColor(Color::White);
    scoreText.setFillColor(Color::White);
    // set position
    scoreText.setPosition(20, 20);
    messageText.setString("out of Time!!");
    FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

    // create 5 branches
    Texture textureBranch;
    textureBranch.loadFromFile("graphics/branch.png");

    // set the texture for each branch sprite
    for (int i = 0; i < NUM_BRANCHES; i++)
    {
        branches[i].setTexture(textureBranch);
        branches[i].setPosition(-2000, -2000);

        // set the sprite origin to create
        branches[i].setOrigin(220, 20);
    }
    updateBranches(1);
    updateBranches(2);
    updateBranches(3);
    updateBranches(4);
    updateBranches(5);
    updateBranches(6);

    while (window.isOpen())
    {
        if (Keyboard::isKeyPressed(Keyboard::Return))
        {
            paused = false;
            // reset time and score
            score = 0;
            timeRemaining = 6.0f;
        }

        if (!paused)
        {
            Time dt = clock.restart();
            timeRemaining -= dt.asSeconds();
            timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

            if (timeRemaining <= 0.0f)
            {
                paused = true;
                messageText.setString("game over");
                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
            }

            // Cloud 1 movement
            if (!cloudActive1)
            {
                cloudSpeed1 = (rand() % 100) + 100;
                cloudSprite1.setPosition(-100, (rand() % 50) + 100);
                cloudActive1 = true;
            }
            else
            {
                cloudSprite1.move(cloudSpeed1 * dt.asSeconds(), 0);
                if (cloudSprite1.getPosition().x > 2000)
                {
                    cloudActive1 = false;
                }
            }

            // Cloud 2 movement
            if (!cloudActive2)
            {
                cloudSpeed2 = (rand() % 100) + 100;
                cloudSprite2.setPosition(-500, (rand() % 50) + 100);
            }
            else
            {
                cloudSprite2.move(cloudSpeed2 * dt.asSeconds(), 0);
                if (cloudSprite2.getPosition().x > 2000)
                {
                    cloudActive2 = false;
                }
            }

            // Cloud 3 movement
            if (!cloudActive3)
            {
                cloudSpeed3 = (rand() % 100) + 100;
                cloudSprite3.setPosition(-50, (rand() % 50) + 50);
                cloudActive3 = true;
            }
            else
            {
                cloudSprite3.move(cloudSpeed3 * dt.asSeconds(), 0);
                if (cloudSprite3.getPosition().x > 2000)
                {
                    cloudActive3 = false;
                }
            }

            // Bee movement
            if (!beeActive)
            {
                beeSpeed = (rand() % 200) + 200;
                beeHeight = (rand() % 500) + 500;
                beeSprite.setPosition(2000, beeHeight);
                beeActive = true;
            }
            else
            {
                beeSprite.move(-beeSpeed * dt.asSeconds(), 0);
                if (beeSprite.getPosition().x < -100)
                {
                    beeActive = false;
                }
            }
            // update the score
            std::stringstream ss;
            ss << "Score: " << score;
            scoreText.setString(ss.str());

            // update the branch
            for (int i = 0; i < NUM_BRANCHES; i++)
            {
                float height = i * 150;
                if (branchPosition[i] == side::LEFT)
                {

                    // move the sprite to left
                    branches[i].setPosition(350, height);
                    branches[i].setRotation(180);
                }
                else if (branchPosition[i] == side::RIGHT)
                {

                    // move the sprite to right
                    branches[i].setPosition(920, height);
                    branches[i].setRotation(0);
                }
                else
                {
                    // hide the branch
                    branches[i].setPosition(3000, height);
                }
            }
            updateBranches(1);
            updateBranches(2);
            updateBranches(3);
            updateBranches(4);
            updateBranches(5);
            updateBranches(6);
        }

        // Clear window
        window.clear();

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        // Display elements
        window.draw(backgroundSprite);
        window.draw(cloudSprite1);
        window.draw(cloudSprite2);
        window.draw(cloudSprite3);
        // draw the branches
        for (int i = 0; i < NUM_BRANCHES; i++)
        {
            window.draw(branches[i]);
        }
        window.draw(treeSprite);
        window.draw(beeSprite);
        window.draw(scoreText);
        window.draw(timeBar);
        if (paused)
        {
            window.draw(messageText);
        }
        window.display();
    }

    return 0;
}
void updateBranches(int seed)
{
    // move the branches down one place
    for (int j = NUM_BRANCHES; j > 0; j--)
    {
        branchPosition[j] = branchPosition[j - 1];
        // position left,right,none
        srand((int)time(0) + seed);
        int r = {rand() % 5};
        switch (r)
        {
        case 0:
            branchPosition[0] = side::LEFT;
            break;
        case 1:
            branchPosition[0] = side::RIGHT;
            break;

        default:
            branchPosition[0] = side::NONE;
            break;
        }
    }
}