/*
NX_ObjectPool
Copyright (C) 2025 Nyaunix
This file is part of NX_ObjectPool and is distributed under the Harvest-Share License.
See the LICENSE file in the repository for details.
*/


#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NX_PoolContainer.h"
#include "NX_PoolManager.generated.h"


UCLASS(Blueprintable)
class NX_OBJECTPOOL_API UPoolManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Pool", meta = (DefaultToSelf = "IncomingWorldContext"))
	static UPoolManager* GetPoolManagerGlobal(UObject* IncomingWorldContext);
	
	

	UFUNCTION(BlueprintCallable, Category="Pool", meta = (DeterminesOutputType = "IncomingClass"))
	UObject* GiveObject(UClass* IncomingClass);

	UFUNCTION(BlueprintCallable, Category = "Pool", meta = (DefaultToSelf = "IncomingWorldContext", DeterminesOutputType = "IncomingClass"))
	UObject* GiveActor(UObject* IncomingWorldContext, TSubclassOf<AActor> IncomingClass);
	
	
	UFUNCTION(BlueprintCallable, Category = "Pool")
	void TakeObject(UObject* IncomingObject);
	

	
	UFUNCTION(BlueprintCallable, Category = "Pool")
	void ClearPoolContainers();


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<UClass*, UPoolContainer*> PoolContainers;
};
