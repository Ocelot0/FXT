//=================================================
// Written by Lee Gil Su
// Copyright 2018. Lee Gil Su. all rights reserved.
//=================================================

#include "FXT.h"
#include "FXTStyle.h"
#include "FXTCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

#include "FXTCore.h"

static const FName FXTTabName("FXT");

#define LOCTEXT_NAMESPACE "FFXTModule"

void FFXTModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FFXTStyle::Initialize();
	FFXTStyle::ReloadTextures();

	FFXTCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FFXTCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FFXTModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FFXTModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		//* Toolbar button position setup
		ToolbarExtender->AddToolBarExtension(TOOLBAREXTENTIONHOOK, EExtensionHook::Before, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FFXTModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(FXTTabName, FOnSpawnTab::CreateRaw(this, &FFXTModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FFXTTabTitle", TAB_LABEL)) //* TabLabel setup
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FFXTModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FFXTStyle::Shutdown();

	FFXTCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(FXTTabName);
}

TSharedRef<SDockTab> FFXTModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		.Icon(FXTStyle::Get().GetBrush("FXT.Icon16"))	//* TabIcon setup
		[
			SNew(SFXTMain)
		];
}

void FFXTModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(FXTTabName);
}

void FFXTModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FFXTCommands::Get().OpenPluginWindow);
}

void FFXTModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FFXTCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFXTModule, FXT)