#pragma region step 3
#include "PauseState.hpp"
#include "Game.hpp"
#include "GameState.hpp"
#include "State.hpp"

PauseState::PauseState(StateStack& stack, Context context, Game* game)
: State(stack, context, game)
, m_SceneGraph(new SceneNode(game))
, m_PauseBackground(nullptr)
{
	BuildScene();
}

PauseState::~PauseState()
{
}

void PauseState::draw()
{
	((GameState*)((*mStack->GetStateStack())[0].get()))->m_PauseSceneGraph->draw();
}

bool PauseState::update(const GameTimer& gt)
{
	((GameState*)((*mStack->GetStateStack())[0].get()))->m_PauseSceneGraph->update(gt);
	return false;
}

bool PauseState::handleEvent(WPARAM btnState)
{
	if (btnState == 'P' )
	{
		requestStackPop();
	}
	else if (btnState == VK_BACK)
	{
		requestStateClear();
		requestStackPush(States::Menu);
	}

	return false;
}

void PauseState::BuildScene()
{
	
}

#pragma endregion