#include "grid.h"

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

	min_x = center.p.x - width / 2;
	min_y = center.p.y - height / 2;
	max_x = center.p.x + width / 2;
	max_y = center.p.y + height / 2;
}



cell_indices grid::find_cell(worldPoint p)
{
	const float32 &x = p.p.x;
	const float32 &y = p.p.y;

	if(x < min_x || y < min_y || x > max_x || y > max_y)
	{
		//world point passed is out of grid field
		return { 33, 33 };
	}

	const uint32_t hor_idx = width / (width - x + min_x);
	const uint32_t ver_idx = height / (height - x + min_y);

	return { hor_idx, ver_idx };
}
