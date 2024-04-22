// Copyright Epic Games, Inc. All Rights Reserved.

#include "DrugEmpireCharacter.h"
#include "DrugEmpireProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "InteractComponent.h"
#include "InventoryComponent.h"
#include "CharacterWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ADrugEmpireCharacter

ADrugEmpireCharacter::ADrugEmpireCharacter()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	InteractComponent = CreateDefaultSubobject<UInteractComponent>(TEXT("InteractComponent"));

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));

	InventoryComponent->OnInventoryUpdate.AddDynamic(this, &ADrugEmpireCharacter::InventoryUpdate);

	PlayerUsingUI = false;

}

void ADrugEmpireCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	ClientCreateCharacterWidget();
}

//////////////////////////////////////////////////////////////////////////// Input

void ADrugEmpireCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADrugEmpireCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADrugEmpireCharacter::Look);

		// Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ADrugEmpireCharacter::Interact);

		// Character Menu
		EnhancedInputComponent->BindAction(CharacterMenuAction, ETriggerEvent::Started, this, &ADrugEmpireCharacter::CharacterMenu);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void ADrugEmpireCharacter::Move(const FInputActionValue& Value)
{
	if (PlayerUsingUI) { return; }

	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ADrugEmpireCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ADrugEmpireCharacter::Interact() {

	UE_LOG(LogTemp, Warning, TEXT("[Interact] Player pressed interact key"));

	InteractComponent->Interact();

}

void ADrugEmpireCharacter::CharacterMenu_Implementation() {

	if (CharacterWidget == nullptr) { return; }

	if (CharacterWidget->IsVisible()) {
		CharacterWidget->SetVisibility(ESlateVisibility::Hidden);

		ToggleWidgetInput(false);
	} else {
		CharacterWidget->SetVisibility(ESlateVisibility::Visible);

		ToggleWidgetInput(true);
	}

	//if (CharacterWidget != nullptr) {
	//	this->InventoryComponent->OnInventoryUpdate.RemoveDynamic(CharacterWidget, &UCharacterWidget::RefreshInventory);

	//	CharacterWidget->RemoveFromParent();
	//	CharacterWidget = nullptr;

	//	ToggleWidgetInput(false);

	//	return;
	//}

	//CharacterWidget = Cast<UCharacterWidget>(CreateWidget(GetWorld(), CharacterWidgetClass));
	////CharacterWidget->SetOwningPlayer(this->GetController()->Pawn)

	//if (CharacterWidget != nullptr) {
	//	CharacterWidget->AddToViewport();

	//	ToggleWidgetInput(true);
	//}

}

void ADrugEmpireCharacter::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool ADrugEmpireCharacter::GetHasRifle()
{
	return bHasRifle;
}

void ADrugEmpireCharacter::ToggleWidgetInput(bool Show) {

	APlayerController* PC = Cast<APlayerController>(GetController());

	if (Show) {
		PC->SetInputMode(FInputModeGameAndUI());

		GetCharacterMovement()->MaxWalkSpeed = 0.f;
	} else {
		PC->SetInputMode(FInputModeGameOnly());

		GetCharacterMovement()->MaxWalkSpeed = 600.f;
	}

	PlayerUsingUI = Show;
	ServerChangePlayerMaxSpeed(GetCharacterMovement()->MaxWalkSpeed);

	PC->SetShowMouseCursor(Show);
	PC->bEnableMouseOverEvents = Show;

}

void ADrugEmpireCharacter::ServerChangePlayerMaxSpeed_Implementation(float NewSpeed) {

	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;

}

void ADrugEmpireCharacter::ClientCreateCharacterWidget_Implementation() {

	CharacterWidget = Cast<UCharacterWidget>(CreateWidget(GetWorld(), CharacterWidgetClass));
	CharacterWidget->SetVisibility(ESlateVisibility::Hidden);
	CharacterWidget->AddToViewport();

}

void ADrugEmpireCharacter::InventoryUpdate_Implementation() {

	UE_LOG(LogTemp, Warning, TEXT("Update called by %s"), *this->GetName());

	if (CharacterWidget) {
		CharacterWidget->RefreshInventory();
	}

}
