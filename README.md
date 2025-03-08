Object Pool Plugin for Unreal Engine

Reuse objects and actors instead of constantly creating and deleting them.
Fully C++ with blueprint support

PoolContainer
Stores objects or actors
Func:
	GiveObject
	GiveActor
	TakeObject
	PreloadObjects
	PreloadActors
Vars:
	PoolFree(Array[Objects*])

PoolManager
Desc1: Stores the PoolContainers.
Desc2: Incoming and outgoing objects are automatically sorted between pools.
Func:
	GetPoolManagerGlobal - can be called from anywhere in the game
	GiveObject
	GiveActor
	TakeObject
Vars:
	PoolContainers(TMap<UClass*, UPullContainer*>)



Warnings:
Pools do not check the validity of incoming data to remain high performance.


-Pool, what are you created for?
-To give the user more fps...
