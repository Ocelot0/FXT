// Fill out your copyright notice in the Description page of Project Settings.

#include "SFXTInfo.h"
#include "SlateOptMacros.h"
#include "FXTCore.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SFXTInfo::Construct(const FArguments& InArgs)
{
	TArray<FString> LicenseText;
	FLicense::GetLicense(LicenseText);
	for (FString i : LicenseText) {
		LicenseTextListSrc.Add(MakeShareable(new FString(i)));
	}

	ChildSlot.Padding(4.f)
	[
		SNew(SBorder).BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder")).Padding(4.f)[
			SNew(SBox).VAlign(VAlign_Fill).HAlign(HAlign_Fill)[
				SNew(SVerticalBox)
				//*License
				+ SVerticalBox::Slot().AutoHeight().Padding(0.f, 4.f, 0.f, 0.f)[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot().AutoHeight()[
						SNew(SHorizontalBox)
						//* Wiki page hyperlink
						+ SHorizontalBox::Slot().AutoWidth()[
							SNew(SFXTButton).OnClicked(this, &SFXTInfo::OnCliked_WikiPage)
								.bUseImage(true)
								.Image(FXTStyle::Get().GetBrush("FXT.Icon64"))
								.InitialColor(FXTStyle::Clr_Default())
								.ToolTipText(FXTC::T(BTN_CREATEPARENT_WIKIPAGE))
								.ButtonStyle(&FEditorStyle::Get(), "FlatButton")
						]
						//* Copyright
						+SHorizontalBox::Slot().AutoWidth().Padding(4.0f, 0.0f).VAlign(VAlign_Bottom)[
							SNew(SVerticalBox)
							+ SVerticalBox::Slot().AutoHeight()[
								SNew(STextBlock).Text(FXTC::GetFullVersionText()).TextStyle(FXTStyle::GetTBStyle("FooterText"))
							]
							+ SVerticalBox::Slot().AutoHeight()[
								SNew(STextBlock).Text(FXTC::GetCopyrightText()).TextStyle(FXTStyle::GetTBStyle("FooterText"))
							]
						]
					]
					//* MIT License
					+ SVerticalBox::Slot().Padding(0.f, 10.f).MaxHeight(300.f).VAlign(VAlign_Top)[
						SNew(SBorder).BorderImage(FEditorStyle::GetBrush("ToolPanel.DarkGroupBorder")).Padding(4.f)[
							SAssignNew(LicenseTextListView, SListView<TSharedPtr<FString>>)
								.ListItemsSource(&LicenseTextListSrc)
								.OnGenerateRow(this, &SFXTInfo::OnGenerateRowLicenseText)
								.OnSelectionChanged(this, &SFXTInfo::OnSelectionChangedLicenseText)
								.ItemHeight(14.f)
								.SelectionMode(ESelectionMode::None)
						]//-SBorder
					]
				]//-SVerticalBox::Slot()
			]//-SBox
		]//-SBorder
	];//-ChildSlot
}

FReply SFXTInfo::OnCliked_WikiPage()
{
	//* Warning Message popup
	FText Message = FXTC::T("You are about to open an external URL(https://github.com/Ocelot0/FXT/wiki). This will open your web browser. Do you want to proceed?");
	FText URLDialog = FXTC::T("Open external link");

	FSuppressableWarningDialog::FSetupInfo Info(Message, URLDialog, "SuppressOpenURLWarning");
	Info.ConfirmText = FXTC::T("Yes");
	Info.CancelText = FXTC::T("No");
	FSuppressableWarningDialog OpenURLWarning(Info);
	if (OpenURLWarning.ShowModal() == FSuppressableWarningDialog::Confirm)
	{
		FPlatformProcess::LaunchURL(*FString("https://github.com/Ocelot0/FXT/wiki"), nullptr, nullptr);
	}

	return FReply::Handled();
}

TSharedRef<ITableRow> SFXTInfo::OnGenerateRowLicenseText(TSharedPtr<FString> InItem, const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(STableRow< TSharedPtr<FXTParentListItemType> >, OwnerTable)
		.Padding(2.f)
		[
			SNew(SHorizontalBox)
			//Child set hidden Button
			+ SHorizontalBox::Slot().AutoWidth().HAlign(HAlign_Left)[
				SNew(STextBlock)
				.Text(FXTC::T(*InItem.Get()))
				.TextStyle(FXTStyle::GetTBStyle("FooterText"))
			]
		];
}

void SFXTInfo::OnSelectionChangedLicenseText(TSharedPtr<FString> InItem, ESelectInfo::Type SelectInfo)
{
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
