/*
NX_ObjectPool
Copyright (C) 2025 Nyaunix
MIT License
*/


#pragma once
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NX_PoolContainer.generated.h"


UCLASS(Blueprintable)
class NX_OBJECTPOOL_API UPoolContainer : public UObject
{
	GENERATED_BODY()
	
public:
	//Gives
	UFUNCTION(BlueprintCallable, Category = "Pool", meta = (DeterminesOutputType = "IncomingClass"))
	UObject* GiveObject(UClass* IncomingClass);
	
	UFUNCTION(BlueprintCallable, Category = "Pool", meta = (DefaultToSelf = "IncomingWorldContext", DeterminesOutputType = "IncomingClass"))
	UObject* GiveActor(UObject* IncomingWorldContext, TSubclassOf<AActor> IncomingClass);
	
	//Takes
	UFUNCTION(BlueprintCallable, Category = "Pool")
	void TakeObject(UObject* IncomingObject);
	

	//Preloads
	UFUNCTION(BlueprintCallable, Category = "Pool")
	void PreloadObjects(UClass* IncomingClass, int32 IncomingCount);
	
	UFUNCTION(BlueprintCallable, Category = "Pool", meta = (DefaultToSelf = "IncomingWorldContext"))
	void PreloadActors(UObject* IncomingWorldContext, UClass* IncomingClass, int32 IncomingCount);
	

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void PoolClear();


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UObject*> PoolFree;
	
};
