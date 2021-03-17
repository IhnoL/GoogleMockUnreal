// Copyright 2020-present Nans Pellicari (nans.pellicari@gmail.com).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

using UnrealBuildTool;
using System.IO;

namespace UnrealBuildTool.Rules
{

    public class GoogleTest : ModuleRules
    {
        public GoogleTest(ReadOnlyTargetRules Target) : base(Target)
        {
            Type = ModuleType.External;

            UnsafeTypeCastWarningLevel = WarningLevel.Off;

            string googleTestBasePath = Path.Combine(ModuleDirectory, "googletest-release-1.10.0");

            PublicSystemIncludePaths.Add(Path.Combine(googleTestBasePath, "googlemock"));
            PublicSystemIncludePaths.Add(Path.Combine(googleTestBasePath, "googlemock", "include"));
            PublicSystemIncludePaths.Add(Path.Combine(googleTestBasePath, "googletest"));
            PublicSystemIncludePaths.Add(Path.Combine(googleTestBasePath, "googletest", "include"));

            PublicDefinitions.Add("GTEST_OS_WINDOWS=1");
            PublicDefinitions.Add("GTEST_OS_WINDOWS_MOBILE=0");
            PublicDefinitions.Add("GTEST_OS_LINUX_ANDROID=0");
            PublicDefinitions.Add("GTEST_OS_LINUX=0");
            PublicDefinitions.Add("GTEST_OS_MAC=0");
            PublicDefinitions.Add("GTEST_OS_HPUX=0");
            PublicDefinitions.Add("GTEST_OS_QNX=0");
            PublicDefinitions.Add("GTEST_OS_FREEBSD=0");
            PublicDefinitions.Add("GTEST_OS_NACL=0");
            PublicDefinitions.Add("GTEST_OS_NETBSD=0");
            PublicDefinitions.Add("GTEST_OS_FUCHSIA=0");
            PublicDefinitions.Add("GTEST_OS_LINUX_ANDROID=0");
            PublicDefinitions.Add("GTEST_OS_SYMBIAN=0");
            PublicDefinitions.Add("GTEST_OS_WINDOWS_MINGW=0");
            PublicDefinitions.Add("GTEST_OS_WINDOWS_PHONE=0");
            PublicDefinitions.Add("GTEST_OS_WINDOWS_RT=0");
            PublicDefinitions.Add("GTEST_OS_CYGWIN=0");
            PublicDefinitions.Add("GTEST_OS_SOLARIS=0");
            PublicDefinitions.Add("GTEST_OS_WINDOWS_TV_TITLE=0");
            PublicDefinitions.Add("GTEST_OS_IOS=0");
            PublicDefinitions.Add("GTEST_OS_AIX=0");
            PublicDefinitions.Add("GTEST_OS_ZOS=0");

            PublicDefinitions.Add("GTEST_DONT_DEFINE_FAIL=0");
            PublicDefinitions.Add("GTEST_DONT_DEFINE_SUCCEED=0");
            PublicDefinitions.Add("GTEST_DONT_DEFINE_ASSERT_EQ=0");
            PublicDefinitions.Add("GTEST_DONT_DEFINE_ASSERT_NE=0");
            PublicDefinitions.Add("GTEST_DONT_DEFINE_ASSERT_LE=0");
            PublicDefinitions.Add("GTEST_DONT_DEFINE_ASSERT_LT=0");
            PublicDefinitions.Add("GTEST_DONT_DEFINE_ASSERT_GE=0");
            PublicDefinitions.Add("GTEST_DONT_DEFINE_ASSERT_GT=0");
            PublicDefinitions.Add("GTEST_DONT_DEFINE_TEST=0");

            PublicDefinitions.Add("GTEST_HAS_DOWNCAST_=0");
            PublicDefinitions.Add("GTEST_HAS_MUTEX_AND_THREAD_LOCAL_=0");
            PublicDefinitions.Add("GTEST_HAS_NOTIFICATION_=0");
            PublicDefinitions.Add("GTEST_HAS_ABSL=0");
            PublicDefinitions.Add("GTEST_HAS_GETTIMEOFDAY_=0");

            PublicDefinitions.Add("__GXX_EXPERIMENTAL_CXX0X__=0");
            PublicDefinitions.Add("GTEST_USES_PCRE=0");
            PublicDefinitions.Add("GTEST_USES_POSIX_RE=0");
            PublicDefinitions.Add("GTEST_ENV_HAS_TR1_TUPLE_=0");
            PublicDefinitions.Add("GTEST_LINKED_AS_SHARED_LIBRARY=0");
            PublicDefinitions.Add("GTEST_CREATE_SHARED_LIBRARY=0");
            PublicDefinitions.Add("GTEST_CAN_STREAM_RESULTS_=0");
            PublicDefinitions.Add("GTEST_FOR_GOOGLE_=0");
            PublicDefinitions.Add("GTEST_GCC_VER_=0");

            
            PublicDefinitions.Add("GTEST_INTERNAL_HAS_STRING_VIEW=0");
            PublicDefinitions.Add("GTEST_OS_DRAGONFLY=0");
            PublicDefinitions.Add("GTEST_OS_GNU_KFREEBSD=0");
            PublicDefinitions.Add("GTEST_OS_OPENBSD=0");
            PublicDefinitions.Add("GTEST_OS_HAIKU=0");
            PublicDefinitions.Add("GTEST_OS_ESP8266=0");
            PublicDefinitions.Add("GTEST_OS_ESP32=0");


            PublicDefinitions.Add("WIN32_LEAN_AND_MEAN=1");
            
            PublicDefinitions.Add("GTEST_ENABLE_CATCH_EXCEPTIONS_=1");
        }
    }
}