//=================================================
// Written by Lee Gil Su
// Copyright 2018. Lee Gil Su. all rights reserved.
//=================================================

#include "SFXTComboButton.h"
#include "SlateOptMacros.h"

#include "SBoxPanel.h"
#include "SButton.h"
#include "STextBlock.h"
#include "SImage.h"

#include "EditorStyleSet.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SFXTComboButton::Construct(const FArguments& InArgs)
{
	//Delegate binding
	ButtonOnClicked = InArgs._OnClicked;
	OnUpdateSource = InArgs._OnUpdateSource;
	OnItemSelect = InArgs._OnItemSelect;

	//*UseImage flag
	auto Vis_Image_Lam = [InArgs] {
		return InArgs._bUseImage ? EVisibility::Visible : EVisibility::Collapsed;
	};
	auto Vis_Image_Attr = TAttribute<EVisibility>::Create(
		TAttribute<EVisibility>::FGetter::CreateLambda(Vis_Image_Lam));

	auto Vis_Text_Lam = [InArgs] {
		return InArgs._bUseImage ? EVisibility::Collapsed : EVisibility::Visible;
	};
	auto Vis_Text_Attr = TAttribute<EVisibility>::Create(
		TAttribute<EVisibility>::FGetter::CreateLambda(Vis_Text_Lam));

	SMenuAnchor::Construct(SMenuAnchor::FArguments()
		.Placement(EMenuPlacement::MenuPlacement_ComboBox)
		.Method(EPopupMethod::UseCurrentWindow)
		[
			//combo box button
			SNew(SButton)
			.ContentPadding(FMargin(0.f, 0.f))
			.ButtonStyle(&FEditorStyle::Get().GetWidgetStyle< FButtonStyle >("FlatButton"))
			.OnClicked(this, &SFXTComboButton::OnClicked)
			.ToolTipText(InArgs._TooltipText)
			[
				SNew(SHorizontalBox)
				//image
				+ SHorizontalBox::Slot().AutoWidth()
				[
					SNew(SImage)
					.Visibility(Vis_Image_Attr)
					.Image(InArgs._Image)
				]
				//text
				+ SHorizontalBox::Slot()//.AutoWidth()
				[
					SNew(STextBlock)
					.Visibility(Vis_Text_Attr)
					.TextStyle(InArgs._TextStyle)
					.Text(InArgs._Text)
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
					.OnGenerateRow(this, &SFXTComboButton::OGR_Combo)
					.OnSelectionChanged(this, &SFXTComboButton::OSC_Combo)
					.SelectionMode(ESelectionMode::Single)
				]
			]
		)
	);
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FReply SFXTComboButton::OnClicked()
{
	if (!ButtonOnClicked.IsBound()) return FReply::Handled();

	//Execute Delegate
	ButtonOnClicked.Execute();

	//*Combo box
	//get combo box contents
	OnUpdateSource.ExecuteIfBound(LVComboSource);

	if (LVComboSource.Num() > 0)
	{
		//Open
		SetIsOpen(ShouldOpenDueToClick(), false);

		//refresh combo box
		if (LVCombo.IsValid()) LVCombo->RequestListRefresh();
	}

	return FReply::Handled();
}

TSharedRef<ITableRow> SFXTComboButton::OGR_Combo(TSharedPtr<FString> InItem, const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(STableRow<TSharedPtr<FString>>, OwnerTable)
		.Padding(2.f)
		[
			SNew(STextBlock).Text(FText::FromString(*InItem.Get()))
		];
}

void SFXTComboButton::OSC_Combo(TSharedPtr<FString> InItem, ESelectInfo::Type SelectInfo)
{
	if (SelectInfo == ESelectInfo::OnMouseClick) {
		//call back
		OnItemSelect.ExecuteIfBound(*InItem.Get());

		//close combo box
		SetIsOpen(false, false);
	}
}


