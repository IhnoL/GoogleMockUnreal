#include "ApplicationModule.h"
#include "CoreTypes.h"
#include "Misc/AutomationTest.h"
#include "MockDeclarations/GeometryInteractorMockDeclarations.h"
#include "Scenes/GeometryVariantSetDetail/IGeometryVariantSetDetailInteractor.h"

namespace GeometryVariantSetDetailInteractorTest{
#if WITH_DEV_AUTOMATION_TESTS
#define DEFAULT_TEST_FLAGS EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::EngineFilter

	using ::testing::AtLeast;
	using ::testing::Exactly;
	using ::testing::Return;
	using ::testing::ReturnNull;
	using ::testing::AtMost;

	GeometryInteractorMockDeclarations* Mock;
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

#pragma endregion
#pragma region CreateGeometryVariant

	IMPLEMENT_SIMPLE_AUTOMATION_TEST(CreateGeometryVariant_CallsCreateGeometryVariant,
	                                 "CustomVariantManager.4Application.GeometryVariantSetDetailInteractor.CreateGeometryVariant.CallsCreateGeometryVariant", DEFAULT_TEST_FLAGS)

	bool CreateGeometryVariant_CallsCreateGeometryVariant::RunTest(const FString& Parameters)
	{
		Setup();

		EXPECT_CALL(*Mock->MockTagManagerService, GetAllGeometryTagsInEditorWorld)
		.Times(Exactly(1))
        .WillRepeatedly(Return(Mock->DefaultTags));

		EXPECT_CALL(*Mock->MockVariantManagerService, CreateGeometryVariant(Mock->DefaultVariantSet, Mock->FindableTag))
		.Times(Exactly(1))
		.WillRepeatedly(Return(Mock->DefaultVariantWithName));

		VerifyPresentListVariantsCalled(1);
		VerifyPresentErrorCalled(0);

		GeometryVariantSetDetailInteractor->CreateGeometryVariant(CreateGeometryVariant::FRequest{Mock->FindableTag});

		Teardown();
		return true;
	}

	IMPLEMENT_SIMPLE_AUTOMATION_TEST(CreateGeometryVariant_CallsPresentError_OnWrongTag,
	                                 "CustomVariantManager.4Application.GeometryVariantSetDetailInteractor.CreateGeometryVariant.CallsPresentError_OnWrongTag", DEFAULT_TEST_FLAGS)

	bool CreateGeometryVariant_CallsPresentError_OnWrongTag::RunTest(const FString& Parameters)
	{
		Setup();

		EXPECT_CALL(*Mock->MockTagManagerService, GetAllGeometryTagsInEditorWorld)
		.Times(Exactly(1))
        .WillRepeatedly(Return(Mock->DefaultTags));

		EXPECT_CALL(*Mock->MockVariantManagerService, CreateGeometryVariant(Mock->DefaultVariantSet, Mock->FindableTag))
        .Times(Exactly(0));

		VerifyPresentListVariantsCalled(0);
		VerifyPresentErrorCalled(1);

		GeometryVariantSetDetailInteractor->CreateGeometryVariant(CreateGeometryVariant::FRequest{"AnotherTag"});

		Teardown();
		return true;
	}

	IMPLEMENT_SIMPLE_AUTOMATION_TEST(CreateGeometryVariant_CallsPresentError_OnFailure,
	                                 "CustomVariantManager.4Application.GeometryVariantSetDetailInteractor.CreateGeometryVariant.CallsPresentError_OnFailure", DEFAULT_TEST_FLAGS)

