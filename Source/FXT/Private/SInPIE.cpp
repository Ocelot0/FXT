//=================================================
// Written by Lee Gil Su
// Copyright 2018. Lee Gil Su. all rights reserved.
//=================================================

#include "SInPIE.h"
#include "SlateOptMacros.h"
#include "FXTCore.h"

SInPIE::~SInPIE() 
{
	FFXTDelegate::OnAutoSequencePlay.RemoveAll(this);
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SInPIE::Construct(const FArguments& InArgs)
{
	//delegate binding
	FFXTDelegate::OnAutoSequencePlay.AddSP(this, &SInPIE::OnAutoSequencePlay);

	//*Target Level seq label
	auto TXT_TargetLevelSeqActorLabel_Lam = [this] {
		if (FXTC::chkA(TargetLevelSequencer)) {
			return FXTC::T(TargetLevelSequencer->GetActorLabel());
		}
		return FXTC::T(CB_SEQUENCERAUTOPLAY_DEFAULT);
	};
	auto TXT_TargetLevelSeqActorLabel_Attr = TAttribute<FText>::Create(
		TAttribute<FText>::FGetter::CreateLambda(TXT_TargetLevelSeqActorLabel_Lam));

	auto ENABLE_SequencerOptions_Lam = [this] {
		if (CurrentSequencePlayer && CurrentSequencePlayer->IsPlaying()) {
			return false;
		}
		return true;
	};
	auto ENABLE_SequencerOptions_Attr = TAttribute<bool>::Create(
		TAttribute<bool>::FGetter::CreateLambda(ENABLE_SequencerOptions_Lam));

	auto ENABLE_SequencerTimeline_Lam = [this] {
		if (!CurrentSequencePlayer) return false;
		if (CurrentSequencePlayer && CurrentSequencePlayer->IsPlaying()) return false;
		return true;
	};
	auto ENABLE_SequencerTimeline_Attr = TAttribute<bool>::Create(
		TAttribute<bool>::FGetter::CreateLambda(ENABLE_SequencerTimeline_Lam));

	auto ENABLE_SequencerBtn_Lam = [this] {
		return CurrentSequencePlayer ? true : false;
	};
	auto ENABLE_SequencerBtn_Attr = TAttribute<bool>::Create(
		TAttribute<bool>::FGetter::CreateLambda(ENABLE_SequencerBtn_Lam));

	auto VIS_SeqcontrolPlayBtn_Lam = [this] {
		if (CurrentSequencePlayer && CurrentSequencePlayer->IsPlaying()) {
			return EVisibility::Collapsed;
		}
		return EVisibility::Visible;
	};
	auto VIS_SeqcontrolPlayBtn_Attr = TAttribute<EVisibility>::Create(
		TAttribute<EVisibility>::FGetter::CreateLambda(VIS_SeqcontrolPlayBtn_Lam));

	auto VIS_SeqcontrolPauseBtn_Lam = [this] {
		if (!CurrentSequencePlayer) {
			return EVisibility::Collapsed;
		}
		if (CurrentSequencePlayer && !CurrentSequencePlayer->IsPlaying()) {
			return EVisibility::Collapsed;
		}
		return EVisibility::Visible;
	};
	auto VIS_SeqcontrolPauseBtn_Attr = TAttribute<EVisibility>::Create(
		TAttribute<EVisibility>::FGetter::CreateLambda(VIS_SeqcontrolPauseBtn_Lam));

	//time line
	auto FLOAT_TimelineMin_Lam = [this] {
		if (CurrentSequencePlayer) {
			return CurrentSequencePlayer->GetPlaybackStart();
		}
		return 0.f;
	};
	auto FLOAT_TimelineMin_Attr = TAttribute<TOptional<float>>::Create(
		TAttribute<TOptional<float>>::FGetter::CreateLambda(FLOAT_TimelineMin_Lam));

	auto FLOAT_TimelineMax_Lam = [this] {
		if (CurrentSequencePlayer) {
			return CurrentSequencePlayer->GetPlaybackEnd();
		}
		return 0.f;
	};
	auto FLOAT_TimelineMax_Attr = TAttribute<TOptional<float>>::Create(
		TAttribute<TOptional<float>>::FGetter::CreateLambda(FLOAT_TimelineMax_Lam));

	auto FLOAT_TimelineCurrent_Lam = [this] {
		if (CurrentSequencePlayer) {
			return CurrentSequencePlayer->GetPlaybackPosition();
		}
		return 0.f;
	};
	auto FLOAT_TimelineCurrent_Attr = TAttribute<float>::Create(
		TAttribute<float>::FGetter::CreateLambda(FLOAT_TimelineCurrent_Lam));
	
	ChildSlot.Padding(4.0f)
	[
		SNew(SVerticalBox)
		//PIE mode
		+ SVerticalBox::Slot()[
			SNew(SVerticalBox)
			//*Stop PIE
			+ SVerticalBox::Slot().Padding(0.f, 4.f).AutoHeight()[
				SNew(SBorder).BorderImage(FEditorStyle::GetBrush("ToolPanel.DarkGroupBorder"))[
					SNew(SHorizontalBox)
					//Stop PIE button
					+ SHorizontalBox::Slot().AutoWidth()[
						SNew(SFXTButton)
						.OnClicked(this, &SInPIE::BTN_StopPIE)
						.bUseImage(true)
						.Image(FXTStyle::Get().GetBrush("EditorIcon.PIEStop"))
						.ToolTipText(FXTC::T(BTN_STOPPIE_TOOLTIP))
						.ButtonStyle(&FEditorStyle::Get(), "FlatButton")
					]//-SHorizontalBox::Slot()
					//Stop PIE description
					+ SHorizontalBox::Slot().Padding(8.f, 0.f).AutoWidth().VAlign(VAlign_Center)[
						SNew(SVerticalBox)
						+SVerticalBox::Slot().AutoHeight()[
							SNew(STextBlock)
							.Text(FXTC::T(DESC_PIEMODE_0))
							.TextStyle(FXTStyle::GetTBStyle("WarningText"))
						]
						+ SVerticalBox::Slot().AutoHeight()[
							SNew(STextBlock)
							.Text(FXTC::T(DESC_PIEMODE_1))
							.TextStyle(FXTStyle::GetTBStyle("WarningText"))
						]
					]
				]
			]//-SVerticalBox::Slot() Stop PIE

			//* Sequencer controller
			+ SVerticalBox::Slot().Padding(0.f, 4.f).AutoHeight()[
				SNew(SBorder).BorderImage(FEditorStyle::GetBrush("ToolPanel.DarkGroupBorder"))[
					SNew(SVerticalBox)
					//Sequencer controller options
					+ SVerticalBox::Slot().Padding(4.f, 0.f).AutoHeight()[
						SNew(SHorizontalBox)
						//Select Levelsequencer
						+ SHorizontalBox::Slot().MaxWidth(100.0f)[
							SNew(SBorder).BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder")).Padding(0.f)[
								SNew(SFXTComboButton)
								.Text(TXT_TargetLevelSeqActorLabel_Attr)
								.TextStyle(FXTStyle::GetTBStyle("DefaultText"))
								.bUseImage(false)
								.ToolTipText(FXTC::T(CB_SEQUENCERAUTOPLAY_TOOLTIP))
								.OnClicked(this, &SInPIE::OnClickedRB_TargetSeq)
								.OnUpdateSource(this, &SInPIE::OUS_TargetSeq)
								.OnItemSelect(this, &SInPIE::OIS_TargetSeq)
								.IsEnabled(ENABLE_SequencerOptions_Attr)
							]
						]
						//Loop num
						+ SHorizontalBox::Slot().MaxWidth(35.0f).Padding(4.f, 0.f)[
							SNew(SSpinBox<int32>).ContentPadding(0.f)
							.ToolTipText(FXTC::T(SB_HOWMANYTIMESLOOP_TOOLTIP))
							.MinValue(-1).MaxValue(999).Delta(1)
							.Value(LoopHowManyTimes)
							.OnValueChanged(this, &SInPIE::OVC_LoopHowManyTimes)
							.IsEnabled(ENABLE_SequencerOptions_Attr)
						]
					]

					//Sequencer timeline
					+ SVerticalBox::Slot().Padding(0.f, 4.f).AutoHeight()[
						SNew(SHorizontalBox)
						+SHorizontalBox::Slot().MaxWidth(140.0f).Padding(4.f, 0.f)[
							SAssignNew(SeqTimeline, SSpinBox<float>).ContentPadding(0.f)
							.ToolTipText(FXTC::T(SB_HOWMANYTIMESLOOP_TOOLTIP))
							.MinValue(FLOAT_TimelineMin_Attr).MaxValue(FLOAT_TimelineMax_Attr).Delta(0.01f)
							.Value(FLOAT_TimelineCurrent_Attr)
							.OnValueChanged(this, &SInPIE::OVC_SeqPlaybackPosition)
							.IsEnabled(ENABLE_SequencerTimeline_Attr)
						]
					]

					//Sequencer controller buttons
					+SVerticalBox::Slot().AutoHeight()[
						SNew(SHorizontalBox)
						//goto front sequencer button
						+ SHorizontalBox::Slot().Padding(4.f).AutoWidth()[
							SNew(SFXTButton)
							.OnClicked(this, &SInPIE::BTN_GotoFrontSeq)
							.bUseImage(true)
							.Image(FXTStyle::Get().GetBrush("EditorIcon.GotoFront"))
							.ToolTipText(FXTC::T(BTN_SEQGOTOFRONT_TOOLTIP))
							.ButtonStyle(&FEditorStyle::Get(), "FlatButton")
							.IsEnabled(ENABLE_SequencerBtn_Attr)
						]//-SHorizontalBox::Slot()
						//Play sequencer button
						+ SHorizontalBox::Slot().Padding(4.f).AutoWidth()[
							SNew(SBox).Visibility(VIS_SeqcontrolPlayBtn_Attr)[
								SNew(SFXTButton)
								.OnClicked(this, &SInPIE::BTN_PlaySeq)
								.bUseImage(true)
								.Image(FXTStyle::Get().GetBrush("EditorIcon.PlaySeq"))
								.ToolTipText(FXTC::T(BTN_SEQPLAY_TOOLTIP))
								.ButtonStyle(&FEditorStyle::Get(), "FlatButton")
								.IsEnabled(ENABLE_SequencerBtn_Attr)
							]
						]//-SHorizontalBox::Slot()
						 //Play sequencer button
						+ SHorizontalBox::Slot().Padding(4.f).AutoWidth()[
							SNew(SBox).Visibility(VIS_SeqcontrolPauseBtn_Attr)[
								SNew(SFXTButton)
								.OnClicked(this, &SInPIE::BTN_PauseSeq)
								.bUseImage(true)
								.Image(FXTStyle::Get().GetBrush("EditorIcon.PauseSeq"))
								.ToolTipText(FXTC::T(BTN_SEQPAUSE_TOOLTIP))
								.ButtonStyle(&FEditorStyle::Get(), "FlatButton")
								.IsEnabled(ENABLE_SequencerBtn_Attr)
							]
						]//-SHorizontalBox::Slot()
					]
				]
			]

		]//-SVerticalBox::Slot()
	];//-ChildSlot
	
}

