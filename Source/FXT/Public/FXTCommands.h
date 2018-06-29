//=================================================
// Written by Lee Gil Su
// Copyright 2018. Lee Gil Su. all rights reserved.
//=================================================

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "FXTStyle.h"

class FFXTCommands : public TCommands<FFXTCommands>
{
public:

	FFXTCommands()
		: TCommands<FFXTCommands>(TEXT("FXT"), NSLOCTEXT("Contexts", "FXT", "FXT Plugin"), NAME_None, FFXTStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};