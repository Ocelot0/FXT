//=================================================
// Written by Lee Gil Su
// Copyright 2018. Lee Gil Su. all rights reserved.
//=================================================

#include "SFXTParent.h"
#include "SlateOptMacros.h"
#include "FXTCore.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
SFXTParent::~SFXTParent()
{
	GEngine->OnLevelActorAdded().RemoveAll(this);
	GEngine->OnLevelActorDeleted().RemoveAll(this);
	FCoreDelegates::OnActorLabelChanged.RemoveAll(this);
}

void SFXTParent::Construct(const FArguments& InArgs)
{
	//*Delegate Binding
	GEngine->OnLevelActorAdded().AddSP(this, &SFXTParent::OnLevelActorAdded);
	GEngine->OnLevelActorDeleted().AddSP(this, &SFXTParent::OnLevelActorDeleted);
	FCoreDelegates::OnActorLabelChanged.AddRaw(this, &SFXTParent::OnActorLabelChanged);

	//*Visibility
	auto Vis_EditChildList_Lam = [this] {
		return bEditChildList ? EVisibility::Visible : EVisibility::Collapsed;
	};
	auto Vis_EditChildList_Attr = TAttribute<EVisibility>::Create(
		TAttribute<EVisibility>::FGetter::CreateLambda(Vis_EditChildList_Lam));

	//*Text attr
	auto TXT_CurrentParent_Lam = [this] {
		if (!FXTParentList->GetNumItemsSelected() == 1) return FXTC::T("Childs");

		//Get selected parent actor
		TArray<TSharedPtr<FXTParentListItemType>> SelectedParents = FXTParentList->GetSelectedItems();
		return FXTC::T(SelectedParents[0].Get()->Label);
	};
	auto TXT_CurrentParent_Attr = TAttribute<FText>::Create(
		TAttribute<FText>::FGetter::CreateLambda(TXT_CurrentParent_Lam));

	//*Property
	float ListViewWidth = 230.0f;
	float TB_NewParentNameWidth = 200.0f;
	float SB_NewParentOffsetWidth = 60.0f;
	float InputBoxHeight = 20.0f;

	ChildSlot
	[
		SNew(SBorder).BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder")).Padding(2.f)[
			SNew(SBox).VAlign(VAlign_Fill).HAlign(HAlign_Fill)[
				SNew(SVerticalBox)
				//*Tool pannel
				+ SVerticalBox::Slot().AutoHeight()[
					SNew(SVerticalBox)
					
					+ SVerticalBox::Slot().AutoHeight().Padding(0.f, 0.f, 0.f, 2.f)[
						SNew(SHorizontalBox)
						//*Add Parent
						+ SHorizontalBox::Slot().AutoWidth()[
							SNew(SFXTButton).OnClicked(this, &SFXTParent::OnClicked_CreateNewParent)
							.bUseImage(true)
							.Image(FXTStyle::Get().GetBrush("FXT.Icon20"))
							.InitialColor(FXTStyle::Clr_Default())
							.ToolTipText(FXTC::T(BTN_CREATEPARENT_TOOLTIP))
							.ButtonStyle(&FEditorStyle::Get(), "EditorViewportToolBar.MenuButton")
							]//-SHorizontalBox::Slot()
						//*Add Parent option
						+ SHorizontalBox::Slot().Padding(2.f, 2.f, 0.f, 0.f).MaxWidth(TB_NewParentNameWidth)[
							SNew(SHorizontalBox)
							+ SHorizontalBox::Slot()[
								SNew(SVerticalBox) + SVerticalBox::Slot().MaxHeight(InputBoxHeight)[
									SAssignNew(TB_NewParentName, SEditableTextBox)
										.HintText(FXTC::T("Parent Name"))
										.ToolTipText(FXTC::T(TB_NEWPARENTNAME_TOOLTIP))
								]
							]//-SHorizontalBox::Slot()
							//reset custom name text box
							+ SHorizontalBox::Slot().AutoWidth().Padding(FMargin(2.f, 0.f))[
								SNew(SVerticalBox) +SVerticalBox::Slot().AutoHeight()[
									SNew(SFXTButton).OnClicked(this, &SFXTParent::OnClicked_ResetCustomName)
									.bUseImage(true)
									.Image(FEditorStyle::GetBrush("PropertyWindow.DiffersFromDefault"))
									.InitialColor(FXTStyle::Clr_Default())
									.ButtonStyle(FEditorStyle::Get(), "NoBorder")
								]//-SVerticalBox::Slot()
							]//-SHorizontalBox::Slot()
						]//-SHorizontalBox::Slot() ;AddparentOption
						//*Spinbox : pineapple spawn location offset from view location
						+ SHorizontalBox::Slot().Padding(3.f, 0.f).MaxWidth(SB_NewParentOffsetWidth)[
							SNew(SHorizontalBox)
							+ SHorizontalBox::Slot().MaxWidth(16.f)[
								SNew(SVerticalBox) + SVerticalBox::Slot().MaxHeight(16.f).VAlign(VAlign_Center)[
									SNew(SImage).Image(FXTStyle::Get().GetBrush("EditorIcon.GenericLOD"))
								]
							]
							+ SHorizontalBox::Slot().AutoWidth()[
								SNew(SVerticalBox) + SVerticalBox::Slot().MaxHeight(InputBoxHeight)[
									SNew(SSpinBox<float>).ContentPadding(0.f)
										.ToolTipText(FXTC::T(SB_NEWPARENTVIEWOFFSET_TOOLTIP))
										.MinValue(100.f).MaxValue(350.f).Delta(10.f)
										.Value(NewParentOffset)
										.OnValueChanged(this, &SFXTParent::OVC_NewParentOffset)
								]
							]
						]
						//* Goto sequencer option
						+ SHorizontalBox::Slot().Padding(2.f, 2.f, 0.f, 0.f).AutoWidth()[
							SNew(SVerticalBox) +SVerticalBox::Slot().AutoHeight().Padding(0.f, 0.f, 0.f, 2.f)[
								SNew(SHorizontalBox)
								//Goto sequencer option
								+ SHorizontalBox::Slot().AutoWidth()[
									SNew(SHorizontalBox) + SHorizontalBox::Slot().MaxWidth(16.f)[
										SNew(SVerticalBox) + SVerticalBox::Slot().MaxHeight(16.f).VAlign(VAlign_Center)[
											SNew(SImage).Image(FXTStyle::Get().GetBrush("RowIcon.LevelSequenceActor"))
										]
									]
									+ SHorizontalBox::Slot().AutoWidth()[
										SNew(SVerticalBox) + SVerticalBox::Slot().MaxHeight(InputBoxHeight)[
											//Open seq ed
											SNew(SCheckBox).OnCheckStateChanged(this, &SFXTParent::CB_bGotoSeq_OpenSeqEditor)
											.IsChecked(bGotoSeq_OpenSeqEditor ? ECheckBoxState::Checked : ECheckBoxState::Unchecked)
											.ToolTipText(FXTC::T(CB_GOTOSEQOPENSEQ_TOOLTIP))
										]
									]
									+ SHorizontalBox::Slot().AutoWidth()[
										SNew(SVerticalBox) + SVerticalBox::Slot().MaxHeight(InputBoxHeight)[
											//Focus
											SNew(SCheckBox).OnCheckStateChanged(this, &SFXTParent::CB_bGotoSeq_Focus)
											.IsChecked(bGotoSeq_Focus ? ECheckBoxState::Checked : ECheckBoxState::Unchecked)
											.ToolTipText(FXTC::T(CB_GOTOSEQFOCUS_TOOLTIP))
										]
									]
								]//-SHorizontalBox::Slot() ;Goto sequencer option
							]//-SVerticalBox::Slot() ;Row button option
						]//-SHorizontalBox::Slot() ;Row button option
					]//-SVerticalBox::Slot()
				]//-SVerticalBox::Slot()
				+ SVerticalBox::Slot()[
					SNew(SHorizontalBox)
					//*FXTParentList
					+ SHorizontalBox::Slot().MaxWidth(ListViewWidth)[
						SNew(SBorder).BorderImage(FEditorStyle::GetBrush("ToolPanel.DarkGroupBorder"))[
							SAssignNew(FXTParentList, SListView<TSharedPtr<FXTParentListItemType>>)
							.ListItemsSource(&FXTParentListItems)
							.OnGenerateRow(this, &SFXTParent::OnGenerateRowFXTParentList)
							.OnSelectionChanged(this, &SFXTParent::OnSelectionChangedFXTParentList)
							.ItemHeight(14.f)
							.SelectionMode(ESelectionMode::Single)
							.HeaderRow(
								SNew(SHeaderRow)+SHeaderRow::Column(FName(TEXT("AFXTParentList")))
								[
									SNew(SHorizontalBox)
									//Header text
									+ SHorizontalBox::Slot().HAlign(HAlign_Left).VAlign(VAlign_Center)[
										SNew(STextBlock).Text(FXTC::T("AFXTParent")).TextStyle(FFXTStyle::GetTBStyle("ListViewText.Row"))
									]
									//Edit Child button
									+ SHorizontalBox::Slot().HAlign(HAlign_Right)[
										SNew(SFXTButton).OnClicked(this, &SFXTParent::OnClicked_EditChildList)
										.Icon(FEditorFontGlyphs::Pencil)
										.TextStyle(FFXTStyle::GetTBStyle("ListViewText.RowButton"))
										.ToolTipText(FXTC::T(BTN_EDITCHILD_TOOLTIP))
									]//-SHorizontalBox::Slot()
								]//-SHeaderRow
							)
						]//-SBorder
					]//-SHorizontalBox::Slot()
					 //*FXTChildList
					+ SHorizontalBox::Slot().Padding(2.f, 0.f).MaxWidth(ListViewWidth)[
						SNew(SBorder).Visibility(Vis_EditChildList_Attr).BorderImage(FEditorStyle::GetBrush("ToolPanel.DarkGroupBorder"))[
							SAssignNew(ChildListView, SListView<TSharedPtr<FXTParentListItemType>>)
							.ListItemsSource(&ChildListViewItems)
							.OnGenerateRow(this, &SFXTParent::OnGenerateRowChildListView)
							.OnSelectionChanged(this, &SFXTParent::OnSelectionChangedChildListView)
							.ItemHeight(14.f)
							.SelectionMode(ESelectionMode::None)
							.HeaderRow(
								SNew(SHeaderRow) + SHeaderRow::Column(FName(TEXT("AFXTParentList")))
								[
									SNew(SHorizontalBox)
									//Header text
									+ SHorizontalBox::Slot().HAlign(HAlign_Left).VAlign(VAlign_Center)[
										SNew(STextBlock).Text(TXT_CurrentParent_Attr).TextStyle(FFXTStyle::GetTBStyle("ListViewText.Row"))
									]//-SHorizontalBox::Slot()
									 //Reset Child list button
									+ SHorizontalBox::Slot().HAlign(HAlign_Right)[
										SNew(SFXTButton).OnClicked(this, &SFXTParent::OnClicked_ResetChildList)
											.bUseImage(true)
											.Image(FEditorStyle::GetBrush("PropertyWindow.Button_Clear"))
											.InitialColor(FXTStyle::Clr_Default())
											.ToolTipText(FXTC::T(BTN_RESETCHILDLIST_TOOLTIP))
									]//-SHorizontalBox::Slot()
								]//-SHeaderRow
							)
						]//-SBorder
					]//-SHorizontalBox::Slot()
				]//-SVerticalBox::Slot()
			]//-SBox
		]//-SBorder
	];

	//Update List
	UpdateFXTParentList();

}

