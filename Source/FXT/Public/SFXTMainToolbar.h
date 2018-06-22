//=================================================
// Written by Lee Gil Su
// Copyright 2018. Lee Gil Su. all rights reserved.
//=================================================
#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "DeclarativeSyntaxSupport.h"

class FXT_API SFXTMainToolbar : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SFXTMainToolbar)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, const TSharedRef<SFXTMain>& InOwner);

	TWeakPtr<SFXTMain> OwnerPtr;


public:
	//*Button Color Attr
	TAttribute<FSlateColor> Clr_byToolType(EFXTToolType CompareType);

	//*Button Border Attr
	TAttribute<const FSlateBrush*> Border_byToolType(EFXTToolType CompareType);

	//*Parenting Tool
	FReply BTN_Parent();

	//*INFO
	FReply BTN_Info();

};
