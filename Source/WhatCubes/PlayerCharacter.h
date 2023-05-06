// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Actors/WorldManager.h"
#include "PlayerCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;

UCLASS()
class WHATCUBES_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	/**
	 * @brief mesh: 1st person view (arms; seen only by self)
	 */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/**
	 * @brief person camera
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/**
	 * @brief MappingContext
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/**
	 * @brief Jump Input Action
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/**
	 * @brief Move Input Action
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/**
	 * @brief LineTrace 局部起始地点，有骨骼后替代
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector HandLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	 * @brief Called for movement input
	 * @param Value 前后左右 -1 0 1
	 */
	void Move(const FInputActionValue& Value);

	/**
	 * @brief Called for looking input
	 * @param Value 上下左右 -1 0 1
	 */
	void Look(const FInputActionValue& Value);

	/**
	 * @brief 左键互动
	 * @param Value 是否操作
	 */
	void MainInteractive(const FInputActionValue& Value);

public:
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
	AWorldManager* WorldManager;
	
};
