
#include "Scenes/VariantSetDetailInteractor.h"

#include "ApplicationModule.h"
#include "Entities/ICustomVariant.h"
#include "Scenes/IVariantSetDetailPresenter.h"
#include "Services/IAssetFileService.h"
#include "Services/IVariantManagerService.h"
#include "Services/ITagManagerService.h"
#include "Scenes/ISceneDataStore.h"

void FVariantSetDetailInteractor::ActivateVariant(const ActivateVariant::FRequest& Request)
{	
	ICustomVariantSet* SelectedVariantSet = GetVariantManagerService()->GetVariantSetByName(GetSceneDatastore()->GetSelectedVariantSetName());
	if (SelectedVariantSet != nullptr)
	{
		const auto VariantSet =  GetVariantManagerService()->FetchVariantByName(SelectedVariantSet, Request.VariantName);
		if (VariantSet
		    && GetVariantManagerService()->ActivateVariant(SelectedVariantSet, VariantSet)
		    == EVariantManagerServiceResult::Success)
		{
			ListVariants();
			return;
		}
	}
	GetPresenter()->PresentError(ShowError::FResponse{"ActivateVariant failed"});
}

void FVariantSetDetailInteractor::RefreshAllVariants()
{
	ICustomVariantSet* SelectedVariantSet = GetVariantManagerService()->GetVariantSetByName(GetSceneDatastore()->GetSelectedVariantSetName());
	if(SelectedVariantSet != nullptr
		&& GetVariantManagerService()->RefreshVariantSet(SelectedVariantSet) == EVariantManagerServiceResult::Success)
	{	
		ListVariants();
		ListTags();
	}
	else
	{
		GetPresenter()->PresentError(ShowError::FResponse{"RefreshAllVariants failed"});
	}
}



void FVariantSetDetailInteractor::DeleteVariant(const DeleteVariant::FRequest& Request)
{
	ICustomVariantSet* SelectedVariantSet = GetVariantManagerService()->GetVariantSetByName(GetSceneDatastore()->GetSelectedVariantSetName());
	if (SelectedVariantSet != nullptr)
	{
		const auto Variant =  GetVariantManagerService()->FetchVariantByName(SelectedVariantSet, Request.VariantName);
		if(Variant
			&& GetVariantManagerService()->DeleteVariant(SelectedVariantSet, Variant)
			== EVariantManagerServiceResult::Success)
		{
			ListVariants();
			return;
		}	
	}
	GetPresenter()->PresentError(ShowError::FResponse{"Deletion of Variant failed"});
}

void FVariantSetDetailInteractor::RefreshVariantThumbnailFromViewPort(const RefreshVariantThumbnailFromViewPort::FRequest& Request)
{
	ICustomVariantSet* SelectedVariantSet = GetVariantManagerService()->GetVariantSetByName(GetSceneDatastore()->GetSelectedVariantSetName());
	if (SelectedVariantSet != nullptr)
	{
		const auto Variant =  GetVariantManagerService()->FetchVariantByName(SelectedVariantSet, Request.VariantName);
		if(GetVariantManagerService()->RefreshVariantThumbnailFromEditorViewPort(SelectedVariantSet, Variant) == EVariantManagerServiceResult::Success)
		{
			ListVariants();
			return;
		}
	}
	GetPresenter()->PresentError(ShowError::FResponse{"RefreshVariantThumbnailFromViewPort failed"});
}

void FVariantSetDetailInteractor::RefreshVariantThumbnailFromFile(const RefreshVariantThumbnailFromFile::FRequest& Request)
{	
	ICustomVariantSet* SelectedVariantSet = GetVariantManagerService()->GetVariantSetByName(GetSceneDatastore()->GetSelectedVariantSetName());
	if (SelectedVariantSet != nullptr)
	{
		const auto Variant =  GetVariantManagerService()->FetchVariantByName(SelectedVariantSet, Request.VariantName);
		if(GetVariantManagerService()->RefreshVariantThumbnailFromFile(SelectedVariantSet, Variant, Request.SourceImagePath) == EVariantManagerServiceResult::Success)
		{
			ListVariants();
			return;
		}
	}
	GetPresenter()->PresentError(ShowError::FResponse{"RefreshVariantThumbnailFromFile failed"});
}

void FVariantSetDetailInteractor::ClearThumbnail(const ClearThumbnail::FRequest& Request)
{
	ICustomVariantSet* SelectedVariantSet = GetVariantManagerService()->GetVariantSetByName(GetSceneDatastore()->GetSelectedVariantSetName());
	if (SelectedVariantSet != nullptr)
	{
		const auto Variant =  GetVariantManagerService()->FetchVariantByName(SelectedVariantSet, Request.VariantName);
		if(GetVariantManagerService()->ClearVariantThumbnail(SelectedVariantSet, Variant) == EVariantManagerServiceResult::Success)
		{
			ListVariants();
			return;
		}
	}
	GetPresenter()->PresentError(ShowError::FResponse{"ClearThumbnail failed"});
}

void FVariantSetDetailInteractor::RenameVariant(const RenameVariant::FRequest& Request)
{
	if(Request.NameNew.IsEmpty())
	{
		GetPresenter()->PresentError(ShowError::FResponse{"Name must not be empty. Rename failed"});
		return;
	}
	
	ICustomVariantSet* SelectedVariantSet = GetVariantManagerService()->GetVariantSetByName(GetSceneDatastore()->GetSelectedVariantSetName());
	if (SelectedVariantSet != nullptr)
	{
		const auto Variant =  GetVariantManagerService()->FetchVariantByName(SelectedVariantSet, Request.VariantName);
		if(Variant
            && GetVariantManagerService()->RenameVariant(SelectedVariantSet, Variant, Request.NameNew)
            == EVariantManagerServiceResult::Success)
		{
			ListVariants();
			return;
		}
	}
	GetPresenter()->PresentError(ShowError::FResponse{"RenameVariant failed"});
}

TSharedRef<IVariantManagerService> FVariantSetDetailInteractor::GetVariantManagerService()
{
	if (!VariantManagerService.IsValid())
	{
		VariantManagerService = FApplicationModule::Get().Container.GetInstance<IVariantManagerService>();
	}
	return VariantManagerService.ToSharedRef();
}

TSharedRef<IAssetFileService> FVariantSetDetailInteractor::GetAssetFileService()
{
	if (!AssetFileService.IsValid())
	{
		AssetFileService = FApplicationModule::Get().Container.GetInstance<IAssetFileService>();
	}
	return AssetFileService.ToSharedRef();
}

TSharedRef<ITagManagerService> FVariantSetDetailInteractor::GetTagManagerService()
{
	if (!TagMangerService.IsValid())
	{
		TagMangerService = FApplicationModule::Get().Container.GetInstance<ITagManagerService>();
	}
	return TagMangerService.ToSharedRef();
}