// Fill out your copyright notice in the Description page of Project Settings.


#include "AR_PlayerState.h"


void AAR_PlayerState::SetCredits(const int32& Value)
{
	Credits = Value;
}

void AAR_PlayerState::AddCredits(const int32& Value)
{
	Credits += Value;
}

int32 AAR_PlayerState::GetCredits() const
{
	return Credits;
}
