#include "includes.h"
#include "Entity.h"
#include "Player.h"
#include "ChaserEnemy.h"
#include "PatrollingEnemy.h"
#include "Potion.h"
#include "Key.h"
#include "Map.h"

int main()
{
    RenderWindow window(VideoMode(1920, 1080), "Escape the Dungeon", Style::Fullscreen);
    window.setFramerateLimit(60);

    sf::Texture chaserTexture;
    if (!chaserTexture.loadFromFile("assets/chaser.png"))
    {
        std::cerr << "Erreur de chargement de l'image chaser.png\n";
        return -1;
    }

    sf::Texture patrollingTexture;
    if (!patrollingTexture.loadFromFile("assets/patrolling.png"))
    {
        std::cerr << "Erreur de chargement de l'image patrolling.png\n";
        return -1;
    }

    sf::Texture potionTexture;
    if (!potionTexture.loadFromFile("assets/potion.png"))
    {
        std::cerr << "Erreur de chargement de l'image potion.png\n";
        return -1;
    }

    sf::Texture keyTexture;
    if (!keyTexture.loadFromFile("assets/key.png"))
    {
        std::cerr << "Erreur de chargement de l'image key.png\n";
        return -1;
    }

    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("assets/player.png"))
    {
        std::cerr << "Erreur de chargement de l'image player.png\n";
        return -1;
    }

    sf::Texture explosionTexture;
    if (!explosionTexture.loadFromFile("assets/explo.png")) {
        std::cerr << "Erreur de chargement de l'image explosion.png\n";
        return -1;
    }

    sf::Sprite explosionSprite;
    explosionSprite.setTexture(explosionTexture);
    explosionSprite.setTextureRect(sf::IntRect(0, 0, 128, 128));
    explosionSprite.setPosition(1920 / 2 - 64, 1080 / 2 - 64);

    float explosionFrameDuration = 0.1f;
    float explosionElapsedTime = 0.0f;
    int explosionCurrentFrame = 0;
    bool showExplosion = false;

    Player player(50.0f, 50.0f, { 50.0f, 50.0f }, 5.0f, playerTexture);

    vector<Enemy*> enemies;
    enemies.push_back(new ChaserEnemy(80.0f, 80.0f, { 1600.0f, 500.0f }, 70.0f, player, chaserTexture));
    enemies.push_back(new ChaserEnemy(50.0f, 50.0f, { 50.0f, 800.0f }, 250.0f, player, chaserTexture));
    enemies.push_back(new PatrollingEnemy(50.0f, 50.0f, { 400.0f, 50.0f }, { 1300.0f, 50.0f }, 400.0f, patrollingTexture));
    enemies.push_back(new PatrollingEnemy(50.0f, 50.0f, { 50.0f, 150.0f }, { 800.0f, 150.0f }, 400.0f, patrollingTexture));
    enemies.push_back(new PatrollingEnemy(50.0f, 50.0f, { 850.0f, 300.0f }, { 1000.0f, 300.0f }, 250.0f, patrollingTexture));
    enemies.push_back(new PatrollingEnemy(80.0f, 80.0f, { 50.0f, 900.0f }, { 1830.0f, 900.0f }, 500.0f, patrollingTexture));
    enemies.push_back(new PatrollingEnemy(70.0f, 70.0f, { 150.0f, 850.0f }, { 150.0f, 980.0f }, 350.0f, patrollingTexture));
    enemies.push_back(new PatrollingEnemy(100.0f, 100.0f, { 50.0f, 400.0f }, { 450.0f, 400.0f }, 400.0f, patrollingTexture));

    std::vector<Interactable*> interactables;

    interactables.push_back(new Potion(potionTexture, { std::rand() % 1800 + 50.0f, std::rand() % 1000 + 50.0f }, 2.0f, { 30.0f, 30.0f }));
    interactables.push_back(new Potion(potionTexture, { std::rand() % 1800 + 50.0f, std::rand() % 1000 + 50.0f }, 3.0f, { 30.0f, 30.0f }));
    interactables.push_back(new Key(keyTexture, { std::rand() % 1600 + 50.0f, std::rand() % 1000 + 50.0f }, { 50.0f, 30.0f }));

    Clock clock;

    Map map;
    if (!map.loadFromFile("assets/map.txt"))
    {
        std::cerr << "Erreur de chargement de la carte !\n";
        return -1;
    }

    sf::Texture openedTexture;
    if (!openedTexture.loadFromFile("assets/opened.png")) {
        std::cout << "Erreur de chargement de l'image!" << std::endl;
        return -1;
    }
    map.setOpenedDoorTexture(openedTexture);

    sf::Texture endTexture;
    if (!endTexture.loadFromFile("assets/end.png")) {
        std::cout << "Erreur de chargement de l'image!" << std::endl;
        return -1;
    }
    Sprite end(endTexture);

    sf::Font font;
    if (!font.loadFromFile("assets/font.ttf"))
    {
        std::cerr << "Erreur de chargement de la police!\n";
        return -1;
    }

    Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(1920 / 2 - gameOverText.getGlobalBounds().width / 2, 1080 / 2 - gameOverText.getGlobalBounds().height / 2);

    Text victoireText;
    victoireText.setFont(font);
    victoireText.setString("Victoire");
    victoireText.setCharacterSize(50);
    victoireText.setFillColor(sf::Color::Yellow);
    victoireText.setPosition(1920 / 2 - victoireText.getGlobalBounds().width / 2, 1080 / 2 - victoireText.getGlobalBounds().height / 2);

    bool endGame = false;
    bool isVictoire = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (endGame)
        {
            window.clear();

            if (isVictoire)
            {
                window.draw(end);
                RectangleShape semiTransparentRect(Vector2f(1920, 1080));
                semiTransparentRect.setFillColor(Color(0, 0, 0, 150));
                window.draw(semiTransparentRect);
                window.draw(victoireText);
            }
            else
            {
                map.draw(window);
                RectangleShape semiTransparentRect(Vector2f(1920, 1080));
                semiTransparentRect.setFillColor(Color(0, 0, 0, 150));
                window.draw(semiTransparentRect);
                window.draw(gameOverText);
            }

            window.display();

            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                window.close();
            }
            continue;
        }

        bool gameOver = false;

        for (auto& enemy : enemies)
        {
            if (enemy->getBounds().intersects(player.getBounds()))
            {
                gameOver = true;
                break;
            }
        }

        if (map.checkDoorCollision(player.getBounds()))
        {
            if (player.getHasKey() && Keyboard::isKeyPressed(Keyboard::E))
            {
                map.unlockDoor();
                isVictoire = true;
                endGame = true;
                continue;
            }
        }

        float deltaTime = clock.restart().asSeconds();

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        if (showExplosion) {
            explosionElapsedTime += deltaTime;

            if (explosionElapsedTime >= explosionFrameDuration) {
                explosionElapsedTime -= explosionFrameDuration;
                explosionCurrentFrame++;

                explosionSprite.setTextureRect(sf::IntRect((explosionCurrentFrame % 8) * 128,
                    (explosionCurrentFrame / 8) * 128,
                    128, 128));
            }

            if (explosionCurrentFrame >= 16) {
                showExplosion = false;
            }
        }

        if (showExplosion) {
            window.draw(explosionSprite);
        }

        if (gameOver) {
            endGame = true;
            isVictoire = false;
            showExplosion = true;
            explosionElapsedTime = 0.0f;
            explosionCurrentFrame = 0;
            continue;
        }

        for (auto& interactable : interactables)
        {
            if (Potion* potion = dynamic_cast<Potion*>(interactable))
            {
                potion->update(deltaTime);
                if (potion->isCollidingWithPlayer(player))
                {
                    potion->interact(player);
                }
            }
            else if (Key* key = dynamic_cast<Key*>(interactable))
            {
                key->update(deltaTime);
                if (key->isCollidingWithPlayer(player))
                {
                    key->interact(player);
                }
            }
        }


        if (map.checkCollision(player.getBounds()))
        {
            player.handleCollisions(map);
        }

        player.update(deltaTime, map);
        if (enemies.size() != 0)
        {
            for (auto& enemy : enemies)
            {
                enemy->update(deltaTime, map);
            }
        }

        window.clear();
        map.draw(window);
        player.draw(window);
        for (auto& enemy : enemies)
        {
            enemy->draw(window);
        }
        for (auto& interactable : interactables)
        {
            if (Potion* potion = dynamic_cast<Potion*>(interactable))
            {
                potion->draw(window);
            }
            else if (Key* key = dynamic_cast<Key*>(interactable))
            {
                key->draw(window);
            }
        }

        window.display();
    }
    for (auto& enemy : enemies)
    {
        delete enemy;
    }
    enemies.clear();
    return 0;
}