#pragma once
#include "gtest/gtest-matchers.h"

using ::testing::MakeMatcher;
using ::testing::Matcher;
using ::testing::MatcherInterface;
using ::testing::MatchResultListener;

class TestUtils
{
	template <class ArrayContentType>
	class SameSizeMatcher : public MatcherInterface<const TArray<ArrayContentType>&>
	{
	public:
		int32 Size = 0;

		SameSizeMatcher(int32 InSize)
		{
			Size = InSize;
		}

		virtual bool MatchAndExplain(const TArray<ArrayContentType>& x, MatchResultListener* listener) const
		{
			return x.Num() == Size;
		}

		virtual void DescribeTo(::std::ostream* os) const { *os << "array should be of same size"; };
	};

public:
	template <class ArrayContentType>
	static Matcher<const TArray<ArrayContentType>&> ArraysHaveWantedSize(int32 WantedSize)
	{
		return MakeMatcher(new SameSizeMatcher<ArrayContentType>(WantedSize));
	}
};
