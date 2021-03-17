#pragma once

#include "Scenes/VariantSetDetailInteractor.h"

namespace CreateGeometryVariant
{
struct FRequest
{
	FString Tag;
};
}

class IGeometryVariantSetDetailInteractor : public virtual FVariantSetDetailInteractor
{
public:
	virtual void CreateGeometryVariant(const CreateGeometryVariant::FRequest& Request) = 0;
	virtual void CreateGeometryAllOffVariant() = 0;
	virtual bool CanCreateGeometryAllOffVariant() = 0;
};

Expose_TNameOf(IGeometryVariantSetDetailInteractor)
