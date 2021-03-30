#ifndef BOOK_TITLESTATE_HPP
#define BOOK_TITLESTATE_HPP

#include "State.hpp"
#include "SpriteNode.h"
#include "../../Common/d3dApp.h"

class TitleState : public State
{
	public:
		TitleState(StateStack& stack, Context context, Game* game);
		virtual void		draw();
		virtual bool		update(const GameTimer& gt);
		virtual bool		handleEvent(WPARAM btnState);

	private:
		SpriteNode* m_TitleScreenBackground;
		SpriteNode* m_TitleScreenPrompt;

		SceneNode* m_SceneGraph;

		// Inherited via State
		virtual void BuildScene() override;
};

#endif // BOOK_TITLESTATE_HPP
