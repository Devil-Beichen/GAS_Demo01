// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "AroundTargetActor.generated.h"

/**
 * 选中周围目标
 */
UCLASS()
class GAS_DEMO01_API AAroundTargetActor : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

public:
	// 启动目标选择
	virtual void StartTargeting(UGameplayAbility* Ability) override;

	// 确认目标数据请求并且发送出去
	virtual void ConfirmTargetingAndContinue() override;

	// 周围半径
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn = true), Category="GroundSelect")
	float AroundRadius = 10.f;
};
