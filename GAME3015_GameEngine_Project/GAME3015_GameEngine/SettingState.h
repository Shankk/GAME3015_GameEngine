#pragma once


#include "State.hpp"
#include "SpriteNode.h"
#include "../../Common/d3dApp.h"

class SettingState : public State
{
public: 
	SettingState(StateStack& stack, Context context, Game* game);
	virtual void			draw();
	virtual bool			update(const GameTimer& gt);
	virtual bool			handleEvent(WPARAM btnState);

	void					updateOptionText();


private:
	enum OptionNames
	{
		WASD,
		ARROWKEYS,
		Return
	};


private:

	SceneNode* m_SceneGraph;
	SpriteNode* m_SettingBackground;
	SpriteNode* m_KeybindWASD;
	SpriteNode* m_KeybindARROW;
	SpriteNode* m_QuitButton;
	SpriteNode* m_SelectorSprite;
	std::vector<SpriteNode*>	mOptions;
	std::size_t				mOptionIndex;
	int mTotalNumOptions;

	// Inherited via State
	virtual void BuildScene() override;
};
