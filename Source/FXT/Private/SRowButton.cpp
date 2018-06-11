//=================================================
// Written by Lee Gil Su
// Copyright 2018. Lee Gil Su. all rights reserved.
//=================================================

#include "SRowButton.h"
#include "SlateOptMacros.h"

#include "SBoxPanel.h"
#include "SButton.h"
#include "STextBlock.h"
#include "SImage.h"

#include "EditorStyleSet.h"

#define LOCTEXT_NAMESPACE "SRowButton"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SRowButton::Construct(const FArguments& InArgs)
{
	Icon = InArgs._Icon.Get();

	RowLabel = InArgs._RowLabel;
	RowBTNOnClicked = InArgs._OnClicked;

	bToggleState = InArgs._InitialToggleState;
	IconColor = InArgs._InitialColor;

	//*UseImage flag
	auto Vis_Image_Lam = [InArgs] {
		return InArgs._bUseImage ? EVisibility::Visible : EVisibility::Collapsed;
	};
	auto Vis_Image_Attr = TAttribute<EVisibility>::Create(
		TAttribute<EVisibility>::FGetter::CreateLambda(Vis_Image_Lam));

	auto Vis_Icon_Lam = [InArgs] {
		return InArgs._bUseImage ? EVisibility::Collapsed : EVisibility::Visible;
	};
	auto Vis_Icon_Attr = TAttribute<EVisibility>::Create(
		TAttribute<EVisibility>::FGetter::CreateLambda(Vis_Icon_Lam));

	//*IconStyle
	auto IconColor_Lam = [this] {
		return RowLabel.IsEmpty() ? FFXTStyle::Clr_Error() : IconColor;
	};
	auto IconColor_Attr = TAttribute<FSlateColor>::Create(
		TAttribute<FSlateColor>::FGetter::CreateLambda(IconColor_Lam));

	//*Icon
	auto IconText_Lam = [this] {
		return RowLabel.IsEmpty() ? FEditorFontGlyphs::Exclamation_Triangle : Icon;
	};
	auto IconText_Attr = TAttribute<FText>::Create(
		TAttribute<FText>::FGetter::CreateLambda(IconText_Lam));

	//*ToolTip
	FText ValidToolTipText = InArgs._TooltipText;
	FText ErrorToolTipText = LOCTEXT("InvalidToolTip", "Error : RowLabel is empty.");
	auto TooltipText_Lam = [this, ErrorToolTipText, ValidToolTipText] {
		return RowLabel.IsEmpty() ? ErrorToolTipText : ValidToolTipText;
	};
	auto TooltipText_Attr = TAttribute<FText>::Create(
		TAttribute<FText>::FGetter::CreateLambda(TooltipText_Lam));

	ChildSlot
	[
		SNew(SButton)
		.ButtonStyle(&FEditorStyle::Get().GetWidgetStyle< FButtonStyle >("FlatButton"))
		.OnClicked(this, &SRowButton::OnClicked)
		.ToolTipText(TooltipText_Attr)
		[
			SNew(SHorizontalBox)
			//image
			+ SHorizontalBox::Slot().AutoWidth()	
			[
				SNew(SImage)
				.Visibility(Vis_Image_Attr)
				.Image(InArgs._Image)
				.ColorAndOpacity(IconColor_Attr)
			]
			//icon
			+ SHorizontalBox::Slot().AutoWidth()
			[
				SNew(STextBlock)
				.Visibility(Vis_Icon_Attr)
				.TextStyle(InArgs._IconStyle)
				.ColorAndOpacity(IconColor_Attr)
				.Text(IconText_Attr)
			]
		]
	];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FReply SRowButton::OnClicked()
{
	if (!RowBTNOnClicked.IsBound() && RowLabel.IsEmpty()) return FReply::Handled();
		
	//Toggle
	bToggleState = bToggleState ? false : true;

	//Execute Delegate
	RowBTNOnClicked.Execute(SharedThis(this));

	return FReply::Handled();
}

void SRowButton::SetIcon(FText inIcon)
{
	Icon = inIcon;
}

#undef LOCTEXT_NAMESPACE