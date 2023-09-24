#pragma once
#include "common.h"

class Block
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	std::vector<Pos*> positions;
	std::vector<Pos> nextChange;

	void initTexture();
	void initSprite();
	void initVariables();
	void initPositions();
public:
	Block();
	~Block();

	std::vector<Pos> getNextChange();
	void resetNextChange();

	std::vector<Pos> moveLeft();
	std::vector<Pos> moveRight();
	std::vector<Pos> moveDown();
	std::vector<Pos> rotate();

	void update();
	void render(sf::RenderTarget* target);
};

