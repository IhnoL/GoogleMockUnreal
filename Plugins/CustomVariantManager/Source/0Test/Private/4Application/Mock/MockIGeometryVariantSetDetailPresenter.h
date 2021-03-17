#pragma once

#include "gmock/gmock.h"
#include "Scenes/GeometryVariantSetDetail/IGeometryVariantSetDetailPresenter.h"

class MockIGeometryVariantSetDetailPresenter : public IGeometryVariantSetDetailPresenter
{
public:
	MOCK_METHOD(void, PresentListGeometryVariants, (const ListGeometryVariants::FResponse& Response), (override));
	MOCK_METHOD(void, PresentListTags, (const ListTags::FResponse& Response), (override));
	MOCK_METHOD(void, PresentError, (const ShowError::FResponse& Response), (override));
};
