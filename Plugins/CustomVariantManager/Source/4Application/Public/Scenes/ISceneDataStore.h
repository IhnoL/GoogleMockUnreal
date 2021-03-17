#pragma once

struct ISceneDatastore
{
	virtual ~ISceneDatastore() = default;
    virtual FString GetSelectedVariantSetName() = 0;
	virtual void SetSelectedVariantSetName(FString& VariantSetName) = 0;
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnVariantSetSelectionChanged, const FString&)
	FOnVariantSetSelectionChanged OnVariantSetSelectionChangedDelegate;
};

class FSceneDatastore : public ISceneDatastore
{
	FString VariantSetName;

public:
	virtual void SetSelectedVariantSetName(FString& VariantSetNameIn) override
	{
		VariantSetName = VariantSetNameIn;
	}

	virtual FString GetSelectedVariantSetName() override
	{
		return VariantSetName;
	}
};