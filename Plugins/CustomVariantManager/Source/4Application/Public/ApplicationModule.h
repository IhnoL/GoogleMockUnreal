#pragma once

#include "CoreMinimal.h"
#include "Misc/TypeContainer.h"
#include "Modules/ModuleInterface.h"
#include "Scenes/GeometryVariantSetDetail/IGeometryVariantSetDetailInteractor.h"
#include "Scenes/GeometryVariantSetDetail/Interactor/GeometryVariantSetDetailInteractor.h"

class APPLICATION_API FApplicationModule : public IModuleInterface
{
public:	
	static inline FApplicationModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FApplicationModule>("Application");
	}

	TTypeContainer<> Container;

	virtual void RegisterVIPInterfaces();
	virtual void UnregisterVIPInterfaces();

	/* This will get called when the editor loads the module */
	virtual void StartupModule() override;

	/* This will get called when the editor unloads the module */
	virtual void ShutdownModule() override;

#if WITH_GOOGLE_TEST
	DECLARE_DELEGATE(FOnVipInterfacesRegistered)
	FOnVipInterfacesRegistered OnVipInterfacesRegisteredDelegate;

	// only used from test-module to have a "constructor"
	IGeometryVariantSetDetailInteractor* CreateGeometryVariantSetDetailInteractor()
	{
		return new FGeometryVariantSetDetailInteractor();
	}
#endif
};
