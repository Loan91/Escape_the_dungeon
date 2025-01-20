#include "includes.h"
#include "Entity.h"
#include "Player.h"
#include "ChaserEnemy.h"
#include "PatrollingEnemy.h"
#include "Potion.h"
#include "Key.h"

int main()
{
	RenderWindow window(VideoMode(1920, 1080), "Escape the Dungeon", Style::Fullscreen);
    window.setFramerateLimit(60);

	Player player(50.0f, 50.0f, {400.0f, 300.0f}, 5.0f);

    vector<Enemy*> enemies;
    enemies.push_back(new ChaserEnemy(60.0f, 60.0f, { 100.0f, 100.0f }, 300.0f, player));
    enemies.push_back(new ChaserEnemy(60.0f, 60.0f, { 1000.0f, 1000.0f }, 300.0f, player));
    enemies.push_back(new PatrollingEnemy(100.0f, 100.0f, {200.0f, 200.0f}, {1000.0f, 200.0f}, 400.0f));
    enemies.push_back(new PatrollingEnemy(100.0f, 100.0f, { 200.0f, 800.0f }, { 1000.0f, 800.0f }, 400.0f));

    std::vector<Interface*> interactables;

    interactables.push_back(new Potion(15.0f, { rand() % 1800 + 50.0f, rand() % 1000 + 50.0f }));
    interactables.push_back(new Potion(15.0f, { rand() % 1800 + 50.0f, rand() % 1000 + 50.0f }));
    interactables.push_back(new Key({ 20.0f, 20.0f }, { rand() % 1800 + 50.0f, rand() % 1000 + 50.0f }));
    interactables.push_back(new Key({ 20.0f, 20.0f }, { rand() % 1800 + 50.0f, rand() % 1000 + 50.0f }));

	Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        sf::Font font;
        if (!font.loadFromFile("assets/font.ttf"))
        {
            std::cerr << "Erreur de chargement de la police!\n";
            return -1;
        }

        sf::Texture mapTexture;
        if (!mapTexture.loadFromFile("assets/map.png")) {
            std::cout << "Erreur de chargement de l'image!" << std::endl;
            return -1;
        }
        sf::Sprite map(mapTexture);

        Text gameOverText;
        gameOverText.setFont(font);
        gameOverText.setString("Game Over");
        gameOverText.setCharacterSize(50);
        gameOverText.setFillColor(sf::Color::Red);
        gameOverText.setPosition(1920 / 2 - gameOverText.getGlobalBounds().width / 2, 1080 / 2 - gameOverText.getGlobalBounds().height / 2);

        float deltaTime = clock.restart().asSeconds();

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

        player.update(deltaTime);
        if (enemies.size() != 0)
        {
            for (auto& enemy : enemies)
            {
                enemy->update(deltaTime);

            }
        }
        window.clear();
        window.draw(map);
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
        for (auto& enemy : enemies)
        {
            if (enemy->getBounds().intersects(player.getBounds()))
            {
                window.clear();
                window.draw(map);
                RectangleShape semiTransparentRect(Vector2f(1920, 1080));
                semiTransparentRect.setFillColor(Color(0, 0, 0, 150));
                window.draw(semiTransparentRect);
                window.draw(gameOverText);
            }
        }
        window.display();
    }
    enemies.clear();
    return 0;
}