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

	auto TXT_CreateNewParentMessage_Lam = [this] {
		return FXTC::T(TB_NewParentNameOutputMessage);
	};
	auto TXT_CreateNewParentMessage_Attr = TAttribute<FText>::Create(
		TAttribute<FText>::FGetter::CreateLambda(TXT_CreateNewParentMessage_Lam));

	//*Property
	float ListViewWidth = 210.0f;
	float TB_NewParentNameWidth = 175.0f;

	ChildSlot.Padding(4.f)
	[
		SNew(SBorder).BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder")).Padding(4.f)[
			SNew(SBox).VAlign(VAlign_Fill).HAlign(HAlign_Fill)[
				SNew(SVerticalBox)
				//*Tool pannel
				+ SVerticalBox::Slot().AutoHeight()[
					SNew(SVerticalBox)
					//*Add Parent
					+ SVerticalBox::Slot().AutoHeight()[
						SNew(SHorizontalBox)
						//Create new parent button
						+ SHorizontalBox::Slot().Padding(0.f, 0.f, 4.f, 4.f).AutoWidth()[
							SNew(SFXTButton).OnClicked(this, &SFXTParent::OnClicked_CreateNewParent)
							.bUseImage(true)
							.Image(FXTStyle::Get().GetBrush("FXT.Icon24"))
							.InitialColor(FXTStyle::Clr_Default())
							.ToolTipText(FXTC::T(BTN_CREATEPARENT_TOOLTIP))
							.ButtonStyle(&FEditorStyle::Get(), "EditorViewportToolBar.MenuButton")
							]//-SHorizontalBox::Slot()
						//Create new parent utils
						+ SHorizontalBox::Slot().MaxWidth(TB_NewParentNameWidth)[
							SNew(SVerticalBox)
							+ SVerticalBox::Slot().AutoHeight()[
								SNew(SHorizontalBox)
								+ SHorizontalBox::Slot()[
									SAssignNew(TB_NewParentName, SEditableTextBox)
									.HintText(FXTC::T("Parent Name"))
								]
								//reset custom name text box
								+ SHorizontalBox::Slot().AutoWidth()[
									SNew(SVerticalBox)
									+ SVerticalBox::Slot().AutoHeight()[
										SNew(SFXTButton).OnClicked(this, &SFXTParent::OnClicked_ResetCustomName)
										.bUseImage(true)
										.Image(FEditorStyle::GetBrush("PropertyWindow.DiffersFromDefault"))
										.InitialColor(FXTStyle::Clr_Default())
										.ButtonStyle(FEditorStyle::Get(), "NoBorder")
									]
								]
							]
							+ SVerticalBox::Slot().AutoHeight()[
								SNew(STextBlock).Text(TXT_CreateNewParentMessage_Attr)
							]
						]//-SHorizontalBox::Slot()		
					]//-SVerticalBox::Slot()
				]//-SVerticalBox::Slot()
				+ SVerticalBox::Slot()[
					SNew(SHorizontalBox)
					//*FXTParentList
					+ SHorizontalBox::Slot().MaxWidth(ListViewWidth)[
						SNew(SBorder)[
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
					+ SHorizontalBox::Slot().MaxWidth(ListViewWidth)[
						SNew(SBorder).Visibility(Vis_EditChildList_Attr)[
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
	TB_NewParentNameOutputMessage = "";

	//Check name dupling
	bool bNameDupling = false;
	FString CustomName = TB_NewParentName->GetText().ToString();
	if (!CustomName.IsEmpty()) {
		TArray<AFXTParent*> AllParents;
		FXTC::Itr<AFXTParent>(AllParents);
		for (AFXTParent* itr : AllParents){
			if (FXTC::chkA(itr) && itr->GetActorLabel() == CustomName) {
				bNameDupling = true;
				TB_NewParentNameOutputMessage = "Failed : Already exist name.";
				break;
			}
		}
	}

	FEditorViewportClient* client = (FEditorViewportClient*)GEditor->GetActiveViewport()->GetClient();
	if (client && !bNameDupling) {
		//Get spawn position
		FVector EditorCameraDirection = client->GetViewRotation().Vector();
		FVector EditorCameraPosition = client->GetViewLocation();
		FVector SpawnLocation = EditorCameraPosition + (EditorCameraDirection * 128.0f);

		FTransform SpawnTransform = FTransform();
		SpawnTransform.SetLocation(SpawnLocation);

		//Spawn actor
		AFXTParent* SpawnedActor = FXTC::AddActor<AFXTParent>(SpawnTransform);

		//Set Actor label
		if (!CustomName.IsEmpty()) SpawnedActor->SetActorLabel(CustomName);

		TB_NewParentNameOutputMessage = "Spawned : " + SpawnedActor->GetActorLabel();
	}

	return FReply::Handled();
}

FReply SFXTParent::OnClicked_ResetCustomName()
{
	TB_NewParentName->SetText(FXTC::T(""));

	return FReply::Handled();
}

TSharedRef<ITableRow> SFXTParent::OnGenerateRowFXTParentList(TSharedPtr<FXTParentListItemType> InItem, const TSharedRef<STableViewBase>& OwnerTable)
{
	AFXTParent* A = FXTC::GetActorByLabel<AFXTParent>(InItem.Get()->Label);
	bool LastHidden = A->GetChildHidden();

	//Num of childs
	int32 NumOfChilds = A->GetNumOfChilds();
	FText NumOfChildsTEXT = FXTC::T( "(" + FString::FromInt(NumOfChilds) + ")");

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
			+ SHorizontalBox::Slot().AutoWidth().HAlign(HAlign_Fill).VAlign(VAlign_Center)[
				SNew(STextBlock).Text(FXTC::T(InItem.Get()->Label)).TextStyle(FFXTStyle::GetTBStyle("ListViewText.Row"))
			]
			//Num of childs
			+ SHorizontalBox::Slot().Padding(2.f, 0.f).AutoWidth().HAlign(HAlign_Fill).VAlign(VAlign_Bottom)[
				SNew(STextBlock).Visibility(NumOfChilds > 0 ? EVisibility::Visible : EVisibility::Collapsed)
				.Text(NumOfChildsTEXT)
				.Font(FEditorStyle::Get().GetFontStyle("FontAwesome.9"))
				.ColorAndOpacity(FXTStyle::Clr_Hidden())
			]
			//Add child button
			+ SHorizontalBox::Slot().HAlign(HAlign_Right)[
				SNew(SRowButton).OnClicked(this, &SFXTParent::OnClickedRB_AddChild).RowLabel(InItem.Get()->Label)
				.bUseImage(true)
				.Image(FEditorStyle::GetBrush("PropertyWindow.Button_Use"))
				.ToolTipText(FXTC::T(BTN_ADDCHILDFROMSELECTED_TOOLTIP))
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

TSharedRef<ITableRow> SFXTParent::OnGenerateRowChildListView(TSharedPtr<FXTParentListItemType> InItem, const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(STableRow< TSharedPtr<FXTParentListItemType> >, OwnerTable)
	.Padding(2.f)
	[
		SNew(SHorizontalBox)
		//Label
		+ SHorizontalBox::Slot().AutoWidth().HAlign(HAlign_Fill).VAlign(VAlign_Center)[
			SNew(STextBlock).Text(FXTC::T(InItem.Get()->Label)).TextStyle(FFXTStyle::GetTBStyle("ListViewText.Row"))
		]
		//remove child button
		+ SHorizontalBox::Slot().HAlign(HAlign_Right)[
			SNew(SRowButton).OnClicked(this, &SFXTParent::OnClickedRB_RemoveChild).RowLabel(InItem.Get()->Label)
			.bUseImage(true)
			.Image(FEditorStyle::GetBrush("PropertyWindow.Button_Delete"))
			.ToolTipText(FXTC::T(BTN_REMOVECHILD_TOOLTIP))
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
	if (FXTC::chkA(A)) {
		A->ResetChildList();
		
		//*Update list view
		UpdateFXTParentList();
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
