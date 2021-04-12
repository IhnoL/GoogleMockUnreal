# GoogleMockUnreal

This repository contains a minimum working example for using Unreal Automation Tests together with GoogleMock from the GoogleTest-Framework.
The underlying plugin is only a snippet of a bigger project, extending the Unreal-Engine VariantManager. Inside of the project a Clean-Architecture in combination with Dependency Injection and VIP-cycles is used.

All interesting source code is inside of the two plugins: CustomVariantManager + GoogleTest (GoogleMockUnreal -> Plugins)

The included tests can be executed by opening the GoogleMockUnreal.uproject (alternative: building from source) and then inside of the Unreal Editor: 
Window -> TestAutomation -> CustomVariantManager

To package a project, change the Test-Modules type from "Editor" to "Program". This will prevent the module from being build.

## Article:
https://www.maibornwolff.de/en/blog/how-we-create-real-unittests-unreal-engine-googlemock