// Fill out your copyright notice in the Description page of Project Settings.


#include "GroundSelectTargetActor.h"

#include "Abilities/GameplayAbility.h"


// Sets default values
AGroundSelectTargetActor::AGroundSelectTargetActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AGroundSelectTargetActor::StartTargeting(UGameplayAbility* Ability)
{
	Super::StartTargeting(Ability);

	// 获取玩家控制器
	PrimaryPC = Cast<APlayerController>(Ability->GetOwningActorFromActorInfo()->GetInstigatorController());
}

/**
 * @brief 确认目标选择并继续执行后续逻辑
 * 
 * 该函数用于从玩家视角位置向目标点发射射线，检测指定半径内的碰撞，并收集所有符合条件的角色。
 * 最终将目标位置和角色列表封装到目标数据句柄中，供后续逻辑使用。
 */
void AGroundSelectTargetActor::ConfirmTargetingAndContinue()
{
	FVector LookPoint;
	GetPlayerLookAtPoint(LookPoint); // 获取玩家当前视角的注视点

	TArray<FOverlapResult> OverlapResults; // 存储重叠检测的结果
	TArray<TWeakObjectPtr<AActor>> OverlapActors; // 存储重叠的角色

	FCollisionQueryParams QueryParams; // 射线检测的查询参数
	QueryParams.bTraceComplex = false; // 不启用复杂碰撞检测
	QueryParams.bReturnPhysicalMaterial = false; // 不返回物理材质信息

	// 获取玩家控制的Pawn，并将其添加到忽略列表中，避免检测到自身
	APawn* SelfPawn = PrimaryPC->GetPawn();
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
		FCollisionShape::MakeSphere(SelectRadius),
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

	// 创建目标位置信息，并将其添加到目标数据句柄中
	FGameplayAbilityTargetData_LocationInfo* CenterLocation = new FGameplayAbilityTargetData_LocationInfo();
	CenterLocation->TargetLocation.LiteralTransform = FTransform(LookPoint);
	CenterLocation->TargetLocation.LocationType = EGameplayAbilityTargetingLocationType::LiteralTransform;
	TargetDataHandle.Add(CenterLocation);

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


// 获取玩家视角下的目标点
bool AGroundSelectTargetActor::GetPlayerLookAtPoint(FVector& Out_LookPoint)
{
	// 获取玩家视角位置和旋转

	FVector ViewLocation; // 存储玩家视角的位置
	FRotator ViewRotation; // 存储玩家视角的旋转


	// 获取玩家的视角位置和旋转
	PrimaryPC->GetPlayerViewPoint(ViewLocation, ViewRotation);

	FHitResult HitResult; // 存储射线检测的结果
	FCollisionQueryParams QueryParams; // 射线检测的查询参数
	QueryParams.bTraceComplex = true; // 启用复杂碰撞检测

	// 获取玩家控制的Pawn，并将其添加到忽略列表中，避免检测到自身
	APawn* SelfPawn = PrimaryPC->GetPawn();
	if (SelfPawn)
	{
		QueryParams.AddIgnoredActor(SelfPawn);
	}

	// 从玩家视角位置向视线方向发射射线，检测5000单位距离内的碰撞
	bool TraceResult = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		ViewLocation,
		ViewLocation + ViewRotation.Vector() * 5000.f,
		ECC_Visibility,
		QueryParams
	);

	// 如果检测到碰撞，将碰撞点位置赋值给输出参数
	if (TraceResult)
	{
		Out_LookPoint = HitResult.ImpactPoint;
	}

	return TraceResult; // 返回检测结果
}

// Called when the game starts or when spawned
void AGroundSelectTargetActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGroundSelectTargetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
