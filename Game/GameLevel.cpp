#include "GameLevel.h"
#include "Game/Game.h"

GameLevel::GameLevel(const std::string& path, int widht, int height,Game& game) :
	m_Game(game)
{
	ResourceLoader::Texture2DFromImage(m_DefaulBlockTexture, "assets/texture/block.png");
	ResourceLoader::Texture2DFromImage(m_SolidBlockTexture, "assets/texture/block_solid.png");
	std::ifstream file(path);
	std::string line;
	std::vector<std::vector<unsigned int>> tiles;
	std::vector<unsigned int> current_line;
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			for (int i = 0; i < line.size(); i++)
			{
				current_line.push_back(((int)line[i] - 48));
			}
			tiles.push_back(current_line);
			current_line.clear();
		}
	}
	else {
		std::exit(1);
	}
	unsigned int level_height = height / 2;
	unsigned int unit_width = widht / (unsigned int)tiles[0].size();
	unsigned int unit_height = level_height / (unsigned int)tiles.size();
	Bricks.reserve(tiles[0].size() * tiles.size());
	bool is_solid;
	glm::vec3 m_Color;
	for (unsigned int y = 0; y < tiles.size(); y++)
	{
		for (unsigned int x = 0; x < tiles[0].size(); x++)
		{
			if (tiles[y][x] > 0)
			{
				glm::vec2 Size(unit_width, unit_height);
				if (tiles[y][x] == 1)
				{
					m_Color = glm::vec3(1.0f);
					is_solid = true;
					m_SolidCount++;
				}
				else
				{
					if (tiles[y][x] == 2) {
						m_Color = glm::vec3(1.0f, 0.0f, 1.0f);
					}
					else {
						m_Color = glm::vec3(1.0f, 1.0f, 0.0f);
					}
					is_solid = false;
					m_BricksCount++;
				}
				Bricks.push_back(Tile(glm::vec2(
					unit_width * x + unit_width / 2.0f, height - unit_height - (y * unit_height) + unit_height / 2.0f),
					glm::vec2(unit_width, unit_height),
					m_Color, is_solid));
			}
		}
	}
}

GameLevel::~GameLevel()
{
}

void GameLevel::Draw()
{
	for (const auto& tile : Bricks)
	{
		if (!tile.m_Destroyed)
		{
			if (tile.m_Solid)
			{
				Renderer::DrawSprite(m_SolidBlockTexture, tile.Position, tile.Size, tile.m_Color);
			}
			else {
				Renderer::DrawSprite(m_DefaulBlockTexture, tile.Position, tile.Size,tile.m_Color);
			}
		}
	}
}

void GameLevel::Destroy(Tile& tile)
{
	tile.m_Destroyed = true;
	m_BricksCount--;
	if (m_BricksCount == 0)
	{
		m_Game.Win();
	}
}

void GameLevel::Reset()
{
	for (auto& brick : Bricks)
	{
		brick.m_Destroyed = false;
	}
	m_BricksCount = (unsigned int)Bricks.size() - m_SolidCount;
}
