// Copyright 2025 Nyaunix
// Licensed under the Apache License 2.0

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NX_PullContainer.h"
#include "NX_PullManager.generated.h"




UCLASS(Blueprintable)
class NX_PULLOBJECT_API UPullManager : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Pull", meta = (DefaultToSelf = "IncomingWorldContext"))
	static UPullManager* GetPullManagerGlobal(UObject* IncomingWorldContext);
	
	

	UFUNCTION(BlueprintCallable, Category="Pull", meta = (DeterminesOutputType = "IncomingClass"))
	UObject* GiveObject(UClass* IncomingClass);

	UFUNCTION(BlueprintCallable, Category = "Pull", meta = (DefaultToSelf = "IncomingWorldContext", DeterminesOutputType = "IncomingClass"))
	UObject* GiveActor(UObject* IncomingWorldContext, TSubclassOf<AActor> IncomingClass);
	
	
	UFUNCTION(BlueprintCallable, Category = "Pull")
	void TakeObject(UObject* IncomingObject);
	

	
	UFUNCTION(BlueprintCallable, Category = "Pull")
	void ClearPullContainers();


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TMap<UClass*, UPullContainer*> PullContainers;
};
