//=================================================
// Written by Lee Gil Su
// Copyright 2018. Lee Gil Su. all rights reserved.
//=================================================

#include "SPIETool.h"
#include "SlateOptMacros.h"
#include "FXTCore.h"

SPIETool::~SPIETool() 
{
	FEditorDelegates::BeginPIE.RemoveAll(this);
	FEditorDelegates::EndPIE.RemoveAll(this);
	FEditorDelegates::PostPIEStarted.RemoveAll(this);
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SPIETool::Construct(const FArguments& InArgs)
{
	FEditorDelegates::BeginPIE.AddSP(this, &SPIETool::OnBeginPIE);
	FEditorDelegates::PostPIEStarted.AddSP(this, &SPIETool::PostPIEStarted);
	FEditorDelegates::EndPIE.AddSP(this, &SPIETool::OnEndPIE);

	//*Target Level seq label
	auto TXT_TargetLevelSeqActorLabel_Lam = [this] {
		if (FXTC::chkA(TargetLevelSequencer)) {
			return FXTC::T(TargetLevelSequencer->GetActorLabel());
		}
		return FXTC::T(CB_SEQUENCERAUTOPLAY_DEFAULT);
	};
	auto TXT_TargetLevelSeqActorLabel_Attr = TAttribute<FText>::Create(
		TAttribute<FText>::FGetter::CreateLambda(TXT_TargetLevelSeqActorLabel_Lam));

	ChildSlot
	[
		SNew(SBorder).BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder")).Padding(4.f)[
			SNew(SBox).VAlign(VAlign_Fill).HAlign(HAlign_Fill)[

				SNew(SVerticalBox)
				+ SVerticalBox::Slot().AutoHeight()[
					SNew(SHorizontalBox) 
					//Simulate
					+SHorizontalBox::Slot().AutoWidth()[
						SNew(SFXTButton).OnClicked(this, &SPIETool::BTN_Simulate)
							.bUseImage(true)
							.Image(FXTStyle::Get().GetBrush("EditorIcon.Simulate"))
							.ToolTipText(FXTC::T(BTN_SIMULATE_TOOLTIP))
							.ButtonStyle(&FEditorStyle::Get(), "FlatButton")
					]//-SHorizontalBox::Slot()
					//Play in viewport
					+ SHorizontalBox::Slot().AutoWidth()[
						SNew(SFXTButton).OnClicked(this, &SPIETool::BTN_PlayActiveViewport)
							.bUseImage(true)
							.Image(FXTStyle::Get().GetBrush("EditorIcon.PlayActiveViewport"))
							.ToolTipText(FXTC::T(BTN_PLAY_TOOLTIP))
							.ButtonStyle(&FEditorStyle::Get(), "FlatButton")
					]//-SHorizontalBox::Slot()
					//Play new window
					+ SHorizontalBox::Slot().AutoWidth()[
						SNew(SFXTButton).OnClicked(this, &SPIETool::BTN_PlayNewWindow)
							.bUseImage(true)
							.Image(FXTStyle::Get().GetBrush("EditorIcon.PlayNewWindow"))
							.ToolTipText(FXTC::T(BTN_PLAYNEWWINDOW_TOOLTIP))
							.ButtonStyle(&FEditorStyle::Get(), "FlatButton")
					]//-SHorizontalBox::Slot()
				]//-SVerticalBox::Slot() ;Main

				+ SVerticalBox::Slot().AutoHeight()[
					SNew(SSeparator)
				]//-SVerticalBox::Slot()

				
				+ SVerticalBox::Slot()[

						SNew(SScrollBox)
						//Immersive on pie option
						+SScrollBox::Slot().Padding(0., 4.f)[
							SNew(SBorder).BorderImage(FEditorStyle::GetBrush("ToolPanel.DarkGroupBorder")).Padding(4.f)[
								SNew(SVerticalBox) +SVerticalBox::Slot().AutoHeight()[
									SNew(SHorizontalBox)
									+ SHorizontalBox::Slot().AutoWidth()[
										SNew(SCheckBox)
										.OnCheckStateChanged(this, &SPIETool::CB_bImmersiveOnPIE)
										.IsChecked(bImmersiveOnPIE ? ECheckBoxState::Checked : ECheckBoxState::Unchecked)
										.ToolTipText(FXTC::T(CB_IMMERSIVEONPIE))
									]
									+ SHorizontalBox::Slot().Padding(2.f).AutoWidth()[
										SNew(STextBlock)
										.Text(FXTC::T(CB_IMMERSIVEONPIE))
										.TextStyle(FXTStyle::GetTBStyle("DefaultText"))
									]
								]
							]
						]//-SScrollBox::Slot()
						//Sequencer auto play
						+ SScrollBox::Slot().Padding(0., 4.f)[
							SNew(SBorder).BorderImage(FEditorStyle::GetBrush("ToolPanel.DarkGroupBorder")).Padding(4.f)[
								SNew(SVerticalBox)
								//select sequencer
								+ SVerticalBox::Slot().AutoHeight()[
									SNew(SHorizontalBox)
									+ SHorizontalBox::Slot().AutoWidth()[
										SNew(SCheckBox)
										.OnCheckStateChanged(this, &SPIETool::CB_bSeqPlayOnPIE)
										.IsChecked(bSeqPlayOnPIE ? ECheckBoxState::Checked : ECheckBoxState::Unchecked)
										.ToolTipText(FXTC::T(CB_SEQUENCERAUTOPLAY))
									]
									+ SHorizontalBox::Slot().MaxWidth(100.0f)[
										SNew(SBorder).BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder")).Padding(0.f)[
											SNew(SFXTComboButton)
											.Text(TXT_TargetLevelSeqActorLabel_Attr)
											.TextStyle(FXTStyle::GetTBStyle("DefaultText"))
											.bUseImage(false)
											.ToolTipText(FXTC::T(CB_SEQUENCERAUTOPLAY_TOOLTIP))
											.OnClicked(this, &SPIETool::OnClickedRB_SeqAutoPlay)
											.OnUpdateSource(this, &SPIETool::OUS_SeqAutoPlay)
											.OnItemSelect(this, &SPIETool::OIS_SeqAutoPlay)
										]
									]
									+ SHorizontalBox::Slot().Padding(2.f).AutoWidth()[
										SNew(STextBlock)
										.Text(FXTC::T(CB_SEQUENCERAUTOPLAY))
										.TextStyle(FXTStyle::GetTBStyle("DefaultText"))
									]
								]//-SVerticalBox::Slot()
								//Loop num
								+ SVerticalBox::Slot().Padding(0.f, 2.f).AutoHeight()[
									SNew(SHorizontalBox)
									+ SHorizontalBox::Slot().MaxWidth(35.0f).Padding(1.f)[
										SNew(SSpinBox<int32>).ContentPadding(0.f)
										.ToolTipText(FXTC::T(SB_HOWMANYTIMESLOOP_TOOLTIP))
										.MinValue(-1).MaxValue(999).Delta(1)
										.Value(LoopHowManyTimes)
										.OnValueChanged(this, &SPIETool::OVC_LoopHowManyTimes)
									]
									+ SHorizontalBox::Slot().Padding(2.f, 4.f).AutoWidth()[
										SNew(STextBlock)
										.Text(FXTC::T(SB_HOWMANYTIMESLOOP))
										.TextStyle(FXTStyle::GetTBStyle("DefaultText"))
									]
								]//-SVerticalBox::Slot() ;Loop num
							]//-SBorder
						]//-SScrollBox::Slot()

				]//-SVerticalBox::Slot()

			]//-SBox
		]//-SBorder
	];

}
FReply SPIETool::BTN_Simulate()
{
	//Simulate
	Play(true, false);

	return FReply::Handled();
}

