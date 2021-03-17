#include "DomainModule.h"

#define LOCTEXT_NAMESPACE "FDomainModule"

void FDomainModule::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT("Domain module has started!"));
}

void FDomainModule::ShutdownModule()
{
	UE_LOG(LogTemp, Warning, TEXT("Domain module has shut down"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FDomainModule,Domain)