void SInPIE::Tick(const FGeometry & AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
}

FReply SInPIE::BTN_StopPIE()
{
	GEditor->RequestEndPlayMap();

	return FReply::Handled();
}

ULevelSequencePlayer* SInPIE::GetLevelSequencePlayer(ALevelSequenceActor* LevelSequenceActor)
{
	if (!LevelSequenceActor) return nullptr;

	//Get Levelsequence
	const ULevelSequence* LevelSequence = LevelSequenceActor->GetSequence();

	//Get LevelSequencePlayer
	ULevelSequencePlayer* ResultLevelSequencePlayer = nullptr;
	for (TObjectIterator<ULevelSequencePlayer> i; i; ++i) {
		if (i->GetSequence() == LevelSequence) {
			ResultLevelSequencePlayer = *i;
			break;
		}
	}

	return ResultLevelSequencePlayer;
}

void SInPIE::OnAutoSequencePlay(ALevelSequenceActor* InTargetLevelSequencer)
{
	if (FXTC::chkA(InTargetLevelSequencer)) {
		TargetLevelSequencer = InTargetLevelSequencer;
		CurrentSequencePlayer = GetLevelSequencePlayer(TargetLevelSequencer);
	}
}

FReply SInPIE::OnClickedRB_TargetSeq()
{
	return FReply::Handled();
}

