#pragma once
#include "Scenes/GeometryVariantSetDetail/IGeometryVariantSetDataStore.h"
#include "Scenes/GeometryVariantSetDetail/IGeometryVariantSetDetailInteractor.h"
#include "Scenes/GeometryVariantSetDetail/IGeometryVariantSetDetailPresenter.h"

struct ICustomGeometryVariantSet;
struct IGeometryVariantSetDatastore;
struct ICustomVariantSet;
struct ITagManagerService;
struct IAssetFileService;
struct IVariantManagerService;

class FGeometryVariantSetDetailInteractor : public IGeometryVariantSetDetailInteractor
{
public:
	FGeometryVariantSetDetailInteractor();
	virtual ~FGeometryVariantSetDetailInteractor();

	virtual void CreateGeometryVariant(const CreateGeometryVariant::FRequest& Request) override;
	virtual void CreateGeometryAllOffVariant() override;
	virtual bool CanCreateGeometryAllOffVariant() override;
	virtual void ListVariants() override;
	virtual void ListTags() override;

protected:
	virtual IGeometryVariantSetDetailPresenter* GetPresenter() override;
	virtual IGeometryVariantSetDatastore* GetSceneDatastore() override;

private:
	bool DoesVariantAlreadyExist(ICustomGeometryVariantSet* Set, const FString& Tag) const;
	
	TSharedPtr<IGeometryVariantSetDetailPresenter> Presenter;
	TSharedPtr<IGeometryVariantSetDatastore> SceneDatastore;
};