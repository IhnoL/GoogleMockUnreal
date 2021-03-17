#pragma once
#include "Entities/ICustomVariantSet.h"

enum class EAssetFileServiceResult
{
	Success,
	Error
};

struct IAssetFileService
{
	virtual ~IAssetFileService() = default;	
	virtual TArray<ICustomVariantSet*> GetAllVariantSets() = 0;
	virtual ICustomVariantSet* GetVariantSet(const FString& UniqueName) = 0;
	virtual EAssetFileServiceResult DeleteVariantSet(const FString& UniqueName) = 0;
	virtual EAssetFileServiceResult DeleteVariantSet(ICustomVariantSet& VariantSet) = 0;
};

Expose_TNameOf(IAssetFileService)
