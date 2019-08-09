// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/MasterCharacter.h"
#include "Engine.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AMasterCharacter::AMasterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");	
	CameraComponent->SetupAttachment(SpringArmComponent);

	NeckSocket = CreateDefaultSubobject<USceneComponent>("NeckSocket");
	RightHandSocket = CreateDefaultSubobject<USceneComponent>("RightHandSocket");

	if (USkeletalMeshComponent* SM = GetMesh())
	{
		NeckSocket->AttachToComponent(SM, FAttachmentTransformRules::KeepRelativeTransform,TEXT("NeckSocket"));
		RightHandSocket->AttachToComponent(SM, FAttachmentTransformRules::KeepRelativeTransform, TEXT("RightHandSocket"));
	}
	
	WeaponActor = CreateDefaultSubobject<UChildActorComponent>("WeaponActor");
	WeaponActor->SetupAttachment(NeckSocket);

	isUseWeapon = false;
}

// Called when the game starts or when spawned
void AMasterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMasterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMasterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMasterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMasterCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &AMasterCharacter::LookUp);
	PlayerInputComponent->BindAxis("TurnRight", this, &AMasterCharacter::TurnRight);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AMasterCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &AMasterCharacter::StopJumping);

}

void AMasterCharacter::MoveForward(float Value)
{
	
	if ((Controller != NULL) && (Value != 0.0f))
	{		
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMasterCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
		
	}
}

void AMasterCharacter::TurnRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		AddControllerYawInput(Value);
	}
}

void AMasterCharacter::LookUp(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		AddControllerPitchInput(Value);
	}
}

