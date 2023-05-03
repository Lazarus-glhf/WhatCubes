#include "ChunkUtil.h"

decltype(auto) ChunkUtil::ChunkCoordFromBlockCoord(CoordInt BlockPos)
{
	return (BlockPos >> 4);
}

decltype(auto) ChunkUtil::BlockCoordFromChunkCoord(CoordInt ChunkPos)
{
	return (ChunkPos << 4);
}

