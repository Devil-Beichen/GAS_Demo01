// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BaseGameplayAbility.generated.h"

// 技能消耗类型
UENUM(BlueprintType)
enum ECostType : uint8
{
	// 血量
	ECT_HP UMETA(DisplayName = "HP"),
	// 蓝量
	ECT_MP UMETA(DisplayName = "MP"),
	// 能量
	ECT_Strength UMETA(DisplayName = "Strength"),
};

// 游戏玩法能力信息
USTRUCT(BlueprintType)
struct FGameplayAbilityInfo
{
	GENERATED_BODY()

public:
	// 技能CD
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AbilityInfo")
	float CD;

	// 技能消耗类型
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AbilityInfo")
	TEnumAsByte<ECostType> CostType;

	// 技能消耗值
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AbilityInfo")
	float CostValue;

	// 技能图标
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AbilityInfo")
	UMaterialInstance* IconMaterial;

	// 技能类
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AbilityInfo")
	TSubclassOf<class UBaseGameplayAbility> AbilityClass;

	// 构造函数
	FGameplayAbilityInfo():
		CD(0),
		CostType(ECT_HP),
		CostValue(0),
		IconMaterial(nullptr),
		AbilityClass(nullptr)
	{
	}

	// 构造函数(带参)
	FGameplayAbilityInfo(float CD, ECostType CostType, float CostValue, UMaterialInstance* IconMaterial, TSubclassOf<class UBaseGameplayAbility> AbilityClass)
	{
		this->CD = CD;
		this->CostType = CostType;
		this->CostValue = CostValue;
		this->IconMaterial = IconMaterial;
		this->AbilityClass = AbilityClass;
	}
};

/**
 * 基础游戏玩法能力
 */
UCLASS()
class GAS_DEMO01_API UBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	// 技能图标
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AbilityInfo")
	UMaterialInstance* IconMaterial;

	// 获取技能信息
	UFUNCTION(BlueprintCallable, Category="AbilityInfo")
	FGameplayAbilityInfo GetAbilityInfo(int Level);
};
