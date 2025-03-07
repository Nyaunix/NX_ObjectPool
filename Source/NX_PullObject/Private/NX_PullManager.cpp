// Copyright 2025 Nyaunix
// Licensed under the Apache License 2.0

#include "NX_PullManager.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "NX_PullContainer.h"






UPullManager* UPullManager::GetPullManagerGlobal(UObject* IncomingWorldContext)
{
	static TWeakObjectPtr<UPullManager> Singleton;
	if (Singleton.IsValid())
	{
		return Singleton.Get();
		
	}
	UWorld* World = IncomingWorldContext ? IncomingWorldContext->GetWorld() : nullptr;
	if (!World) {
		return nullptr;
	}

	UPullManager* NewManager = NewObject<UPullManager>(World);
	Singleton = NewManager;
	return NewManager;
}


//Gives
UObject* UPullManager::GiveObject(UClass* IncomingClass)
{
	//Find PullContainer
	UPullContainer** FoundPull = PullContainers.Find(IncomingClass);
	if (FoundPull) {
		//Give or create object from container
		return (*FoundPull)->GiveObject(IncomingClass);
	}
	//Create new container
	UPullContainer* NewPull = NewObject<UPullContainer>(this);// old GetTransientPackage()
	//Create object from container
	PullContainers.Add(IncomingClass, NewPull);
	return NewPull->GiveObject(IncomingClass);
}

UObject* UPullManager::GiveActor(UObject* IncomingWorldContext, TSubclassOf<AActor> IncomingClass)
{
	//Find PullContainer
	UPullContainer** FoundPull = PullContainers.Find(IncomingClass);
	if (FoundPull) {
		//Give or create object from container
		return (*FoundPull)->GiveActor(IncomingWorldContext, IncomingClass);
	}
	//Create new container
	UPullContainer* NewPull = NewObject<UPullContainer>(this);// old GetTransientPackage()
	//Create object from container
	PullContainers.Add(IncomingClass, NewPull);
	return NewPull->GiveActor(IncomingWorldContext, IncomingClass);
	
	return nullptr;
}



void UPullManager::TakeObject(UObject* IncomingObject)
{
	UPullContainer** LocalPull = PullContainers.Find(IncomingObject->GetClass());
	if(LocalPull){
		(*LocalPull)->TakeObject(IncomingObject);
	}
	else {
		//Create new container
		UPullContainer* NewPull = NewObject<UPullContainer>(GetTransientPackage());
		//Create object from container
		PullContainers.Add(IncomingObject->GetClass(), NewPull);
		NewPull->TakeObject(IncomingObject);
	}
}



void UPullManager::ClearPullContainers()
{
	TArray<UPullContainer*> LContainers;
	PullContainers.GenerateValueArray(LContainers);
	for (UPullContainer* LPullContainer : LContainers) {
		LPullContainer->PullClear();
	}
	PullContainers.Empty();
}
