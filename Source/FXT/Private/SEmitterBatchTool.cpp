//=================================================
// Written by Lee Gil Su
// Copyright 2018. Lee Gil Su. all rights reserved.
//=================================================

#include "SEmitterBatchTool.h"
#include "SlateOptMacros.h"
#include "FXTCore.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SEmitterBatchTool::Construct(const FArguments& InArgs)
{
	
	ChildSlot
	[
		SNew(SBorder).BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder")).Padding(2.f)[

			SNew(SVerticalBox)
			//AssetPicker
			+SVerticalBox::Slot().AutoHeight()[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot().AutoWidth()[
					SNew(SAssetPicker)
					.OnGetAllowedClasses(this, &SEmitterBatchTool::AssetPicker_OnGetAllowedClasses)
					.OnAssetSelected(this, &SEmitterBatchTool::AssetPicker_OnAssetSelected)
				]
				//batch Tools
				+ SHorizontalBox::Slot().Padding(2.f, 0.f)[

					SNew(SScrollBox).Orientation(EOrientation::Orient_Horizontal)
					+SScrollBox::Slot()[
						SNew(SHorizontalBox)
						+SHorizontalBox::Slot().AutoWidth()[
							SNew(SVerticalBox)
							//refresh button
							+ SVerticalBox::Slot().AutoHeight().Padding(0.f, 2.f)[
								SNew(SFXTButton).OnClicked(this, &SEmitterBatchTool::btn_Refresh)
								.bUseImage(false).Text(FXTC::T(TEXT("Refresh Emitters")))
								.ButtonStyle(&FEditorStyle::Get(), "FlatButton.Success")
							]
							//batch set to local button
							+ SVerticalBox::Slot().AutoHeight().Padding(0.f, 2.f)[
								SNew(SFXTButton).OnClicked(this, &SEmitterBatchTool::btn_SetAllLocal)
								.bUseImage(false).Text(FXTC::T(TEXT("Batch : bUseLocalSpace(1)")))
								.ButtonStyle(&FEditorStyle::Get(), "FlatButton").TextStyle(FFXTStyle::GetTBStyle("DefaultText"))
							]
							//batch set to world button
							+ SVerticalBox::Slot().AutoHeight().Padding(0.f, 2.f)[
								SNew(SFXTButton).OnClicked(this, &SEmitterBatchTool::btn_SetAllWorld)
								.bUseImage(false).Text(FXTC::T(TEXT("Batch : bUseLocalSpace(0)")))
								.ButtonStyle(&FEditorStyle::Get(), "FlatButton").TextStyle(FFXTStyle::GetTBStyle("DefaultText"))
							]
						]
					]//-SScrollBox::Slot()
				]//-SHorizontalBox::Slot()
			]//-SVerticalBox::Slot() ;AssetPicker
			//Module List view
			+ SVerticalBox::Slot().Padding(2.f)[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot().MaxWidth(200.f)[
					SNew(SBorder).BorderImage(FEditorStyle::GetBrush("ToolPanel.DarkGroupBorder")).Padding(2.f)[
						SAssignNew(EmitterListView, SListView<TSharedPtr<FEmitterListItemType>>)
						.ListItemsSource(&EmitterListViewSource)
						.OnGenerateRow(this, &SEmitterBatchTool::OnGenerateRowEmitterListView)
						.OnSelectionChanged(this, &SEmitterBatchTool::OnSelectionChangedEmitterListView)
						.ItemHeight(14.f)
						.SelectionMode(ESelectionMode::None)
					]
				]
			]
		]//-SBorder

	];
	
}

void SEmitterBatchTool::AssetPicker_OnGetAllowedClasses(TArray<const UClass*>& outclasses)
{
	outclasses.Add(UParticleSystem::StaticClass());
}

void SEmitterBatchTool::AssetPicker_OnAssetSelected(const FAssetData& AssetData)
{
	UParticleSystem* PS = Cast<UParticleSystem>(AssetData.GetAsset());
	if (PS) {
		CurrentParticleSystem = PS;
		UpdateEmitterListView();
	}
}

