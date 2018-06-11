// Fill out your copyright notice in the Description page of Project Settings.

#include "FXTParent.h"

#include "FXTCore.h"
#include "IImageWrapperModule.h"
#include "IImageWrapper.h"


// Sets default values
AFXTParent::AFXTParent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = RComp;

	EditorBillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("EditorBillboardComponent"));
	EditorBillboardComponent->SetupAttachment(RootComponent);
	EditorBillboardComponent->SetHiddenInGame(true);

	UpdateEditorBillboard();
}

void AFXTParent::OnConstruction(const FTransform & Transform)
{
	Super::OnConstruction(Transform);

	//* update billboard
	UpdateEditorBillboard();

	//* set child hidden when editor start as last hidden
	SetChildHidden(bChildHidden);
}

// Called when the game starts or when spawned
void AFXTParent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFXTParent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UTexture2D * AFXTParent::LoadTexture2DFromFile(const FString & FullFilePath)
{
	UTexture2D* LoadedTexture2D = nullptr;

	TArray<uint8> RawImageData;
	if (!FFileHelper::LoadFileToArray(RawImageData, *FullFilePath)) { //Attempt to load file
		return nullptr; //load fail
	}

	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);

	//Create UTexture2D
	if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(RawImageData.GetData(), RawImageData.Num()))
	{
		const TArray<uint8>* UncompressedBGRA = NULL;
		if (ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA)) {
			LoadedTexture2D = UTexture2D::CreateTransient(ImageWrapper->GetWidth(), ImageWrapper->GetHeight(), PF_B8G8R8A8);
			if (LoadedTexture2D) {
				void* TextureData = LoadedTexture2D->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
				FMemory::Memcpy(TextureData, UncompressedBGRA->GetData(), UncompressedBGRA->Num());
				LoadedTexture2D->PlatformData->Mips[0].BulkData.Unlock();
				LoadedTexture2D->UpdateResource();

				return LoadedTexture2D;
			}
		}
	}

	//fail, anyway.
	return nullptr;
}

void AFXTParent::UpdateEditorBillboard()
{
	FString TargetImageName = TEXT("FXT_Main_128.png");

	EditorBillboardComponent->SetSprite(LoadTexture2DFromFile(PLUGIN_RESOUCRES_PATH / TargetImageName));
}

void AFXTParent::SetChildHidden(bool NewHidden)
{
	bChildHidden = NewHidden;

	for (AActor* A : ChildList) {
		if(FXTC::chkA(A)) A->SetIsTemporarilyHiddenInEditor(NewHidden);
	}
}

void AFXTParent::RefreshChildList()
{
	TArray<int32> targetindecies;

	//*Find Null element
	if (ChildList.Num() > 0)
	{
		for (int32 i = 0; i < ChildList.Num(); i++)
		{
			if (!FXTC::chkA(ChildList[i])) {
				targetindecies.Add(i);
			}
		}
	}

	//*Remove Null elements
	if (targetindecies.Num() > 0)
	{
		for (int32 i = 0; i < targetindecies.Num(); i++) {
			ChildList.RemoveAt(targetindecies[i]);
		}
	}

}

void AFXTParent::ResetChildList()
{
	for (AActor* itr : ChildList) {
		if (FXTC::chkA(itr)) {
			//set visible
			itr->SetIsTemporarilyHiddenInEditor(false);

			//*Detach
			itr->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		}
	}

	ChildList.Empty();
}

void AFXTParent::RemoveChildByLabel(FString TargetLabel)
{
	int32 TargetIndex = -1;
	for (int32 i = 0; i < ChildList.Num(); i++)
	{
		if (FXTC::chkA(ChildList[i]) && ChildList[i]->GetActorLabel() == TargetLabel) {
			TargetIndex = i;
			break;
		}
	}

	if (TargetIndex >= 0 && TargetIndex < ChildList.Num()) {
		//set visible
		ChildList[TargetIndex]->SetIsTemporarilyHiddenInEditor(false);

		//*Detach
		ChildList[TargetIndex]->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		//remove from list
		ChildList.RemoveAt(TargetIndex);
	}
}

void AFXTParent::AddChildFromSelectedActors()
{
	//*Get Selected Actors
	if (GEditor->GetSelectedActorCount() > 0)
	{
		//Get Selection
		USelection* SelectedActors = GEditor->GetSelectedActors();

		//Get All Parents for prevent dupling
		TArray<AFXTParent*> Parents;
		FXTC::Itr<AFXTParent>(Parents);

		//Iterate Selection
		for (FSelectionIterator i(*SelectedActors); i; ++i) {
			//Cast to AActor
			AActor* A = CastChecked<AActor>(*i);
			if (FXTC::chkA(A) && A != this) {

				//Remove from another parents
				for (AFXTParent* itr : Parents) {
					itr->RemoveChildByLabel(A->GetActorLabel());
				}

				//Add to list
				ChildList.AddUnique(A);

				//*Attach
				A->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
			}
		}
	}
}

