// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/KPlayerCharacter.h"
#include "InputActionValue.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


AKPlayerCharacter::AKPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComp->SetupAttachment(SpringArmComp);


}

void AKPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AKPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
// Called to bind functionality to input
void AKPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AKPlayerCharacter::Jump()
{
	Super::Jump();  // 调用基类的Jump方法
}

void AKPlayerCharacter::StopJumping()
{
	Super::StopJumping();  // 调用基类的StopJumping方法
}

void AKPlayerCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MoveVector = Value.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector() * MoveVector.Y);
	AddMovementInput(GetActorRightVector() * MoveVector.X);
}

void AKPlayerCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>();
	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);
}
