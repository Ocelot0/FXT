//=================================================
// Written by Lee Gil Su
// Copyright 2018. Lee Gil Su. all rights reserved.
//=================================================

#include "SFXTMain.h"
#include "SlateOptMacros.h"
#include "FXTCore.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SFXTMain::Construct(const FArguments& InArgs)
{
	CurrentTool = EFXTToolType::EParent;
	
	ChildSlot
	[
		SNew(SVerticalBox)
		//*Contents
		+SVerticalBox::Slot().VAlign(VAlign_Fill).HAlign(HAlign_Fill)[
			SNew(SBorder).BorderImage(FEditorStyle::GetBrush("ToolPanel.DarkGroupBorder"))[
				SNew(SBox)[
					SNew(SVerticalBox)
					//*MenuToolbar
					+ SVerticalBox::Slot().AutoHeight().VAlign(VAlign_Top)[
						SNew(SFXTMainToolbar, SharedThis(this))
					]//-SVerticalBox::Slot()
					//*ParentTool
					+ SVerticalBox::Slot().VAlign(VAlign_Fill)[
						SNew(SFXTParent).Visibility(Vis_byToolType(EFXTToolType::EParent))
					]//-SVerticalBox::Slot()
					 //*ParentTool
					+ SVerticalBox::Slot().VAlign(VAlign_Fill)[
						SNew(SFXTInfo).Visibility(Vis_byToolType(EFXTToolType::EInfo))
					]//-SVerticalBox::Slot()
				]//-SBox
			]//-SBorder
		]//-SVerticalBox::Slot()
	];//-ChildSlot()
	
}
void SFXTMain::SetCurrentTool(EFXTToolType NewToolType)
{
	CurrentTool = NewToolType;
}

TAttribute<EVisibility> SFXTMain::Vis_byToolType(EFXTToolType CompareType)
{
	auto Vis_IsCurrentTool_Lam = [this, CompareType] {
		return CurrentTool == CompareType ? EVisibility::Visible : EVisibility::Collapsed;
	};
	
	return TAttribute<EVisibility>::Create(
		TAttribute<EVisibility>::FGetter::CreateLambda(Vis_IsCurrentTool_Lam));
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
