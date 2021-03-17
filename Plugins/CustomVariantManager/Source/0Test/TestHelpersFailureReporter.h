#pragma once

#include "CoreMinimal.h"

#include "src/gmock-all.cc"
#include "src/gtest-all.cc"

class TestHelpersFailureReporter : public testing::internal::FailureReporterInterface {
public:
	void ReportFailure(FailureType type, const char* file, int line,
                       const std::string& message) override {		

		const auto Message = FString(message.c_str());
		UE_LOG(LogTemp, Error, TEXT("%s"), *Message);
	}
};