void SEmitterBatchTool::SetEmitterUseLocalSpace(UParticleModuleRequired* Target, bool NewUseLocalSpace)
{
	if (Target) {
		Target->bUseLocalSpace = NewUseLocalSpace ? 1 : 0;
	}
}

FReply SEmitterBatchTool::btn_Refresh()
{
	UpdateEmitterListView();

	return FReply::Handled();
}

FReply SEmitterBatchTool::btn_SetAllLocal()
{
	if (!CurrentParticleSystem) return FReply::Handled();

	//set all local
	for (UParticleEmitter* i : CurrentParticleSystem->Emitters) {
		UParticleLODLevel* LODLevel = i->GetLODLevel(0);
		SetEmitterUseLocalSpace(LODLevel->RequiredModule, true);
	}

	UpdateEmitterListView();

	return FReply::Handled();
}

FReply SEmitterBatchTool::btn_SetAllWorld()
{
	if (!CurrentParticleSystem) return FReply::Handled();

	//set all world
	for (UParticleEmitter* i : CurrentParticleSystem->Emitters) {
		UParticleLODLevel* LODLevel = i->GetLODLevel(0);
		SetEmitterUseLocalSpace(LODLevel->RequiredModule, false);
	}

	UpdateEmitterListView();

	return FReply::Handled();
}

TSharedRef<ITableRow> SEmitterBatchTool::OnGenerateRowEmitterListView(TSharedPtr<FEmitterListItemType> InItem, const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(STableRow< TSharedPtr<FEmitterListItemType> >, OwnerTable)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()[
				SNew(STextBlock).Text(FXTC::T(InItem->Label)).TextStyle(FFXTStyle::GetTBStyle("ListViewText.Row"))
			]
			//Right aligned row buttons
			+ SHorizontalBox::Slot().HAlign(HAlign_Right)[
				SNew(SHorizontalBox)
				//Toggle bUseLocalSpace button
				+ SHorizontalBox::Slot().AutoWidth()[
					SNew(SRowButton)
					.OnClicked(this, &SEmitterBatchTool::OnClickedRB_ToggleUseLocalSpace).RowLabel(InItem.Get()->Label)
					.bUseImage(true)
					.Image(InItem.Get()->bUseLocalSpace ? FXTStyle::Get().GetBrush("EditorIcon.Local") : FXTStyle::Get().GetBrush("EditorIcon.World"))
				]
			]
			
		];
}

void SEmitterBatchTool::UpdateEmitterListView()
{
	if (!EmitterListView.IsValid()) return;
	if (!CurrentParticleSystem) return;

	//clear sources
	EmitterListViewSource.Empty();

	for (UParticleEmitter* i : CurrentParticleSystem->Emitters) {

		UParticleLODLevel* LODLevel = i->GetLODLevel(0);
		EmitterListViewSource.Add(MakeShareable(
			new FEmitterListItemType(i->EmitterName, LODLevel->RequiredModule->bUseLocalSpace)));
	}

	EmitterListView->RequestListRefresh();

}

void SEmitterBatchTool::OnSelectionChangedEmitterListView(TSharedPtr<FEmitterListItemType> InItem, ESelectInfo::Type SelectInfo)
{
}

FReply SEmitterBatchTool::OnClickedRB_ToggleUseLocalSpace(const TSharedRef<SRowButton>& outBTN)
{
	if (!CurrentParticleSystem) return FReply::Handled();

	//UE_LOG(LogTemp, Warning, TEXT("toggle buselocal space [%s]"), *outBTN.Get().GetRowLabel());
	for (UParticleEmitter* i : CurrentParticleSystem->Emitters) {

		//search by name
		if (i->GetEmitterName().ToString() == outBTN.Get().GetRowLabel()) {
			UParticleLODLevel* LODLevel = i->GetLODLevel(0);
			SetEmitterUseLocalSpace(LODLevel->RequiredModule, !LODLevel->RequiredModule->bUseLocalSpace);
			break;
		}
		
	}

	//update list view
	UpdateEmitterListView();

	return FReply::Handled();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
