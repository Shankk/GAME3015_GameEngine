#include "GameState.hpp"
#include "Game.hpp"

GameState::GameState(StateStack& stack, Context context, Game* game)
: State(stack, context, game)
, mWorld(&(mGame->mWorld))
, m_PauseBackground(nullptr)
, m_PauseSceneGraph(new SceneNode(game))
{
	BuildScene();
}

void GameState::draw()
{
	mWorld->draw();
}

bool GameState::update(const GameTimer& gt)
{
	ProcessInput();
	mWorld->update(gt);
	return true;
}

bool GameState::handleEvent(WPARAM btnState)
{
	if (btnState == 'P')
	{
		requestStackPush(States::Pause);
	}

	return true;
}

void GameState::ProcessInput()
{
	CommandQueue& commands = mWorld->getCommandQueue();
	(getContext().player)->handleEvent(commands);
	(getContext().player)->handleRealtimeInput(commands);
}

void GameState::BuildScene()
{

	mGame->mAllRitems.clear();
	mGame->mOpaqueRitems.clear();
	mGame->mFrameResources.clear();

	mGame->BuildMaterials();

	mWorld->buildScene();

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mGame, "PauseDisplay"));
	m_PauseBackground = backgroundSprite.get();
	m_PauseBackground->setPosition(0, 0.15, -1);
	m_PauseBackground->setScale(8, 1.0, 8);
	m_PauseBackground->setVelocity(0, 0, 0);
	m_PauseSceneGraph->attachChild(std::move(backgroundSprite));

	m_PauseSceneGraph->build();
	
	for (auto& e : mGame->mAllRitems)
		mGame->mOpaqueRitems.push_back(e.get());

	mGame->BuildFrameResources();
}
