#pragma once

namespace ShowError
{
struct FResponse
{
	FString Message;
};
}

namespace ListTags
{
struct FResponse
{
	TArray<FString> Tags;
};
}

class IVariantSetDetailPresenter
{
public:
	virtual void PresentError(const ShowError::FResponse& Response) = 0;
};
