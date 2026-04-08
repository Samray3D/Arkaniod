#include "GameStateMainMenu.h"
#include "Game.h"
#include <assert.h>

namespace SnakeGame
{
	void GameStateMainMenu::Init(Game* game)
	{
		m_game = game;
		assert(font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		menu.rootItem.children.clear();

		menu.rootItem.hintText.setString("ARKANOID");
		menu.rootItem.hintText.setFont(font);
		menu.rootItem.hintText.setCharacterSize(48);
		menu.rootItem.hintText.setFillColor(sf::Color::Red);
		menu.rootItem.childrenOrientation = Orientation::Vertical;
		menu.rootItem.childrenAlignment = Alignment::Middle;
		menu.rootItem.childrenSpacing = 10.f;
		menu.rootItem.children.push_back(&startGameItem);
		menu.rootItem.children.push_back(&recordsItem);
		menu.rootItem.children.push_back(&exitGameItem);

		startGameItem.text.setString("Start Game");
		startGameItem.text.setFont(font);
		startGameItem.text.setCharacterSize(24);
		
		recordsItem.text.setString("Records");
		recordsItem.text.setFont(font);
		recordsItem.text.setCharacterSize(24);

		exitGameItem.text.setString("Exit Game");
		exitGameItem.text.setFont(font);
		exitGameItem.text.setCharacterSize(24);
		exitGameItem.hintText.setString("Are you sure?");
		exitGameItem.hintText.setFont(font);
		exitGameItem.hintText.setCharacterSize(48);
		exitGameItem.hintText.setFillColor(sf::Color::Red);
		exitGameItem.childrenOrientation = Orientation::Horizontal;
		exitGameItem.childrenAlignment = Alignment::Middle;
		exitGameItem.childrenSpacing = 10.f;
		exitGameItem.children.push_back(&yesItem);
		exitGameItem.children.push_back(&noItem);

		yesItem.text.setString("Yes");
		yesItem.text.setFont(font);
		yesItem.text.setCharacterSize(24);

		noItem.text.setString("No");
		noItem.text.setFont(font);
		noItem.text.setCharacterSize(24);

		InitMenuItem(menu.rootItem);
		SelectMenuItem(menu, &startGameItem);
	}

	void GameStateMainMenu::Shutdown()
	{

	}

	void GameStateMainMenu::HandleWindowEvent(const sf::Event& event)
	{
		if (!menu.selectedItem)
		{
			return;
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				CollapseSelectedItem(menu);
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				if (menu.selectedItem == &startGameItem)
				{
					m_game->SwitchStateTo(GameStateType::Playing);
				}
				else if (menu.selectedItem == &recordsItem)
				{
					m_game->PushState(GameStateType::Records, true);
				}
				else if (menu.selectedItem == &optionsItem)
				{
					ExpandSelectedItem(menu);
				}
				else if (menu.selectedItem == &yesItem)
				{
					sf::RenderWindow* window = m_game->GetWindow();
					if (window)
					{
						window->close();
					}
				}
				else if (menu.selectedItem == &noItem)
				{
					CollapseSelectedItem(menu);
				}
				else
				{
					ExpandSelectedItem(menu);
				}
			}

			Orientation orientation = menu.selectedItem->parent->childrenOrientation;
			if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Up ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Left)
			{
				SelectPreviousMenuItem(menu);
			}
			else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Down ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Right)
			{
				SelectNextMenuItem(menu);
			}

		}
	}

	void GameStateMainMenu::Update(float timeDelta)
	{
		
	}

	void GameStateMainMenu::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getView().getSize();

		sf::Text* hintText = &GetCurrentMenuContext(menu)->hintText;
		hintText->setOrigin(GetTextOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		window.draw(*hintText);

		DrawMenu(menu, window, viewSize / 2.f, { 0.5f, 0.f });
	}

}
