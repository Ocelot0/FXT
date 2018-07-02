//=================================================
// Written by Lee Gil Su
// Copyright 2018. Lee Gil Su. all rights reserved.
//=================================================
#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "DeclarativeSyntaxSupport.h"

class FXT_API SPIETool : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SPIETool)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	~SPIETool();

private:
	//*Play button
	FReply BTN_Simulate();
	FReply BTN_PlayActiveViewport();
	FReply BTN_PlayNewWindow();
	TSubclassOf<AGameModeBase> LastGameMode;

	void Play(bool bSimulate, bool bNewWindow = false);
	void SetImmersiveMode(TSharedPtr<ILevelViewport> LevelViewport, bool bNewImmersive);

	bool bInPIE = false;
	void OnBeginPIE(const bool bBeginPIE);
	void PostPIEStarted(const bool bBeginPIE);
	void OnEndPIE(const bool bEndPIE);
	void OnFullyEndPIE();
	FTimerHandle PIEFullyFinishTimerHandle;


private:
	//*PIE options 

	//immersive on pie
	bool bImmersiveOnPIE = false;
	void CB_bImmersiveOnPIE(ECheckBoxState NewValue);

	//sequencer auto play on pie
	bool bSeqPlayOnPIE = false;
	void CB_bSeqPlayOnPIE(ECheckBoxState NewValue);
	class ALevelSequenceActor* TargetLevelSequencer;

	FReply OnClickedRB_SeqAutoPlay();
	void OUS_SeqAutoPlay(TArray<TSharedPtr<FString>>& outItem);
	void OIS_SeqAutoPlay(FString& outLabel);

	//seq autoplay : how many times loop
	int32 LoopHowManyTimes = -1;
	void OVC_LoopHowManyTimes(int32 NewValue);

};
