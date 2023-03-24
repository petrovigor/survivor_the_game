#pragma once

#include "types.h"
#include "point.h"
#include <Windows.h>
#include <utility>


using cell_indices = std::pair<uint32_t, uint32_t>;

struct grid
{
	uint32_t cells_hor, cells_ver;
	worldPoint center;
	world_units_t cell_size;

	world_units_t min_x, max_x, min_y, max_y;
	world_units_t width;
	world_units_t height;

	grid() = default;

	void create(uint32_t cells_width, uint32_t cells_height, world_units_t cell_size);
	void draw(HDC bhdc, const worldPoint &playerPos, float32 cox, float32 coy);

	cell_indices find_cell(worldPoint p);
	//uint32_t find_normalized_idx(worldPoint p);

};



