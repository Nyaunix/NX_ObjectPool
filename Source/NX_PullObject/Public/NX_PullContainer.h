// Copyright 2025 Nyaunix
// Licensed under the Apache License 2.0

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NX_PullContainer.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class NX_PULLOBJECT_API UPullContainer : public UObject
{
	GENERATED_BODY()
	
public:
	//Gives
	UFUNCTION(BlueprintCallable, Category = "Pull", meta = (DeterminesOutputType = "IncomingClass"))
	UObject* GiveObject(UClass* IncomingClass);
	
	UFUNCTION(BlueprintCallable, Category = "Pull", meta = (DefaultToSelf = "IncomingWorldContext", DeterminesOutputType = "IncomingClass"))
	UObject* GiveActor(UObject* IncomingWorldContext, TSubclassOf<AActor> IncomingClass);
	
	//Takes
	UFUNCTION(BlueprintCallable, Category = "Pull")
	void TakeObject(UObject* IncomingObject);
	

	//Preloads
	UFUNCTION(BlueprintCallable, Category = "Pull")
	void PreloadObjects(UClass* IncomingClass, int32 IncomingCount);
	
	UFUNCTION(BlueprintCallable, Category = "Pull", meta = (DefaultToSelf = "IncomingWorldContext"))
	void PreloadActors(UObject* IncomingWorldContext, UClass* IncomingClass, int32 IncomingCount);
	

	UFUNCTION(BlueprintCallable, Category = "Pull")
	void PullClear();


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UObject*> PullFree;
	
};
