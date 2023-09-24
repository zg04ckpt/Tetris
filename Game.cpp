#include "Game.h"

void Game::initMusicAndSound()
{
	int random = rand() % 2 + 1;
	if(random == 1)
		this->bg_music.openFromFile("music_sound/bg_music3.wav");
	else
		this->bg_music.openFromFile("music_sound/bg_music5.wav");
	this->bg_music.setLoop(true);
	this->bg_music.play();

	this->score_sb.loadFromFile("music_sound/sound7.wav");
	this->lose_sb.loadFromFile("music_sound/gameover.wav");
	this->getScoreSound.setBuffer(this->score_sb);
	this->loseSound.setBuffer(this->lose_sb);
}

void Game::initField()
{
	for (int i = 0; i < FIELD_H; i++)
	{
		for (int j = 0; j < FIELD_W; j++)
		{
			this->field[i][j] = -1;
		}
	}
}

void Game::initVariables()
{
	this->keyHold = false;
	this->slow = false;
	this->isUpdate = true;
	this->score = 0;
	this->isPause = false;
	this->mouseHold = false;
	this->isLose = false;

	std::ifstream ifs("highest_score.txt");
	ifs >> this->highestScore;
	ifs.close();
}

void Game::initBlock()
{
	this->block = new Block();
}

void Game::initTextureAndSprite()
{
	this->texture.loadFromFile(TEXTURE_PATH);
	this->sprite.setTexture(this->texture);
	this->sprite.setTextureRect(sf::IntRect(0, 0, UNIT, UNIT));
}


void Game::initWindow()
{
	this->window = new sf::RenderWindow
	(
		sf::VideoMode(SCREEN_W, SCREEN_H),
		TITLE,
		sf::Style::Close | sf::Style::Titlebar
	);
	this->window->setFramerateLimit(60);
}

Game::Game()
{
	this->initMusicAndSound();
	this->initField();
	this->initWindow();
	this->initVariables();
	this->initTextureAndSprite();
}

Game::~Game()
{
	delete this->window;
	delete this->block;
}


void Game::processEvent()
{
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
			case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::KeyPressed:
				if (this->event.key.code == sf::Keyboard::Escape)
				{
					//lưu điểm cao nhất 
					std::ofstream ofs("highest_score.txt", std::ios::trunc);
					ofs << this->highestScore;
					ofs.close();
					this->window->close();
				}
				break;
			case sf::Event::KeyReleased:
				this->keyHold = false;
				this->slow = false;
				this->boost = false;
				break;
			case sf::Event::MouseButtonReleased:
				this->mouseHold = false;
				break;
		}
	}
}

void Game::processInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !this->keyHold)
	{
		;
		if (this->isLocked(this->block->moveLeft()))
		{
			this->block->resetNextChange();
		}
		else
		{
			this->block->update();
		}
		this->keyHold = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !this->keyHold)
	{
		if (this->isLocked(this->block->moveRight()))
		{
			this->block->resetNextChange();
		}
		else
		{
			this->block->update();
		}
		this->keyHold = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !this->keyHold)
	{	
		if (this->isLocked(this->block->rotate()))
		{
			this->block->resetNextChange();
		}
		else
		{
			this->slow = true;
			this->block->update();
		}
		this->keyHold = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !this->keyHold)
	{
		this->boost = true;
		this->keyHold = true;
	}
}



bool Game::isLocked(std::vector<Pos> v)
{
	Pos center = v[1];
	for (Pos p : v)
	{
		if (p.x < 0 || p.x >= FIELD_W || p.y >= FIELD_H || this->field[p.y][p.x] != -1)
		{
			return true;
		}
	}
	return false;
}

void Game::reset()
{
	this->block = new Block();
	this->initField();
	this->score = 0;
}

