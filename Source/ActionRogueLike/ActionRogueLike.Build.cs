// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ActionRogueLike : ModuleRules
{
	public ActionRogueLike(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "AIModule", "GameplayTasks", "UMG" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new string[]
		{
			"ActionRogueLike/Public/AI",
			"ActionRogueLike/Public/AI/Tasks",
			"ActionRogueLike/Public/AI/Services",
			// "ActionRogueLike/Public/Base",
			// "ActionRogueLike/Public/Base/Actors",
			// "ActionRogueLike/Public/Base/Components",
			// "ActionRogueLike/Public/Base/Effects",
			// "ActionRogueLike/Public/Base/Items",
			"ActionRogueLike/Public/Components",
			// "ActionRogueLike/Public/Components/PlayerController",
			// "ActionRogueLike/Public/Components/PlayerCharacter",
			// "ActionRogueLike/Public/Components/Weapon",
			"ActionRogueLike/Public/Core",
			// "ActionRogueLike/Public/Effects",
			// "ActionRogueLike/Public/Effects/Buffs",
			// "ActionRogueLike/Public/Effects/Debuffs",
			"ActionRogueLike/Public/Env",
			"ActionRogueLike/Public/Input",
			"ActionRogueLike/Public/Interfaces",
			// "ActionRogueLike/Public/Items",
			// "ActionRogueLike/Public/Items/Pickups",
			"ActionRogueLike/Public/Libraries",
			"ActionRogueLike/Public/Misc",
			"ActionRogueLike/Public/Player",
			"ActionRogueLike/Public/Projectiles",
			"ActionRogueLike/Public/UI",
			// "ActionRogueLike/Public/UI/Objects",
			// "ActionRogueLike/Public/Weapons"
		});
		
		
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
