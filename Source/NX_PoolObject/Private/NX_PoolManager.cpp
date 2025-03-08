// Copyright 2025 Nyaunix
// Licensed under the Apache License 2.0

#include "NX_PoolManager.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "NX_PoolContainer.h"






UPoolManager* UPoolManager::GetPoolManagerGlobal(UObject* IncomingWorldContext)
{
	static TWeakObjectPtr<UPoolManager> Singleton;
	if (Singleton.IsValid())
	{
		return Singleton.Get();
		
	}
	UWorld* World = IncomingWorldContext ? IncomingWorldContext->GetWorld() : nullptr;
	if (!World) {
		return nullptr;
	}

	UPoolManager* NewManager = NewObject<UPoolManager>(World);
	Singleton = NewManager;
	return NewManager;
}


//Gives
UObject* UPoolManager::GiveObject(UClass* IncomingClass)
{
	//Find PoolContainer
	UPoolContainer** FoundPool = PoolContainers.Find(IncomingClass);
	if (FoundPool) {
		//Give or create object from container
		return (*FoundPool)->GiveObject(IncomingClass);
	}
	//Create new container
	UPoolContainer* NewPool = NewObject<UPoolContainer>(this);// old GetTransientPackage()
	//Create object from container
	PoolContainers.Add(IncomingClass, NewPool);
	return NewPool->GiveObject(IncomingClass);
}

UObject* UPoolManager::GiveActor(UObject* IncomingWorldContext, TSubclassOf<AActor> IncomingClass)
{
	//Find PoolContainer
	UPoolContainer** FoundPool = PoolContainers.Find(IncomingClass);
	if (FoundPool) {
		//Give or create object from container
		return (*FoundPool)->GiveActor(IncomingWorldContext, IncomingClass);
	}
	//Create new container
	UPoolContainer* NewPool = NewObject<UPoolContainer>(this);// old GetTransientPackage()
	//Create object from container
	PoolContainers.Add(IncomingClass, NewPool);
	return NewPool->GiveActor(IncomingWorldContext, IncomingClass);
	
	return nullptr;
}



void UPoolManager::TakeObject(UObject* IncomingObject)
{
	UPoolContainer** LocalPool = PoolContainers.Find(IncomingObject->GetClass());
	if(LocalPool){
		(*LocalPool)->TakeObject(IncomingObject);
	}
	else {
		//Create new container
		UPoolContainer* NewPool = NewObject<UPoolContainer>(GetTransientPackage());
		//Create object from container
		PoolContainers.Add(IncomingObject->GetClass(), NewPool);
		NewPool->TakeObject(IncomingObject);
	}
}



void UPoolManager::ClearPoolContainers()
{
	TArray<UPoolContainer*> LContainers;
	PoolContainers.GenerateValueArray(LContainers);
	for (UPoolContainer* LPoolContainer : LContainers) {
		LPoolContainer->PoolClear();
	}
	PoolContainers.Empty();
}
