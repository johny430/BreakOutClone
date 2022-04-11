#pragma once
#include <vector>
#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "Tile.h"
#include "Engine/Engine.h"

class Game;

class GameLevel
{
public:
	GameLevel(const std::string& path,int widht,int height,Game& game);
	~GameLevel();
	void Draw();
	void Destroy(Tile& tile);
	void Reset();
public:
	std::vector<Tile> Bricks;
private:
	Texture m_SolidBlockTexture;
	Texture m_DefaulBlockTexture;
	unsigned int m_SolidCount = 0;
	unsigned int m_BricksCount = 0;
	Game& m_Game;
};