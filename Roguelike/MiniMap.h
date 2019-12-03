#ifndef MINIMAP_H
#define MINIMAP_H

#include "Map.h"

namespace MiniMap
{
	inline static void Draw(Map& map, int playerX, int playerY, int size = 2)
	{
		for (int y = 0; y < map.Height(); y++)
		{
			for (int x = 0; x < map.Width(); x++)
			{
				int realX = x * size;
				int realY = y * size;

				if (map.Tiles()[x + y * map.Width()].explored)
				{
					if (map.Tiles()[x + y * map.Width()].tileId == 1)
					{
						for (int i = 0; i < size; i++)
							for (int j = 0; j < size; j++)
								Graphics::Instance().DrawPixel(Graphics::SCREEN_WIDTH - map.Width() * size + realX + i, realY + j, { 112, 128, 144, 125 });
					}
					else if (map.Tiles()[x + y * map.Width()].tileId == 0)
					{
						for (int i = 0; i < size; i++)
							for (int j = 0; j < size; j++)
								Graphics::Instance().DrawPixel(Graphics::SCREEN_WIDTH - map.Width() * size + realX + i, realY + j, { 192, 192, 192, 125 });
					}
				}
			}
		}

		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				Graphics::Instance().DrawPixel(Graphics::SCREEN_WIDTH - map.Width() * size + playerX * size + i, playerY * size + j, { 0, 255, 0, 125 });
	}
};

#endif