FReply SPIETool::BTN_PlayActiveViewport()
{
	//Play Active viewport
	Play(false, false);

	return FReply::Handled();
}

FReply SPIETool::BTN_PlayNewWindow()
{
	//Play New window
	Play(true, true);

	return FReply::Handled();
}

void SPIETool::Play(bool bSimulate, bool bNewWindow)
{
	if (!bInPIE)
	{
		UWorld* const World = GEditor->GetEditorWorldContext().World();
		ULevelEditorPlaySettings* PlayInSettings = GetMutableDefault<ULevelEditorPlaySettings>();

		//check
		if (!World) return;
		if (!PlayInSettings) return;

		//Get last settings
		//*Get last game mode
		LastGameMode = World->GetWorldSettings()->DefaultGameMode;

		//*Get PIE new window setting
		bool LastCenterNewWindow = PlayInSettings->CenterNewWindow;
		FIntPoint LastNewWindowPosition = PlayInSettings->NewWindowPosition;

		//switch settings
		{
			//* Switch game mode temporary
			World->GetWorldSettings()->DefaultGameMode = AFXTGameMode::StaticClass();

			//*Switch PIE window setting temporary
			PlayInSettings->CenterNewWindow = false;
			PlayInSettings->NewWindowPosition = FIntPoint(10, 10);
		}

		//*Start PIE
		if (bNewWindow) {
			//New window
			GEditor->PlayInEditor(World, false);
		}
		else
		{
			//Play in active viewport
			{
				FLevelEditorModule& LevelEditorModule = FModuleManager::Get().GetModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
				TSharedPtr<ILevelViewport> ActiveLevelViewport = LevelEditorModule.GetFirstActiveViewport();

				if (ActiveLevelViewport.IsValid())
				{
					//Play
					GEditor->RequestPlaySession(false, ActiveLevelViewport, bSimulate);

					//immersive mode
					if (bImmersiveOnPIE && ActiveLevelViewport.IsValid() && !ActiveLevelViewport.Get()->IsImmersive()) {
						SetImmersiveMode(ActiveLevelViewport, true);
					}
				}
				
			}
		}

		//reset settings to last setting
		{
			//*Reset PIE window settings
			PlayInSettings->CenterNewWindow = LastCenterNewWindow;
			PlayInSettings->NewWindowPosition = LastNewWindowPosition;
		}

	}
}

