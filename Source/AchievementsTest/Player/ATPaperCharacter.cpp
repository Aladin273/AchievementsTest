// Fill out your copyright notice in the Description page of Project Settings.


#include "ATPaperCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"

AATPaperCharacter::AATPaperCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

FVector AATPaperCharacter::GetMovementInput() const
{
	return MovementInput;
}

FVector AATPaperCharacter::GetRelativeVelocity() const
{
	return GetActorRotation().UnrotateVector(GetVelocity());
}

void AATPaperCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AATPaperCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateCharacter();
	UpdateAnimation();
}

void AATPaperCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AATPaperCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AATPaperCharacter::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AATPaperCharacter::Jump);
}

void AATPaperCharacter::UpdateCharacter()
{
	if (!bFlipOnVelocity)
		return;

	if ((GetRelativeVelocity().Y > 0.0f && !bFacingRight)
		|| (GetRelativeVelocity().Y < 0.0f && bFacingRight))
	{
		bFacingRight = !bFacingRight;
		FVector CurrentScale = GetSprite()->GetRelativeScale3D();
		CurrentScale.X = -CurrentScale.X;
		GetSprite()->SetRelativeScale3D(CurrentScale);
	}
}

void AATPaperCharacter::UpdateAnimation()
{
	UPaperFlipbook* CurrentAnimation = IdleAnimation;

	if (GetCharacterMovement()->IsFalling())
		CurrentAnimation = JumpAnimation;
	else if (!GetMovementInput().IsZero())
		CurrentAnimation = RunAnimation;

	if (GetSprite()->GetFlipbook() != CurrentAnimation)
		GetSprite()->SetFlipbook(CurrentAnimation);
}

void AATPaperCharacter::MoveForward(float Amount)
{
	MovementInput.X = Amount;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void AATPaperCharacter::MoveRight(float Amount)
{
	MovementInput.Y = Amount;
	AddMovementInput(GetActorRightVector(), Amount);
}
