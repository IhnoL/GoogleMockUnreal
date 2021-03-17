#pragma once

#include "4Application/Mock/MockIGeometryVariantSetDatastore.h"
#include "4Application/Mock/MockIGeometryVariantSetDetailPresenter.h"
#include "4Application/Mock/MockIVariantManagerService.h"
#include "5Domain/Mock/MockICustomGeometryVariant.h"
#include "5Domain/Mock/MockICustomGeometryVariantSet.h"
#include "Services/IVariantManagerService.h"
#include "4Application/Mock/MockITagManagerService.h"

class MockIGeometryVariantSetDatastore;
using ::testing::AtLeast;
using ::testing::Exactly;
using ::testing::Return;
using ::testing::AtMost;

class GeometryInteractorMockDeclarations
{
public:
	TSharedPtr<MockIVariantManagerService> MockVariantManagerService;
	TSharedPtr<MockIGeometryVariantSetDatastore> MockDatastore;
	TSharedPtr<MockIGeometryVariantSetDetailPresenter> MockPresenter;
	TSharedPtr<MockITagManagerService> MockTagManagerService;

	TArray<ICustomVariant*> DefaultVariants;
	TArray<ICustomGeometryVariant*> DefaultGeometryVariants;
	ICustomGeometryVariantSet* DefaultVariantSet;
	MockICustomGeometryVariantSet* MockGeometryVariantSet; 
	MockICustomGeometryVariant* DefaultVariantWithName;
	MockICustomGeometryVariant* DefaultVariantWithTag;

	FString FindableVariantName;
	FString FindableVariantSetName;
	FString FindableTag;
	TArray<FString> DefaultTags;

	GeometryInteractorMockDeclarations()
	{
		FindableVariantName = FString("FindableVariantName");
		FindableVariantSetName = FString("FindableVariantSetName");
		FindableTag = FString("FindableTag");
		DefaultTags = {FindableTag, FString("Tag_0"), FString("Tag_1"), FString("Tag_2"), FString("Tag_3")};

		Setup();
	}

	~GeometryInteractorMockDeclarations()
	{
		Teardown();
	}
	
	/**
	* Create Mocks and Defaults
	* Should be called at beginning of each test
	*/
	void Setup()
	{
		MockGeometryVariantSet = new MockICustomGeometryVariantSet();
		DefaultVariantSet = new MockICustomGeometryVariantSet();
		SetupMockGeometryVariants();

		SetupMockTagManagerService();
		SetupMockVariantManagerService();
		SetupMockDatastore();
		SetupMockPresenter();
	}
	
	/**
	* Destroy Mocks and evaluate EXPECTS
	* Should be called at end of each test, to prevent leaks and to verify that all constraints are fulfilled
	*  - in destructor phase of MOCKS the constraints are evaluated -
	*/
	void Teardown()
	{
		MockVariantManagerService.Reset();
		MockDatastore.Reset();
		MockPresenter.Reset();
		MockTagManagerService.Reset();

		FApplicationModule::Get().Container.Unregister<IVariantManagerService>();
		FApplicationModule::Get().Container.Unregister<IGeometryVariantSetDatastore>();
		FApplicationModule::Get().Container.Unregister<IGeometryVariantSetDetailPresenter>();
		FApplicationModule::Get().Container.Unregister<ITagManagerService>();

		delete MockGeometryVariantSet;
		delete DefaultVariantWithTag;
		delete DefaultVariantSet;
		for (auto DefaultVariant : DefaultGeometryVariants)
		{
			delete DefaultVariant;
		}
		DefaultGeometryVariants.Empty(DefaultGeometryVariants.Num());
	}

	void SetupMockTagManagerService()
	{
		MockTagManagerService = MakeShared<MockITagManagerService>();
		FApplicationModule::Get().Container.RegisterInstance<ITagManagerService>(MockTagManagerService.ToSharedRef());

		EXPECT_CALL(*MockTagManagerService, GetAllGeometryTagsInEditorWorld)
        .WillRepeatedly(Return(DefaultTags));
	}

	void SetupMockVariantManagerService()
	{
		MockVariantManagerService = MakeShared<MockIVariantManagerService>();
		FApplicationModule::Get().Container.RegisterInstance<IVariantManagerService>(MockVariantManagerService.ToSharedRef());

		EXPECT_CALL(*MockVariantManagerService, GetVariantSetByName)
        .WillRepeatedly(Return(DefaultVariantSet));

		EXPECT_CALL(*MockVariantManagerService, GetAllGeometryVariants)
         .WillRepeatedly(Return(DefaultGeometryVariants));

		EXPECT_CALL(*MockVariantManagerService, FetchVariantByName(DefaultVariantSet, FindableVariantName))
         .WillRepeatedly(Return(DefaultVariantWithName));
	}

	void SetupMockPresenter()
	{
		MockPresenter = MakeShared<MockIGeometryVariantSetDetailPresenter>();
		FApplicationModule::Get().Container.RegisterInstance<IGeometryVariantSetDetailPresenter>(MockPresenter.ToSharedRef());

		EXPECT_CALL(*MockPresenter, PresentError)
        .Times(Exactly(0));
	}

	void SetupMockDatastore()
	{
		MockDatastore = MakeShared<MockIGeometryVariantSetDatastore>();
		FApplicationModule::Get().Container.RegisterInstance<IGeometryVariantSetDatastore>(MockDatastore.ToSharedRef());

		EXPECT_CALL(*MockDatastore, GetSelectedVariantSetName)
        .WillRepeatedly(Return(FString("")));

		EXPECT_CALL(*MockDatastore, GetSelectedVariantSetName)
        .WillRepeatedly(Return(FindableVariantSetName));
	}
	
	void SetupMockGeometryVariants()
	{
		DefaultVariantWithName = new MockICustomGeometryVariant();
		EXPECT_CALL(*DefaultVariantWithName, GetName)
        .WillRepeatedly(Return(FindableVariantName));
		DefaultGeometryVariants.Add(DefaultVariantWithName);

		for (int i = 0; i < 5; i++)
		{
			MockICustomGeometryVariant* RandomMockVariant = new MockICustomGeometryVariant();
			EXPECT_CALL(*RandomMockVariant, GetName)
            .WillRepeatedly(Return(FString("VariantName_" + i)));
			DefaultGeometryVariants.Add(RandomMockVariant);
		}

		DefaultVariantWithTag = new MockICustomGeometryVariant();
		EXPECT_CALL(*DefaultVariantWithTag, GetTag)
		.WillRepeatedly(Return(FindableTag));
		DefaultVariants.Add(DefaultVariantWithTag);
	}
};
