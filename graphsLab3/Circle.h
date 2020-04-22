#pragma once
#include <SFML/Graphics.hpp>
class Circle
{
public:
	Circle(sf::Font & t_font );
	~Circle(); 



	void load(std::string t_string, sf::Vector2f t_postion);
	void render(sf::RenderWindow & t_window);

	sf::CircleShape m_NodeCircle;
	sf::Vector2f m_NodePostion;
	float m_radius = 50;
	sf::Text m_name;


	sf::Font & m_font;
	
};

