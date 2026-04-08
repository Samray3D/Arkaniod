#include "GameStatePauseMenu.h"
#include "Game.h"
#include <assert.h>

namespace SnakeGame
{
	void GameStatePauseMenu::Init(Game* game)
	{
		m_game = game;

		assert(font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		background.setFillColor(sf::Color(0, 0, 0, 128)); // Semi-transparent black

		titleText.setString("Pause");
		titleText.setFont(font);
		titleText.setCharacterSize(48);
		titleText.setFillColor(sf::Color::Red);

		menu.rootItem.childrenOrientation = Orientation::Vertical;
		menu.rootItem.childrenAlignment = Alignment::Middle;
		menu.rootItem.children.push_back(&resumeItem);
		menu.rootItem.children.push_back(&exitItem);
		
		resumeItem.text.setString("Return to game");
		resumeItem.text.setFont(font);
		resumeItem.text.setCharacterSize(24);

		exitItem.text.setString("Exit to main menu");
		exitItem.text.setFont(font);
		exitItem.text.setCharacterSize(24);

		InitMenuItem(menu.rootItem);
		SelectMenuItem(menu, &resumeItem);
	}

	void GameStatePauseMenu::Shutdown()
	{

	}

	void GameStatePauseMenu::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				m_game->PopState();
				return;
			}

			if (menu.selectedItem == nullptr)
			{
				return;
			}

			if (event.key.code == sf::Keyboard::Enter)
			{
				if (menu.selectedItem == &resumeItem)
				{
					m_game->PopState();
				}
				else if (menu.selectedItem == &exitItem)
				{
					m_game->SwitchStateTo(GameStateType::MainMenu);
				}
			}

			Orientation orientation = menu.selectedItem->parent->childrenOrientation;
			if (event.key.code == sf::Keyboard::Up)
			{
				SelectPreviousMenuItem(menu);
			}
			else if (event.key.code == sf::Keyboard::Down)
			{
				SelectNextMenuItem(menu);
			}
		}
	}

	void GameStatePauseMenu::Update(float timeDelta)
	{

	}

	void GameStatePauseMenu::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getView().getSize();
		
		background.setSize(viewSize);
		window.draw(background);

		titleText.setOrigin(GetTextOrigin(titleText, { 0.5f, 0.f }));
		titleText.setPosition(viewSize.x / 2.f, 100);
		window.draw(titleText);

		DrawMenu(menu, window, window.getView().getCenter(), { 0.5f, 0.f });
	}

}
