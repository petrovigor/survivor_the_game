#include "grid.h"
#include <iostream>

void grid::draw(HDC bhdc, const worldPoint &playerPosition, float32 cox, float32 coy) {
	const float32 grid_size_width = (cells_hor * cell_size);
	const float32 grid_size_height = (cells_ver * cell_size);

	const float32 x = (400.0f - playerPosition.p.x + cox) - grid_size_width/2;
	const float32 y = (300.0f - playerPosition.p.y + coy) - grid_size_height/2;

	float32 offset = 0;
	for(int i = 0; i < cells_ver + 1; ++i)
	{
		MoveToEx(bhdc, x, y + offset, 0);
		LineTo(bhdc, x + grid_size_width, y + offset);
		offset += cell_size;
	}

	offset = 0;
	for(int i = 0; i < cells_hor + 1; ++i)
	{
		MoveToEx(bhdc, x + offset, y , 0);
		LineTo(bhdc, x + offset, y + grid_size_height);
		offset += cell_size;
	}
}

void grid::create(uint32_t _cells_width, uint32_t _cells_height, world_units_t _cell_size)
{
	center = worldPoint{ _cell_size, _cell_size };
	cells_hor = _cells_width;
	cells_ver = _cells_height;
	cell_size = _cell_size;

	width = cells_hor * cell_size;
	height = cells_ver * cell_size;

	min_x = center.p.x - cell_size - width / 2;
	min_y = center.p.y - cell_size - height / 2;
	max_x = center.p.x - cell_size + width / 2;
	max_y = center.p.y - cell_size + height / 2;
}



cell_indices grid::find_cell(worldPoint p)
{
	const float32 &x = p.p.x;
	const float32 &y = p.p.y;

	//std::cout << "wp: " << p.p.x << " / " << p.p.y << std::endl;
	if(x < min_x || y < min_y || x > max_x || y > max_y)
	{
		//world point passed is out of grid field
		return { -1, -1 };
	}

	//optimize it please====================================

	float32 _min_y = min_y;
	float32 _max_y = min_y + cell_size;

	for(int i = 0; i < cells_hor; ++i)
	{
		float32 _min_x = min_x;
		float32 _max_x = min_x + cell_size;

		for(int j = 0; j < cells_ver; ++j)
		{
			if(x >= _min_x && x <= _max_x && y >= _min_y && y <= _max_y)
			{
				return { j, i };
			}

			_min_x += cell_size;
			_max_x += cell_size;
		}

		_min_y += cell_size;
		_max_y += cell_size;
	}
	//=====================================================

	//should be never called
	return { -1, -1 };
}
