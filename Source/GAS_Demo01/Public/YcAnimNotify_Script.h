// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "YcAnimNotify_Script.generated.h"

/** 逸辰的动画通知
*	通过反射去调用没有传入参数的 函数/事件
*/
UCLASS()
class GAS_DEMO01_API UYcAnimNotify_Script : public UAnimNotify
{
	GENERATED_BODY()

public:
	// 需要调用的函数名称
	UPROPERTY(EditAnywhere, Category = "名称相关")
	FName FunctionName;

	// 反射函数的名字
	virtual FString GetNotifyName_Implementation() const override;

	// 触发时调用通知
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
