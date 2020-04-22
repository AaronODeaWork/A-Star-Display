#include "Circle.h"




Circle::Circle(sf::Font & t_font) :
	m_font(t_font)
{
}

Circle::~Circle()
{
}

void Circle::load(std::string t_string, sf::Vector2f t_postion)
{
	m_NodePostion = sf::Vector2f(t_postion.x+500 ,t_postion.y+100 );
	m_NodeCircle.setPosition(m_NodePostion);
	m_NodeCircle.setFillColor(sf::Color::Blue);
	m_NodeCircle.setRadius(m_radius);
	m_name.setString( t_string );
	m_name.setFont(m_font);
	m_name.setFillColor(sf::Color::Black);
	m_name.setScale(2, 2);
	m_name.setPosition(sf::Vector2f(m_NodePostion.x+m_radius,m_NodePostion.y + 20));

}

void Circle::render(sf::RenderWindow & t_window)
{
	//t_window.clear(sf::Color::White);

	t_window.draw(m_NodeCircle);
	t_window.draw(m_name);
}
