//=================================================
// Written by Lee Gil Su
// Copyright 2018. Lee Gil Su. all rights reserved.
//=================================================

#pragma once

#include "CoreMinimal.h"
#include "ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FFXTModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();
	
private:

	void AddToolbarExtension(FToolBarBuilder& Builder);
	void AddMenuExtension(FMenuBuilder& Builder);

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

private:
	TSharedPtr<class FUICommandList> PluginCommands;
};