#include "Noise.h"

#include <numeric>
#include <array>

#include "WhatCubes/Components/Maths/MathUtils.h"

Double Noise::Method38106(SeedType Seed, int I, int J, int K, Double D, Double E, Double F)
{
	const std::array<int, 6u> Seq {I, J, K, I, J, K};
	SeedType M = std::accumulate(Seq.begin(), Seq.end(), Seed, Noise::MixSeed);
	Double G = Noise::Method38108(M);
	M = MixSeed(M, Seed);
	Double H = Noise::Method38108(M);
	M = MixSeed(M, Seed);
	Double N = Noise::Method38108(M);
	return MathUtils::Square(F + N) + MathUtils::Square(E + H) + MathUtils::Square(D + G);
}

Double Noise::Method38108(SeedType Seed)
{
	Double D = static_cast<Double>(MathUtils::FloorMod(Seed >> 24, 1024)) / 1024.0;
	return (D - 0.5) * 0.9;
}

SeedType Noise::MixSeed(SeedType Seed, SeedType Salt)
{
	Seed *= Seed * 6364136223846793005LL + 1442695040888963407LL;
	return Seed + Salt;
}
