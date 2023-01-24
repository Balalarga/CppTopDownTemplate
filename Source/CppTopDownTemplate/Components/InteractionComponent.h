// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"

#include "Delegates/DelegateCombinations.h"
#include "Delegates/DelegateCombinations.h"

#include "InteractionComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CPPTOPDOWNTEMPLATE_API UInteractionComponent: public UCapsuleComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInteractionComponent();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UWidgetComponent* InteractionWidget;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool OnInteract(ACharacter* Pawn);

	virtual void OnInteractImpl(ACharacter* Pawn);

	// Delegate for blueprint logic and multi-object reaction on it
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShadowChange, bool, InShadow);
	// Make an instance of delegate
	UPROPERTY(BlueprintReadOnly)
	FOnShadowChange OnShadowChange;

	/*Could be more
		UPROPERTY(BlueprintReadOnly)
		FOnShadowChange OnShadowChange2;

		UPROPERTY(BlueprintReadOnly)
		FOnShadowChange OnShadowChange3;
		...
	*/

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime,
	                           ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
