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

class AFXTParent;
class SRowComboButton;

struct FXTParentListItemType
{
	FXTParentListItemType()
		: Label(TEXT("Parent"))
	{}

	//Create with FXTParent
	FXTParentListItemType(AFXTParent* InActor);

	//Create with Actor
	FXTParentListItemType(AActor* InActor);

	FString Label;
};

class FXT_API SFXTParent : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SFXTParent)
	{}
	SLATE_END_ARGS()

	~SFXTParent();

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	//*Editor event delegate function
	void OnLevelActorAdded(AActor* InActor);
	void OnLevelActorDeleted(AActor* InActor);
	void OnActorLabelChanged(AActor* inActor);

	void OnBeginPIE(const bool bBeginPIE);
	void OnEndPIE(const bool bEndPIE);
	void OnFullyEndPIE();
	FTimerHandle PIEFullyFinishTimerHandle;

private:
	//*Tool Pannel
	//*Create new parent actor
	//Name
	TSharedPtr<SEditableTextBox> TB_NewParentName;
	FString TB_NewParentNameOutputMessage;

	//Create new parent
	FReply OnClicked_CreateNewParent();
	FReply OnClicked_ResetCustomName();

	//New parent option
	float NewParentOffset = 128.0f;
	void OVC_NewParentOffset(float NewValue);

	//Goto sequence option
	bool bGotoSeq_OpenSeqEditor = true;
	void CB_bGotoSeq_OpenSeqEditor(ECheckBoxState NewValue);

	bool bGotoSeq_Focus = false;
	void CB_bGotoSeq_Focus(ECheckBoxState NewValue);

private:
	//*ListView : AFXTParent
	//ListView Widget
	TSharedPtr< SListView<TSharedPtr<FXTParentListItemType>> > FXTParentList;

	//ListView item data array
	TArray< TSharedPtr<FXTParentListItemType> > FXTParentListItems;

	//Generate List View Row
	TSharedRef<ITableRow> OnGenerateRowFXTParentList(TSharedPtr<FXTParentListItemType> InItem, const TSharedRef<STableViewBase>& OwnerTable);

	//Update List View
	void UpdateFXTParentList();

	//On Selection Changed
	void OnSelectionChangedFXTParentList(TSharedPtr<FXTParentListItemType> InItem, ESelectInfo::Type SelectInfo);

	//LastSelect
	TSharedPtr<FXTParentListItemType> LastSelectedItemFXTParentList;

	//Reselect timer
	void ReselectTimerFXTParentList();
	FTimerHandle ReselectTimerHandleFXTParentList;

	//*Parent list view buttons
	FReply OnClicked_EditChildList();

	//Hide button
	FReply OnClickedRB_ChildHiddenToggle(const TSharedRef<SRowButton>& outBTN);

	//Add child button
	FReply OnClickedRB_AddChild(const TSharedRef<SRowButton>& outBTN);

	//Add child button
	FReply OnClickedRB_DestroyParent(const TSharedRef<SRowButton>& outBTN);

	//goto button
	FReply OnClickedRB_GotoParent(const TSharedRef<SRowButton>& outBTN);

	//goto seq button
	FReply OnClickedRB_GotoSeq(const TSharedRef<SRowComboButton>& outBTN);
	void OUS_GotoSeq(TArray<TSharedPtr<FString>>& outItem, const TSharedRef<SRowComboButton>& outBTN);
	void OIS_GotoSeq(FString& outLabel);



private:
	//*ListView :: Child List
	bool bEditChildList = false;

	//ListView Widget
	TSharedPtr< SListView<TSharedPtr<FXTParentListItemType>> > ChildListView;

	//ListView item data array
	TArray< TSharedPtr<FXTParentListItemType> > ChildListViewItems;

	//Generate List View Row
	TSharedRef<ITableRow> OnGenerateRowChildListView(TSharedPtr<FXTParentListItemType> InItem, const TSharedRef<STableViewBase>& OwnerTable);

	//Update List View
	void UpdateChildListView();

	//On Selection Changed
	void OnSelectionChangedChildListView(TSharedPtr<FXTParentListItemType> InItem, ESelectInfo::Type SelectInfo);


	//*Child list view button
	FReply OnClicked_ResetChildList();

	FReply OnClickedRB_GotoChild(const TSharedRef<SRowButton>& outBTN);
	FReply OnClickedRB_RemoveChild(const TSharedRef<SRowButton>& outBTN);
};
