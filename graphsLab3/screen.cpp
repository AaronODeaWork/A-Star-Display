#include "screen.h"

void visit(Node * node) {
	cout << "Visiting: " << node->data().first << endl;
}

Screen::Screen() :
	m_window{ sf::VideoMode{ 1920 , 1080, 32 }, "map ",sf::Style::Default },
	m_graph(30)
{
	if (!mapTexture.loadFromFile("map.png"))
	{
		std::cout << "map error" << std::endl;
	}
	mapSprite.setTexture(mapTexture);
	mapSprite.setPosition(sf::Vector2f(-20, 0));

	if (!m_font.loadFromFile("arial.ttf"))
	{
		std::cout << "font error" << std::endl;
	}
	myfile.open("nodes.txt");
	while (myfile >> city.first >> x >> y)
	{
		m_graph.addNode(city, i, x, y);

		nodeMap[city.first] = i;
		m_NodeShape.push_back(Circle(m_font));
		m_NodeShape.at(i).load(city.first, sf::Vector2f(x* 3, y * 3));
		i++;
	}
	myfile.close();
	myfile.open("arcs.txt");

	while (myfile >> from >> to >> weight) {
		m_graph.addArc(nodeMap[from], nodeMap[to], weight);
	}
	myfile.close();

}

Screen::~Screen()
{
}

void Screen::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			// Close window : exit
			if (event.type == sf::Event::Closed)
				m_window.close();
		}
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
		}

		render(); // as many as possible
	}


}

void Screen::aStar()
{
	path.clear();
	m_graph.aStar(m_graph.nodeIndex(nodeMap[m_clickOne]), m_graph.nodeIndex(nodeMap[m_clickTwo]), visit, path);
	std::cout << "----------------------------------------------------------------------------------------------------------------" << std::endl;
	for (int i = (path.size() - 1); i >= 0; i--)
	{
		std::cout << path[i]->data().first << std::endl;
		for (int j = 0; j < m_NodeShape.size(); j++)
		{
			if (m_NodeShape[j].m_name.getString() == path[i]->data().first)
			{
				m_NodeShape[j].m_NodeCircle.setFillColor(sf::Color::Red);
			}
		}
	}
	std::cout << "----------------------------------------------------------------------------------------------------------------" << std::endl;

}

void Screen::processEvents()
{
}

void Screen::update(sf::Time t_deltaTime)
{

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && leftClicked == false)
	{
		for (int i = 0; i < m_NodeShape.size(); i++)
		{
			if (sf::Mouse::getPosition(m_window).x > m_NodeShape[i].m_NodePostion.x &&
				sf::Mouse::getPosition(m_window).x <= (m_NodeShape[i].m_NodePostion.x + (m_NodeShape[i].m_radius *2)) &&
				sf::Mouse::getPosition(m_window).y > m_NodeShape[i].m_NodePostion.y &&
				sf::Mouse::getPosition(m_window).y <= (m_NodeShape[i].m_NodePostion.y + (m_NodeShape[i].m_radius * 2))
				)
			{
			
					m_NodeShape[i].m_NodeCircle.setFillColor(sf::Color::Green);
					m_clickOne = m_NodeShape[i].m_name.getString();
					leftClicked = true;
			}
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && rightClicked == false)
	{
		for (int i = 0; i < m_NodeShape.size(); i++)
		{
			if (sf::Mouse::getPosition(m_window).x > m_NodeShape[i].m_NodePostion.x &&
				sf::Mouse::getPosition(m_window).x <= (m_NodeShape[i].m_NodePostion.x + (m_NodeShape[i].m_radius * 2)) &&
				sf::Mouse::getPosition(m_window).y > m_NodeShape[i].m_NodePostion.y &&
				sf::Mouse::getPosition(m_window).y <= (m_NodeShape[i].m_NodePostion.y + (m_NodeShape[i].m_radius * 2))
				)
			{
					m_NodeShape[i].m_NodeCircle.setFillColor(sf::Color::Green);
					m_clickTwo = m_NodeShape[i].m_name.getString();
					rightClicked = true;
			}
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
	{
		for (int i = 0; i < m_NodeShape.size(); i++)
		{
			m_NodeShape[i].m_NodeCircle.setFillColor(sf::Color::Blue);
		}
		rightClicked = false;
		leftClicked = false;
		aStar();
	}


}

void Screen::render()
{
	
	m_window.clear();
	m_window.draw(mapSprite);
	for (int i = 0; i < m_NodeShape.size(); i++)
	{
		m_NodeShape[i].render(m_window);
	}
	m_window.display();
}

