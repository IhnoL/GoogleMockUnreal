#pragma once

#include "CoreMinimal.h"

#include "src/gmock-all.cc"
#include "src/gtest-all.cc"

class TestHelpersFailureReporter : public testing::EmptyTestEventListener
{
	void OnTestPartResult(const testing::TestPartResult& result) override
	{
		if (result.type() == testing::TestPartResult::kFatalFailure
			|| result.type() == testing::TestPartResult::kNonFatalFailure)
		{
			const auto Message = FString(result.message());
			UE_LOG(LogTemp, Error, TEXT("%s"), *Message);
		}
	}
};