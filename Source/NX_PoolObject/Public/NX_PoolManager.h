// Copyright 2025 Nyaunix
// Licensed under the Apache License 2.0

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