void SPIETool::SetImmersiveMode(TSharedPtr<ILevelViewport> LevelViewport, bool bNewImmersive)
{
	if (LevelViewport.IsValid()) {
		const bool bAllowAnimation = true;
		LevelViewport.Get()->MakeImmersive(bNewImmersive, bAllowAnimation);
	}
}

void SPIETool::OnBeginPIE(const bool bBeginPIE)
{
	//begin pie
	bInPIE = true;
}

void SPIETool::PostPIEStarted(const bool bBeginPIE)
{
	UWorld* const World = GEditor->GetEditorWorldContext().World();
	if (World) {
		//*Reset default game mode as last
		World->GetWorldSettings()->DefaultGameMode = LastGameMode;

		//Get Gamemode actor
		for (TObjectIterator<AFXTGameMode> i; i; ++i) {
			if (*i) {
				UE_LOG(LogTemp, Warning, TEXT("World valid [%s]"), *i->GetActorLabel());
			}
		}
		
		//TODO: auto start sequencer
		if (bSeqPlayOnPIE && FXTC::chkA(TargetLevelSequencer)) {

			//Get Levelsequence
			const ULevelSequence* TargetLevelSequence = TargetLevelSequencer->GetSequence();

			//Get LevelSequencePlayer
			ULevelSequencePlayer* TargetLevelSequencePlayer = nullptr;
			for (TObjectIterator<ULevelSequencePlayer> i; i; ++i) {
				if (i->GetSequence() == TargetLevelSequence) {
					TargetLevelSequencePlayer = *i;
					break;
				}
			}

			//*Play sequencer!
			if (TargetLevelSequence && TargetLevelSequencePlayer) {
				TargetLevelSequencePlayer->PlayLooping(LoopHowManyTimes);
				FFXTDelegate::OnAutoSequencePlay.Broadcast(TargetLevelSequencer);
			}

		}

	}
}

void SPIETool::OnEndPIE(const bool bEndPIE)
{
	//Start Timer until PIE fully finish
	GEditor->GetTimerManager().Get().SetTimer(
		PIEFullyFinishTimerHandle, FTimerDelegate::CreateSP(this, &SPIETool::OnFullyEndPIE), 0.03f, false, 0.03f);
}

void SPIETool::OnFullyEndPIE()
{
	GEditor->GetTimerManager()->ClearTimer(PIEFullyFinishTimerHandle);

	//end pie
	bInPIE = false;

	//imersive mode
	FLevelEditorModule& LevelEditorModule = FModuleManager::Get().GetModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));
	TSharedPtr<ILevelViewport> ActiveLevelViewport = LevelEditorModule.GetFirstActiveViewport();

	if (bImmersiveOnPIE && ActiveLevelViewport.IsValid() && ActiveLevelViewport.Get()->IsImmersive()) {
		SetImmersiveMode(ActiveLevelViewport, false);
	}

}

void SPIETool::CB_bImmersiveOnPIE(ECheckBoxState NewValue)
{
	bImmersiveOnPIE = (NewValue == ECheckBoxState::Checked) ? true : false;
}

void SPIETool::CB_bSeqPlayOnPIE(ECheckBoxState NewValue)
{
	bSeqPlayOnPIE = (NewValue == ECheckBoxState::Checked) ? true : false;
}

FReply SPIETool::OnClickedRB_SeqAutoPlay()
{
	return FReply::Handled();
}

void SPIETool::OUS_SeqAutoPlay(TArray<TSharedPtr<FString>>& outItem)
{
	outItem.Empty();

	TArray<ALevelSequenceActor*> LSAs;
	FXTC::Itr<ALevelSequenceActor>(LSAs);

	if (LSAs.Num() > 0) {
		for (ALevelSequenceActor* i : LSAs) 
		{
			outItem.Add(MakeShareable(new FString(i->GetActorLabel())));
		}
	}
}

void SPIETool::OIS_SeqAutoPlay(FString & outLabel)
{
	ALevelSequenceActor* LSA = FXTC::GetActorByLabel<ALevelSequenceActor>(outLabel);

	if (FXTC::chkA(LSA)) {
		TargetLevelSequencer = LSA;
	}
}

void SPIETool::OVC_LoopHowManyTimes(int32 NewValue)
{
	LoopHowManyTimes = NewValue;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
