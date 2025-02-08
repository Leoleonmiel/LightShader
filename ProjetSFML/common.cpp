#include "common.h"

sf::Sprite LoadSprite(const std::string _path, bool _isCentered)
{
	sf::Texture* tempTex = new sf::Texture(); 
	tempTex->loadFromFile(_path);

	sf::Sprite tempSprite;
	tempSprite.setTexture(*tempTex);

	if (_isCentered) 
	{
		sf::Vector2u tempTaille = tempTex->getSize();
		sf::Vector2f tempOrigin = sf::Vector2f(tempTaille.x / 2, tempTaille.y / 2);
		tempSprite.setOrigin(tempOrigin);
	}

	return tempSprite;
}

void BlitSprite(sf::Sprite _sprite, sf::Vector2f _pos, float _angle, sf::RenderWindow& _window)
{
	_sprite.setRotation(_angle);
	_sprite.setPosition(_pos);
	_window.draw(_sprite);
}

void BlitSprite(sf::Sprite _sprite, sf::Vector2f _pos, float _angle, sf::RenderTexture& _rt, sf::RenderStates _mode)
{
	_sprite.setRotation(_angle);
	_sprite.setPosition(_pos);
	_rt.draw(_sprite, _mode);
}
void BlitSprite(sf::Sprite _sprite, sf::Vector2f _pos, float _angle, sf::RenderTexture& _rt, sf::BlendMode _mode)
{
	_sprite.setRotation(_angle);
	_sprite.setPosition(_pos);
	_rt.draw(_sprite, _mode);
}