void SFXTParent::OnLevelActorAdded(AActor* InActor)
{
	//Update List
	UpdateFXTParentList();
}

void SFXTParent::OnLevelActorDeleted(AActor* InActor)
{
	//Update List
	UpdateFXTParentList();

	//*Refresh child list for all parents
	TArray<AFXTParent*> Parents;
	FXTC::Itr<AFXTParent>(Parents);
	for (AFXTParent* itr : Parents) {
		itr->RefreshChildList();
	}

}

void SFXTParent::OnActorLabelChanged(AActor* inActor)
{
	//Update List
	UpdateFXTParentList();
}

FReply SFXTParent::OnClicked_CreateNewParent()
{
	//Check name dupling
	bool bNameDupling = false;
	FString CustomName = TB_NewParentName->GetText().ToString();
	if (!CustomName.IsEmpty()) {
		TArray<AFXTParent*> AllParents;
		FXTC::Itr<AFXTParent>(AllParents);
		for (AFXTParent* itr : AllParents){
			if (FXTC::chkA(itr) && itr->GetActorLabel() == CustomName) {
				bNameDupling = true;
				break;
			}
		}
	}

	FEditorViewportClient* client = (FEditorViewportClient*)GEditor->GetActiveViewport()->GetClient();
	if (client && !bNameDupling) {
		//Get spawn position
		FVector EditorCameraDirection = client->GetViewRotation().Vector();
		FVector EditorCameraPosition = client->GetViewLocation();
		FVector SpawnLocation = EditorCameraPosition + (EditorCameraDirection * NewParentOffset);

		FTransform SpawnTransform = FTransform();
		SpawnTransform.SetLocation(SpawnLocation);

		//Spawn actor
		AFXTParent* SpawnedActor = FXTC::AddActor<AFXTParent>(SpawnTransform);

		//Set Actor label
		if (!CustomName.IsEmpty()) SpawnedActor->SetActorLabel(CustomName);
	}

	return FReply::Handled();
}

