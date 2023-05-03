#include "Biome.h"

Biome::Biome(BiomeType Rhs)
{
	SetBiomeType(Rhs);
}

BiomeType Biome::GetBiomeType() const
{
	return this->Type;
}

void Biome::SetBiomeType(BiomeType Rhs)
{
	this->Type = Rhs;
}

Optional<BiomeType> Biome::SetBiomeType(IndexType Rhs)
{
	Optional<BiomeType> NewType = BiomeTypes::TryFrom(Rhs);
	if (NewType.Get())
	{
		this->Type = *NewType.Get();
	}
	return Type;
}
