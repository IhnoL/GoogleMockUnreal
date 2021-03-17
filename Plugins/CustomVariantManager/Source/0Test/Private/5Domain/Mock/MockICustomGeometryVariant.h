#pragma once

#include "Entities/Geometry/ICustomGeometryVariant.h"
#include "gmock/gmock.h"

class UTexture2D;

class MockICustomGeometryVariant: public ICustomGeometryVariant
{
public:
	MOCK_METHOD(UTexture2D*, GetThumbnail,(), (const, override));
	MOCK_METHOD(FString, GetName,(), (const, override));
	MOCK_METHOD(FString, GetTag,(), (const ,override));
	MOCK_METHOD(int32, GetNumberOfComponents,(), (const ,override));
	MOCK_METHOD(bool, GetIsActive,(), (const , override));
	MOCK_METHOD(bool, IsAllOffVariant, (), (const, override));
};
