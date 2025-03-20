/*
NX_ObjectPool
Copyright (C) 2025 Nyaunix
MIT License
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
	static bool InitPoolManager(UObject* IncomingWorldContext);

	UFUNCTION(BlueprintCallable, Category = "Pool", meta = (DefaultToSelf = "IncomingWorldContext"))
	static UPoolManager* GetPoolManagerUnchecked(UObject* IncomingWorldContext);
	
	UFUNCTION(BlueprintCallable, Category = "Pool")
	static UPoolManager* GetPoolManagerChecked();

	

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

	static TWeakObjectPtr<UPoolManager> Singleton;
};
