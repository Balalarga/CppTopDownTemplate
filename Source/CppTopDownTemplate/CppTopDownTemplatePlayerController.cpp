// Copyright Epic Games, Inc. All Rights Reserved.

#include "CppTopDownTemplatePlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "CppTopDownTemplateCharacter.h"
#include "Engine/World.h"

ACppTopDownTemplatePlayerController::ACppTopDownTemplatePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ACppTopDownTemplatePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void ACppTopDownTemplatePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ACppTopDownTemplatePlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ACppTopDownTemplatePlayerController::OnSetDestinationReleased);

	InputComponent->BindAction("EnableCameraRotation", IE_Pressed, this, &ACppTopDownTemplatePlayerController::OnEnableCameraRotationPressed);
	InputComponent->BindAction("EnableCameraRotation", IE_Released, this, &ACppTopDownTemplatePlayerController::OnEnableCameraRotationReleased);

	InputComponent->BindAxis("MouseX");
}

void ACppTopDownTemplatePlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (ACppTopDownTemplateCharacter* MyPawn = Cast<ACppTopDownTemplateCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void ACppTopDownTemplatePlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	if (const APawn* MyPawn = GetPawn())
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (Distance > 120.0f)
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void ACppTopDownTemplatePlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void ACppTopDownTemplatePlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void ACppTopDownTemplatePlayerController::OnEnableCameraRotationPressed()
{
	bCameraRotation = true;
}

void ACppTopDownTemplatePlayerController::OnEnableCameraRotationReleased()
{
	bCameraRotation = false;
}
