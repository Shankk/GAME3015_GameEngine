#include "MenuState.hpp"
#include "Game.hpp"

MenuState::MenuState(StateStack& stack, Context context, Game* game)
: State(stack, context, game)
, mOptionIndex(0)
, m_SceneGraph(new SceneNode(game))
, m_MenuScreenBackground(nullptr)
, m_PlayButton(nullptr)
, m_SettingButton(nullptr)
, m_QuitButton(nullptr)
, m_SelectorSprite (nullptr)
{
	BuildScene();

}

void MenuState::draw()
{
	m_SceneGraph->draw();
}

bool MenuState::update(const GameTimer& gt)
{
	m_SceneGraph->update(gt);

	float x = mOptions[mOptionIndex]->getWorldPosition().x - 1.25f;
	float y = mOptions[mOptionIndex]->getWorldPosition().y;
	float z = mOptions[mOptionIndex]->getWorldPosition().z;

	m_SelectorSprite->setPosition(x, y, z);

	return true;
}

bool MenuState::handleEvent(WPARAM btnState)
{
	if (btnState == VK_RETURN)
	{
		if (mOptionIndex == Play)
		{
			requestStackPop();
			requestStackPush(States::Game);
		}
		else if (mOptionIndex == Setting)
		{
			requestStackPop();
			requestStackPush(States::Setting);
		}
		else if (mOptionIndex == Exit)
		{
			requestStackPop();
		}
	}
	else if (btnState == VK_LEFT)
	{
		
		if (mOptionIndex > 0)
			mOptionIndex--;
		else
			mOptionIndex = mOptions.size() - 1;

		updateOptionText();
	}
	else if (btnState == VK_RIGHT)
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

void MenuState::updateOptionText()
{
	if (mOptions.empty())
		return;

}

void MenuState::BuildScene()
{

	mGame->mAllRitems.clear();
	mGame->mOpaqueRitems.clear();
	mGame->mFrameResources.clear();


	mGame->BuildMaterials();

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(mGame, "TitleScreen"));
	m_MenuScreenBackground = backgroundSprite.get();
	m_MenuScreenBackground->setPosition(0, 0, 0.0);
	m_MenuScreenBackground->setScale(12.0, 1.0, 8.5);
	m_MenuScreenBackground->setVelocity(0, 0, 0);
	m_SceneGraph->attachChild(std::move(backgroundSprite));

	std::unique_ptr<SpriteNode> menuPlaySprite(new SpriteNode(mGame, "MenuPlay"));
	m_PlayButton = menuPlaySprite.get();
	m_PlayButton->setPosition(-2, 0.1, 0.0);
	m_PlayButton->setScale(4.0, 1.0, 4.0);
	m_PlayButton->setVelocity(0, 0, 0);
	m_SceneGraph->attachChild(std::move(menuPlaySprite));
	mOptions.push_back(m_PlayButton);

	std::unique_ptr<SpriteNode> menuSettingSprite(new SpriteNode(mGame, "MenuSettingTex"));
	m_SettingButton = menuSettingSprite.get();
	m_SettingButton->setPosition(0, 0.1, 0.0);
	m_SettingButton->setScale(4.0, 1.0, 4.0);
	m_SettingButton->setVelocity(0, 0, 0);
	m_SceneGraph->attachChild(std::move(menuSettingSprite));
	mOptions.push_back(m_SettingButton);

	std::unique_ptr<SpriteNode> menuQuitSprite(new SpriteNode(mGame, "MenuQuit"));
	m_QuitButton = menuQuitSprite.get();
	m_QuitButton->setPosition(2.5, 0.1, 0.0);
	m_QuitButton->setScale(4.0, 1.0, 4.0);
	m_QuitButton->setVelocity(0, 0, 0);
	m_SceneGraph->attachChild(std::move(menuQuitSprite));

	mOptions.push_back(m_QuitButton);

	std::unique_ptr<SpriteNode> menuArrowSprite(new SpriteNode(mGame, "MenuArrow"));
	m_SelectorSprite = menuArrowSprite.get();
	m_SelectorSprite->setPosition(-0.5, 0.1, 0.0);
	m_SelectorSprite->setScale(0.75f, 1.0f, 0.75f);
	m_SelectorSprite->setVelocity(0, 0, 0);
	m_SceneGraph->attachChild(std::move(menuArrowSprite));

	m_SceneGraph->build();


	for (auto& e : mGame->mAllRitems)
		mGame->mOpaqueRitems.push_back(e.get());

	mGame->BuildFrameResources();

}
