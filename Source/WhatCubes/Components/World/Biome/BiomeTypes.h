#pragma once
#include "WhatCubes/Components/Pre.h"
#include "WhatCubes/Components/Lang/Optional.h"

enum class BiomeType {
    PLAIN,
    DESERT,
    RIVER,
};

class BiomeTypes
{
public:
    /**
     * @brief 
     * @param Rhs 
     * @return 
     */
    static Optional<BiomeType> TryFrom(IndexType Rhs);
};
