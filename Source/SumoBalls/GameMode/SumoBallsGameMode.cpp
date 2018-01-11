// Fill out your copyright notice in the Description page of Project Settings.

#include "SumoBallsGameMode.h"
#include "Player/BallPlayer.h"

ASumoBallsGameMode::ASumoBallsGameMode()
{
	DefaultPawnClass = ABallPlayer::StaticClass();
}

