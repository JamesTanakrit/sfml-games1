#include"AllHeader.h"
#include"player.h"
#include"enemy.h"
#include"bullet.h"
#include"Item.h"

float multiplier = 1;

int main()
{
    RenderWindow window(VideoMode(800, 600), "Game", Style::Titlebar | Style::Close);
    window.setVerticalSyncEnabled(true);

    srand(time(NULL));

    Clock clock;
    float deltaTime = 0;
    
    Texture maptexture;
    maptexture.loadFromFile("map.png");
    Sprite map;
    map.setTexture(maptexture);

    Player player;

    vector<Bullet> bullets;
    float fireRate = 0, fireRateMax = 0.5;

    vector<Enemy> enemies;
    float enemyRate = 0, enemyRateMax = 0.5;
    int EnemyNumMax = 10;

    vector<Item> items;

    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds() * multiplier;
        Event ev;
        while (window.pollEvent(ev))
        {
            if (ev.type == Event::Closed)
                window.close();
            else if (ev.type == Event::LostFocus)
            {
                multiplier = 0;
            }
            else if (ev.type == Event::GainedFocus)
            {
                multiplier = 1;
            }
        }

        //update
        player.update(deltaTime);

        //Update Bullet
        fireRate += deltaTime;
        enemyRate += deltaTime;

        if (Mouse::isButtonPressed(Mouse::Left) && fireRate >= fireRateMax)
        {
            Vector2f mousePos = Vector2f(Mouse::getPosition(window));
            Vector2f playerPos = player.getPosition() + player.getSize()/2.f - Vector2f(2.5f, 2.5f);
            bullets.push_back(Bullet(playerPos, mousePos - playerPos, 300.f));
            fireRate = 0;
        }

        for (size_t i = 0; i < bullets.size(); i++)
        {
            bullets[i].update(deltaTime);
            bool outLeft = bullets[i].getPosition().x + bullets[i].getSize().x < 0;
            bool outRight = bullets[i].getPosition().x > 800;
            bool outTop = bullets[i].getPosition().y + bullets[i].getSize().y < 0;
            bool outDown = bullets[i].getPosition().y > 600;
            if (outLeft || outRight || outTop || outDown)
            {
                bullets.erase(bullets.begin() + i);
            }
        }

        //Update enemy

        if (enemies.size() <= EnemyNumMax && enemyRate >= enemyRateMax)
        {
            enemies.push_back(Enemy(Vector2f(40, 40), Vector2f(760 * (rand() % 2), randint(128, 430)), randint(75, 100)));
            enemies[enemies.size() - 1].setPlayer(&player);
            enemyRate = 0;
        }
    
        for (size_t i = 0; i < enemies.size(); i++)
        {
            enemies[i].update(deltaTime);
            for (size_t j = 0; j < bullets.size(); j++)
            {
                if (bullets[j].getGlobalBounds().intersects(enemies[i].getGlobalBounds()))
                {
                    items.push_back(Item(enemies[i].getPosition(), Vector2f(20, 20), 0));
                    enemies.erase(enemies.begin() + i);
                    bullets.erase(bullets.begin() + j);
                    break;
                }
            }
        }

        for (size_t i = 0; i < items.size(); i++)
        {
            if (items[i].isPickedUp(player.getGlobalBounds()))
            {
                // do something
                if (items[i].tag == 0)
                {
                    fireRateMax = 0.1;
                }
                items.erase(items.begin() + i);
            }
        }

        window.clear();
        window.draw(map);

        //draw

        //draw bullets
        for (size_t i = 0; i < bullets.size(); i++)
        {
            bullets[i].render(window);
        }

        //draw enemies
        for (size_t i = 0; i < enemies.size(); i++)
        {
            enemies[i].render(window);
        }

        //draw items
        for (size_t i = 0; i < items.size(); i++)
        {
            items[i].render(window);
        }

        player.render(window);
        window.display();
    }
    return 0;
}