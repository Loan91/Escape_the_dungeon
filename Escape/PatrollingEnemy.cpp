#include "PatrollingEnemy.h"

PatrollingEnemy::PatrollingEnemy(float width, float height, Vector2f startPoint, Vector2f endPoint, float speed, const sf::Texture& texture) : Enemy(width, height, startPoint, speed), startPoint(startPoint), endPoint(endPoint), movingToEnd(true)
{
	sprite.setTexture(texture);
    sprite.setScale(width / texture.getSize().x, height / texture.getSize().y);
    sprite.setPosition(startPoint);
}

void PatrollingEnemy::update(float deltaTime, const Map& map)
{
    // Déterminer le point cible en fonction de la direction
    Vector2f targetPoint = movingToEnd ? endPoint : startPoint;
    Vector2f direction = targetPoint - sprite.getPosition();

    // Calculer la longueur du vecteur de direction pour normaliser le vecteur
    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0)
    {
        direction = direction / length; // Normaliser le vecteur pour avoir une vitesse constante
    }

    // Déplacer l'ennemi
    sprite.move(direction * speed * deltaTime);

    // Vérifier si l'ennemi a atteint sa cible (proche de son point de destination)
    if (length < speed * deltaTime)
    {
        // Inverser la direction et définir la nouvelle position exacte sur la cible
        movingToEnd = !movingToEnd;
        sprite.setPosition(targetPoint); // Positionner l'ennemi exactement au point cible
    }

    // Vérification des limites de l'écran (encadre l'ennemi dans les bords de la fenêtre)
    Vector2f position = sprite.getPosition();
    if (position.x < 0) position.x = 0;
    if (position.y < 0) position.y = 0;
    if (position.x + sprite.getGlobalBounds().width > 1920) position.x = 1920 - sprite.getGlobalBounds().width;
    if (position.y + sprite.getGlobalBounds().height > 1080) position.y = 1080 - sprite.getGlobalBounds().height;

    // Appliquer la position modifiée
    sprite.setPosition(position);
}