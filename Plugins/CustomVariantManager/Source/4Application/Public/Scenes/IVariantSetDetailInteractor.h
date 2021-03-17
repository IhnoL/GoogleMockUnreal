#pragma once

class SWidget;

namespace ActivateVariant
{
	struct FRequest
	{
		FString VariantName;
	};
};

namespace DeleteVariant
{
	struct FRequest
	{
		FString VariantName;
	};
}

namespace RenameVariant
{
	struct FRequest
	{
		FString VariantName;
		FString NameNew;
	};
}

namespace RefreshVariantThumbnailFromViewPort
{
	struct FRequest
	{
		FString VariantName;
	};
}

namespace RefreshVariantThumbnailFromFile
{
	struct FRequest
	{
		FString VariantName;
		FString SourceImagePath;
	};
}

namespace ClearThumbnail
{
	struct FRequest
	{
		FString VariantName;
	};
}


DECLARE_DELEGATE_OneParam(FOnEditVariant, RenameVariant::FRequest)	
DECLARE_DELEGATE_OneParam(FOnDeleteVariant, DeleteVariant::FRequest)
DECLARE_DELEGATE_OneParam(FOnActivateVariant, ActivateVariant::FRequest)

struct IVariantSetDetailInteractor
{
	virtual ~IVariantSetDetailInteractor() = default;

	virtual void ActivateVariant(const ActivateVariant::FRequest& Request) = 0;
	virtual void ListVariants() = 0;
	virtual void ListTags() = 0;
	virtual void RefreshAllVariants() = 0;
	virtual void RenameVariant(const RenameVariant::FRequest& Request) = 0;
	virtual void DeleteVariant(const DeleteVariant::FRequest& Request) = 0;
	virtual void RefreshVariantThumbnailFromViewPort(const RefreshVariantThumbnailFromViewPort::FRequest& Request) = 0;
	virtual void RefreshVariantThumbnailFromFile(const RefreshVariantThumbnailFromFile::FRequest& Request) = 0;
	virtual void ClearThumbnail(const ClearThumbnail::FRequest& Request) = 0;
};