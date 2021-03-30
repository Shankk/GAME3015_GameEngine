#ifndef BOOK_MENUSTATE_HPP
#define BOOK_MENUSTATE_HPP

#include "State.hpp"
#include "SpriteNode.h"
#include "../../Common/d3dApp.h"


class MenuState : public State
{
	public:
								MenuState(StateStack& stack, Context context, Game* game);

		virtual void			draw();
		virtual bool			update(const GameTimer& gt);
		virtual bool			handleEvent(WPARAM btnState);

		void					updateOptionText();


	private:
		enum OptionNames
		{
			Play,
			Setting,
			Exit,
		};


	private:

		SceneNode* m_SceneGraph;
		SpriteNode* m_MenuScreenBackground;
		SpriteNode* m_PlayButton;
		SpriteNode* m_SettingButton;
		SpriteNode* m_QuitButton;
		SpriteNode* m_SelectorSprite;

		std::vector<SpriteNode*>	mOptions;
		std::size_t				mOptionIndex;

		// Inherited via State
		virtual void BuildScene() override;
};

#endif // BOOK_MENUSTATE_HPP