	bool CreateGeometryVariant_CallsPresentError_OnFailure::RunTest(const FString& Parameters)
	{
		Setup();

		EXPECT_CALL(*Mock->MockTagManagerService, GetAllGeometryTagsInEditorWorld)
        .Times(Exactly(1))
        .WillRepeatedly(Return(Mock->DefaultTags));

		EXPECT_CALL(*Mock->MockVariantManagerService, CreateGeometryVariant(Mock->DefaultVariantSet, Mock->FindableTag))
        .Times(Exactly(1))
		.WillRepeatedly(ReturnNull());

		VerifyPresentErrorCalled(1);
		VerifyPresentListVariantsCalled(0);

		GeometryVariantSetDetailInteractor->CreateGeometryVariant(CreateGeometryVariant::FRequest{Mock->FindableTag});

		Teardown();
		return true;
	}

	IMPLEMENT_SIMPLE_AUTOMATION_TEST(CreateGeometryVariant_CallsPresentError_OnVariantAlreadyExist,
	                                 "CustomVariantManager.4Application.GeometryVariantSetDetailInteractor.CreateGeometryVariant.CallsPresentError_OnVariantAlreadyExist", DEFAULT_TEST_FLAGS)

	bool CreateGeometryVariant_CallsPresentError_OnVariantAlreadyExist::RunTest(const FString& Parameters)
	{
		Setup();

		EXPECT_CALL(*Mock->MockGeometryVariantSet, GetVariants)
		.WillRepeatedly(Return(Mock->DefaultVariants));

		EXPECT_CALL(*Mock->MockVariantManagerService, GetVariantSetByName)
		.WillRepeatedly(Return(Mock->MockGeometryVariantSet));

		EXPECT_CALL(*Mock->DefaultVariantWithTag, GetTag)
		.Times(Exactly(1))
		.WillRepeatedly(Return(*Mock->FindableTag));

		EXPECT_CALL(*Mock->MockTagManagerService, GetAllGeometryTagsInEditorWorld)
		.Times(Exactly(1))
		.WillRepeatedly(Return(Mock->DefaultTags));

		EXPECT_CALL(*Mock->MockVariantManagerService, CreateGeometryVariant)
		.Times(Exactly(0));

		VerifyPresentErrorCalled(1);
		VerifyPresentListVariantsCalled(0);

		GeometryVariantSetDetailInteractor->CreateGeometryVariant(CreateGeometryVariant::FRequest{Mock->FindableTag});

		Teardown();
		return true;
	}

#pragma region CreateGeometryAllOffVariant


	IMPLEMENT_SIMPLE_AUTOMATION_TEST(CreateGeometryAllOffVariant_CallsCreateGeometryAllOffVariant,
	                                 "CustomVariantManager.4Application.GeometryVariantSetDetailInteractor.CreateGeometryAllOffVariant.CallsCreateGeometryAllOffVariant", DEFAULT_TEST_FLAGS)

	bool CreateGeometryAllOffVariant_CallsCreateGeometryAllOffVariant::RunTest(const FString& Parameters)
	{
		Setup();

		EXPECT_CALL(*Mock->MockVariantManagerService, CreateGeometryAllOffVariant(Mock->DefaultVariantSet))
		.Times(Exactly(1))
		.WillRepeatedly(Return(Mock->DefaultVariantWithName));

		EXPECT_CALL(*Mock->MockVariantManagerService, ActivateVariant(Mock->DefaultVariantSet, Mock->DefaultVariantWithName))
		.Times(Exactly(1))
		.WillRepeatedly(Return(EVariantManagerServiceResult::Success));

		EXPECT_CALL(*Mock->MockVariantManagerService, RefreshVariantThumbnailFromEditorViewPort(Mock->DefaultVariantSet, Mock->DefaultVariantWithName))
			.Times(Exactly(1))
			.WillRepeatedly(Return(EVariantManagerServiceResult::Success));

		VerifyPresentErrorCalled(0);
		VerifyPresentListVariantsCalled(1);

		GeometryVariantSetDetailInteractor->CreateGeometryAllOffVariant();

		Teardown();
		return true;
	}