void SInPIE::OUS_TargetSeq(TArray<TSharedPtr<FString>>& outItem)
{
	outItem.Empty();

	//Get LevelSequenceActor in level
	TArray<ALevelSequenceActor*> LSAs;
	FXTC::Itr<ALevelSequenceActor>(LSAs);

	if (LSAs.Num() > 0) {
		for (ALevelSequenceActor* i : LSAs)
		{
			if (i->SequencePlayer) {
				outItem.Add(MakeShareable(new FString(i->GetActorLabel())));
			}
		}
	}
}

void SInPIE::OIS_TargetSeq(FString & outLabel)
{
	ALevelSequenceActor* LSA = FXTC::GetActorByLabel<ALevelSequenceActor>(outLabel);

	if (FXTC::chkA(LSA)) {
		TargetLevelSequencer = LSA;
		CurrentSequencePlayer = GetLevelSequencePlayer(TargetLevelSequencer);
	}
}

void SInPIE::OVC_LoopHowManyTimes(int32 NewValue)
{
	LoopHowManyTimes = NewValue;
}

void SInPIE::OVC_SeqPlaybackPosition(float NewValue)
{
	if (CurrentSequencePlayer) {
		CurrentSequencePlayer->SetPlaybackPosition(NewValue);
	}
}

FReply SInPIE::BTN_GotoFrontSeq()
{
	if (CurrentSequencePlayer) {
		CurrentSequencePlayer->Stop();
		CurrentSequencePlayer->JumpToPosition(CurrentSequencePlayer->GetPlaybackStart());
	}

	return FReply::Handled();
}

FReply SInPIE::BTN_PlaySeq()
{
	if (CurrentSequencePlayer) {
		//if current playback position is end, goto front
		if (CurrentSequencePlayer->GetPlaybackPosition() >= CurrentSequencePlayer->GetPlaybackEnd()) {		
			CurrentSequencePlayer->JumpToPosition(CurrentSequencePlayer->GetPlaybackStart());
		}
		
		CurrentSequencePlayer->PlayLooping(LoopHowManyTimes);
	}

	return FReply::Handled();
}

FReply SInPIE::BTN_PauseSeq()
{
	if (CurrentSequencePlayer) {
		CurrentSequencePlayer->Pause();
	}

	return FReply::Handled();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
