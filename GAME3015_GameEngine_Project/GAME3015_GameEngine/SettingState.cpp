#include "SettingState.h"
#include "Game.hpp"

SettingState::SettingState(StateStack& stack, Context context, Game* game)
	: State(stack, context, game) , mOptions() , mOptionIndex(0)
	, m_SceneGraph(new SceneNode(game))
	, m_SettingBackground(nullptr)
	, m_KeybindWASD(nullptr)
	, m_KeybindARROW(nullptr)
	, m_QuitButton(nullptr)
	, m_SelectorSprite(nullptr)
{
	BuildScene();
}

void SettingState::draw()
{

	m_SceneGraph->draw();

}

bool SettingState::update(const GameTimer& gt)
{
	m_SceneGraph->update(gt);

	float x = mOptions[mOptionIndex]->getWorldPosition().x - 1.6;
	float y = mOptions[mOptionIndex]->getWorldPosition().y;
	float z = mOptions[mOptionIndex]->getWorldPosition().z;

	m_SelectorSprite->setPosition(x, y, z);

	
	return true;
}

bool SettingState::handleEvent(WPARAM btnState)
{

	if (btnState == VK_RETURN )
	{
		// If Index equals WASD then we assign player move keys to WASD
		if (mOptionIndex == WASD)
		{
			mGame->mPlayer.assignKey(Player::Action::MoveUp, 'W');
			mGame->mPlayer.assignKey(Player::Action::MoveDown, 'S');
			mGame->mPlayer.assignKey(Player::Action::MoveLeft, 'A');
			mGame->mPlayer.assignKey(Player::Action::MoveRight, 'D');
			mGame->mPlayer.resetKeyFlags();

			requestStackPop();
			requestStackPush(States::Menu);
		}
		// If Index equals ARROWKEYS then we assign player move keys to  ARROWKEYS
		else if (mOptionIndex == ARROWKEYS)
		{ 
			mGame->mPlayer.assignKey(Player::Action::MoveUp, VK_UP);
			mGame->mPlayer.assignKey(Player::Action::MoveDown, VK_DOWN);
			mGame->mPlayer.assignKey(Player::Action::MoveLeft, VK_LEFT);
			mGame->mPlayer.assignKey(Player::Action::MoveRight, VK_RIGHT);
			mGame->mPlayer.resetKeyFlags();

			requestStackPop();
			requestStackPush(States::Menu);
		}
		else if (mOptionIndex == Return) 
		{
			requestStackPop();
			requestStackPush(States::Menu);
		}
	}
	else if (btnState == VK_UP)
	{
		
		if (mOptionIndex > 0)
			mOptionIndex--;
		else
			mOptionIndex = mOptions.size() - 1;

		updateOptionText();
	}
	else if (btnState == VK_DOWN)
	{
		
		if (mOptionIndex < mOptions.size() - 1)
			mOptionIndex++;
		else
			mOptionIndex = 0;

		updateOptionText();
	}
	else
	{
		return false;
	}

	return true;
}

void SettingState::updateOptionText()
{
	if (mOptions.empty())
		return;

	
}

void SettingState::BuildScene()
{

	mGame->mAllRitems.clear();
	mGame->mOpaqueRitems.clear();
	mGame->mFrameResources.clear();


	mGame->BuildMaterials();

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mGame, "TitleScreen"));
	m_SettingBackground = backgroundSprite.get();
	m_SettingBackground->setPosition(0, 0, 0.0);
	m_SettingBackground->setScale(12.0, 1.0, 8.5);
	m_SettingBackground->setVelocity(0, 0, 0);
	m_SceneGraph->attachChild(std::move(backgroundSprite));

	std::unique_ptr<SpriteNode> mSettingWASDSprite(new SpriteNode(mGame, "SettingWASD"));
	m_KeybindWASD = mSettingWASDSprite.get();
	m_KeybindWASD->setPosition(0, 0.1, 1.0);
	m_KeybindWASD->setScale(3.0, 1.0, 2.0);
	m_KeybindWASD->setVelocity(0, 0, 0);
	m_SceneGraph->attachChild(std::move(mSettingWASDSprite));
	mOptions.push_back(m_KeybindWASD);

	std::unique_ptr<SpriteNode> mSettingARROWSprite(new SpriteNode(mGame, "SettingArrow"));
	m_KeybindARROW = mSettingARROWSprite.get();
	m_KeybindARROW->setPosition(0, 0.1, 0.0);
	m_KeybindARROW->setScale(3.0, 1.0, 2.0);
	m_KeybindARROW->setVelocity(0, 0, 0);
	m_SceneGraph->attachChild(std::move(mSettingARROWSprite));
	mOptions.push_back(m_KeybindARROW);

	std::unique_ptr<SpriteNode> menuQuitSprite(new SpriteNode(mGame, "SettingReturn"));
	m_QuitButton = menuQuitSprite.get();
	m_QuitButton->setPosition(0, 0.1, -1.0);
	m_QuitButton->setScale(3.0, 1.0, 2.0);
	m_QuitButton->setVelocity(0, 0, 0);
	m_SceneGraph->attachChild(std::move(menuQuitSprite));

	mOptions.push_back(m_QuitButton);

	std::unique_ptr<SpriteNode> menuArrowSprite(new SpriteNode(mGame, "MenuArrow"));
	m_SelectorSprite = menuArrowSprite.get();
	m_SelectorSprite->setPosition(-0.5, 0.1, 0.0);
	m_SelectorSprite->setScale(0.5f, 1.0f, 0.5f);
	m_SelectorSprite->setVelocity(0, 0, 0);
	m_SceneGraph->attachChild(std::move(menuArrowSprite));

	m_SceneGraph->build();


	for (auto& e : mGame->mAllRitems)
		mGame->mOpaqueRitems.push_back(e.get());


	mGame->BuildFrameResources();

}
