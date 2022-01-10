// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Perfect_World : ModuleRules
{
	public Perfect_World(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
