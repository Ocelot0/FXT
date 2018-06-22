//=================================================
// Written by Lee Gil Su
// Copyright 2018. Lee Gil Su. all rights reserved.
//=================================================

#include "SRowComboButton.h"
#include "SlateOptMacros.h"

#include "SBoxPanel.h"
#include "SButton.h"
#include "STextBlock.h"
#include "SImage.h"

#include "EditorStyleSet.h"

#define LOCTEXT_NAMESPACE "SRowComboButton"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SRowComboButton::Construct(const FArguments& InArgs)
{
	Icon = InArgs._Icon.Get();

	RowLabel = InArgs._RowLabel;

	bToggleState = InArgs._InitialToggleState;
	IconColor = InArgs._InitialColor;

	//Delegate binding
	RowBTNOnClicked = InArgs._OnClicked;
	OnUpdateSource = InArgs._OnUpdateSource;
	OnItemSelect = InArgs._OnItemSelect;

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

	SMenuAnchor::Construct(SMenuAnchor::FArguments()
		.Placement(EMenuPlacement::MenuPlacement_ComboBox)
		.Method(EPopupMethod::UseCurrentWindow)
		[
			//combo box button
			SNew(SButton)
			.ContentPadding(FMargin(0.f, 0.f))
			.ButtonStyle(&FEditorStyle::Get().GetWidgetStyle< FButtonStyle >("FlatButton"))
			.OnClicked(this, &SRowComboButton::OnClicked)
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
		]
		.MenuContent(
			//Combobox contents
			SNew(SBorder).BorderImage(FEditorStyle::GetBrush("GlobalAssetPicker.Background"))
			[
				SNew(SBox).MaxDesiredHeight(150.f)[
					SAssignNew(LVCombo, SListView<TSharedPtr<FString>>)
					.ListItemsSource(&LVComboSource)
					.OnGenerateRow(this, &SRowComboButton::OGR_Combo)
					.OnSelectionChanged(this, &SRowComboButton::OSC_Combo)
					.SelectionMode(ESelectionMode::Single)
				]
			]
		)
	);
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FReply SRowComboButton::OnClicked()
{
	if (!RowBTNOnClicked.IsBound() && RowLabel.IsEmpty()) return FReply::Handled();

	//Toggle
	bToggleState = bToggleState ? false : true;

	//Execute Delegate
	RowBTNOnClicked.Execute(SharedThis(this));

	//*Combo box
	//get combo box contents
	OnUpdateSource.ExecuteIfBound(LVComboSource, SharedThis(this));

	if (LVComboSource.Num() > 0)
	{
		//Open
		SetIsOpen(ShouldOpenDueToClick(), false);

		//refresh combo box
		if (LVCombo.IsValid()) LVCombo->RequestListRefresh();
	}

	return FReply::Handled();
}

void SRowComboButton::SetIcon(FText inIcon)
{
	Icon = inIcon;
}

TSharedRef<ITableRow> SRowComboButton::OGR_Combo(TSharedPtr<FString> InItem, const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(STableRow<TSharedPtr<FString>>, OwnerTable)
		.Padding(2.f)
		[
			SNew(STextBlock).Text(FText::FromString(*InItem.Get()))
		];
}

void SRowComboButton::OSC_Combo(TSharedPtr<FString> InItem, ESelectInfo::Type SelectInfo)
{
	if (SelectInfo == ESelectInfo::OnMouseClick) {
		//call back
		OnItemSelect.ExecuteIfBound(*InItem.Get());

		//close combo box
		SetIsOpen(false, false);
	}
}

#undef LOCTEXT_NAMESPACE
