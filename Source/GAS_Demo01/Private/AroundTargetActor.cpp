// Fill out your copyright notice in the Description page of Project Settings.


#include "AroundTargetActor.h"

#include "Abilities/GameplayAbility.h"


void AAroundTargetActor::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);
	// 获取玩家控制器
	PrimaryPC = Cast<APlayerController>(Ability->GetOwningActorFromActorInfo()->GetInstigatorController());
}

void AAroundTargetActor::ConfirmTargetingAndContinue()
{
	APawn* SelfPawn = PrimaryPC->GetPawn();
	if (!SelfPawn) return;

	FVector LookPoint = SelfPawn->GetActorLocation();

	TArray<FOverlapResult> OverlapResults; // 存储重叠检测的结果
	TArray<TWeakObjectPtr<AActor>> OverlapActors; // 存储重叠的角色

	FCollisionQueryParams QueryParams; // 射线检测的查询参数
	QueryParams.bTraceComplex = false; // 不启用复杂碰撞检测
	QueryParams.bReturnPhysicalMaterial = false; // 不返回物理材质信息

	if (SelfPawn)
	{
		QueryParams.AddIgnoredActor(SelfPawn);
	}

	// 从玩家视角位置向目标点发射射线，检测指定半径内的碰撞
	bool QuerResult = GetWorld()->OverlapMultiByObjectType(
		OverlapResults,
		LookPoint,
		FQuat::Identity,
		FCollisionObjectQueryParams(ECC_Pawn),
		FCollisionShape::MakeSphere(AroundRadius),
		QueryParams
	);

	// 如果检测到碰撞，遍历所有重叠结果，筛选出符合条件的角色
	if (QuerResult)
	{
		for (int i = 0; i < OverlapResults.Num(); i++)
		{
			APawn* Enemy = Cast<APawn>(OverlapResults[i].GetActor());
			if (Enemy && !OverlapActors.Contains(Enemy))
			{
				OverlapActors.AddUnique(Enemy); // 将符合条件的角色添加到列表中
			}
		}
	}

	FGameplayAbilityTargetDataHandle TargetDataHandle; // 目标数据句柄，用于封装目标信息

	// 如果有符合条件的角色，创建角色数组信息，并将其添加到目标数据句柄中
	if (OverlapActors.Num() > 0)
	{
		FGameplayAbilityTargetData_ActorArray* ActorArray = new FGameplayAbilityTargetData_ActorArray();
		ActorArray->SetActors(OverlapActors);
		TargetDataHandle.Add(ActorArray);
	}

	// 检查并处理目标数据准备情况
	check(ShouldProduceTargetData());

	// 如果确认目标操作被允许，则广播目标数据准备完成的消息
	if (IsConfirmTargetingAllowed())
	{
		TargetDataReadyDelegate.Broadcast(TargetDataHandle);
	}
}
