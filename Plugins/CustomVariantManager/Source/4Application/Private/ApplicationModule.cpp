#define LOCTEXT_NAMESPACE "FApplicationModule"
#include "ApplicationModule.h"
#include "Scenes/GeometryVariantSetDetail/IGeometryVariantSetDataStore.h"
#include "Scenes/GeometryVariantSetDetail/IGeometryVariantSetDetailInteractor.h"
#include "Scenes/GeometryVariantSetDetail/Interactor/GeometryVariantSetDetailInteractor.h"


void FApplicationModule::RegisterVIPInterfaces()
{
	Container.RegisterClass<IGeometryVariantSetDatastore, FGeometryVariantSetDatastore>(ETypeContainerScope::Process);	
	Container.RegisterClass<IGeometryVariantSetDetailInteractor, FGeometryVariantSetDetailInteractor>(ETypeContainerScope::Process);
	
#if WITH_GOOGLE_TEST
	OnVipInterfacesRegisteredDelegate.ExecuteIfBound();
#endif
}

void FApplicationModule::UnregisterVIPInterfaces()
{
	Container.Unregister<IGeometryVariantSetDatastore>();
	Container.Unregister<IGeometryVariantSetDetailInteractor>();
}

void FApplicationModule::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT("Application module has started!"));
}

void FApplicationModule::ShutdownModule()
{
	UE_LOG(LogTemp, Warning, TEXT("Application module has shut down"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FApplicationModule,Application)