void Game::processMouseClick()
{
	if (this->gui.getExitButtonBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this->window))) ||
		this->gui.getExit2Button().getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this->window))))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			//lưu điểm cao nhất 
			std::ofstream ofs("highest_score.txt", std::ios::trunc);
			ofs << this->highestScore;
			ofs.close();
			this->window->close();
		}
	}

	if (this->gui.getPauseButtonBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this->window))))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->mouseHold)
		{
			std::cout << "pause\n";
			this->isPause = !this->isPause;
			this->gui.pause = !this->gui.pause;
			this->mouseHold = true;
		}
	}

	if (this->gui.getLoadButtonBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this->window))) || 
		this->gui.getLoadBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this->window))) || 
		this->gui.getMusicBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this->window))))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			std::cout << "keo\n";
			this->gui.setCurX(sf::Mouse::getPosition(*this->window).x);
			this->mouseHold = true;
		}
	}

	if (this->gui.getReplayButton().getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this->window))))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !this->mouseHold)
		{
			std::cout << "replay\n";
			this->isLose = false;
			this->reset();
			this->mouseHold = true;
		}
	}
}

void Game::updateBlock()
{
	float realFallTime;
	if (this->score < 5)
		realFallTime = 0.5f;
	else if (this->score < 20)
		realFallTime = 0.4f;
	else if (this->score < 50)
		realFallTime = 0.3f;
	else
		realFallTime = 0.2f;

	if (this->slow) realFallTime += DELAY_TIME;
	if (this->boost) realFallTime = 0.1f;

	

	if (this->fallTimer.getElapsedTime().asSeconds() >= realFallTime)
	{
		if (this->isLocked(this->block->moveDown()))
		{
			//khi block đã rơi xuống đáy
			this->block->resetNextChange(); //reset để nextChange = vị trí hiện tại
			std::vector<Pos> locked = this->block->getNextChange();
			for (Pos p : locked)
			{
				field[p.y][p.x] = 1;
			}

			//xóa block đã khoa và tạo block mới
			delete this->block;
			this->block = new Block();
			//kiểm tra nếu block mới tạo bị khóa luôn là thua
			if (this->isLocked(this->block->getNextChange()))
			{
				this->loseSound.play();
				this->isLose = true;

				//lưu điểm cao nhất 
				std::ofstream ofs("highest_score.txt", std::ios::trunc);
				ofs << this->highestScore;
				ofs.close();
			}
		}
		else
		{
			this->block->update();
			this->fallTimer.restart();
		}
	}
}

void Game::updateField()
{
	//kiểm tra xem có hàng nào đó đầy hay không
	for (int i = FIELD_H-1; i >= 0; i--)
	{
		bool isRowFull = true;
		for (int j = 0; j < FIELD_W; j++)
		{
			if (this->field[i][j] == -1)
			{
				isRowFull = false;
			}
		}

		if (isRowFull)
		{
			this->score += 5;
			if (this->score > this->highestScore) this->highestScore = this->score;

			this->getScoreSound.play();

			for (int k = i; k >= 1; k--)
			{
				for (int h = 0; h < FIELD_W; h++)
				{
					this->field[k][h] = this->field[k - 1][h];
				}
			}

			for (int h = 0; h < FIELD_W; h++)
			{
				this->field[0][h] = -1;
			}

			break;
		}
	}
}

void Game::updateVolume()
{
	this->bg_music.setVolume(this->gui.getVolume());
}

void Game::renderField()
{
	for (int i = 0; i < FIELD_H; i++)
	{
		for (int j = 0; j < FIELD_W; j++)
		{
			if (this->field[i][j] != -1)
			{
				this->sprite.setPosition(j * UNIT, i * UNIT);
				this->window->draw(this->sprite);
			}
		}
	}
}

void Game::update()
{
	this->processEvent();
	this->updateVolume();
	if (!this->gui.begin)
	{
		this->processInput();
		this->processMouseClick();
		if (!this->isPause && !this->isLose)
		{
			this->updateBlock();
		}
		this->gui.update(this->score, this->highestScore);
		this->updateField();
	}
	else
	{
		this->gui.updateBegin(0, 2);
		if (this->gui.getPlayButtonBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this->window))))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				this->gui.begin = false;
				this->initBlock();
			}
		}
	}
}



void Game::render()
{
	this->window->clear(sf::Color::White);

	if (this->gui.begin)
	{
		this->gui.renderBegin(this->window);
	}
	else
	{
		this->gui.render(this->window);
		this->block->render(this->window);
		this->renderField();
		if (this->isPause)
		{
			this->window->draw(this->gui.getPauseLabel());
		}
		else if (this->isLose)
		{
			this->window->draw(this->gui.getLoseLabel());
			this->window->draw(this->gui.getExit2Button());
			this->window->draw(this->gui.getReplayButton());
		}
	}

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}
