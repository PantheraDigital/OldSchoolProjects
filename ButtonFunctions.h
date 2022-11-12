#pragma once


#include "GameplayStateMachine.h"

class GameplayStateChange
{
	GameplayStateMachine* m_pStateMachine;
	GameplayStateMachine::SceneName m_stateChange;

public:
	GameplayStateChange(GameplayStateMachine* stateMachine, GameplayStateMachine::SceneName newState)
		:m_pStateMachine(stateMachine)
		, m_stateChange(newState)
	{}

	~GameplayStateChange()
	{
		m_pStateMachine = nullptr;
	}


	void operator() ()
	{
		m_pStateMachine->LoadScene(m_stateChange);
	}

};

class QuitGame
{
	GameplayStateMachine* m_pStateMachine;
public:
	QuitGame(GameplayStateMachine* stateMachine)
		:m_pStateMachine(stateMachine) 
	{}

	~QuitGame()
	{
		m_pStateMachine = nullptr;
	}


	void operator() ()
	{
		m_pStateMachine->GetGame()->Quit();
	}

};