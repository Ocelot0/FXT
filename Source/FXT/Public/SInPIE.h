//=================================================
// Written by Lee Gil Su
// Copyright 2018. Lee Gil Su. all rights reserved.
//=================================================

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "DeclarativeSyntaxSupport.h"


class FXT_API SInPIE : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SInPIE)
	{}
	SLATE_END_ARGS()

	~SInPIE();
	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime);

private:
	FReply BTN_StopPIE();

private:
	//*Sequencer controller
	class ALevelSequenceActor* TargetLevelSequencer;
	ULevelSequencePlayer* CurrentSequencePlayer;
	ULevelSequencePlayer* GetLevelSequencePlayer(ALevelSequenceActor* LevelSequenceActor);

	void OnAutoSequencePlay(ALevelSequenceActor* InTargetLevelSequencer);

	FReply OnClickedRB_TargetSeq();
	void OUS_TargetSeq(TArray<TSharedPtr<FString>>& outItem);
	void OIS_TargetSeq(FString& outLabel);

	//seq autoplay : how many times loop
	int32 LoopHowManyTimes = -1;
	void OVC_LoopHowManyTimes(int32 NewValue);

	//seq autoplay : position
	TSharedPtr<SSpinBox<float>> SeqTimeline;
	void OVC_SeqPlaybackPosition(float NewValue);

	FReply BTN_GotoFrontSeq();
	FReply BTN_PlaySeq();
	FReply BTN_PauseSeq();


};
