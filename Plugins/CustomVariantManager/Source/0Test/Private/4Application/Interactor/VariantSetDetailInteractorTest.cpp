#include "ApplicationModule.h"
#include "CoreTypes.h"
#include "Misc/AutomationTest.h"
#include "MockDeclarations/GeometryInteractorMockDeclarations.h"
#include "Scenes/GeometryVariantSetDetail/IGeometryVariantSetDetailInteractor.h"
#include "Services/IVariantManagerService.h"

namespace VariantSetDetailInteractorTest
{

#if WITH_DEV_AUTOMATION_TESTS
#define DEFAULT_TEST_FLAGS EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::EngineFilter

using ::testing::AtLeast;
using ::testing::Exactly;
using ::testing::Return;
using ::testing::AtMost;


GeometryInteractorMockDeclarations* Mock;
// We need one of the "special" Interactors here, to test the base Interactor methods, as the base one is no accessible to the outside
	IGeometryVariantSetDetailInteractor* GeometryVariantSetDetailInteractor;

void Setup()
{
	GeometryVariantSetDetailInteractor = FApplicationModule::Get().CreateGeometryVariantSetDetailInteractor();
	Mock = new GeometryInteractorMockDeclarations();
}

void Teardown()
{
	delete GeometryVariantSetDetailInteractor;
	delete Mock;
}

void VerifyPresentListVariantsCalled(int Times)
{
	EXPECT_CALL(*Mock->MockPresenter, PresentListGeometryVariants)
    .Times(Exactly(Times));
}

void VerifyPresentErrorCalled(int Times)
{
	EXPECT_CALL(*Mock->MockPresenter, PresentError)
    .Times(Exactly(Times));
}

#pragma region ActivateVariant

IMPLEMENT_SIMPLE_AUTOMATION_TEST(ActivateVariant_CallsActivateVariant,
	"CustomVariantManager.4Application.VariantSetDetailInteractor.ActivateVariant.CallsActivateVariant", DEFAULT_TEST_FLAGS)

bool ActivateVariant_CallsActivateVariant::RunTest(const FString& Parameters)
{
	Setup();

	EXPECT_CALL(*Mock->MockVariantManagerService, ActivateVariant)
    .Times(Exactly(1))
    .WillRepeatedly(Return(EVariantManagerServiceResult::Success));

	EXPECT_CALL(*Mock->MockVariantManagerService, FetchVariantByName(Mock->DefaultVariantSet, Mock->FindableVariantName))
    .Times(Exactly(1))
    .WillRepeatedly(Return(Mock->DefaultVariantWithName));

	VerifyPresentListVariantsCalled(1);
	VerifyPresentErrorCalled(0);

	GeometryVariantSetDetailInteractor->ActivateVariant(ActivateVariant::FRequest{Mock->FindableVariantName});

	Teardown();
	return true;
}


IMPLEMENT_SIMPLE_AUTOMATION_TEST(ActivateVariant_CallsPresentError_OnFailure,
	"CustomVariantManager.4Application.VariantSetDetailInteractor.ActivateVariant.CallsPresentError", DEFAULT_TEST_FLAGS)

bool ActivateVariant_CallsPresentError_OnFailure::RunTest(const FString& Parameters)
{
	Setup();

	EXPECT_CALL(*Mock->MockVariantManagerService, ActivateVariant)
    .Times(Exactly(1))
    .WillRepeatedly(Return(EVariantManagerServiceResult::Error));

	VerifyPresentListVariantsCalled(0);
	VerifyPresentErrorCalled(1);

	GeometryVariantSetDetailInteractor->ActivateVariant(ActivateVariant::FRequest{Mock->FindableVariantName});

	Teardown();
	return true;
}

#pragma endregion
#pragma region RefreshAllVariants

IMPLEMENT_SIMPLE_AUTOMATION_TEST(RefreshAllVariants_CallsPresentListGeometryTags_CallsPresentListVariants,
	"CustomVariantManager.4Application.VariantSetDetailInteractor.RefreshAllVariants.CallsPresentListGeometryTags_CallsPresentListVariants", DEFAULT_TEST_FLAGS)

bool RefreshAllVariants_CallsPresentListGeometryTags_CallsPresentListVariants::RunTest(const FString& Parameters)
{
	Setup();

	EXPECT_CALL(*Mock->MockVariantManagerService, RefreshVariantSet)
    .Times(Exactly(1));

	EXPECT_CALL(*Mock->MockPresenter, PresentListTags)
    .Times(Exactly(1));

	VerifyPresentErrorCalled(0);
	VerifyPresentListVariantsCalled(1);

	GeometryVariantSetDetailInteractor->RefreshAllVariants();

	Teardown();
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(RefreshAllVariants_CallsPresentError_OnNoSelectedVariantSet,
	"CustomVariantManager.4Application.VariantSetDetailInteractor.RefreshAllVariants.CallsPresentError_OnNoSelectedVariantSet", DEFAULT_TEST_FLAGS)

bool RefreshAllVariants_CallsPresentError_OnNoSelectedVariantSet::RunTest(const FString& Parameters)
{
	Setup();

	EXPECT_CALL(*Mock->MockVariantManagerService, GetVariantSetByName)
    .Times(Exactly(1))
	.WillRepeatedly(Return(nullptr));

	EXPECT_CALL(*Mock->MockVariantManagerService, RefreshVariantSet)
    .Times(Exactly(0));

	EXPECT_CALL(*Mock->MockPresenter, PresentListTags)
    .Times(Exactly(0));

	VerifyPresentErrorCalled(1);
	VerifyPresentListVariantsCalled(0);

	GeometryVariantSetDetailInteractor->RefreshAllVariants();

	Teardown();
	return true;
}

#pragma endregion
#pragma region RenameVariant

IMPLEMENT_SIMPLE_AUTOMATION_TEST(RenameVariant_CallsRenameVariant,
	"CustomVariantManager.4Application.VariantSetDetailInteractor.RenameVariant.CallsRenameVariant", DEFAULT_TEST_FLAGS)

bool RenameVariant_CallsRenameVariant::RunTest(const FString& Parameters)
{
	Setup();

	EXPECT_CALL(*Mock->MockVariantManagerService, RenameVariant)
    .Times(Exactly(1))
	.WillRepeatedly(Return(EVariantManagerServiceResult::Success));

	VerifyPresentErrorCalled(0);
	VerifyPresentListVariantsCalled(1);

	GeometryVariantSetDetailInteractor->RenameVariant(RenameVariant::FRequest{Mock->FindableVariantName, FString("NewName")});

	Teardown();
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(RenameVariant_CallsPresentError_OnNoNewName,
    "CustomVariantManager.4Application.VariantSetDetailInteractor.RenameVariant.CallsPresentError_OnNoNewName", DEFAULT_TEST_FLAGS)

bool RenameVariant_CallsPresentError_OnNoNewName::RunTest(const FString& Parameters)
{
	Setup();

	EXPECT_CALL(*Mock->MockVariantManagerService, RenameVariant)
    .Times(Exactly(0));

	VerifyPresentErrorCalled(1);
	VerifyPresentListVariantsCalled(0);

	GeometryVariantSetDetailInteractor->RenameVariant(RenameVariant::FRequest{Mock->FindableVariantName, FString("")});

	Teardown();
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(RenameVariant_CallsPresentError_OnFailure,
    "CustomVariantManager.4Application.VariantSetDetailInteractor.RenameVariant.CallsPresentError_OnFailure", DEFAULT_TEST_FLAGS)

bool RenameVariant_CallsPresentError_OnFailure::RunTest(const FString& Parameters)
{
	Setup();

	EXPECT_CALL(*Mock->MockVariantManagerService, RenameVariant)
    .Times(Exactly(1))
	.WillRepeatedly(Return(EVariantManagerServiceResult::Error));

	VerifyPresentErrorCalled(1);
	VerifyPresentListVariantsCalled(0);

	GeometryVariantSetDetailInteractor->RenameVariant(RenameVariant::FRequest{Mock->FindableVariantName, FString("NewName")});

	Teardown();
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(RenameVariant_CallsPresentError_OnNoSelectedVariantSet,
    "CustomVariantManager.4Application.VariantSetDetailInteractor.RenameVariant.CallsPresentError_OnNoSelectedVariantSet", DEFAULT_TEST_FLAGS)

bool RenameVariant_CallsPresentError_OnNoSelectedVariantSet::RunTest(const FString& Parameters)
{
	Setup();

	EXPECT_CALL(*Mock->MockVariantManagerService, GetVariantSetByName)
    .Times(Exactly(1))
    .WillRepeatedly(Return(nullptr));
	
	EXPECT_CALL(*Mock->MockVariantManagerService, RenameVariant)
    .Times(Exactly(0));        

	VerifyPresentErrorCalled(1);
	VerifyPresentListVariantsCalled(0);

	GeometryVariantSetDetailInteractor->RenameVariant(RenameVariant::FRequest{Mock->FindableVariantName, FString("NewName")});

	Teardown();
	return true;
}

#pragma endregion
#pragma region DeleteVariant

IMPLEMENT_SIMPLE_AUTOMATION_TEST(DeleteVariant_CallsDeleteVariant,
    "CustomVariantManager.4Application.VariantSetDetailInteractor.DeleteVariant.CallsDeleteVariant", DEFAULT_TEST_FLAGS)

bool DeleteVariant_CallsDeleteVariant::RunTest(const FString& Parameters)
{
	Setup();

	EXPECT_CALL(*Mock->MockVariantManagerService, DeleteVariant)
    .Times(Exactly(1))
    .WillRepeatedly(Return(EVariantManagerServiceResult::Success));

	VerifyPresentErrorCalled(0);
	VerifyPresentListVariantsCalled(1);

	GeometryVariantSetDetailInteractor->DeleteVariant(DeleteVariant::FRequest{Mock->FindableVariantName});

	Teardown();
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(DeleteVariant_CallsPresentError_OnFailure,
    "CustomVariantManager.4Application.VariantSetDetailInteractor.DeleteVariant.CallsPresentError_OnFailure", DEFAULT_TEST_FLAGS)

bool DeleteVariant_CallsPresentError_OnFailure::RunTest(const FString& Parameters)
{
	Setup();

	EXPECT_CALL(*Mock->MockVariantManagerService, DeleteVariant)
    .Times(Exactly(1))
    .WillRepeatedly(Return(EVariantManagerServiceResult::Error));

	VerifyPresentErrorCalled(1);
	VerifyPresentListVariantsCalled(0);

	GeometryVariantSetDetailInteractor->DeleteVariant(DeleteVariant::FRequest{Mock->FindableVariantName});

	Teardown();
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(DeleteVariant_CallsPresentError_OnNoSelectedVariantSet,
    "CustomVariantManager.4Application.VariantSetDetailInteractor.DeleteVariant.CallsPresentError_OnNoSelectedVariantSet", DEFAULT_TEST_FLAGS)

bool DeleteVariant_CallsPresentError_OnNoSelectedVariantSet::RunTest(const FString& Parameters)
{
	Setup();

	EXPECT_CALL(*Mock->MockVariantManagerService, GetVariantSetByName)
    .Times(Exactly(1))
    .WillRepeatedly(Return(nullptr));

	EXPECT_CALL(*Mock->MockVariantManagerService, DeleteVariant)
    .Times(Exactly(0));

	VerifyPresentErrorCalled(1);
	VerifyPresentListVariantsCalled(0);

	GeometryVariantSetDetailInteractor->DeleteVariant(DeleteVariant::FRequest{Mock->FindableVariantName});

	Teardown();
	return true;
}

#pragma endregion
#pragma region RefreshVariantThumbnailFromViewPort

IMPLEMENT_SIMPLE_AUTOMATION_TEST(RefreshVariantThumbnailFromViewPort_CallsListVariants,
    "CustomVariantManager.4Application.VariantSetDetailInteractor.RefreshVariantThumbnailFromViewPort.CallsListVariants", DEFAULT_TEST_FLAGS)

bool RefreshVariantThumbnailFromViewPort_CallsListVariants::RunTest(const FString& Parameters)
{
	Setup();

	EXPECT_CALL(*Mock->MockVariantManagerService, RefreshVariantThumbnailFromEditorViewPort)
	.Times(Exactly(1))
	.WillRepeatedly(Return(EVariantManagerServiceResult::Success));
	
	VerifyPresentListVariantsCalled(1);
	VerifyPresentErrorCalled(0);

	GeometryVariantSetDetailInteractor->RefreshVariantThumbnailFromViewPort(RefreshVariantThumbnailFromViewPort::FRequest{Mock->FindableVariantName});

	Teardown();
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(RefreshVariantThumbnailFromViewPort_CallsPresentError_OnFailure,
    "CustomVariantManager.4Application.VariantSetDetailInteractor.RefreshVariantThumbnailFromViewPort.CallsPresentError.OnFailure", DEFAULT_TEST_FLAGS)

bool RefreshVariantThumbnailFromViewPort_CallsPresentError_OnFailure::RunTest(const FString& Parameters)
{
	Setup();

	EXPECT_CALL(*Mock->MockVariantManagerService, RefreshVariantThumbnailFromEditorViewPort)
    .Times(Exactly(1))
    .WillRepeatedly(Return(EVariantManagerServiceResult::Error));
	
	VerifyPresentListVariantsCalled(0);
	VerifyPresentErrorCalled(1);

	GeometryVariantSetDetailInteractor->RefreshVariantThumbnailFromViewPort(RefreshVariantThumbnailFromViewPort::FRequest{Mock->FindableVariantName});

	Teardown();
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(RefreshVariantThumbnailFromViewPort_CallsPresentError_OnNoSelectedVariantSet,
    "CustomVariantManager.4Application.VariantSetDetailInteractor.RefreshVariantThumbnailFromViewPort.CallsPresentError.OnNoSelectedVariantSet", DEFAULT_TEST_FLAGS)

bool RefreshVariantThumbnailFromViewPort_CallsPresentError_OnNoSelectedVariantSet::RunTest(const FString& Parameters)
{
	Setup();

	EXPECT_CALL(*Mock->MockVariantManagerService, GetVariantSetByName)
	.Times(Exactly(1))
	.WillRepeatedly(Return(nullptr));
	
	EXPECT_CALL(*Mock->MockVariantManagerService, RefreshVariantThumbnailFromEditorViewPort)
    .Times(Exactly(0));
	
	VerifyPresentListVariantsCalled(0);
	VerifyPresentErrorCalled(1);

	GeometryVariantSetDetailInteractor->RefreshVariantThumbnailFromViewPort(RefreshVariantThumbnailFromViewPort::FRequest{Mock->FindableVariantName});
	
	Teardown();
	return true;
}

#pragma endregion
#pragma region RefreshVariantThumbnailFromFile

IMPLEMENT_SIMPLE_AUTOMATION_TEST(RefreshVariantThumbnailFromFile_CallsListVariants,
    "CustomVariantManager.4Application.VariantSetDetailInteractor.RefreshVariantThumbnailFromFile.CallsListVariants", DEFAULT_TEST_FLAGS)

bool RefreshVariantThumbnailFromFile_CallsListVariants::RunTest(const FString& Parameters)
{
	Setup();

	EXPECT_CALL(*Mock->MockVariantManagerService, RefreshVariantThumbnailFromFile)
	.Times(Exactly(1))
	.WillRepeatedly(Return(EVariantManagerServiceResult::Success));
	
	VerifyPresentListVariantsCalled(1);
	VerifyPresentErrorCalled(0);

	const FString SourceImagePath = "SourceImagePath.png";
	GeometryVariantSetDetailInteractor->RefreshVariantThumbnailFromFile(RefreshVariantThumbnailFromFile::FRequest{Mock->FindableVariantName, SourceImagePath});

	Teardown();
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(RefreshVariantThumbnailFromFile_CallsPresentError_OnFailure,
    "CustomVariantManager.4Application.VariantSetDetailInteractor.RefreshVariantThumbnailFromFile.CallsPresentError.OnFailure", DEFAULT_TEST_FLAGS)

bool RefreshVariantThumbnailFromFile_CallsPresentError_OnFailure::RunTest(const FString& Parameters)
{
	Setup();

	EXPECT_CALL(*Mock->MockVariantManagerService, RefreshVariantThumbnailFromFile)
    .Times(Exactly(1))
    .WillRepeatedly(Return(EVariantManagerServiceResult::Error));
	
	VerifyPresentListVariantsCalled(0);
	VerifyPresentErrorCalled(1);

	const FString SourceImagePath = "SourceImagePath.png";
	GeometryVariantSetDetailInteractor->RefreshVariantThumbnailFromFile(RefreshVariantThumbnailFromFile::FRequest{Mock->FindableVariantName, SourceImagePath});

	Teardown();
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(RefreshVariantThumbnailFromFile_CallsPresentError_OnNoSelectedVariantSet,
    "CustomVariantManager.4Application.VariantSetDetailInteractor.RefreshVariantThumbnailFromFile.CallsPresentError.OnNoSelectedVariantSet", DEFAULT_TEST_FLAGS)

bool RefreshVariantThumbnailFromFile_CallsPresentError_OnNoSelectedVariantSet::RunTest(const FString& Parameters)
{
	Setup();

	EXPECT_CALL(*Mock->MockVariantManagerService, GetVariantSetByName)
	.Times(Exactly(1))
	.WillRepeatedly(Return(nullptr));
	
	EXPECT_CALL(*Mock->MockVariantManagerService, RefreshVariantThumbnailFromFile)
    .Times(Exactly(0));
	
	VerifyPresentListVariantsCalled(0);
	VerifyPresentErrorCalled(1);

	const FString SourceImagePath = "SourceImagePath.png";
	GeometryVariantSetDetailInteractor->RefreshVariantThumbnailFromFile(RefreshVariantThumbnailFromFile::FRequest{Mock->FindableVariantName, SourceImagePath});
	
	Teardown();
	return true;
}

#pragma endregion
#pragma region ClearThumbnail

IMPLEMENT_SIMPLE_AUTOMATION_TEST(ClearVariantThumbnail_CallsListVariants,
    "CustomVariantManager.4Application.VariantSetDetailInteractor.ClearVariantThumbnail.CallsListVariants", DEFAULT_TEST_FLAGS)

bool ClearVariantThumbnail_CallsListVariants::RunTest(const FString& Parameters)
{
	Setup();

	EXPECT_CALL(*Mock->MockVariantManagerService, ClearVariantThumbnail)
	.Times(Exactly(1))
	.WillRepeatedly(Return(EVariantManagerServiceResult::Success));
	
	VerifyPresentListVariantsCalled(1);
	VerifyPresentErrorCalled(0);

	GeometryVariantSetDetailInteractor->ClearThumbnail(ClearThumbnail::FRequest{Mock->FindableVariantName});

	Teardown();
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(ClearVariantThumbnail_CallsPresentError_OnFailure,
    "CustomVariantManager.4Application.VariantSetDetailInteractor.ClearVariantThumbnail.CallsPresentError.OnFailure", DEFAULT_TEST_FLAGS)

bool ClearVariantThumbnail_CallsPresentError_OnFailure::RunTest(const FString& Parameters)
{
	Setup();

	EXPECT_CALL(*Mock->MockVariantManagerService, ClearVariantThumbnail)
    .Times(Exactly(1))
    .WillRepeatedly(Return(EVariantManagerServiceResult::Error));
	
	VerifyPresentListVariantsCalled(0);
	VerifyPresentErrorCalled(1);

	GeometryVariantSetDetailInteractor->ClearThumbnail(ClearThumbnail::FRequest{Mock->FindableVariantName});

	Teardown();
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(ClearVariantThumbnail_CallsPresentError_OnNoSelectedVariantSet,
    "CustomVariantManager.4Application.VariantSetDetailInteractor.ClearVariantThumbnail.CallsPresentError.OnNoSelectedVariantSet", DEFAULT_TEST_FLAGS)

bool ClearVariantThumbnail_CallsPresentError_OnNoSelectedVariantSet::RunTest(const FString& Parameters)
{
	Setup();

	EXPECT_CALL(*Mock->MockVariantManagerService, GetVariantSetByName)
	.Times(Exactly(1))
	.WillRepeatedly(Return(nullptr));
	
	EXPECT_CALL(*Mock->MockVariantManagerService, ClearVariantThumbnail)
    .Times(Exactly(0));
	
	VerifyPresentListVariantsCalled(0);
	VerifyPresentErrorCalled(1);

	GeometryVariantSetDetailInteractor->ClearThumbnail(ClearThumbnail::FRequest{Mock->FindableVariantName});
	
	Teardown();
	return true;
}

#pragma endregion 

#endif
}
