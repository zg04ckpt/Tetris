#ifndef _COMMON_H
#define _COMMON_H

#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>

#include<iostream>
#include<time.h>
#include<vector>
#include<string>
#include<sstream>
#include<fstream>

const std::string TITLE = "Tetris";
const int SCREEN_W = 600;
const int SCREEN_H = 600;
const int UNIT = 18; //PIXEL
const std::string TEXTURE_PATH = "img/tiles.png"; //PIXEL
const std::string FIELD_TEXTURE_PATH = "img/field.png"; //PIXEL
const std::string FONT_PATH = "font/test.otf"; //PIXEL
const int HEADER_SIZE = 36;
const int NORMAL_SIZE = 18;

const int FIELD_W = 20;
const int FIELD_H = 30;

const float FALL_TIME = 0.5f;
const float DELAY_TIME = 0.25f;
const float BOOST_TIME = 0.4f;

struct Pos
{
	int x, y;
};

bool isLocked(int y, int x);
void initField();

#endif // !1
