#pragma once

#include "gmock/gmock.h"
#include "Services/ITagManagerService.h"

class MockITagManagerService : public ITagManagerService
{
public:
	MOCK_METHOD(const TArray<FString>, GetAllGeometryTagsInEditorWorld, (), (const, override));
	MOCK_METHOD(const TArray<FString>, GetAllGeometryTagsInWorld, (UWorld* World), (const, override));
	MOCK_METHOD(const TArray<AActor*>, GetAllActorsInWorldForGeometryTag, (UWorld* World, FString& Tag), (const, override));
	MOCK_METHOD(const TArray<AActor*>, GetAllActorsInEditorWorldForGeometryTag, (FString& Tag), (const, override));
	MOCK_METHOD(const TArray<UActorComponent*>, GetAllActorComponentsInEditorWorldForGeometryTag, (FString& Tag), (const, override));
	MOCK_METHOD(const TArray<UActorComponent*>, GetAllActorComponentsInWorldForGeometryTag, (UWorld* World, FString& Tag), (const, override));
	MOCK_METHOD(const TArray<USceneComponent*>, GetAllSceneComponentsInEditorWorldForGeometryTag, (FString& Tag), (const, override));
	MOCK_METHOD(const TArray<USceneComponent*>, GetAllSceneComponentsInWorldForGeometryTag, (UWorld* World, FString& Tag), (const, override));
	MOCK_METHOD(const TArray<UPrimitiveComponent*>, GetAllPrimitiveComponentsInEditorWorldForGeometryTag, (FString& Tag), (const, override));
	MOCK_METHOD(const TArray<UPrimitiveComponent*>, GetAllPrimitiveComponentsInWorldForGeometryTag, (UWorld* World, FString& Tag), (const, override));

	MOCK_METHOD(const TArray<FString>, GetAllMaterialSlotTagsInEditorWorld, (), (const, override));
	MOCK_METHOD(const TArray<FString>, GetAllMaterialSlotTagsInWorld, (UWorld* World), (const, override));

	MOCK_METHOD(const TArray<UActorComponent*>, GetAllMeshComponentsInWorldForMaterialSlotTag, (UWorld* World, const FString& Tag), (const, override));
	MOCK_METHOD(const TArray<UActorComponent*>, GetAllMeshComponentsInEditorWorldForMaterialSlotTag, (const FString& Tag), (const, override));

	MOCK_METHOD(const TArray<UMaterialInterface*>, GetAllMaterialsForMaterialSlotTag, (const FString& Tag), ( const, override));
};
