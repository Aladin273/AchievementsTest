// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "ATPaperCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UPaperFlipbook;

/**
 * 
 */
UCLASS()
class ACHIEVEMENTSTEST_API AATPaperCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:
	AATPaperCharacter();

	UFUNCTION(BlueprintCallable)
    virtual FVector GetMovementInput() const;

	UFUNCTION(BlueprintCallable)
	virtual FVector GetRelativeVelocity() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Character)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Character)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UPaperFlipbook* IdleAnimation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UPaperFlipbook* JumpAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UPaperFlipbook* RunAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	bool bFacingRight = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	bool bFlipOnVelocity = true;
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	virtual void UpdateCharacter();
	
	virtual void UpdateAnimation();

private:
	void MoveForward(float Amount);
	void MoveRight(float Amount);

	FVector MovementInput = FVector::ZeroVector;
};