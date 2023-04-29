// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldManager.h"

#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SimplexNoise/Public/SimplexNoiseBPLibrary.h"

// Sets default values
AWorldManager::AWorldManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GlobalInfo = CreateDefaultSubobject<UGlobalInfo>(TEXT("Global Info"));
}

// Called when the game starts or when spawned
void AWorldManager::BeginPlay()
{
	Super::BeginPlay();

	// 初始化 实例化静态网格体，在蓝图中调用
	InitInstancedMeshComponents();
	
	Seed = 123;
	USimplexNoiseBPLibrary::setNoiseSeed(Seed);
	
	ChunkNum = RenderingRange / ChunkWidth;

	ShouldUpdatePlayerCoordinate();
	AddChunk();
	// UpdateBlocks();
}

// Called every frame
void AWorldManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ShouldUpdatePlayerCoordinate();
	AddChunk();
	// RemoveChunk();
}

bool AWorldManager::ShouldUpdatePlayerCoordinate()
{
	if (const UWorld* World = GetWorld(); World)
	{
		const APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(World, 0);
		if (PlayerPawn)
		{
			const FVector2D CurrentPlayerLocation = FVector2D(PlayerPawn->GetActorLocation());
			
			if (!(LastPlayerChunkCoordinate * GetChunkRealWidth()).Equals(CurrentPlayerLocation, UpdateDistance))
			{
				LastPlayerChunkCoordinate = CurrentPlayerLocation / GetChunkRealWidth();
				return true;
			}
		}
	}
	return false;
}

void AWorldManager::AddChunk()
{
	for (int X = LastPlayerChunkCoordinate.X - ChunkNum; X != static_cast<int>(LastPlayerChunkCoordinate.X + ChunkNum); )
	{
		for (int Y =  LastPlayerChunkCoordinate.Y - ChunkNum;  Y != static_cast<int>(LastPlayerChunkCoordinate.Y + ChunkNum); )
		{
			FVector2D AddingChunkPosition = FVector2D(X, Y);
			if (!GlobalInfo->ChunksLoaded.Contains(AddingChunkPosition))
			{
				// Call in Blueprint
				if (UChunkComponent* Ref = GenerateChunk(AddingChunkPosition); Ref)
				{
					GlobalInfo->ChunksLoaded.Add(AddingChunkPosition, Ref);
				}
			}
			if (Y < ChunkNum + LastPlayerChunkCoordinate.Y) { Y++; }
			else { Y--; }
		}
		if (X < ChunkNum + LastPlayerChunkCoordinate.X) { X++; }
		else { X--; }
	}
	UpdateBlocks();
}

void AWorldManager::RemoveChunk() const
{
	// for (auto key : GlobalInfo->ChunksLoaded)
	// {
	// 	if (FVector2D::Distance(LastPlayerChunkCoordinate, key.Key) > RenderingRange)
	// 	{
	// 		UChunkComponent* DelChunk = *GlobalInfo->ChunksLoaded.Find(key.Key);
	// 		// DelChunk->Destroy();
	// 		GlobalInfo->ChunksLoaded.Remove(key.Key);
	// 	}
	// }
}

int AWorldManager::GetChunkRealWidth() const
{
	return ChunkWidth * 100;
}

FVector AWorldManager::ChunkIndexToRealPosition(const int X, const int Y) const
{
	return FVector(X * GetChunkRealWidth(), Y * GetChunkRealWidth(), 0);
}

void AWorldManager::UpdateBlocks()
{
	for (const TPair<UE::Math::TVector<double>, EBlockType>& Pair : GlobalInfo->BlocksNeedToCreate)
	{
		const int32 BlockType(static_cast<int32>(Pair.Value));
		UInstancedStaticMeshComponent* ToSpawnBlock = *InstancedMeshComponents.Find(BlockType);
		if (ToSpawnBlock)
		{
			
			ToSpawnBlock->AddInstance(FTransform(Pair.Key));
		}
		GlobalInfo->BlocksCreated.Add(Pair);
	}
	GlobalInfo->BlocksNeedToCreate.Empty();
}

UChunkComponent* AWorldManager::GenerateChunk(const FVector2D& Location)
{
	UChunkComponent* ChunkComponent = NewObject<UChunkComponent>();
	ChunkComponent->RegisterComponent();

	if (ChunkComponent)
	{
		ChunkComponent->WorldManager = this;
		ChunkComponent->ChunkPosition = Location;

		ChunkComponent->GenerateTerrain();
		
		UE_LOG(LogTemp, Warning, TEXT("GeneraedChunk at : %f %f"), Location.X, Location.Y);	
	}
	return ChunkComponent;
}

void AWorldManager::InitInstancedMeshComponents_Implementation()
{
	UE_LOG(LogTemp, Error, TEXT("Calling Default InitInstancedmeshComponents"));
}
