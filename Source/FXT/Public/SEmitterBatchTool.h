//=================================================
// Written by Lee Gil Su
// Copyright 2018. Lee Gil Su. all rights reserved.
//=================================================

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "DeclarativeSyntaxSupport.h"

#include "SListView.h"
#include "STableRow.h"

class SRowComboButton;

struct FEmitterListItemType
{
	FEmitterListItemType()
		: Label(TEXT("emitter"))
	{}

	FEmitterListItemType(FName _EmitterName, bool _bUseLocalSpace)
		: Label(_EmitterName.ToString())
		, bUseLocalSpace(_bUseLocalSpace)
	{}

	FString Label;
	bool bUseLocalSpace;
};

class FXT_API SEmitterBatchTool : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SEmitterBatchTool)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	//*AssetPicker
	void AssetPicker_OnGetAllowedClasses(TArray<const UClass*>& outclasses);
	void AssetPicker_OnAssetSelected(const struct FAssetData& AssetData);

	UParticleSystem* CurrentParticleSystem;

private:
	//*Batch functions
	//Required << bUseLocalSpace
	void SetEmitterUseLocalSpace(UParticleModuleRequired* Target, bool NewUseLocalSpace);

private:
	//*Batch buttons
	FReply btn_Refresh();
	FReply btn_SetAllLocal();
	FReply btn_SetAllWorld();

private:
	//*Module List view
	//List view widget
	TSharedPtr< SListView<TSharedPtr<FEmitterListItemType>> > EmitterListView;

	//Listview item data source
	TArray< TSharedPtr<FEmitterListItemType> > EmitterListViewSource;

	//Generate List view row
	TSharedRef<ITableRow> OnGenerateRowEmitterListView(TSharedPtr<FEmitterListItemType> InItem, const TSharedRef<STableViewBase>& OwnerTable);

	//Update List View
	void UpdateEmitterListView();

	//On selection changed
	void OnSelectionChangedEmitterListView(TSharedPtr<FEmitterListItemType> InItem, ESelectInfo::Type SelectInfo);

	//bUseLocalSpace toggle button
	FReply OnClickedRB_ToggleUseLocalSpace(const TSharedRef<SRowButton>& outBTN);

};
