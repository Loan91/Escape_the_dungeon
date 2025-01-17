#include "includes.h"
#include "Entity.h"
#include "Player.h"
#include "ChaserEnemy.h"

int main()
{
	RenderWindow window(VideoMode(1920, 1080), "Escape the Dungeon", Style::None);
    window.setFramerateLimit(60);

	Player player(50.0f, 50.0f, {400.0f, 300.0f}, 20.0f);

    vector<Enemy*> enemies;
    enemies.push_back(new ChaserEnemy(40.0f, 40.0f, { 100.0f, 100.0f }, 10.0f, player));

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
        
        float deltaTime = clock.restart().asSeconds();

        player.update(deltaTime);
        for (auto& enemy : enemies)
        {
            if (enemy)
            {
                enemy->update(deltaTime);
            }
            else { cout << "Enemy est null" << endl; }
        }

        for (auto& enemy : enemies)
        {
            if (enemy->getBounds().intersects(player.getBounds()))
            {
                cout << "Game Over" << endl;
                return 0;
            }
        }

        window.clear();
        player.draw(window);
        for (auto& enemy : enemies)
        {
            enemy->draw(window);
        }
        window.display();

        for (auto& enemy : enemies)
        {
            delete enemy;
        }
    }
    return 0;
}