#pragma once
#include "GUI.h"
#include "Block.h"

class Game
{
public:
	Game();
	~Game();

	void run();
	
private:
	GUI gui;
	sf::RenderWindow* window;
	sf::Event event;
	Block* block;
	int field[FIELD_H][FIELD_W];
	sf::Clock fallTimer;
	sf::Clock delayTimer;
	sf::Clock boostTimer;

	//texture và sprite để điền các ông đã lock
	sf::Texture texture;
	sf::Sprite sprite;

	//logic
	int score;
	int highestScore;

	//status
	bool keyHold;
	bool mouseHold;
	bool slow;
	bool boost;
	bool isUpdate;
	bool isPause;
	bool isLose;

	//music and sound
	sf::Music bg_music;
	sf::SoundBuffer score_sb, lose_sb;
	sf::Sound getScoreSound, loseSound;

	//init
	void initMusicAndSound();
	void initField();
	void initWindow();
	void initVariables();
	void initBlock();
	void initTextureAndSprite();

	//Func
	bool isLocked(std::vector<Pos> v);
	void reset();

	//
	void processEvent();
	void processInput();
	void processMouseClick();
	void updateBlock();
	void updateField();
	void updateVolume();
	void update();

	void renderField();
	void render();
};