FReply SFXTParent::OnClicked_ResetCustomName()
{
	TB_NewParentName->SetText(FXTC::T(""));

	return FReply::Handled();
}

void SFXTParent::OVC_NewParentOffset(float NewValue)
{
	NewParentOffset = NewValue;
}

void SFXTParent::CB_bGotoSeq_OpenSeqEditor(ECheckBoxState NewValue)
{
	bGotoSeq_OpenSeqEditor = (NewValue == ECheckBoxState::Checked) ? true : false;
}

void SFXTParent::CB_bGotoSeq_Focus(ECheckBoxState NewValue)
{
	bGotoSeq_Focus = (NewValue == ECheckBoxState::Checked) ? true : false;
}

TSharedRef<ITableRow> SFXTParent::OnGenerateRowFXTParentList(TSharedPtr<FXTParentListItemType> InItem, const TSharedRef<STableViewBase>& OwnerTable)
{
	AFXTParent* A = FXTC::GetActorByLabel<AFXTParent>(InItem.Get()->Label);
	bool LastHidden = A->GetChildHidden();

	//Num of childs
	int32 NumOfChilds = A->GetNumOfChilds();
	FText NumOfChildsTEXT = FXTC::T( "(" + FString::FromInt(NumOfChilds) + ")");

	//Num of sequencer
	TArray<ALevelSequenceActor*> LSAs;
	A->GetActorsFromChildList<ALevelSequenceActor>(LSAs);
	int32 NumOfSeq = LSAs.Num();

	float LabelTextMaxWidth = 100.0f;

	return SNew(STableRow< TSharedPtr<FXTParentListItemType> >, OwnerTable)
		.Padding(2.f)
		[
			SNew(SHorizontalBox)
			//Child set hidden Button
			+ SHorizontalBox::Slot().AutoWidth().HAlign(HAlign_Left)[
				SNew(SRowButton).OnClicked(this, &SFXTParent::OnClickedRB_ChildHiddenToggle).RowLabel(InItem.Get()->Label)
				.Icon(LastHidden ? FEditorFontGlyphs::Eye_Slash : FEditorFontGlyphs::Eye)
				.InitialToggleState(LastHidden)
				.InitialColor(LastHidden ? FXTStyle::Clr_Hidden() : FXTStyle::Clr_Default())
				.ToolTipText(FXTC::T(BTN_HIDDENTOGGLE_TOOLTIP))
			]
			//Label
			+ SHorizontalBox::Slot().MaxWidth(LabelTextMaxWidth).AutoWidth().HAlign(HAlign_Fill).VAlign(VAlign_Center)[
				SNew(STextBlock).Text(FXTC::T(InItem.Get()->Label)).TextStyle(FFXTStyle::GetTBStyle("ListViewText.Row"))
					.ToolTipText(FXTC::T(InItem.Get()->Label))
			]
			//Num of childs
			+ SHorizontalBox::Slot().Padding(2.f, 0.f).AutoWidth().HAlign(HAlign_Fill).VAlign(VAlign_Bottom)[
				SNew(STextBlock).Visibility(NumOfChilds > 0 ? EVisibility::Visible : EVisibility::Collapsed)
				.Text(NumOfChildsTEXT)
				.Font(FEditorStyle::Get().GetFontStyle("FontAwesome.9"))
				.ColorAndOpacity(FXTStyle::Clr_Hidden())
			]
			//Utility Buttons
			+ SHorizontalBox::Slot().HAlign(HAlign_Right)[
				SNew(SHorizontalBox)
				//Add child button
				+ SHorizontalBox::Slot().AutoWidth()[
					SNew(SRowButton).OnClicked(this, &SFXTParent::OnClickedRB_AddChild).RowLabel(InItem.Get()->Label)
					.bUseImage(true)
					.Image(FEditorStyle::GetBrush("PropertyWindow.Button_Use"))
					.ToolTipText(FXTC::T(BTN_ADDCHILDFROMSELECTED_TOOLTIP))
				]
				//remove parent button
				+ SHorizontalBox::Slot().AutoWidth()[
					SNew(SRowButton).OnClicked(this, &SFXTParent::OnClickedRB_DestroyParent).RowLabel(InItem.Get()->Label)
						.bUseImage(true)
						.Image(FEditorStyle::GetBrush("PropertyWindow.Button_Delete"))
						.ToolTipText(FXTC::T(BTN_DESTROYPARENT_TOOLTIP))
				]
				//Goto button
				+ SHorizontalBox::Slot().AutoWidth()[
					SNew(SRowButton).OnClicked(this, &SFXTParent::OnClickedRB_GotoParent).RowLabel(InItem.Get()->Label)
						.bUseImage(true)
						.Image(FEditorStyle::GetBrush("PropertyWindow.Button_Browse"))
						.ToolTipText(FXTC::T(BTN_GOTOPARENT_TOOLTIP))
				]
				//Goto seq button
				+ SHorizontalBox::Slot().AutoWidth()[
					SNew(SRowComboButton).RowLabel(InItem.Get()->Label)
						.bUseImage(true)
						.Image(FXTStyle::Get().GetBrush("FXT.GotoSeq"))
						.InitialColor(NumOfSeq > 0 ? FXTStyle::Clr_Default() : FXTStyle::Clr_Hidden())
						.ToolTipText(FXTC::T(BTN_GOTOSEQ_TOOLTIP))
						.OnClicked(this, &SFXTParent::OnClickedRB_GotoSeq)
						.OnUpdateSource(this, &SFXTParent::OUS_GotoSeq)
						.OnItemSelect(this, &SFXTParent::OIS_GotoSeq)
				]
			]
		];
}

