#include "TitleState.hpp"
#include "World.hpp"
#include "Game.hpp"


TitleState::TitleState(StateStack& stack, Context context, Game* game)
: State(stack, context, game)
, m_TitleScreenBackground(nullptr)
, m_SceneGraph(new SceneNode(game))
{
	BuildScene();
}

void TitleState::draw()
{
	// we draw our scene graph
	m_SceneGraph->draw();
}

bool TitleState::update(const GameTimer& gt)
{
	m_SceneGraph->update(gt);
	return true;
}

bool TitleState::handleEvent(WPARAM btnState)
{
	requestStackPop();
	requestStackPush(States::Menu);

	return true;
}



void TitleState::BuildScene()
{
	//Clear items, and resources.
	mGame->mAllRitems.clear();
	mGame->mOpaqueRitems.clear();
	mGame->mFrameResources.clear();
	// Build our materials
	mGame->BuildMaterials();


	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mGame, "TitleScreen"));
	m_TitleScreenBackground = backgroundSprite.get();
	m_TitleScreenBackground->setPosition(0, 0, 0);
	m_TitleScreenBackground->setScale(12.0, 1.0, 8.5);
	m_TitleScreenBackground->setVelocity(0, 0, 0);
	m_SceneGraph->attachChild(std::move(backgroundSprite));

	std::unique_ptr<SpriteNode> TitlePrompt(new SpriteNode(mGame, "TitleScreenPrompt"));
	m_TitleScreenPrompt = TitlePrompt.get();
	m_TitleScreenPrompt->setPosition(0, 0.1, 0);
	m_TitleScreenPrompt->setScale(6, 1.0, 5);
	m_TitleScreenPrompt->setVelocity(0, 0, 0);
	m_SceneGraph->attachChild(std::move(TitlePrompt));


	m_SceneGraph->build();


	for (auto& e : mGame->mAllRitems)
		mGame->mOpaqueRitems.push_back(e.get());

	mGame->BuildFrameResources();
	
}
