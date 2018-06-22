// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FXTParent.generated.h"

UCLASS()
class FXT_API AFXTParent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFXTParent();

	UPROPERTY(BlueprintReadOnly, Category = "FXT")
	class USceneComponent* RComp;

	UPROPERTY(BlueprintReadOnly, Category = "FXT")
	UBillboardComponent* EditorBillboardComponent;

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//*Billboard
	//Load texture from file
	UTexture2D* LoadTexture2DFromFile(const FString& FullFilePath);

	//Update Editor billboard
	void UpdateEditorBillboard();

	//*Child hidden
private:
	UPROPERTY(VisibleAnywhere, Category = "FXT")
		bool bChildHidden = false;

	UPROPERTY(VisibleAnywhere, Category = "FXT")
		TArray<AActor*> ChildList;

public:
	UFUNCTION()
		FORCEINLINE bool GetChildHidden() { return bChildHidden; }
	
	UFUNCTION()
		void SetChildHidden(bool NewHidden = true);

	UFUNCTION()
		void GetChildList(TArray<AActor*>& outchildlist) { outchildlist = ChildList; }

	
	UFUNCTION()
		//@ ClassFName : without class prefix ex)ACharacter > Character
		bool GetActorsFromChildListByClassFName(TArray<AActor*>& outResult, FName ClassFName = FName(TEXT("Actor")));

	template< class T >
	bool GetActorsFromChildList(TArray<T*>& outResult);

	UFUNCTION()
		int32 GetNumOfChilds() { return ChildList.Num(); }

	//refresh child list. remove nulls
	UFUNCTION()
		void RefreshChildList();

	UFUNCTION()
		void ResetChildList();

	UFUNCTION()
		void RemoveChildByLabel(FString TargetLabel);

	UFUNCTION()
		void AddChildFromSelectedActors();


};