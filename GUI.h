#pragma once
#include "common.h"
class GUI
{
public:
	GUI();
	~GUI();

	void renderBegin(sf::RenderTarget* target);
	void updateBegin(int dir_x, int dir_y);

	void update(int score, int highestScore);
	void render(sf::RenderTarget* target);

	sf::FloatRect getPlayButtonBounds();
	sf::FloatRect getPauseButtonBounds();
	sf::FloatRect getExitButtonBounds();
	sf::FloatRect getLoadButtonBounds();
	sf::FloatRect getLoadBounds();
	sf::FloatRect getMusicBounds();
	sf::Sprite getPauseLabel();
	sf::Sprite getLoseLabel();
	sf::Sprite getExit2Button();
	sf::Sprite getReplayButton();

	int getVolume();
	void setCurX(float x);

	bool begin;
	bool pause;
private:
	sf::Texture field_texture, logo_t, play_t, pause_t, exit_t, score_t, highest_t;
	sf::Texture background_t, pause_label_t, music_t, load_t, load_button_t, lose_t, replay_t, continue_t;
	sf::Sprite field_background, logo_s, play_s, pause_s, exit_s, score_s, highest_s;
	sf::Sprite background_s, pause_label_s, music_s, load_s, load_button_s, lose_s, replay_s, continue_s, exit2_s;
	sf::Font font;
	sf::Text scoreText, highestText;

	//xử lí thanh kéo volume
	float length;
	float startX;
	float curX;

	sf::Clock timer;

	void initVariables();
	void initFieldBackground();
	void initTextures();
	void initSprites();
	void initFontAndText();

	void updateVolume();
};

