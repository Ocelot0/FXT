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

DECLARE_DELEGATE_RetVal(FReply, FCBTNOnClicked)
DECLARE_DELEGATE_OneParam(FOnUpdateSource, TArray<TSharedPtr<FString>>&)
DECLARE_DELEGATE_OneParam(FOnItemSelect, FString&)

class FXT_API SFXTComboButton : public SMenuAnchor
{
public:
	SLATE_BEGIN_ARGS(SFXTComboButton)
		: _bUseImage(false)
		, _Image(FEditorStyle::GetBrush("Default"))
		, _Text()
		, _TextStyle(FFXTStyle::GetTBStyle("ListViewText.RowButton"))
		, _TooltipText()
		, _InitialToggleState(false)
		, _InitialColor(FFXTStyle::Clr_Default())
	{}

	SLATE_ARGUMENT(bool, bUseImage)
	SLATE_ARGUMENT(const FSlateBrush*, Image)
	SLATE_ARGUMENT(float, ImageSize)

	SLATE_ATTRIBUTE(FText, Text)
	SLATE_STYLE_ARGUMENT(FTextBlockStyle, TextStyle)
	SLATE_ARGUMENT(FText, TooltipText)

	SLATE_ARGUMENT(bool, InitialToggleState)
	SLATE_ARGUMENT(FSlateColor, InitialColor)

	SLATE_EVENT(FCBTNOnClicked, OnClicked)
	SLATE_EVENT(FOnUpdateSource, OnUpdateSource)
	SLATE_EVENT(FOnItemSelect, OnItemSelect)

	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	//*Button
private:
	FCBTNOnClicked ButtonOnClicked;
	FReply OnClicked();

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
	FOnUpdateSource OnUpdateSource;
	FOnItemSelect OnItemSelect;
};
