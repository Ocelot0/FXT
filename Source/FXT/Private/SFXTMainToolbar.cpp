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

	ChildSlot
	[
		SNew(SBorder).BorderImage(FEditorStyle::GetBrush("ToolPanel.DarkGroupBorder")).Padding(0.f)[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot().AutoHeight()[
				SNew(SHorizontalBox)
				//*Parent Tool Button
				+ SHorizontalBox::Slot().AutoWidth()[			
					SNew(SBorder).BorderImage(Border_byToolType(EFXTToolType::EParent)).Padding(0.f)[
						SNew(SFXTButton).OnClicked(this, &SFXTMainToolbar::BTN_Parent)
							.bUseImage(true)
							.Image(FXTStyle::Get().GetBrush("EditorIcon.SceneOutliner"))
							.ToolTipText(FText::FromString(FXT_TOOLNAME_PARENT))
							.ButtonStyle(&FEditorStyle::Get(), "FlatButton")
					]//-SBorder
				]//-SHorizontalBox::Slot()
				 //*PIE Tool Button
				+ SHorizontalBox::Slot().AutoWidth()[
					SNew(SBorder).BorderImage(Border_byToolType(EFXTToolType::EPIE)).Padding(0.f)[
						SNew(SFXTButton).OnClicked(this, &SFXTMainToolbar::BTN_PIE)
							.bUseImage(true)
							.Image(FXTStyle::Get().GetBrush("EditorIcon.PIE"))
							.ToolTipText(FText::FromString(FXT_TOOLNAME_PIE))
							.ButtonStyle(&FEditorStyle::Get(), "FlatButton")
					]//-SBorder
				]//-SHorizontalBox::Slot()
				//*Info Button
				+ SHorizontalBox::Slot().AutoWidth()[
					SNew(SBorder).BorderImage(Border_byToolType(EFXTToolType::EInfo)).Padding(0.f)[
						SNew(SFXTButton).OnClicked(this, &SFXTMainToolbar::BTN_Info)
							.bUseImage(true)
							.Image(FXTStyle::Get().GetBrush("EditorIcon.Detail"))
							.ToolTipText(FText::FromString(FXT_TOOLNAME_INFO))
							.ButtonStyle(&FEditorStyle::Get(), "FlatButton")
					]//-SBorder
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

TAttribute<const FSlateBrush*> SFXTMainToolbar::Border_byToolType(EFXTToolType CompareType)
{
	auto Border_byToolType_Lam = [this, CompareType] {
		if (OwnerPtr.IsValid()
			&& OwnerPtr.Pin()->GetCurrentTool() == CompareType) {
			return FEditorStyle::GetBrush("ToolPanel.GroupBorder");
		}
		return FEditorStyle::GetBrush("ToolPanel.DarkGroupBorder");
	};

	return TAttribute<const FSlateBrush*>::Create(
		TAttribute<const FSlateBrush*>::FGetter::CreateLambda(Border_byToolType_Lam));
}

FReply SFXTMainToolbar::BTN_Parent()
{
	const TSharedPtr<SFXTMain> OwnerWidget = OwnerPtr.Pin();

	if (OwnerWidget.IsValid()) {
		OwnerWidget->SetCurrentTool(EFXTToolType::EParent);
	}

	return FReply::Handled();
}
FReply SFXTMainToolbar::BTN_PIE()
{
	const TSharedPtr<SFXTMain> OwnerWidget = OwnerPtr.Pin();

	if (OwnerWidget.IsValid()) {
		OwnerWidget->SetCurrentTool(EFXTToolType::EPIE);
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
