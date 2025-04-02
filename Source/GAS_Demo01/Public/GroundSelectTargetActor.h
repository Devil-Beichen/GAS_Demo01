// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GroundSelectTargetActor.generated.h"

/**
 * 地面选择目标Actor
 */
UCLASS()
class GAS_DEMO01_API AGroundSelectTargetActor : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

public:
	AGroundSelectTargetActor();

	// 启动目标选择
	virtual void StartTargeting(UGameplayAbility* Ability) override;

	// 确认目标数据请求并且发送出去
	virtual void ConfirmTargetingAndContinue() override;

	// 获取玩家当前选择点
	UFUNCTION(BlueprintCallable, Category="GroundSelect")
	bool GetPlayerLookAtPoint(FVector& Out_LookPoint);

	// 选中半径
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ExposeOnSpawn = true), Category="GroundSelect")
	float SelectRadius = 10.f;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
