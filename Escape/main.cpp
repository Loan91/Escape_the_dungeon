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

	Player player(50.0f, 50.0f, {100.0f, 100.0f}, 5.0f);

    vector<Enemy*> enemies;
    enemies.push_back(new ChaserEnemy(60.0f, 60.0f, { 1600.0f, 500.0f }, 50.0f, player));
    /*enemies.push_back(new ChaserEnemy(60.0f, 60.0f, { 1000.0f, 1000.0f }, 300.0f, player));*/
    enemies.push_back(new PatrollingEnemy(50.0f, 50.0f, {400.0f, 50.0f}, {1300.0f, 50.0f}, 400.0f));
    enemies.push_back(new PatrollingEnemy(50.0f, 50.0f, {50.0f, 150.0f}, {800.0f, 150.0f}, 400.0f));
    enemies.push_back(new PatrollingEnemy(100.0f, 100.0f, { 50.0f, 400.0f }, { 450.0f, 400.0f }, 400.0f));

    std::vector<Interface*> interactables;

    interactables.push_back(new Potion(15.0f, { std::rand() % 1800 + 50.0f, std::rand() % 1000 + 50.0f }, 2.0f));
    interactables.push_back(new Potion(15.0f, { std::rand() % 1800 + 50.0f, std::rand() % 1000 + 50.0f }, 3.0f));
    interactables.push_back(new Key({ 20.0f, 20.0f }, { rand() % 1600 + 50.0f, rand() % 1000 + 50.0f }));

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

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        bool gameOver = false;
        bool victoire = false;

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
                victoire = true;
            }
        }

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
        float deltaTime = clock.restart().asSeconds();

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        if (gameOver)
        {
            window.clear();
            map.draw(window);
            RectangleShape semiTransparentRect(Vector2f(1920, 1080));
            semiTransparentRect.setFillColor(Color(0, 0, 0, 150));
            window.draw(semiTransparentRect);
            window.draw(gameOverText);
        }
        else if (victoire)
        {
            window.clear();
            window.draw(end);
            RectangleShape semiTransparentRect(Vector2f(1920, 1080));
            semiTransparentRect.setFillColor(Color(0, 0, 0, 150));
            window.draw(semiTransparentRect);
            window.draw(victoireText);
        }
        else
        {
            for (auto& interactable : interactables)
            {
                if (Potion* potion = dynamic_cast<Potion*>(interactable))
                {
                    if (potion->isCollidingWithPlayer(player))
                    {
                        potion->interact(player);
                    }
                }
                else if (Key* key = dynamic_cast<Key*>(interactable))
                {
                    if (key->isCollidingWithPlayer(player))
                    {
                        key->interact(player);
                    }
                }
            }
            player.updateWithMap(deltaTime, map);
            player.update(deltaTime);

            if (map.checkCollision(player.getBounds()))
            {
                player.handleCollisions(map);
            }

            if (enemies.size() != 0)
            {
                for (auto& enemy : enemies)
                {
                    enemy->update(deltaTime);

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
        }
        window.display();
    }
    enemies.clear();
    return 0;
}