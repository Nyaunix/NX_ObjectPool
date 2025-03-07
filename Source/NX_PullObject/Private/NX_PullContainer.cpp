// Copyright 2025 Nyaunix
// Licensed under the Apache License 2.0


#include "NX_PullContainer.h"
#include "Engine/World.h"


//Gives
UObject* UPullContainer::GiveObject(UClass *IncomingClass)
{
	if (!PullFree.IsEmpty()) {
		return PullFree.Pop(); //Remove and return last object of array;
		}
	return NewObject<UObject>(this, IncomingClass);
}
UObject* UPullContainer::GiveActor(UObject* IncomingWorldContext, TSubclassOf<AActor> IncomingClass)
{
	if (!PullFree.IsEmpty()) {
		return PullFree.Pop();
	}
	return IncomingWorldContext->GetWorld()->SpawnActor<AActor>(
		IncomingClass,
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		FActorSpawnParameters()
	);
}

//Takes
void UPullContainer::TakeObject(UObject* IncomingObject)
{
	PullFree.Add(IncomingObject);
}


//Preloads
void UPullContainer::PreloadObjects(UClass* IncomingClass, int32 IncomingCount)
{
	TArray<UObject*> LObjects;
	for (; IncomingCount > 0; IncomingCount--) {
		LObjects.Add(GiveObject(IncomingClass));
	}
	for (UObject* x : LObjects) {
		TakeObject(x);
	}
}

void UPullContainer::PreloadActors(UObject* IncomingWorldContext, UClass* IncomingClass, int32 IncomingCount)
{
	TArray<UObject*> LObjects;
	for (; IncomingCount > 0; IncomingCount--) {
		LObjects.Add(GiveActor(IncomingWorldContext, IncomingClass));
	}
	for (UObject* x : LObjects) {
		TakeObject(x);
	}
}

void UPullContainer::PullClear()
{
	PullFree.Empty();
}