void SFXTParent::UpdateFXTParentList()
{
	if (FXTParentList.IsValid()) {

		//Get all AFXTParents
		TArray<AFXTParent*> AFXTParents;
		FXTC::Itr<AFXTParent>(AFXTParents);
	
		//Update Item source
		FXTParentListItems.Empty();
		if (AFXTParents.Num() > 0){
			for (AFXTParent* itr : AFXTParents) {
				FXTParentListItems.Add(MakeShareable(new FXTParentListItemType(itr)));
			}
		}

		//Sort array
		if (FXTParentListItems.Num() > 1) {
			FXTParentListItems.Sort([](const TSharedPtr<FXTParentListItemType>& A, const TSharedPtr<FXTParentListItemType>& B) {
				return FXTC::CompareNumeric(*A->Label, *B->Label) < 0;
			});
		}

		//Last Selected
		if (FXTParentList->GetNumItemsSelected() == 1) {
			//*Get selected parent actor
			TArray<TSharedPtr<FXTParentListItemType>> SelectedParents = FXTParentList->GetSelectedItems();
			LastSelectedItemFXTParentList = SelectedParents[0];
		}
		else
		{
			LastSelectedItemFXTParentList = nullptr;
		}

		//Update Listview
		FXTParentList->RequestListRefresh();

		//*Reselect last selected with timer
		GEditor->GetTimerManager().Get().SetTimer(
			ReselectTimerHandleFXTParentList, FTimerDelegate::CreateSP(this, &SFXTParent::ReselectTimerFXTParentList), 0.01f, false, 0.01f);
	}
}
void SFXTParent::ReselectTimerFXTParentList()
{
	//close tiemr session
	GEditor->GetTimerManager()->ClearTimer(ReselectTimerHandleFXTParentList);

	if (LastSelectedItemFXTParentList.IsValid()) {
		FString LSLabel = LastSelectedItemFXTParentList.Get()->Label;

		for (TSharedPtr<FXTParentListItemType> itr : FXTParentListItems) {
			if (itr.IsValid() && itr.Get()->Label == LSLabel) {
				FXTParentList->SetItemSelection(itr, true, ESelectInfo::OnMouseClick);
				break;
			}
		}
	}
}

