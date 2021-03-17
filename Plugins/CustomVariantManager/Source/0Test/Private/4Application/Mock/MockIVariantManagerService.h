#pragma once

#include "Services/IVariantManagerService.h"
#include "gmock/gmock.h"

class MockIVariantManagerService : public IVariantManagerService
{
public:
	MOCK_METHOD(TArray<ICustomVariantSet*>, GetAllVariantSets, (), (override));
	MOCK_METHOD(ICustomVariantSet*, GetVariantSetByName, (FString), (override));
	MOCK_METHOD(EVariantManagerServiceResult, RenameVariantSet, (ICustomVariantSet*, const FString&), (override));
	MOCK_METHOD(EVariantManagerServiceResult, DeleteVariantSet, (ICustomVariantSet*), (override));
	MOCK_METHOD(ICustomVariantSet*, CreateVariantSet, (const EVariantSetType& VariantSetType), (override));
	MOCK_METHOD(ICustomVariant*, FetchVariantByName, (ICustomVariantSet* SelectedVariantSet, const FString& VariantName), (override));
	MOCK_METHOD(EVariantManagerServiceResult, RenameVariant, (ICustomVariantSet* VariantSet, ICustomVariant* Variant, const FString& NewVariantName), (override));
	MOCK_METHOD(EVariantManagerServiceResult, DeleteVariant, (ICustomVariantSet* VariantSet, ICustomVariant* Variant), (override));
	MOCK_METHOD(EVariantManagerServiceResult, ActivateVariant, (ICustomVariantSet* VariantSet, ICustomVariant* Variant), (override));
	MOCK_METHOD(EVariantManagerServiceResult, RefreshVariantSet, (ICustomVariantSet* VariantSet), (override));
	MOCK_METHOD(EVariantManagerServiceResult, RefreshAllVariantSets, (), (override));
	MOCK_METHOD(EVariantManagerServiceResult, RefreshVariantThumbnailFromEditorViewPort, (ICustomVariantSet* VariantSet, ICustomVariant* Variant), ( override));
	MOCK_METHOD(EVariantManagerServiceResult, RefreshVariantThumbnailFromFile, (ICustomVariantSet* VariantSet, ICustomVariant* Variant, const FString& SourceImagePath), ( override));
	MOCK_METHOD(EVariantManagerServiceResult, ClearVariantThumbnail, (ICustomVariantSet* VariantSet, ICustomVariant* Variant), ( override));

	/* Geometry Specific */
	MOCK_METHOD(TArray<ICustomGeometryVariant*>, GetAllGeometryVariants, (ICustomGeometryVariantSet* GeometryVariantSet), (override));
	MOCK_METHOD(ICustomGeometryVariant*, CreateGeometryVariant, (ICustomGeometryVariantSet* GeometryVariantSet, const FString& Tag), (override));
	MOCK_METHOD(ICustomGeometryVariant*, CreateGeometryAllOffVariant, (ICustomGeometryVariantSet* GeometryVariantSet), (override));
};
