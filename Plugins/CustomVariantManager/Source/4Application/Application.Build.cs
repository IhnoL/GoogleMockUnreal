using System.IO;
using UnrealBuildTool;
 
public class Application : ModuleRules
{
	public Application(ReadOnlyTargetRules Target) : base(Target)
	{
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bUseRTTI = true;

        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Private/"));

        PublicDependencyModuleNames.AddRange
        (
	        new string[]
	        {
		        "Core",
	        }
        );

        PrivateDependencyModuleNames.AddRange
        (
	        new string[]
	        {
		        "Domain",
	        }
        );
        
        if (Target.bBuildDeveloperTools)
        {
	        PublicDefinitions.Add("WITH_GOOGLE_TEST=1");
	        PrivateDependencyModuleNames.AddRange
	        (
		        new string[]
		        {
			        "GoogleTest",
		        }
	        );
        }
	}
}