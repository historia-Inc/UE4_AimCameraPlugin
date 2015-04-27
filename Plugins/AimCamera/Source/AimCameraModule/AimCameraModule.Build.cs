// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class AimCameraModule : ModuleRules
	{
		public AimCameraModule(TargetInfo Target)
		{
			DynamicallyLoadedModuleNames.AddRange(
				new string[] {
				}
				);

			PublicIncludePaths.AddRange(
				new string[] {
					"AimCamera/Public",
				}
				);

			PrivateIncludePaths.AddRange(
				new string[] {
					"AimCamera/Private",
				}
				);

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
					"Engine",
				}
				);
			if (UEBuildConfiguration.bBuildEditor == true)
			{
				PublicDependencyModuleNames.Add("UnrealEd");
			}

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
				}
				);

			DynamicallyLoadedModuleNames.AddRange(
				new string[]
				{
				}
				);
		}
	}
}