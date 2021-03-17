#pragma once
#include "Scenes/ISceneDataStore.h"

struct IGeometryVariantSetDatastore : FSceneDatastore
{
	virtual ~IGeometryVariantSetDatastore() = default;
	virtual void SetSelectedVariantSetName(FString& VariantSetName) override = 0;
};

Expose_TNameOf(IGeometryVariantSetDatastore)

class FGeometryVariantSetDatastore : public IGeometryVariantSetDatastore
{

public:
	virtual void SetSelectedVariantSetName(FString& VariantSetNameIn) override
	{
		FSceneDatastore::SetSelectedVariantSetName(VariantSetNameIn);
		OnVariantSetSelectionChangedDelegate.Broadcast(VariantSetNameIn);
	}
};