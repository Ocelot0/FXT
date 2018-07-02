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

#include "SListView.h"
#include "STableRow.h"
#include "STextComboBox.h" //Menu anchor

DECLARE_DELEGATE_RetVal_OneParam(FReply, FRowCBTNOnClicked, const TSharedRef<class SRowComboButton>&)
DECLARE_DELEGATE_TwoParams(FRowOnUpdateSource, TArray<TSharedPtr<FString>>&, const TSharedRef<class SRowComboButton>&)
DECLARE_DELEGATE_OneParam(FRowOnItemSelect, FString&)

class FXT_API SRowComboButton : public SMenuAnchor
{
public:
	SLATE_BEGIN_ARGS(SRowComboButton)
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
	SLATE_ARGUMENT(float, ImageSize)

	SLATE_ATTRIBUTE(FText, Icon)
	SLATE_STYLE_ARGUMENT(FTextBlockStyle, IconStyle)
	SLATE_ARGUMENT(FText, TooltipText)

	SLATE_ARGUMENT(bool, InitialToggleState)
	SLATE_ARGUMENT(FSlateColor, InitialColor)

	SLATE_ARGUMENT(FString, RowLabel)

	SLATE_EVENT(FRowCBTNOnClicked, OnClicked)
	SLATE_EVENT(FRowOnUpdateSource, OnUpdateSource)
	SLATE_EVENT(FRowOnItemSelect, OnItemSelect)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	//*Button
private:
	FRowCBTNOnClicked RowBTNOnClicked;
	FReply OnClicked();

	bool bToggleState = false;
public:
	FORCEINLINE bool GetToggleState() { return bToggleState; }

	//*Combo 
private:
	//list view
	TSharedPtr< SListView<TSharedPtr<FString>> > LVCombo;

	//list vie source
	TArray< TSharedPtr<FString> > LVComboSource;

	//On generate
	TSharedRef<ITableRow> OGR_Combo(TSharedPtr<FString> InItem, const TSharedRef<STableViewBase>& OwnerTable);

	//on selection changed
	void OSC_Combo(TSharedPtr<FString> InItem, ESelectInfo::Type SelectInfo);

	//Callback
	FRowOnUpdateSource OnUpdateSource;
	FRowOnItemSelect OnItemSelect;
	


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
