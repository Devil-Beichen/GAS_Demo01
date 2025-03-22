// Fill out your copyright notice in the Description page of Project Settings.


#include "YcAnimNotify_Script.h"

FString UYcAnimNotify_Script::GetNotifyName_Implementation() const
{
	return FunctionName.ToString();
}

void UYcAnimNotify_Script::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if (!MeshComp)return;
	if (AActor* TActor = MeshComp->GetOwner())
		if (UFunction* TempFunction = TActor->FindFunction(FunctionName)) //使用反射函数名，调用函数
			TActor->ProcessEvent(TempFunction, nullptr);
}
