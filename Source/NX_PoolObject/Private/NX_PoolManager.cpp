/*
NX_ObjectPool
Copyright (C) 2025 Nyaunix
MIT License
*/


#include "NX_PoolManager.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "NX_PoolContainer.h"


TWeakObjectPtr<UPoolManager> UPoolManager::Singleton = nullptr;

bool UPoolManager::InitPoolManager(UObject* IncomingWorldContext)
{
	if (Singleton.IsValid())
	{
		return true;
	}
	UWorld* World = IncomingWorldContext ? IncomingWorldContext->GetWorld() : nullptr;
	if (!World) {
		return false;
	}
	Singleton = NewObject<UPoolManager>(World);
	return true;
}

UPoolManager* UPoolManager::GetPoolManagerUnchecked(UObject* IncomingWorldContext)
{
	if (Singleton.IsValid())
	{
		return Singleton.Get();
	}
	if (InitPoolManager(IncomingWorldContext)) {
		return Singleton.Get();
	}
	return nullptr;
}

UPoolManager* UPoolManager::GetPoolManagerChecked()
{
	return Singleton.Get();
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
	UPoolContainer* NewPool = NewObject<UPoolContainer>(this);
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
	UPoolContainer* NewPool = NewObject<UPoolContainer>(this);
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
