#include "common.h"

struct Torch {
	sf::Sprite sprite;
	sf::Shader shader;
	sf::Vector2i position;
	sf::Color color;
};


int main()
{
	sf::Vector2f windowSize(1920, 1080);
	sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "My window");

	sf::Sprite background = LoadSprite("background.png", false);
	sf::Sprite lumiere = LoadSprite("lumiere.png", false);
	lumiere.setOrigin(lumiere.getTextureRect().width / 2, lumiere.getTextureRect().height / 2);

	std::vector<Torch*> torches;
	std::vector<sf::Vector2i> torchPos;
	std::vector<sf::RenderStates> torchState;

	sf::RenderTexture RTEffect;
	RTEffect.create(windowSize.x, windowSize.y);

	sf::RenderTexture RTScene;
	RTScene.create(windowSize.x, windowSize.y);

	sf::Sprite sceneSpr;
	sceneSpr.setTexture(RTScene.getTexture());


	sf::RenderStates blendState;
	sf::Shader hardLightShader;
	hardLightShader.loadFromFile("Shader/HardLightBlend.frag", sf::Shader::Fragment);
	hardLightShader.setUniform("texture1", sf::Shader::CurrentTexture);
	hardLightShader.setUniform("texture2", RTEffect.getTexture());
	blendState.shader = &hardLightShader;


	sf::Shader backgroundShader;
	backgroundShader.loadFromFile("Shader/base.frag", sf::Shader::Fragment);

	sf::Clock clock;
	sf::Shader mouseShader;
	mouseShader.loadFromFile("Shader/Light.frag", sf::Shader::Fragment);
	mouseShader.setUniform("intensity", 0.7f);
	sf::Color color = sf::Color::White;
	mouseShader.setUniform("lcolor", sf::Glsl::Vec4(1.f, 1.f, 1.f, 1.f));
	mouseShader.setUniform("glowingFactor", 5.5f);
	sf::RenderStates mouseState;
	mouseState.blendMode = sf::BlendAdd;
	mouseState.shader = &mouseShader;


	while (window.isOpen())
	{
		window.setMouseCursorVisible(false);
		sf::Event event;
		float timer = clock.getElapsedTime().asSeconds();
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{

					Torch* torch = new Torch();
					torch->sprite = LoadSprite("lumiere2.png", false);
					torch->color = sf::Color(100 + rand() % 255, 100 + rand() % 255, 100 + rand() % 255, 255);
					torch->shader.loadFromFile("Shader/Light.frag", sf::Shader::Fragment);
					torch->shader.setUniform("intensity", 2.0f);
					torch->shader.setUniform("lcolor", sf::Glsl::Vec4(torch->color.r / 255.f, torch->color.g / 255.f, torch->color.b / 255.f, 1.f));
					torch->shader.setUniform("glowingFactor", 5.5f);
					

					sf::Vector2i mousePos = sf::Mouse::getPosition(window);
					mousePos.x -= torch->sprite.getTextureRect().width / 2;
					mousePos.y -= torch->sprite.getTextureRect().height / 2;
					torch->position = mousePos;
					torchPos.push_back(mousePos);
					sf::RenderStates state;
					state.blendMode = sf::BlendAdd;
					state.shader = &torch->shader;
					torchState.push_back(state);
					torches.push_back(torch);
				}
			}
		}

		for (auto torch : torches)
		{
			torch->shader.setUniform("timer", timer);
		}

		mouseShader.setUniform("timer", timer);
		if (timer > 10.f)
		{
			timer = 0.f;
		}

		RTScene.clear(sf::Color(150,150,150,255));
		RTEffect.clear(sf::Color(10, 10, 10, 255));

		BlitSprite(background, { 0,0 }, 0, RTScene);
		if (!torches.empty()) {
			sf::Vector2f lightPos = (sf::Vector2f)torches.back()->position;
			float lightRadius = 100.0f;
		}


		for (int i = 0; i < torches.size(); i++)
		{
			BlitSprite(torches[i]->sprite, (sf::Vector2f)torchPos[i], 0, RTEffect, torchState[i]);
		}

		BlitSprite(lumiere, (sf::Vector2f)sf::Mouse::getPosition(window), 0, RTEffect, mouseState);

		RTEffect.display();
		RTScene.display();
		window.draw(sceneSpr, &hardLightShader);

		for (int i = 0; i < torches.size(); i++)
		{
			torches[i]->sprite.setPosition((sf::Vector2f)torchPos[i]);
			window.draw(torches[i]->sprite);
		}

		window.display();
	}
}
