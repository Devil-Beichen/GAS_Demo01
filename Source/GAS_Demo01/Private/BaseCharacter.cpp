// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "BaseAttributeSet.h"
#include "BaseGameplayAbility.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
}

// 获取GAS组件
UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystem;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AbilitySystem)
	{
		// 监听属性变化
		AbilitySystem->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetHPAttribute()).AddUObject(this, &ABaseCharacter::OnHealthAttributeChanged);
		AbilitySystem->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetMPAttribute()).AddUObject(this, &ABaseCharacter::OnMPAttributeChanged);
		AbilitySystem->GetGameplayAttributeValueChangeDelegate(UBaseAttributeSet::GetStrengthAttribute()).AddUObject(this, &ABaseCharacter::OnStrengthAttributeChanged);
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// 血量属性变化回调
void ABaseCharacter::OnHealthAttributeChanged(const FOnAttributeChangeData& Data)
{
	// 属性变化回调
	if (Data.OldValue != Data.NewValue)
	{
		// UE_LOG(LogTemp, Warning, TEXT("OnHealthAttributeChanged: OldValue = %f, NewValue = %f"), Data.OldValue, Data.NewValue);
		HPChangeEvent.Broadcast(Data.NewValue);
	}
}

// 蓝量属性变化回调
void ABaseCharacter::OnMPAttributeChanged(const FOnAttributeChangeData& Data)
{
	// 属性变化回调
	if (Data.OldValue != Data.NewValue)
	{
		// UE_LOG(LogTemp, Warning, TEXT("OnHealthAttributeChanged: OldValue = %f, NewValue = %f"), Data.OldValue, Data.NewValue);
		MPChangeEvent.Broadcast(Data.NewValue);
	}
}

// 能量属性变化回调
void ABaseCharacter::OnStrengthAttributeChanged(const FOnAttributeChangeData& Data)
{
	// 属性变化回调
	if (Data.OldValue != Data.NewValue)
	{
		// UE_LOG(LogTemp, Warning, TEXT("OnHealthAttributeChanged: OldValue = %f, NewValue = %f"), Data.OldValue, Data.NewValue);
		StrengthChangeEvent.Broadcast(Data.NewValue);
	}
}

// 获取技能信息
FGameplayAbilityInfo ABaseCharacter::GameplayAbilitytyInfo(TSubclassOf<UBaseGameplayAbility> AbilityClass, int Level)
{
	// 获取技能信息
	UBaseGameplayAbility* AbilityIncetance = AbilityClass->GetDefaultObject<UBaseGameplayAbility>();
	if (AbilitySystem && AbilityIncetance)
	{
		return AbilityIncetance->GetAbilityInfo(Level);
	}

	return FGameplayAbilityInfo();
}
