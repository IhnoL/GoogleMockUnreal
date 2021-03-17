#pragma once

#include "Entities/ICustomVariantSet.h"

struct ICustomGeometryVariant;

struct ICustomGeometryVariantSet : ICustomVariantSet
{
	virtual TArray<ICustomGeometryVariant*> GetGeometryVariants() const = 0;
};