void SFXTParent::OnSelectionChangedFXTParentList(TSharedPtr<FXTParentListItemType> InItem, ESelectInfo::Type SelectInfo)
{
	if (!InItem.IsValid()) {
		//*clear child list view
		UpdateChildListView();
		return;
	}

	AFXTParent* A = FXTC::GetActorByLabel<AFXTParent>(InItem.Get()->Label);
	if (FXTC::chkA(A)) {
		//*Update Child List View
		UpdateChildListView();
	}
}

FReply SFXTParent::OnClicked_EditChildList()
{
	//toggle child list view visibility
	bEditChildList = bEditChildList ? false : true;

	return FReply::Handled();
}

FReply SFXTParent::OnClickedRB_ChildHiddenToggle(const TSharedRef<SRowButton>& outBTN)
{
	//*Get actor of row
	const FString& outLabel = outBTN.Get().GetRowLabel();
	AFXTParent* A = FXTC::GetActorByLabel<AFXTParent>(outLabel);

	if (FXTC::chkA(A)) {
		//*Get current button toggle state
		bool ToggleState = outBTN.Get().GetToggleState();

		//*Call function on actor
		A->SetChildHidden(ToggleState);

		//*Set eye icon by hidden state
		outBTN.Get().SetIcon(outBTN.Get().GetToggleState() ? FEditorFontGlyphs::Eye_Slash : FEditorFontGlyphs::Eye);

		//*Set icon color
		outBTN.Get().SetIconColor(ToggleState ? FXTStyle::Clr_Hidden() : FXTStyle::Clr_Default());
	}

	return FReply::Handled();
}

