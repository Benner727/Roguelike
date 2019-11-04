#ifndef FOV_H
#define FOV_H

#include "Map.h"

#include <cmath>

namespace FOV
{
	static int multipliers[4][8] = {
		{1, 0, 0, -1, -1, 0, 0, 1},
		{0, 1, -1, 0, 0, -1, 1, 0},
		{0, 1, 1, 0, 0, -1, -1, 0},
		{1, 0, 0, 1, -1, 0, 0, -1}
	};

	inline static void CastLight(Map& map, int x, int y, int radius, int row,
		float start_slope, float end_slope, int xx, int xy, int yx, int yy)
	{
		if (start_slope < end_slope)
		{
			return;
		}

		float next_start_slope = start_slope;

		for (int i = row; i <= radius; i++)
		{
			bool blocked = false;

			for (int dx = -i, dy = -i; dx <= 0; dx++)
			{
				float l_slope = (dx - 0.5) / (dy + 0.5);
				float r_slope = (dx + 0.5) / (dy - 0.5);				
				if (start_slope < r_slope)
				{
					continue;
				}
				else if (end_slope > l_slope)
				{
					break;
				}

				int sax = dx * xx + dy * xy;
				int say = dx * yx + dy * yy;				
				if ((sax < 0 && (int)std::abs(sax) > x) ||
					(say < 0 && (int)std::abs(say) > y))
				{
					continue;
				}
				
				int ax = x + sax;
				int ay = y + say;
				if (ax >= map.Width() || ay >= map.Height())
				{
					continue;
				}

				int radius2 = radius * radius;
				if ((int)(dx * dx + dy * dy) < radius2)
				{
					map.SetVisible(ax, ay, true);
				}

				if (blocked)
				{
					if (map.Opaque(ax, ay))
					{
						next_start_slope = r_slope;
						continue;
					}
					else
					{
						blocked = false;
						start_slope = next_start_slope;
					}
				}
				else if (map.Opaque(ax, ay))
				{
					blocked = true;
					next_start_slope = r_slope;
					CastLight(map, x, y, radius, i + 1, start_slope, l_slope, xx,
						xy, yx, yy);
				}
			}

			if (blocked)
			{
				break;
			}
		}
	}

	inline static void CalculateFOV(Map& map, int sourceX, int sourceY, int radius)
	{
		for (int y = 0; y < map.Height(); y++)
		{
			for (int x = 0; x < map.Width(); x++)
			{
				map.SetVisible(x, y, false);
			}
		}

		map.SetVisible(sourceX, sourceY, true);

		for (int i = 0; i < 8; i++)
		{
			CastLight(map, sourceX, sourceY, radius, 1, 1.0f, 0.0f,
				multipliers[0][i], multipliers[1][i], multipliers[2][i], multipliers[3][i]);
		}
	}
}

#endif