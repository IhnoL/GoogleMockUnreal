#include "0Test/Public/TestModule.h"

#include "ApplicationModule.h"
#include "0Test/TestHelpersFailureReporter.h"

#define LOCTEXT_NAMESPACE "CustomVariantManagerTest"


IMPLEMENT_MODULE(ITestModule, Test)

void ITestModule::StartupModule()
{
	::testing::TestEventListeners& Listeners = ::testing::UnitTest::GetInstance()->listeners();
	Listeners.Append(new TestHelpersFailureReporter());

	FApplicationModule::Get().OnVipInterfacesRegisteredDelegate.BindLambda([]()
	{
		// Setup runtime Mocks here, when real implementations are not available
	});
}

void ITestModule::ShutdownModule()
{
	if (::testing::internal::failure_reporter != nullptr)
	{
		delete ::testing::internal::failure_reporter;
		::testing::internal::failure_reporter = nullptr;
	}
}
