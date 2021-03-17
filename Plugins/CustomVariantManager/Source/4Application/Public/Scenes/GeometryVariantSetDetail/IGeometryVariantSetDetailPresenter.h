#pragma once

#include "Entities/Geometry/ICustomGeometryVariant.h"
#include "Scenes/IVariantSetDetailPresenter.h"

namespace ListGeometryVariants
{
struct FResponse
{
	TArray<ICustomGeometryVariant*> Variants;
};
}

struct IGeometryVariantSetDetailPresenter : IVariantSetDetailPresenter
{
	virtual ~IGeometryVariantSetDetailPresenter() = default;

	virtual void PresentListGeometryVariants(const ListGeometryVariants::FResponse& Response) = 0;
	virtual void PresentListTags(const ListTags::FResponse& Response) = 0;
};

Expose_TNameOf(IGeometryVariantSetDetailPresenter)
