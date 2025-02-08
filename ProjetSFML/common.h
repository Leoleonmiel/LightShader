#ifndef COMMON__H
#define COMMON__H

#include <iostream>
#include <time.h>

#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/OpenGL.hpp"

sf::Sprite LoadSprite(const std::string _path, bool _isCentered);
void BlitSprite(sf::Sprite _sprite, sf::Vector2f _pos, float _angle, sf::RenderWindow& _window);
void BlitSprite(sf::Sprite _sprite, sf::Vector2f _pos, float _angle, sf::RenderTexture& _rt, sf::RenderStates _mode = sf::RenderStates::Default);
void BlitSprite(sf::Sprite _sprite, sf::Vector2f _pos, float _angle, sf::RenderTexture& _rt, sf::BlendMode _mode);

#endif