	IMPLEMENT_SIMPLE_AUTOMATION_TEST(CreateGeometryAllOffVariant_CallsPresentError_CreationFailed,
	                                 "CustomVariantManager.4Application.GeometryVariantSetDetailInteractor.CreateGeometryAllOffVariant.CallsPresentError_CreationFailed", DEFAULT_TEST_FLAGS)

	bool CreateGeometryAllOffVariant_CallsPresentError_CreationFailed::RunTest(const FString& Parameters)
	{
		Setup();

		EXPECT_CALL(*Mock->MockVariantManagerService, CreateGeometryAllOffVariant(Mock->DefaultVariantSet))
		.Times(Exactly(1))
		.WillRepeatedly(Return(nullptr));

		EXPECT_CALL(*Mock->MockVariantManagerService, ActivateVariant(Mock->DefaultVariantSet, Mock->DefaultVariantWithName))
		.Times(Exactly(0));

		EXPECT_CALL(*Mock->MockVariantManagerService, RefreshVariantThumbnailFromEditorViewPort(Mock->DefaultVariantSet, Mock->DefaultVariantWithName))
			.Times(Exactly(0));

		VerifyPresentErrorCalled(1);
		VerifyPresentListVariantsCalled(0);

		GeometryVariantSetDetailInteractor->CreateGeometryAllOffVariant();

		Teardown();
		return true;
	}

	IMPLEMENT_SIMPLE_AUTOMATION_TEST(CreateGeometryAllOffVariant_CallsPresentError_CouldNotCreateAllOffVariant,
	                                 "CustomVariantManager.4Application.GeometryVariantSetDetailInteractor.CreateGeometryAllOffVariant.CallsPresentError_CouldNotCreateAllOffVariant",
	                                 DEFAULT_TEST_FLAGS)

	bool CreateGeometryAllOffVariant_CallsPresentError_CouldNotCreateAllOffVariant::RunTest(const FString& Parameters)
	{
		Setup();

		EXPECT_CALL(*Mock->MockVariantManagerService, GetVariantSetByName)
		.Times(Exactly(1))
		.WillRepeatedly(Return(nullptr));

		EXPECT_CALL(*Mock->MockVariantManagerService, CreateGeometryAllOffVariant(Mock->DefaultVariantSet))
		.Times(Exactly(0));

		EXPECT_CALL(*Mock->MockVariantManagerService, ActivateVariant(Mock->DefaultVariantSet, Mock->DefaultVariantWithName))
		.Times(Exactly(0));

		EXPECT_CALL(*Mock->MockVariantManagerService, RefreshVariantThumbnailFromEditorViewPort(Mock->DefaultVariantSet, Mock->DefaultVariantWithName))
			.Times(Exactly(0));

		VerifyPresentErrorCalled(1);
		VerifyPresentListVariantsCalled(0);

		GeometryVariantSetDetailInteractor->CreateGeometryAllOffVariant();

		Teardown();
		return true;
	}


	IMPLEMENT_SIMPLE_AUTOMATION_TEST(CanCreateGeometryAllOffVariant__OnValidSet_ReturnsTrue,
	                                 "CustomVariantManager.4Application.GeometryVariantSetDetailInteractor.CanCreateGeometryAllOffVariant.OnValidSet_ReturnTrue", DEFAULT_TEST_FLAGS)

	bool CanCreateGeometryAllOffVariant__OnValidSet_ReturnsTrue::RunTest(const FString& Parameters)
	{
		Setup();

		EXPECT_CALL(*Mock->MockVariantManagerService, GetVariantSetByName)
		.Times(Exactly(1))
		.WillRepeatedly(Return(Mock->DefaultVariantSet));

		EXPECT_CALL(*Mock->MockVariantManagerService, GetAllGeometryVariants)
		.Times(Exactly(1))
		.WillRepeatedly(Return(Mock->DefaultGeometryVariants));

		const bool bResult = GeometryVariantSetDetailInteractor->CanCreateGeometryAllOffVariant();
		TestTrue("CanCreateGeometryAllOffVariant must return true", bResult);

		Teardown();
		return true;
	}

