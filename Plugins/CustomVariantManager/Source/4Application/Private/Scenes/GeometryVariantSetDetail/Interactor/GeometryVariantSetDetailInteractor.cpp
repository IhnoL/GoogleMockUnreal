#include "GeometryVariantSetDetailInteractor.h"
#include "ApplicationModule.h"
#include "Scenes/GeometryVariantSetDetail/IGeometryVariantSetDataStore.h"
#include "Scenes/GeometryVariantSetDetail/IGeometryVariantSetDetailPresenter.h"
#include "Services/ITagManagerService.h"
#include "Services/IVariantManagerService.h"
#include "Entities/Geometry/ICustomGeometryVariantSet.h"
#include "Entities/Geometry/ICustomGeometryVariant.h"

FGeometryVariantSetDetailInteractor::FGeometryVariantSetDetailInteractor()
{
}

FGeometryVariantSetDetailInteractor::~FGeometryVariantSetDetailInteractor()
{
}

void FGeometryVariantSetDetailInteractor::CreateGeometryVariant(const CreateGeometryVariant::FRequest& Request)
{
	if(!GetTagManagerService()->GetAllGeometryTagsInEditorWorld().Contains(Request.Tag))
	{
		GetPresenter()->PresentError(ShowError::FResponse{"Tag for Variant does not exist. Creation failed"});
		return;
	}
	
	ICustomVariantSet* SelectedVariantSet = GetVariantManagerService()->GetVariantSetByName(GetSceneDatastore()->GetSelectedVariantSetName());
	if (ICustomGeometryVariantSet* SelectedGeometryVariantSet = dynamic_cast<ICustomGeometryVariantSet*>(SelectedVariantSet))
	{
		if(DoesVariantAlreadyExist(SelectedGeometryVariantSet, Request.Tag))
		{
			const FString ErrorMessage = FString::Printf(TEXT("Variant with Tag %s already exists"), *Request.Tag);
			GetPresenter()->PresentError(ShowError::FResponse{ErrorMessage});
			return;
		}

		const auto NewGeometryVariant = GetVariantManagerService()->CreateGeometryVariant(SelectedGeometryVariantSet, Request.Tag);
		if (NewGeometryVariant != nullptr)
		{
			GetVariantManagerService()->ActivateVariant(SelectedVariantSet, NewGeometryVariant);
			GetVariantManagerService()->RefreshVariantThumbnailFromEditorViewPort(SelectedVariantSet, NewGeometryVariant);
			
			ListVariants();
		}
		else
		{
			GetPresenter()->PresentError(ShowError::FResponse{"Creation of Variant failed"});
		}
	}
}

void FGeometryVariantSetDetailInteractor::CreateGeometryAllOffVariant()
{
	if(!CanCreateGeometryAllOffVariant())
	{
		GetPresenter()->PresentError(ShowError::FResponse{"An AllOff-Variant already exists"});
		return;
	}
	
	ICustomVariantSet* SelectedVariantSet = GetVariantManagerService()->GetVariantSetByName(GetSceneDatastore()->GetSelectedVariantSetName());
	if (ICustomGeometryVariantSet* SelectedGeometryVariantSet = dynamic_cast<ICustomGeometryVariantSet*>(SelectedVariantSet))
	{
		ICustomGeometryVariant* NewAllOffVariant = GetVariantManagerService()->CreateGeometryAllOffVariant(SelectedGeometryVariantSet);
		if(NewAllOffVariant)
		{
			const FString DefaultAllOffVariantName = FString("All variants off");
			GetVariantManagerService()->RenameVariant(SelectedVariantSet, NewAllOffVariant, DefaultAllOffVariantName);
			
			GetVariantManagerService()->ActivateVariant(SelectedVariantSet, NewAllOffVariant);
			GetVariantManagerService()->RefreshVariantThumbnailFromEditorViewPort(SelectedVariantSet, NewAllOffVariant);
			
			ListVariants();
		}
		else
		{
			GetPresenter()->PresentError(ShowError::FResponse{"Creation of AllOff-Variant failed"});
		}
	}
}

bool FGeometryVariantSetDetailInteractor::CanCreateGeometryAllOffVariant()
{
	ICustomVariantSet* SelectedVariantSet = GetVariantManagerService()->GetVariantSetByName(GetSceneDatastore()->GetSelectedVariantSetName());

	ICustomGeometryVariantSet* SelectedGeometryVariantSet = dynamic_cast<ICustomGeometryVariantSet*>(SelectedVariantSet);
	if(!SelectedGeometryVariantSet)
	{
		return false;
	}

	TArray<ICustomGeometryVariant*> Variants = GetVariantManagerService()->GetAllGeometryVariants(SelectedGeometryVariantSet);
	return Variants.FindByPredicate([&](ICustomGeometryVariant* Variant){ return Variant && Variant->IsAllOffVariant();}) ? false : true;
}

void FGeometryVariantSetDetailInteractor::ListVariants()
{
	ICustomVariantSet* SelectedVariantSet = GetVariantManagerService()->GetVariantSetByName(GetSceneDatastore()->GetSelectedVariantSetName());
	if (ICustomGeometryVariantSet* SelectedGeometryVariantSet = dynamic_cast<ICustomGeometryVariantSet*>(SelectedVariantSet))	
	{
		const auto GeometryVariants = GetVariantManagerService()->GetAllGeometryVariants(SelectedGeometryVariantSet);
		GetPresenter()->PresentListGeometryVariants(ListGeometryVariants::FResponse{GeometryVariants});
	}
	else
	{
		GetPresenter()->PresentError(ShowError::FResponse{"No VariantSet selected. ListVariants failed"});
	}
}

void FGeometryVariantSetDetailInteractor::ListTags()
{
	GetPresenter()->PresentListTags(ListTags::FResponse{GetTagManagerService()->GetAllGeometryTagsInEditorWorld()});
}

IGeometryVariantSetDetailPresenter* FGeometryVariantSetDetailInteractor::GetPresenter()
{
	if (!Presenter.IsValid())
	{
		Presenter = FApplicationModule::Get().Container.GetInstance<IGeometryVariantSetDetailPresenter>();
	}
	return &Presenter.ToSharedRef().Get();
}

IGeometryVariantSetDatastore* FGeometryVariantSetDetailInteractor::GetSceneDatastore()
{
	if (!SceneDatastore.IsValid())
	{
		SceneDatastore = FApplicationModule::Get().Container.GetInstance<IGeometryVariantSetDatastore>();
	}
	return &SceneDatastore.ToSharedRef().Get();
}

bool FGeometryVariantSetDetailInteractor::DoesVariantAlreadyExist(ICustomGeometryVariantSet* Set, const FString& Tag) const
{
	for(ICustomVariant* Variant : Set->GetVariants())
	{
		if(ICustomGeometryVariant* GeometryVariant = dynamic_cast<ICustomGeometryVariant*>(Variant))
		{
			if(GeometryVariant->GetTag().Equals(Tag))
			{
				return true;
			}
		}
	}
	return false;
}