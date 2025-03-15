Reuse objects and actors instead of constantly creating and deleting them.
* Fully C++ with blueprint support

---

### PoolContainer
Stores objects or actors

Func:
* GiveObject
* GiveActor
* TakeObject
* PreloadObjects
* PreloadActors

Vars:

* PoolFree(Array[Objects*])

---

### **PoolManager**

Stores the PoolContainers.

Incoming and outgoing objects are automatically sorted between pools.

Func:
* GetPoolManagerGlobal - can be called from anywhere in the game
* GiveObject
* GiveActor
* TakeObject

Vars:
* PoolContainers(TMap<UClass*, UPoolContainer*>)
---


Warnings:
Pools do not check the validity of incoming data to remain high performance.

![](https://github.com/Nyaunix/NX_ObjectPool/blob/main/Resources/imageContainer.jpg)
![](https://github.com/Nyaunix/NX_ObjectPool/blob/main/Resources/imageManager.jpg)

---
![Discord](https://discord.gg/YBUGddBKT3)