FReply SFXTParent::OnClickedRB_GotoParent(const TSharedRef<SRowButton>& outBTN)
{
	//get client for camera
	FEditorViewportClient* client = (FEditorViewportClient*)GEditor->GetActiveViewport()->GetClient();
	if (client) {

		//*Get actor of row
		const FString& outLabel = outBTN.Get().GetRowLabel();
		AFXTParent* A = FXTC::GetActorByLabel<AFXTParent>(outLabel);

		if (FXTC::chkA(A)) {
			//make camera destination
			FVector Destination = A->GetActorLocation() - client->GetViewRotation().Vector() * 128.0f;

			//Set editor camera location
			client->SetViewLocation(Destination);

			//select target actor
			GEditor->SelectNone(true, true, true);
			GEditor->SelectActor(A, true, true, true, true);
		}
	}

	return FReply::Handled();
}

FReply SFXTParent::OnClickedRB_GotoSeq(const TSharedRef<SRowComboButton>& outBTN)
{
	return FReply::Handled();
}

void SFXTParent::OUS_GotoSeq(TArray<TSharedPtr<FString>>& outItem, const TSharedRef<SRowComboButton>& outBTN)
{
	//*Get actor of row
	const FString& outLabel = outBTN.Get().GetRowLabel();
	AFXTParent* A = FXTC::GetActorByLabel<AFXTParent>(outLabel);

	if (FXTC::chkA(A)) {
		TArray<ALevelSequenceActor*> LSAs;

		outItem.Empty();
		if (A->GetActorsFromChildList<ALevelSequenceActor>(LSAs))
		{
			for (ALevelSequenceActor* i : LSAs) {
				outItem.Add( MakeShareable(new FString(i->GetActorLabel())) );
			}
		}
	}
}

void SFXTParent::OIS_GotoSeq(FString& outLabel)
{
	ALevelSequenceActor* LSA = FXTC::GetActorByLabel<ALevelSequenceActor>(outLabel);

	if (FXTC::chkA(LSA)) {
		//select target actor
		GEditor->SelectNone(true, true, true);
		GEditor->SelectActor(LSA, true, true, true, true);

		//get client for camera
		if (bGotoSeq_Focus)
		{
			FEditorViewportClient* client = (FEditorViewportClient*)GEditor->GetActiveViewport()->GetClient();
			if (client) {

				//make camera destination
				FVector Destination = LSA->GetActorLocation() - client->GetViewRotation().Vector() * 128.0f;

				//Set editor camera location
				client->SetViewLocation(Destination);
			}
		}

		//open level sequence editor
		if (bGotoSeq_OpenSeqEditor) {
			UObject* LoadedObject = LSA->LevelSequence.TryLoad();
			if (LoadedObject != nullptr) {
				FAssetEditorManager::Get().OpenEditorForAsset(LoadedObject);
			}
		}
	}
}

FReply SFXTParent::OnClickedRB_AddChild(const TSharedRef<SRowButton>& outBTN)
{
	//*Get actor of row
	const FString& outLabel = outBTN.Get().GetRowLabel();
	AFXTParent* A = FXTC::GetActorByLabel<AFXTParent>(outLabel);

	//Add selected actor to child
	if (FXTC::chkA(A)) {
		A->AddChildFromSelectedActors();

		//*Set Hidden
		//*Get current button toggle state
		bool ToggleState = A->GetChildHidden();
		A->SetChildHidden(ToggleState);

		//*Update list view
		UpdateFXTParentList();
	}

	return FReply::Handled();
}

