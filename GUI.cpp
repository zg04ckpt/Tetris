#include "GUI.h"

GUI::GUI()
{
	this->initVariables();
	this->initFieldBackground();
	this->initFontAndText();
	this->initTextures();
	this->initSprites();
}

GUI::~GUI()
{
}

sf::FloatRect GUI::getPlayButtonBounds()
{
	return this->play_s.getGlobalBounds();
}

sf::FloatRect GUI::getPauseButtonBounds()
{
	return this->pause_s.getGlobalBounds();
}

sf::FloatRect GUI::getExitButtonBounds()
{
	return this->exit_s.getGlobalBounds();
}

sf::FloatRect GUI::getLoadButtonBounds()
{
	return this->load_button_s.getGlobalBounds();
}

sf::FloatRect GUI::getLoadBounds()
{
	return this->load_s.getGlobalBounds();
}

sf::FloatRect GUI::getMusicBounds()
{
	return this->music_s.getGlobalBounds();
}

sf::Sprite GUI::getPauseLabel()
{
	return this->pause_label_s;
}

sf::Sprite GUI::getLoseLabel()
{
	return this->lose_s;
}

sf::Sprite GUI::getExit2Button()
{
	return this->exit2_s;
}

sf::Sprite GUI::getReplayButton()
{
	return this->replay_s;
}

int GUI::getVolume()
{
	float res;
	res = curX - startX;
	res = res / length * 100.f;
	if (res < 0) res = 0;
	return res;
}

void GUI::setCurX(float x)
{
	this->curX = x;
}

void GUI::initVariables()
{
	this->begin = true;
	this->pause = false;

	this->length = 243;
	this->startX = 95;
	this->curX = this->startX + 150;
}

void GUI::initFieldBackground()
{
	this->field_texture.loadFromFile(FIELD_TEXTURE_PATH);
	this->field_background.setTexture(this->field_texture);
}

void GUI::initTextures()
{
	this->logo_t.loadFromFile("img/logo.png");
	this->play_t.loadFromFile("img/play.png");
	this->pause_t.loadFromFile("img/pause.png");
	this->exit_t.loadFromFile("img/exit.png");
	this->score_t.loadFromFile("img/score.png");
	this->highest_t.loadFromFile("img/highest.png");
	this->background_t.loadFromFile("img/background.png");
	this->pause_label_t.loadFromFile("img/pause_label.png");
	this->music_t.loadFromFile("img/music.png");
	this->load_t.loadFromFile("img/load.png");
	this->load_button_t.loadFromFile("img/load_button.png");
	this->lose_t.loadFromFile("img/lose.png");
	this->replay_t.loadFromFile("img/replay.png");
	this->continue_t.loadFromFile("img/continue.png");
}

void GUI::initSprites()
{
	this->background_s.setTexture(this->background_t);
	this->background_s.setTextureRect(sf::IntRect(0, 0, 600, 600));

	this->logo_s.setTexture(this->logo_t);
	this->logo_s.setPosition(140.5f, 0);

	this->play_s.setTexture(this->play_t);
	this->play_s.setPosition(213.5f, 310);

	this->pause_s.setTexture(this->pause_t);
	this->pause_s.setPosition(402.5f, 400);

	this->exit_s.setTexture(this->exit_t);
	this->exit_s.setPosition(402.5f, 450);

	this->score_s.setTexture(this->score_t);
	this->score_s.setPosition(399.f, 30);

	this->highest_s.setTexture(this->highest_t);
	this->highest_s.setPosition(393.5f, 200);

	this->pause_label_s.setTexture(this->pause_label_t);
	this->pause_label_s.setPosition(43, 200);

	this->music_s.setTexture(this->music_t);
	this->music_s.setPosition(10, 570);

	this->load_button_s.setTexture(this->load_button_t);
	this->load_button_s.setOrigin(10, 10);
	this->load_button_s.setPosition(this->startX, 580);

	this->load_s.setTexture(this->load_t);
	this->load_s.setPosition(this->startX, 575);

	this->lose_s.setTexture(this->lose_t);
	this->lose_s.setPosition(102, 200);

	this->exit2_s.setTexture(this->exit_t);
	this->exit2_s.setPosition(117, 275);

	this->replay_s.setTexture(this->replay_t);
	this->replay_s.setPosition(310, 275);

	this->continue_s.setTexture(this->continue_t);
	this->continue_s.setPosition(402.5f, 400);
}

void GUI::initFontAndText()
{
	this->font.loadFromFile(FONT_PATH);

	//score text
	this->scoreText.setFont(this->font);
	this->scoreText.setCharacterSize(HEADER_SIZE);
	this->scoreText.setPosition(415, 70);
	this->scoreText.setFillColor(sf::Color::Black);

	this->highestText.setFont(this->font);
	this->highestText.setCharacterSize(HEADER_SIZE);
	this->highestText.setPosition(415, 245);
	this->highestText.setFillColor(sf::Color::Green);
}

void GUI::updateVolume()
{
	if (curX - startX <= 243.f && curX - startX >= 0.f)
	{
		this->load_button_s.setPosition(curX, 580);
		this->load_s.setTextureRect(sf::IntRect(0, 0, this->curX - this->startX, 9));
	}
}

void GUI::updateBegin(int dir_x, int dir_y)
{
	if (this->logo_s.getPosition().y < 200)
	{
		if (timer.getElapsedTime().asSeconds() >= 0.01f)
		{
			this->logo_s.move(dir_x, dir_y);
			this->timer.restart();
		}
	}
}

void GUI::update(int score, int highestScore)
{
	std::stringstream ss;
	std::string zero = "";
	if (score < 10) zero += "0000";
	else if (score < 100) zero += "000";
	else if (score < 1000) zero += "00";
	else if (score < 10000) zero += "0";
	ss << zero << score;
	this->scoreText.setString(ss.str());

	std::stringstream ss2;
	std::string zero2 = "";
	if (highestScore < 10) zero2 += "0000";
	else if (highestScore < 100) zero2 += "000";
	else if (highestScore < 1000) zero2 += "00";
	else if (highestScore < 10000) zero2 += "0";
	ss2 << zero2 << highestScore;
	this->highestText.setString(ss2.str());

	this->updateVolume();
}

void GUI::renderBegin(sf::RenderTarget* target)
{
	target->draw(this->background_s);
	target->draw(this->logo_s);
	if (this->logo_s.getPosition().y >= 200)
		target->draw(this->play_s);
}

void GUI::render(sf::RenderTarget* target)
{
	target->draw(this->background_s);
	target->draw(this->field_background);

	if (this->pause)
	{
		this->pause_s.setTexture(this->continue_t);
	}
	else
	{
		this->pause_s.setTexture(this->pause_t);
	}
	target->draw(this->pause_s);

	target->draw(this->exit_s);
	target->draw(this->score_s);
	target->draw(this->scoreText);
	target->draw(this->highest_s);
	target->draw(this->highestText);

	target->draw(this->music_s);
	target->draw(this->load_s);
	target->draw(this->load_button_s);
}
