using UnrealBuildTool;

public class Test : ModuleRules
{
	public Test(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		bUseRTTI = true;

		PublicDependencyModuleNames.AddRange
		(
			new string[]
			{
				"Core"
			}
		);

		PrivateDependencyModuleNames.AddRange
		(
			new string[]
			{
				"Engine",
				"GoogleTest",
				"VariantManager",
				"CoreUObject",
                "Application",
                "Domain",
            }
		);
	}
}
