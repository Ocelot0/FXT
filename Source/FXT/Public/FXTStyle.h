//=================================================
// Written by Lee Gil Su
// Copyright 2018. Lee Gil Su. all rights reserved.
//=================================================

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"

/**  */
class FFXTStyle
{
public:

	static void Initialize();

	static void Shutdown();

	/** reloads textures used by slate renderer */
	static void ReloadTextures();

	/** @return The Slate style set for the Shooter game */
	static const ISlateStyle& Get();

	static FName GetStyleSetName();

private:

	static TSharedRef< class FSlateStyleSet > Create();

private:

	static TSharedPtr< class FSlateStyleSet > StyleInstance;


	//* Style getter
public:
	static const FTextBlockStyle* GetTBStyle(FName inName) { return &Get().GetWidgetStyle<FTextBlockStyle>(inName); }

	//*Color presets
public:
	static FSlateColor Clr_Default() { return FSlateColor(FColor(255, 255, 255, 255)); }
	static FSlateColor Clr_Hidden() { return FSlateColor(FColor(96, 96, 96, 255)); }
	static FSlateColor Clr_Error() { return FSlateColor(FColor(255, 0, 0, 255)); }
	static FSlateColor Clr_Black() { return FSlateColor(FColor(0, 0, 0, 255)); }
	static FSlateColor Clr_Toggle() { return FSlateColor(FColor(255, 255, 0, 255)); }

public:
	//*Icon brush valid check
	//static FName GetIconBrushNameChecked(FName ClassFName = "Actor");
};