FReply SFXTParent::OnClickedRB_DestroyParent(const TSharedRef<SRowButton>& outBTN)
{
	//*Get actor of row
	const FString& outLabel = outBTN.Get().GetRowLabel();
	AFXTParent* A = FXTC::GetActorByLabel<AFXTParent>(outLabel);

	//*Reset list
	if (FXTC::chkA(A)) {
		//* Warning Message popup
		FText Message = FXTC::T(
			"Destroy [" + A->GetActorLabel() + "]. Proceed? \n"
			+ "Yes : Destroy only Parent \n"
			+ "No : Abort \n"
			+ "YesAll : Destroy Parent and all childs");
		FText Title = FXTC::T("Confirm");

		EAppReturnType::Type Dialogresult = FMessageDialog::Open(EAppMsgType::YesNoYesAll, Message, &Title);
		
		//*Destroy parent and all childs
		if (Dialogresult == EAppReturnType::YesAll)
		{
			FText Message = FXTC::T(
				"Destroy [" + FString::FromInt(A->GetNumOfChilds()) + "] actors from [" + A->GetActorLabel() + "] Proceed?");

			Dialogresult = FMessageDialog::Open(EAppMsgType::YesNo, Message, &Title);

			if (Dialogresult == EAppReturnType::Yes) {
				TArray<AActor*> DestroyList;
				A->GetChildList(DestroyList);

				//clear child array
				A->ResetChildList();

				//Destroy Child Actors
				for (AActor* i : DestroyList) {
					i->ConditionalBeginDestroy();
				}

				//Destroy Parent
				A->ConditionalBeginDestroy();

				//Update list view
				UpdateFXTParentList();
			}
		}

		//*Destroy parent only
		if (Dialogresult == EAppReturnType::Yes)
		{
			//clear child array
			A->ResetChildList();

			//Destroy Parent
			A->ConditionalBeginDestroy();

			//Update list view
			UpdateFXTParentList();
		}
	}

	return FReply::Handled();
}

TSharedRef<ITableRow> SFXTParent::OnGenerateRowChildListView(TSharedPtr<FXTParentListItemType> InItem, const TSharedRef<STableViewBase>& OwnerTable)
{
	//* Get Actor of Label
	const FString& outLabel = InItem.Get()->Label;
	AActor* A = FXTC::GetActorByLabel<AActor>(outLabel);

	//Class Text
	FString ClassStr = A->GetClass()->GetFName().ToString();
	FText ClassText = FXTC::T(ClassStr);

	//Get Icon Brush
	FName IconBrushName = FName(*FString("RowIcon." + ClassStr));

	const FSlateBrush* DefaultIconBrush = FXTStyle::Get().GetBrush("RowIcon.Default");
	const FSlateBrush* IconBrush = FXTStyle::Get().GetBrush(IconBrushName);
	bool bUseDefaultIconBrush = IconBrush->GetResourceName().ToString().Right(16) == "Checkerboard.png" ? true : false;

	UE_LOG(LogTemp, Warning, TEXT("given[%s] result[%s]"), *IconBrushName.ToString(), *IconBrush->GetResourceName().ToString().Right(16));
	
	

	return SNew(STableRow< TSharedPtr<FXTParentListItemType> >, OwnerTable)
	.Padding(2.f)
	[
		SNew(SHorizontalBox)
		//Icon
		+ SHorizontalBox::Slot().Padding(1.0f, 0.0f).AutoWidth().HAlign(HAlign_Fill).VAlign(VAlign_Center)[
			SNew(SImage)
			.Image(bUseDefaultIconBrush ? DefaultIconBrush : IconBrush)
			.ColorAndOpacity(FFXTStyle::Clr_Default())
			.ToolTipText(ClassText)
		]
		//Label
		+ SHorizontalBox::Slot().AutoWidth().HAlign(HAlign_Fill).VAlign(VAlign_Center)[
			SNew(STextBlock).Text(FXTC::T(InItem.Get()->Label)).TextStyle(FFXTStyle::GetTBStyle("ListViewText.Row"))
		]
		//Utility Buttons
		+ SHorizontalBox::Slot().HAlign(HAlign_Right)[
			SNew(SHorizontalBox)
			//remove child button
			+ SHorizontalBox::Slot().AutoWidth()[
				SNew(SRowButton).OnClicked(this, &SFXTParent::OnClickedRB_RemoveChild).RowLabel(InItem.Get()->Label)
				.bUseImage(true)
				.Image(FEditorStyle::GetBrush("PropertyWindow.Button_Delete"))
				.ToolTipText(FXTC::T(BTN_REMOVECHILD_TOOLTIP))
			]
			//goto child button
			+ SHorizontalBox::Slot().AutoWidth()[
				SNew(SRowButton).OnClicked(this, &SFXTParent::OnClickedRB_GotoChild).RowLabel(InItem.Get()->Label)
					.bUseImage(true)
					.Image(FEditorStyle::GetBrush("PropertyWindow.Button_Browse"))
					.ToolTipText(FXTC::T(BTN_GOTOCHILD_TOOLTIP))
			]
		]
	];
}

