// Copyright 2025 Nyaunix
// Licensed under the Apache License 2.0


#include "NX_PoolContainer.h"
#include "Engine/World.h"


//Gives
UObject* UPoolContainer::GiveObject(UClass *IncomingClass)
{
	if (!PoolFree.IsEmpty()) {
		return PoolFree.Pop(); //Remove and return last object of array;
		}
	return NewObject<UObject>(this, IncomingClass);
}
UObject* UPoolContainer::GiveActor(UObject* IncomingWorldContext, TSubclassOf<AActor> IncomingClass)
{
	if (!PoolFree.IsEmpty()) {
		return PoolFree.Pop();
	}
	return IncomingWorldContext->GetWorld()->SpawnActor<AActor>(
		IncomingClass,
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		FActorSpawnParameters()
	);
}

//Takes
void UPoolContainer::TakeObject(UObject* IncomingObject)
{
	PoolFree.Add(IncomingObject);
}


//Preloads
void UPoolContainer::PreloadObjects(UClass* IncomingClass, int32 IncomingCount)
{
	TArray<UObject*> LObjects;
	for (; IncomingCount > 0; IncomingCount--) {
		LObjects.Add(GiveObject(IncomingClass));
	}
	for (UObject* x : LObjects) {
		TakeObject(x);
	}
}

void UPoolContainer::PreloadActors(UObject* IncomingWorldContext, UClass* IncomingClass, int32 IncomingCount)
{
	TArray<UObject*> LObjects;
	for (; IncomingCount > 0; IncomingCount--) {
		LObjects.Add(GiveActor(IncomingWorldContext, IncomingClass));
	}
	for (UObject* x : LObjects) {
		TakeObject(x);
	}
}

void UPoolContainer::PoolClear()
{
	PoolFree.Empty();
}
