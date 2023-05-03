#pragma once

#include "WhatCubes/Components/Pre.h"

class ChunkUtil
{
public:
	/**
	 * @brief 方块坐标转区块坐标
	 * @param BlockPos x、y、z 的任意一个
	 * @return 对应的值
	 */
	static decltype(auto) ChunkCoordFromBlockCoord(CoordInt BlockPos);

	/**
	 * @brief 区块坐标转方块坐标
	 * @param ChunkPos x、y、z 的任意一个
	 * @return 对应的值
	 */
	static decltype(auto) BlockCoordFromChunkCoord(CoordInt ChunkPos);
	
};
