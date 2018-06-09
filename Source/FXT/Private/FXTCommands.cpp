//=================================================
// Written by Lee Gil Su
// Copyright 2018. Lee Gil Su. all rights reserved.
//=================================================

#include "FXTCommands.h"
#include "FXTCore.h"

#define LOCTEXT_NAMESPACE "FFXTModule"

void FFXTCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, TOOLBARBUTTON_LABEL, TOOLBARBUTTON_TOOLTIP, EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