	IMPLEMENT_SIMPLE_AUTOMATION_TEST(CanCreateGeometryAllOffVariant_OnInvalidSet_ReturnFalse,
	                                 "CustomVariantManager.4Application.GeometryVariantSetDetailInteractor.CanCreateGeometryAllOffVariant.OnInvalidSet_ReturnFalse", DEFAULT_TEST_FLAGS)

	bool CanCreateGeometryAllOffVariant_OnInvalidSet_ReturnFalse::RunTest(const FString& Parameters)
	{
		Setup();

		EXPECT_CALL(*Mock->MockVariantManagerService, GetVariantSetByName)
		.Times(Exactly(1))
		.WillRepeatedly(Return(nullptr));

		EXPECT_CALL(*Mock->MockVariantManagerService, GetAllGeometryVariants)
		.Times(Exactly(0));

		const bool bResult = GeometryVariantSetDetailInteractor->CanCreateGeometryAllOffVariant();
		TestFalse("CanCreateGeometryAllOffVariant must return true false", bResult);

		Teardown();
		return true;
	}

#pragma endregion

#pragma endregion
#pragma region ListVariants

	IMPLEMENT_SIMPLE_AUTOMATION_TEST(ListVariants_CallsPresentListVariants,
	                                 "CustomVariantManager.4Application.GeometryVariantSetDetailInteractor.ListVariants.CallsPresentListVariants", DEFAULT_TEST_FLAGS)

	bool ListVariants_CallsPresentListVariants::RunTest(const FString& Parameters)
	{
		Setup();

		EXPECT_CALL(*Mock->MockVariantManagerService, GetAllGeometryVariants(Mock->DefaultVariantSet))
        .Times(Exactly(1))
        .WillRepeatedly(Return(Mock->DefaultGeometryVariants));

		VerifyPresentErrorCalled(0);
		VerifyPresentListVariantsCalled(1);

		GeometryVariantSetDetailInteractor->ListVariants();

		Teardown();
		return true;
	}

	IMPLEMENT_SIMPLE_AUTOMATION_TEST(ListVariants_CallsPresentError_OnNoSelectedVariantSet,
	                                 "CustomVariantManager.4Application.GeometryVariantSetDetailInteractor.ListVariants.CallsPresentError_OnNoSelectedVariantSet", DEFAULT_TEST_FLAGS)

	bool ListVariants_CallsPresentError_OnNoSelectedVariantSet::RunTest(const FString& Parameters)
	{
		Setup();

		EXPECT_CALL(*Mock->MockVariantManagerService, GetVariantSetByName)
        .Times(Exactly(1))
        .WillRepeatedly(nullptr);

		VerifyPresentErrorCalled(1);
		VerifyPresentListVariantsCalled(0);

		GeometryVariantSetDetailInteractor->ListVariants();

		Teardown();
		return true;
	}

#pragma endregion
#pragma region ListTags

	IMPLEMENT_SIMPLE_AUTOMATION_TEST(ListTags_CallsPresentListTags,
	                                 "CustomVariantManager.4Application.GeometryVariantSetDetailInteractor.ListTags.CallsPresentListTags", DEFAULT_TEST_FLAGS)

	bool ListTags_CallsPresentListTags::RunTest(const FString& Parameters)
	{
		Setup();

		EXPECT_CALL(*Mock->MockTagManagerService, GetAllGeometryTagsInEditorWorld)
        .Times(Exactly(1))
        .WillRepeatedly(Return(Mock->DefaultTags));

		EXPECT_CALL(*Mock->MockPresenter, PresentListTags)
        .Times(Exactly(1));

		VerifyPresentErrorCalled(0);

		GeometryVariantSetDetailInteractor->ListTags();

		Teardown();
		return true;
	}


#endif
}
