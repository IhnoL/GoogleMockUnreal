#pragma once
#include "Scenes/GeometryVariantSetDetail/IGeometryVariantSetDataStore.h"

#include "gmock/gmock.h"

class MockIGeometryVariantSetDatastore : public IGeometryVariantSetDatastore
{
public:

	MOCK_METHOD(FString, GetSelectedVariantSetName, (), (override));
	MOCK_METHOD(void, SetSelectedVariantSetName, (FString& VariantSetName), ( override));
};
