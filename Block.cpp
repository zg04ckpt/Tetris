#include "Block.h"
#include "Game.h"

void Block::initTexture()
{
	this->texture.loadFromFile(TEXTURE_PATH);
}

void Block::initSprite()
{
	this->sprite.setTexture(this->texture);

	//randow color
	int color = rand() % 7 + 1;
	this->sprite.setTextureRect(sf::IntRect(UNIT * color, 0, UNIT, UNIT));
}

void Block::initPositions()
{
	int type = rand() % 7 + 1;
	if (type == 1)
	{
		this->positions.push_back(new Pos{ 1, 0 });
		this->positions.push_back(new Pos{ 1, 1 });
		this->positions.push_back(new Pos{ 1, 2 });
		this->positions.push_back(new Pos{ 1, 3 });
	}
	else if (type == 2)
	{
		this->positions.push_back(new Pos{ 0, 0 });
		this->positions.push_back(new Pos{ 1, 0 });
		this->positions.push_back(new Pos{ 0, 1 });
		this->positions.push_back(new Pos{ 1, 1 });
	}
	else if (type == 3)
	{
		this->positions.push_back(new Pos{ 0, 0 });
		this->positions.push_back(new Pos{ 1, 0 });
		this->positions.push_back(new Pos{ 1, 1 });
		this->positions.push_back(new Pos{ 1, 2 });
	}
	else if (type == 4)
	{
		this->positions.push_back(new Pos{ 1, 0 });
		this->positions.push_back(new Pos{ 1, 1 });
		this->positions.push_back(new Pos{ 0, 1 });
		this->positions.push_back(new Pos{ 0, 2 });
	}
	else if (type == 5)
	{
		this->positions.push_back(new Pos{ 0, 0 });
		this->positions.push_back(new Pos{ 0, 1 });
		this->positions.push_back(new Pos{ 1, 1 });
		this->positions.push_back(new Pos{ 1, 2 });
	}
	else if (type == 6)
	{
		this->positions.push_back(new Pos{ 1, 0 });
		this->positions.push_back(new Pos{ 1, 1 });
		this->positions.push_back(new Pos{ 1, 2 });
		this->positions.push_back(new Pos{ 0, 2 });
	}
	else if (type == 7)
	{
		this->positions.push_back(new Pos{ 1, 0 });
		this->positions.push_back(new Pos{ 1, 1 });
		this->positions.push_back(new Pos{ 0, 1 });
		this->positions.push_back(new Pos{ 1, 2 });
	}
	for (int i = 0; i < 4; i++)
	{
		this->positions[i]->x += 8;
		this->nextChange.push_back(*this->positions[i]);
	}
}

Block::Block()
{
	this->initTexture();
	this->initSprite();
	this->initPositions();
}

Block::~Block()
{
	for (auto p : this->positions)
	{
		delete p;
	}
}

std::vector<Pos> Block::getNextChange()
{
	std::vector<Pos> v;
	for (auto p : this->positions)
	{
		v.push_back(*p);
	}
	return v;
}

void Block::resetNextChange()
{
	for (int i = 0; i < 4; i++)
	{
		this->nextChange[i].x = this->positions[i]->x;
	}
}

std::vector<Pos> Block::moveLeft()
{
	for (int i = 0; i < 4; i++)
	{
		this->nextChange[i].x = this->positions[i]->x - 1;
	}
	return this->nextChange;
}

std::vector<Pos> Block::moveRight()
{
	for (int i = 0; i < 4; i++)
	{
		this->nextChange[i].x = this->positions[i]->x + 1;
	}
	return this->nextChange;
}

std::vector<Pos> Block::moveDown()
{
	for (int i = 0; i < 4; i++)
	{
		this->nextChange[i].y = this->positions[i]->y + 1;
	}
	return this->nextChange;
}

std::vector<Pos> Block::rotate()
{
	Pos* center = this->positions[1];
	for (int i = 0; i < 4; i++)
	{
		int dx = center->x - this->positions[i]->x;
		int dy = center->y - this->positions[i]->y;
		this->nextChange[i].x = center->x + dy;
		this->nextChange[i].y = center->y - dx;
	}
	return this->nextChange;
}

void Block::update()
{
	for (int i = 0; i < 4; i++)
	{
		this->positions[i]->x = this->nextChange[i].x;
		this->positions[i]->y = this->nextChange[i].y;
	}
}

void Block::render(sf::RenderTarget* target)
{
	for (auto p : this->positions)
	{
		this->sprite.setPosition(p->x * UNIT, p->y * UNIT);
		target->draw(this->sprite);
	}
}
