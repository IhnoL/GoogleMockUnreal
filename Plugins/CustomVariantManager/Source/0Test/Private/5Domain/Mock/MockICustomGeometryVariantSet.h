#pragma once
#include "Entities/Geometry/ICustomGeometryVariantSet.h"
#include "gmock/gmock.h"

class MockICustomGeometryVariantSet : public ICustomGeometryVariantSet
{
public:
	MOCK_METHOD(TArray<ICustomVariant*>, GetVariants, (), (const, override));
	MOCK_METHOD(TArray<ICustomGeometryVariant*>, GetGeometryVariants, (), (const, override));
	MOCK_METHOD(bool, AddVariantAsset, (ICustomVariant* Variant), (override));
	MOCK_METHOD(bool, RemoveVariantAsset, (ICustomVariant* Variant), ( override));

	MOCK_METHOD(FString, GetName, (), (const, override));
	MOCK_METHOD(EVariantSetType, GetType, (), (const, override));
};