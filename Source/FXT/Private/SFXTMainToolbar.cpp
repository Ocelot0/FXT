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
					.InitialColor(Clr_ParentBTN_Attr)
				]//-SHorizontalBox::Slot()
			]//-SVerticalBox::Slot()
		]//-SBorder
	];
	
}
FReply SFXTMainToolbar::BTN_Parent()
{
	const TSharedPtr<SFXTMain> OwnerWidget = OwnerPtr.Pin();

	if (OwnerWidget.IsValid()) {
		OwnerWidget->SetCurrentTool(EFXTToolType::EParent);
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *OwnerWidget->DebugStr);
	}

	return FReply::Handled();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
