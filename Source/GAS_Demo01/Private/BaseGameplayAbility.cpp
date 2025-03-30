// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameplayAbility.h"


// 获取技能信息
FGameplayAbilityInfo UBaseGameplayAbility::GetAbilityInfo(int Level)
{
	// 获取冷却和消耗
	const UGameplayEffect* CDEffect = GetCooldownGameplayEffect();
	const UGameplayEffect* CostEffect = GetCostGameplayEffect();

	float CD = 0.f;
	float CostValue = 0.f;
	ECostType CostType = ECostType::ECT_HP;

	if (CDEffect && CostEffect)
	{
		CDEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(Level, CD);
		if (CostEffect->Modifiers.Num() > 0)
		{
			// 获取消耗类型和值
			FGameplayModifierInfo CostEffectModifierInfo = CostEffect->Modifiers[0];
			CostEffectModifierInfo.ModifierMagnitude.GetStaticMagnitudeIfPossible(Level, CostValue);
			FString CostTypeName = CostEffectModifierInfo.Attribute.AttributeName;

			if (CostTypeName == "HP")
			{
				CostType = ECostType::ECT_HP;
			}
			if (CostTypeName == "MP")
			{
				CostType = ECostType::ECT_MP;
			}
			if (CostTypeName == "Strength")
			{
				CostType = ECostType::ECT_Strength;
			}

			return FGameplayAbilityInfo(CD, CostType, CostValue, IconMaterial, GetClass());
		}
	}

	return FGameplayAbilityInfo();
}
