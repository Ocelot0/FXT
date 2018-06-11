//=================================================
// Written by Lee Gil Su
// Copyright 2018. Lee Gil Su. all rights reserved.
//=================================================

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "DeclarativeSyntaxSupport.h"

enum class EFXTToolType;

class FXT_API SFXTMain : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SFXTMain)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

public:
	FString DebugStr = "Main widget";

private:
	//*Tool
	EFXTToolType CurrentTool;
public:
	EFXTToolType GetCurrentTool() { return CurrentTool; }
	void SetCurrentTool(EFXTToolType NewToolType);
	TAttribute<EVisibility> Vis_byToolType(EFXTToolType CompareType);

};
