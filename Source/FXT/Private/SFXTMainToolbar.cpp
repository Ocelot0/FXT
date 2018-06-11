//=================================================
// Written by Lee Gil Su
// Copyright 2018. Lee Gil Su. all rights reserved.
//=================================================

#include "SFXTMainToolbar.h"
#include "SlateOptMacros.h"
#include "FXTCore.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SFXTMainToolbar::Construct(const FArguments& InArgs, const TSharedRef<SFXTMain>& InOwner)
{
	OwnerPtr = InOwner;

	//*ButtonColor : Parent
	auto Clr_ParentBTN_Lam = [this] {
		if (OwnerPtr.IsValid()) {
			return OwnerPtr.Pin()->GetCurrentTool() == EFXTToolType::EParent ? FXTStyle::Clr_Toggle() : FXTStyle::Clr_Default();
		}
		return FXTStyle::Clr_Hidden();
	};
	auto Clr_ParentBTN_Attr = TAttribute<FSlateColor>::Create(
		TAttribute<FSlateColor>::FGetter::CreateLambda(Clr_ParentBTN_Lam));

	ChildSlot.Padding(4.f)
	[
		SNew(SBorder).BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder")).Padding(4.f)[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot().AutoHeight()[
				SNew(SHorizontalBox)
				//*Parent Tool Button
				+ SHorizontalBox::Slot().AutoWidth()[			
					SNew(SFXTButton).OnClicked(this, &SFXTMainToolbar::BTN_Parent)
					.Text(FText::FromString(FXT_TOOLNAME_PARENT))
					.ButtonStyle(&FEditorStyle::Get(), "FlatButton")
					.TextStyle(FXTStyle::GetTBStyle("ButtonText.Dark"))
					.InitialColor(Clr_byToolType(EFXTToolType::EParent))
				]//-SHorizontalBox::Slot()
				//*Info Button
				+ SHorizontalBox::Slot().AutoWidth()[
					SNew(SFXTButton).OnClicked(this, &SFXTMainToolbar::BTN_Info)
						.Text(FText::FromString(FXT_TOOLNAME_INFO))
						.ButtonStyle(&FEditorStyle::Get(), "FlatButton")
						.TextStyle(FXTStyle::GetTBStyle("ButtonText.Dark"))
						.InitialColor(Clr_byToolType(EFXTToolType::EInfo))
				]//-SHorizontalBox::Slot()
			]//-SVerticalBox::Slot()
		]//-SBorder
	];
	
}
TAttribute<FSlateColor> SFXTMainToolbar::Clr_byToolType(EFXTToolType CompareType)
{
	auto Vis_IsCurrentTool_Lam = [this, CompareType] {
		if (OwnerPtr.IsValid()) {
			return OwnerPtr.Pin()->GetCurrentTool() == CompareType ? FXTStyle::Clr_Toggle() : FXTStyle::Clr_Default();
		}
		return FXTStyle::Clr_Hidden();
	};

	return TAttribute<FSlateColor>::Create(
		TAttribute<FSlateColor>::FGetter::CreateLambda(Vis_IsCurrentTool_Lam));
}

FReply SFXTMainToolbar::BTN_Parent()
{
	const TSharedPtr<SFXTMain> OwnerWidget = OwnerPtr.Pin();

	if (OwnerWidget.IsValid()) {
		OwnerWidget->SetCurrentTool(EFXTToolType::EParent);
	}

	return FReply::Handled();
}
FReply SFXTMainToolbar::BTN_Info()
{
	const TSharedPtr<SFXTMain> OwnerWidget = OwnerPtr.Pin();

	if (OwnerWidget.IsValid()) {
		OwnerWidget->SetCurrentTool(EFXTToolType::EInfo);
	}

	return FReply::Handled();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
