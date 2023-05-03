#include "Biomes.h"

#include <limits>

#include "Utils/Noise.h"

Biomes& Biomes::GetInstance()
{
	static std::unique_ptr<Biomes> Instance {nullptr};
	if (Instance) return *Instance;
	Instance.reset(new Biomes);

	using namespace std::string_literals;
	Instance->Name2Idx["plain"s] = BiomeType::PLAIN;
	Instance->Name2Idx["desert"s] = BiomeType::DESERT;
	Instance->Name2Idx["river"s] = BiomeType::RIVER;
	
	return *Instance;
}

Optional<BiomeType> Biomes::GetBiomeTypeByName(std::string&& Name) const
{
	for (char& Ch : Name)
	{
		Ch = tolower(Ch);
	}
	if (std::unordered_map<std::string, BiomeType>::const_iterator Fnd = Name2Idx.find(Name); Fnd != Name2Idx.end())
	{
		return {Fnd->second};
	}
	else
	{
		return {};
	}
}

IndexType Biomes::IndexFromBiomeType(BiomeType Rhs)
{
	return static_cast<IndexType>(Rhs);
}

IndexType Biomes::IndexFromBiomeType(Optional<BiomeType> Rhs)
{
	const BiomeType* Ret = Rhs.Get();
	if (Ret)
	{
		return static_cast<IndexType>(*Ret);
	}
	else
	{
		return std::numeric_limits<IndexType>::max();
	}
}

Biome Biomes::GetBiome(SeedType Seed, MathUtils::Coord Pos)
{
	IndexType P;
	int I {Pos.GetX() - 2};
	int J {Pos.GetY() - 2};
	int K {Pos.GetZ() - 2};
	int L = (I >> 2);
	int M = (J >> 2);
	int N = (K >> 2);
	Double D = (L & 3) / 4.0;
	Double E = (M & 3) / 4.0;
	Double F = (N & 3) / 4.0;
	int O = 0;
	Double G = std::numeric_limits<Double>::infinity();
	for (P = 0; P < 8; ++P)
	{
		Double U, T, H;
		bool Bl3, Bl2;
		CoordInt S, R;
		bool Bl = ((P & 4) == 0);
		int Q = Bl ? L : L + 1;
		Bl2 = ((P & 2) == 0);
		Bl3 = ((P & 1) == 0);
		Double V = Noise::Method38106(Seed, Q, R = (Bl2 ? M : M + 1), S = (Bl3 ? N : N + 1), H = (Bl ? D : D - 1), T = (Bl2 ? E : E - 1), U = (Bl3 ? F : F - 1));
		if (!(G > V)) continue;
		O = P;
		G = V;
	}
	P = ((O & 4) == 0 ? L : L + 1);
	int W = ((O & 2) == 0 ? M : M + 1);
	int X = ((O & 1) == 0 ? N : N + 1);
	UE_LOG(LogTemp, Warning, TEXT("PWX: %d %d %d"), P, W, X);
	return GetBiomeForNoiseGen(P, W, X);
}

Biome Biomes::GetBiomeForNoiseGen(CoordInt BiomeX, CoordInt BiomeY, CoordInt BiomeZ)
{
	return {BiomeTypes::TryFrom((BiomeX + BiomeY * 0 + BiomeZ) % 3).GetOrDefault(BiomeType::PLAIN)};
}
