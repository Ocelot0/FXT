//=================================================
// Written by Lee Gil Su
// Copyright 2018. Lee Gil Su. all rights reserved.
//=================================================

#pragma once

#include "FXTStyle.h"

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "DeclarativeSyntaxSupport.h"

class FXT_API SFXTButton : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SFXTButton)
		: _bUseImage(false)
		, _Image(FEditorStyle::GetBrush("Default"))
		, _Icon()
		, _Text()
		, _TextStyle(FFXTStyle::GetTBStyle("ButtonText"))
		, _ButtonStyle(&FEditorStyle::Get().GetWidgetStyle< FButtonStyle >("FlatButton"))
		, _InitialColor(FFXTStyle::Clr_Default())
	{}

	SLATE_ARGUMENT(bool, bUseImage)
	SLATE_ARGUMENT(const FSlateBrush*, Image)

	SLATE_ATTRIBUTE(FText, Icon)
	SLATE_ATTRIBUTE(FText, Text)
	SLATE_STYLE_ARGUMENT(FTextBlockStyle, TextStyle)
	SLATE_STYLE_ARGUMENT(FButtonStyle, ButtonStyle)

	SLATE_ATTRIBUTE(FSlateColor, InitialColor)

	SLATE_EVENT(FOnClicked, OnClicked)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
};
