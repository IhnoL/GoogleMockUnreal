#pragma once

class UWorld;
class UActorComponent;
class USceneComponent;
class UPrimitiveComponent;
class UStaticMeshComponent;
class UMaterialInterface;

struct ITagManagerService
{
	virtual ~ITagManagerService() = default;

	virtual const TArray<FString> GetAllGeometryTagsInEditorWorld() const = 0;
	virtual const TArray<FString> GetAllGeometryTagsInWorld(UWorld* World) const = 0;

	virtual const TArray<AActor*> GetAllActorsInWorldForGeometryTag(UWorld* World, FString& Tag) const = 0;
	virtual const TArray<AActor*> GetAllActorsInEditorWorldForGeometryTag(FString& Tag) const = 0;
	
	virtual const TArray<UActorComponent*> GetAllActorComponentsInEditorWorldForGeometryTag(FString& Tag) const = 0;
	virtual const TArray<UActorComponent*> GetAllActorComponentsInWorldForGeometryTag(UWorld* World, FString& Tag) const = 0;

	virtual const TArray<USceneComponent*> GetAllSceneComponentsInEditorWorldForGeometryTag(FString& Tag) const = 0;
	virtual const TArray<USceneComponent*> GetAllSceneComponentsInWorldForGeometryTag(UWorld* World, FString& Tag) const = 0;

	virtual const TArray<UPrimitiveComponent*> GetAllPrimitiveComponentsInEditorWorldForGeometryTag(FString& Tag) const = 0;
	virtual const TArray<UPrimitiveComponent*> GetAllPrimitiveComponentsInWorldForGeometryTag(UWorld* World, FString& Tag) const = 0;

	/** Material Slot **/
	virtual const TArray<UMaterialInterface*> GetAllMaterialsForMaterialSlotTag(const FString& Tag) const = 0;

	virtual const TArray<FString> GetAllMaterialSlotTagsInEditorWorld() const = 0;
	virtual const TArray<FString> GetAllMaterialSlotTagsInWorld(UWorld* World) const = 0;

	virtual const TArray<UActorComponent*> GetAllMeshComponentsInWorldForMaterialSlotTag(UWorld* World, const FString& Tag) const = 0;
	virtual const TArray<UActorComponent*> GetAllMeshComponentsInEditorWorldForMaterialSlotTag(const FString& Tag) const = 0;
};

Expose_TNameOf(ITagManagerService)

