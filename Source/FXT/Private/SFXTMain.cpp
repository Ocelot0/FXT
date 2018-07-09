//=================================================
// Written by Lee Gil Su
// Copyright 2018. Lee Gil Su. all rights reserved.
//=================================================

#include "SFXTMain.h"
#include "SlateOptMacros.h"
#include "FXTCore.h"

SFXTMain::~SFXTMain() 
{
	FEditorDelegates::BeginPIE.RemoveAll(this);
	FEditorDelegates::EndPIE.RemoveAll(this);
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SFXTMain::Construct(const FArguments& InArgs)
{
	FEditorDelegates::BeginPIE.AddSP(this, &SFXTMain::OnBeginPIE);
	FEditorDelegates::EndPIE.AddSP(this, &SFXTMain::OnEndPIE);

	CurrentTool = EFXTToolType::EParent;

	//Visibility in PIE
	auto Vis_InPIE_Lam = [this] {
		return bInPIE ? EVisibility::Visible : EVisibility::Collapsed;
	};
	auto Vis_InPIE_Attr = TAttribute<EVisibility>::Create(
		TAttribute<EVisibility>::FGetter::CreateLambda(Vis_InPIE_Lam));

	//Visibility Tools
	auto Vis_Tools_Lam = [this] {
		return bInPIE ? EVisibility::Collapsed : EVisibility::Visible;
	};
	auto Vis_Tools_Attr = TAttribute<EVisibility>::Create(
		TAttribute<EVisibility>::FGetter::CreateLambda(Vis_Tools_Lam));
	
	ChildSlot
	[
		SNew(SVerticalBox)
		//PIE mode
		+ SVerticalBox::Slot()[
			SNew(SVerticalBox).Visibility(Vis_InPIE_Attr) +SVerticalBox::Slot()[
				SNew(SInPIE)
			]
		]
		
		//Editor mode
		+ SVerticalBox::Slot()[
			SNew(SVerticalBox).Visibility(Vis_Tools_Attr)
			//*Contents
			+SVerticalBox::Slot().VAlign(VAlign_Fill).HAlign(HAlign_Fill)[
				SNew(SBorder).BorderImage(FEditorStyle::GetBrush("ToolPanel.DarkGroupBorder"))[
					SNew(SBox)[
						SNew(SVerticalBox)
						//*MenuToolbar
						+ SVerticalBox::Slot().AutoHeight().VAlign(VAlign_Top)[
							SNew(SFXTMainToolbar, SharedThis(this))
						]//-SVerticalBox::Slot()
						//*Parent Tool
						+ SVerticalBox::Slot().VAlign(VAlign_Fill)[
							SNew(SFXTParent).Visibility(Vis_byToolType(EFXTToolType::EParent))
						]//-SVerticalBox::Slot()
						 //*PIE Tool
						+ SVerticalBox::Slot().VAlign(VAlign_Fill)[
							SNew(SPIETool).Visibility(Vis_byToolType(EFXTToolType::EPIE))
						]//-SVerticalBox::Slot()
						 //*EmitterBatch Tool
						+ SVerticalBox::Slot().VAlign(VAlign_Fill)[
							SNew(SEmitterBatchTool).Visibility(Vis_byToolType(EFXTToolType::EEmitterBatch))
						]//-SVerticalBox::Slot()
						 //*INFO
						+ SVerticalBox::Slot().VAlign(VAlign_Fill)[
							SNew(SFXTInfo).Visibility(Vis_byToolType(EFXTToolType::EInfo))
						]//-SVerticalBox::Slot()
					]//-SBox
				]//-SBorder
			]//-SVerticalBox::Slot()
		]//-SVerticalBox::Slot()

	];//-ChildSlot()
	
}

void SFXTMain::OnBeginPIE(const bool bBeginPIE)
{
	bInPIE = true;
}

void SFXTMain::OnEndPIE(const bool bEndPIE)
{
	//Start Timer until PIE fully finish
	GEditor->GetTimerManager().Get().SetTimer(
		PIEFullyFinishTimerHandle, FTimerDelegate::CreateSP(this, &SFXTMain::OnFullyEndPIE), 0.03f, false, 0.03f);
}

void SFXTMain::OnFullyEndPIE()
{
	//reset timer manager
	GEditor->GetTimerManager()->ClearTimer(PIEFullyFinishTimerHandle);

	bInPIE = false;
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