void SFXTParent::UpdateChildListView()
{
	if (!ChildListView.IsValid()) return;

	//*Reset list view when SourceParent nullptr
	ChildListViewItems.Empty();

	if (FXTParentList->GetNumItemsSelected() == 1) {

		//*Get selected parent actor
		TArray<TSharedPtr<FXTParentListItemType>> SelectedParents = FXTParentList->GetSelectedItems();

		const FString& outLabel = SelectedParents[0].Get()->Label;
		AFXTParent* A = FXTC::GetActorByLabel<AFXTParent>(outLabel);

		if (FXTC::chkA(A))
		{
			TArray<AActor*> inChildList;
			A->GetChildList(inChildList);

			if (inChildList.Num() > 0) {
				for (AActor* itr : inChildList) {
					ChildListViewItems.Add(MakeShareable(new FXTParentListItemType(itr)));
				}
			}

			//Sort array
			if (ChildListViewItems.Num() > 1) {
				ChildListViewItems.Sort([](const TSharedPtr<FXTParentListItemType>& A, const TSharedPtr<FXTParentListItemType>& B) {
					return FXTC::CompareNumeric(*A->Label, *B->Label) < 0;
				});
			}
		}
	}

	ChildListView->RequestListRefresh();
}

void SFXTParent::OnSelectionChangedChildListView(TSharedPtr<FXTParentListItemType> InItem, ESelectInfo::Type SelectInfo)
{
}

FReply SFXTParent::OnClicked_ResetChildList()
{
	if (!FXTParentList->GetNumItemsSelected() == 1) return FReply::Handled();

	//*Get selected parent actor
	TArray<TSharedPtr<FXTParentListItemType>> SelectedParents = FXTParentList->GetSelectedItems();

	const FString& outLabel = SelectedParents[0].Get()->Label;
	AFXTParent* A = FXTC::GetActorByLabel<AFXTParent>(outLabel);

	//*Reset list
	if (FXTC::chkA(A) && A->GetNumOfChilds() > 0) {
		//* Warning Message popup
		FText Message = FXTC::T(
			"Remove [" + FString::FromInt(A->GetNumOfChilds()) + "] childs from [" + A->GetActorLabel() 
			+ "].\n"
			+ "It won't destroy actors, only remove reference from parent. Proceed?");
		FText Title = FXTC::T("Confirm");

		EAppReturnType::Type Dialogresult = FMessageDialog::Open(EAppMsgType::YesNo, Message, &Title);

		if (Dialogresult == EAppReturnType::Yes)
		{
			A->ResetChildList();

			//*Update list view
			UpdateFXTParentList();
		}
	}
	
	return FReply::Handled();
}

FReply SFXTParent::OnClickedRB_GotoChild(const TSharedRef<SRowButton>& outBTN)
{
	//get client for camera
	FEditorViewportClient* client = (FEditorViewportClient*)GEditor->GetActiveViewport()->GetClient();
	if (client) {

		//*Get actor of row
		const FString& outLabel = outBTN.Get().GetRowLabel();
		AActor* A = FXTC::GetActorByLabel<AActor>(outLabel);

		if (FXTC::chkA(A)) {
			//make camera destination
			FVector Destination = A->GetActorLocation() - client->GetViewRotation().Vector() * 128.0f;

			//Set editor camera location
			client->SetViewLocation(Destination);

			//select target actor
			GEditor->SelectNone(true, true, true);
			GEditor->SelectActor(A, true, true, true, true);
		}
	}

	return FReply::Handled();
}

FReply SFXTParent::OnClickedRB_RemoveChild(const TSharedRef<SRowButton>& outBTN)
{
	if (!FXTParentList->GetNumItemsSelected() == 1) return FReply::Handled();

	//*Get selected parent actor
	TArray<TSharedPtr<FXTParentListItemType>> SelectedParents = FXTParentList->GetSelectedItems();

	const FString& outLabel = SelectedParents[0].Get()->Label;
	AFXTParent* A = FXTC::GetActorByLabel<AFXTParent>(outLabel);

	//*Remove child
	if (FXTC::chkA(A)) {
		const FString& TargetLabel = outBTN.Get().GetRowLabel();
		A->RemoveChildByLabel(TargetLabel);
		
		//*Update list view
		UpdateFXTParentList();
	}

	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FXTParentListItemType::FXTParentListItemType(AFXTParent* InActor)
{
	if (InActor) {
		Label = InActor->GetActorLabel();
	}
}

FXTParentListItemType::FXTParentListItemType(AActor* InActor)
{
	if (InActor) {
		Label = InActor->GetActorLabel();
	}
}
