#pragma once
#include "Scenes/IVariantSetDetailInteractor.h"

class IVariantSetDetailPresenter;
struct ITagManagerService;
struct ISceneDatastore;
struct IAssetFileService;
struct IVariantManagerService;

class FVariantSetDetailInteractor : public IVariantSetDetailInteractor
{
public:
	virtual void ActivateVariant(const ActivateVariant::FRequest& Request) override;
	virtual void RefreshAllVariants() override;
	virtual void RenameVariant(const RenameVariant::FRequest& Request) override;
	virtual void DeleteVariant(const DeleteVariant::FRequest& Request) override;
	virtual void RefreshVariantThumbnailFromViewPort(const RefreshVariantThumbnailFromViewPort::FRequest& Request) override;
	virtual void RefreshVariantThumbnailFromFile(const RefreshVariantThumbnailFromFile::FRequest& Request) override;
	virtual void ClearThumbnail(const ClearThumbnail::FRequest& Request) override;

	virtual void ListTags() override {};
	
protected:
	virtual IVariantSetDetailPresenter* GetPresenter()
	{
		// Should never be called, as overridden by dominance in specific implementation
		return nullptr;
	}

	virtual ISceneDatastore* GetSceneDatastore()
	{
		return nullptr;
	}
	
	TSharedPtr<IVariantManagerService> VariantManagerService;
	TSharedPtr<IAssetFileService> AssetFileService;
	TSharedPtr<ITagManagerService> TagMangerService;

	TSharedRef<IVariantManagerService> GetVariantManagerService();
	TSharedRef<IAssetFileService> GetAssetFileService();
	TSharedRef<ITagManagerService> GetTagManagerService();
};
