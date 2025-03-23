// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class UBaseAttributeSet;
struct FOnAttributeChangeData;

// 监听血量变化的代理
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangeEvent, float, NewValue);

UCLASS(BlueprintType)
class GAS_DEMO01_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	// 获取GAS组件
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 技能组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystem;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 监听血量变化代理
	UPROPERTY(BlueprintAssignable, Category="Ability")
	FOnHealthChangeEvent HPChangeEvent;

	// 监听血量变化
	void OnHealthAttributeChanged(const FOnAttributeChangeData& Data);
};
