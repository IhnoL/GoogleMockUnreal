#pragma once

#include "gmock/gmock.h"
#include "Scenes/GeometryVariantSetDetail/IGeometryVariantSetDetailPresenter.h"

class MockIVariantSetDetailPresenter : public IVariantSetDetailPresenter
{
public:
	MOCK_METHOD(void, PresentError, (const ShowError::FResponse& Response), (override));
};
