using UnrealBuildTool;
 
public class Domain : ModuleRules
{
    public Domain(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bUseRTTI = true;

        PublicDependencyModuleNames.AddRange
        (
            new string[]
            {
                "Core",
            }
        );
    }
}