//=================================================
// Written by Lee Gil Su
// Copyright 2018. Lee Gil Su. all rights reserved.
//=================================================

#pragma once

#include "FXTStyle.h"
#include "EditorFontGlyphs.h"

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "DeclarativeSyntaxSupport.h"

DECLARE_DELEGATE_RetVal_OneParam(FReply, FRowBTNOnClicked, const TSharedRef<class SRowButton>&)

class FXT_API SRowButton : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SRowButton)
		: _bUseImage(false)
		, _Image(FEditorStyle::GetBrush("Default"))
		, _Icon(FEditorFontGlyphs::Check_Circle)
		, _RowLabel()
		, _TooltipText()
		, _InitialToggleState(false)
		, _InitialColor(FFXTStyle::Clr_Default())
		, _IconStyle(FFXTStyle::GetTBStyle("ListViewText.RowButton"))
	{}

	SLATE_ARGUMENT(bool, bUseImage)
	SLATE_ARGUMENT(const FSlateBrush*, Image)

	SLATE_ATTRIBUTE(FText, Icon)
	SLATE_STYLE_ARGUMENT(FTextBlockStyle, IconStyle)
	SLATE_ARGUMENT(FText, TooltipText)

	SLATE_ARGUMENT(bool, InitialToggleState)
	SLATE_ARGUMENT(FSlateColor, InitialColor)

	SLATE_ARGUMENT(FString, RowLabel)

	SLATE_EVENT(FRowBTNOnClicked, OnClicked)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	//*Button
private:
	FRowBTNOnClicked RowBTNOnClicked;
	FReply OnClicked();

	bool bToggleState = false;
public:
	FORCEINLINE bool GetToggleState() { return bToggleState; }

	//*RowLabel
private:
	FString RowLabel;
public:
	FORCEINLINE const FString& GetRowLabel() { return RowLabel; }

	//*Icon
private:
	FText Icon;
	FSlateColor IconColor = FSlateColor(FColor(255, 255, 255, 255));

public:
	void SetIcon(FText inIcon);
	void SetIconColor(FSlateColor NewIconColor) { IconColor = NewIconColor; }

};
