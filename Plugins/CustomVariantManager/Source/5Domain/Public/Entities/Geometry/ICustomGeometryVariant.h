#pragma once

#include "Entities/ICustomVariant.h"

struct ICustomGeometryVariant : ICustomVariant
{
	virtual FString GetTag() const = 0;
	virtual int32 GetNumberOfComponents() const = 0;
	virtual bool IsAllOffVariant() const = 0;
};