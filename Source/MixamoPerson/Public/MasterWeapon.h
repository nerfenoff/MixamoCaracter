// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MasterWeapon.generated.h"

UCLASS()
class MIXAMOPERSON_API AMasterWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMasterWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Weapon)
	USkeletalMeshComponent* Mesh;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};