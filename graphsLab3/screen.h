#pragma once
#include <SFML/Graphics.hpp>
#include "Circle.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "Graph.h"
#include <utility> // for STL pair

using namespace std;

typedef GraphArc<std::pair<std::string, int>, int> Arc;
typedef GraphNode<std::pair<std::string, int>, int> Node;


class Screen
{
public:
	Screen();
	~Screen();
	sf::RenderWindow m_window; // main SFML window



	void run();

	void aStar();
	
private:
	
	sf::Texture mapTexture;
	sf::Sprite mapSprite;

	bool leftClicked = false;
	bool rightClicked = false;
	std::string m_clickOne;
	std::string m_clickTwo;

	sf::Font m_font;

	std::vector<Circle> m_NodeShape;

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();

	Graph< pair<string, int>, int > m_graph; // (30);

	int i = 0;
	map<string, int>nodeMap;
	pair<string, int> city;

	ifstream myfile;
	int x, y;
	std::string from, to;
	int weight;
	std::vector<Node *> path;
};

