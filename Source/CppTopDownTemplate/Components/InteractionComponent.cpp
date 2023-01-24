// Fill out your copyright notice in the Description page of Project Settings.

#include "InteractionComponent.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

bool UInteractionComponent::OnInteract_Implementation(ACharacter* Pawn)
{
	return false;
}

void UInteractionComponent::OnInteractImpl(ACharacter* Pawn)
{
	// BlueprintNativeEvent
	if (OnInteract(Pawn))
		return;

	// C++ logic
}

// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (IsValid(Owner))
	{
		InteractionWidget = Cast<UWidgetComponent>(Owner->GetComponentByClass(UWidgetComponent::StaticClass()));
	}
}

// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime,
                                          ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

