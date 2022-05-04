#include <random>
#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

#include "gameHandler.h"
#include "attack.h"
#include "weapon.h"

#include "spider.h"
#include "creeper.h"

bool gameHandler::checkRange(int numToCheck, int min, int max)
{
	if (numToCheck < min || numToCheck > max)
	{
		return false;
	}
	return true;
}

void gameHandler::createPlayer()
{
	inventorySize = 3;
	player gameplayer;

	createWeapon("Iron Sword", 1, 20, inventory);
	createWeapon("Diamond Sword", 3, 100, inventory);
	createItem("Gunpowder", 1, inventory);
	createPotion("Heal Potion", 3, 8, inventory);


}

//Creates the random vector of enemies to fight
void gameHandler::createEnemies()
{

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 10);

	for (int i = 0; i < dist6(rng); i++)
	{
		enemies.push_back(enemy("zombie", 1));

		if (dist6(rng) == 4 || dist6(rng) == 5) {
			enemies.push_back(spider("Spider", 1));
		}
		if (dist6(rng) == 3 || dist6(rng) == 7)
		{
			enemies.push_back(creeper());
		}

		numberOfEnemies = i + 1;
	}
}



void gameHandler::battle()
{


	do {

	int alphaval;
	cout << "Enter a number between 0 and " << numberOfEnemies << endl;
	cin >> alphaval;
	while (alphaval < 0 || alphaval > numberOfEnemies)
	{
		cout << "Invalid entry! Please enter a valid value: ";
		cin >> alphaval;
		curEnemy = alphaval;
	}


	if (numberOfEnemies == 0) {
		quitGame("You win! Good job defeating all the enemies " + gamePlayer.pName + "!");
	}


	while (numberOfEnemies != 0)
	{
		system("CLS");

		selected = fightMenu(selectedItem, inventory, enemies[curEnemy]);


		if (!gamePlayer.hasDied())
		{
			//Use Item
			if (selected == 0)
			{
				if (selectedItem.useVal == 1)
				{

					attack a = attack();

					if (checkRange(gamePlayer.stamina, 0, 8)) {
						a.attackPower = selectedItem.damage;

						gamePlayer.stamina -= a.staminaCost;
						selectedItem.durability--;
						gamePlayer.doAttack(enemies[curEnemy], a.attackPower);
						enemies[curEnemy].health -= a.attackPower;
					}
					else
					{
						cout << "You are too tired to fight... heal up before you start " << endl;

						Sleep(1000);
					}





					if (enemies[curEnemy].health > 0)
					{
						cout << "Enemy is attacking player\n";
						//if (enemies[curEnemy]. > 0)
						{
							cout << "Enemy hit player for " << 1 << " damage!\n";
							gamePlayer.health -= 1;
							Sleep(1500);
						}
					}
					else
					{
						cout << "\n The " + enemies[curEnemy].name + " has died!\n";
						//removed the current ememy selected ... hopefully
						enemies.erase(enemies.begin(), enemies.end() - 1);
						numberOfEnemies--;
						break;
					}
					
				}



				else if (selectedItem.useVal == 0)
				{
					if (gamePlayer.getHealth() < 10) {

						cout << "Healed player";
						gamePlayer.healPlayer(10);

						useItemFromInventory(selectedItem);
					}
				}
				else
				{
					cout << "No item selected.";
					Sleep(1000);
				}
			}
			//Open Inventory
			else if (selected == 1)
			{
				displayList(inventory, 2);
			}
			//Main Menu
			else if (selected == 2)
			{
				break;
			}
			else
				cout << "ERROR: INVALID MOVE\n\n";
		}
		else
		{
			quitGame("You lose! The player has died...!");
			break;
		}


	}




	cout << "Fight over... Press any key to continue... \n\n";
	_getch();
	gameMenu();



	} while (numberOfEnemies > 0);
}

int gameHandler::fightMenu(Item selectedWeapon, list<Item*> inventory, enemy curEnemy)
{
	string result;
	char choiceList[3];
	bool selected = false;
	bool exit = false;
	do//Main combat system
	{
		system("CLS");

		cout << "---------YOU ARE IN BATTLE!----------\n";
		cout << "     What would you like to do?" << endl << endl
			<< "Tip: Use the A and D keys to toggle the selection. \n Use the W and S to select an option." << endl << endl;

		cout << "\nNumber of enemies on the battlefield: " << numberOfEnemies << endl << endl;


		if (selectedWeapon.durability > 0)
		{
			cout << "Player health: " << gamePlayer.getHealth() << endl
				<< "Player stamina: " << gamePlayer.stamina << endl << endl
				<< "Current weapon:" << selectedWeapon.name << endl
				<< "    Durability: " << selectedWeapon.durability << endl << endl
				<< "  Enemy health: " << curEnemy.health << endl << endl;
		}
		else
		{
			cout << "Player health: " << gamePlayer.getHealth() << endl
				<< "Player stamina: " << gamePlayer.stamina << endl << endl
				<< "Current weapon:" << selectedWeapon.name << endl << endl
				<< "  Enemy health: " << curEnemy.health << endl << endl;
		}
		for (int i = 0; i < 3; i++)
		{
			if (i == selectorIndex2)
				choiceList[i] = '>';
			else
				choiceList[i] = ' ';
		}
		cout << choiceList[0] << "Use Item " << choiceList[1] << "Inventory " << choiceList[2] << "Main Menu \n";//Displays options
		char input = _getch();
		switch (input)
		{
		case ('a'):
			if (selectorIndex2 == 0)
				selectorIndex2 = 2;
			else
				selectorIndex2--;
			break;
		case ('d'):
			if (selectorIndex2 == 2)
				selectorIndex2 = 0;
			else
				selectorIndex2++;
			break;
		case ('w'):
			selected = true;
			break;
		case ('s'):
			exit = true;
			break;
		default:
			break;
		}
	} while (!selected && !exit);
	if (choiceList[0] == '>')
		return 0;
	else if (choiceList[1] == '>')
		return 1;
	else if (choiceList[2] == '>')
		return 2;
	else
		return 3;
}

void gameHandler::gameMenu()
{
	input = 0;
	char choice;
	selectorIndex = 0;
	selectorIndex2 = 0;
	system("CLS");
	cout << "---What would you like to do now?" << endl;

	cout << "                            \n\n"
		<< "GAME MENU:                   \n  "
		<< "\t1 - Quick Battle           \n  "
		<< "\t2 - Display Stats         \n  "
		<< "\t3 - See Inventory          \n  "
		<< "\t4 - Player V Player Battle ( AI )          \n  "
		<< "\t5 - Quit \n\n";
	while (input != 1)
	{
		choice = _getch();
		input++;
	}
	cout << endl;
	switch (choice)
	{
	case ('1'):
		battle();
		gameMenu();
		break;
	case ('2'):
		gamePlayer.displayStats();
		gameMenu();
		break;
	case ('3'):
		displayList(inventory, 1);
		gameMenu();
		break;
	case ('4'):
		doPlayerVPlayerBattle();
		gameMenu();
		break;
	case ('5'):
		cout << "Thank you for playing...\n";
		return;
		break;
	default:
		system("CLS");
		cout << "Sorry, that input is invalid.\n"
			<< "\tPlease try again.\n";
		gameMenu();
		break;
	}
}

void gameHandler::doPlayerVPlayerBattle()
{
	player winningPlayer;
	bool playerOneWon = false;
	bool battleOver = false;
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 1);

	std::uniform_int_distribution<std::mt19937::result_type> distItems(0, 3);

	

	for (int i = 0; i < dist6(rng); i++)
	{
		if (dist6(rng) == 0)
		{
			playerOneWon = true;
		}
		else
		{
			playerOneWon = false;
		}
	}
	string NameArray[10] = { "budz", "pain", "konan", "nagato", "itachi", "tobi", "madara", "naruto", "danzou", "kakashi" };
	string Random, Random2;
	srand(time(0));

	for (int j = 0; j <= 9; j++)
	{
		Random = NameArray[rand() % 10];
		NameArray[j] = Random; 
	}
	for (int i = 0; i <= 9; i++)
	{
		Random2 = NameArray[rand() % 10];
		NameArray[i] = Random2; 
	}


	battlePlayer1.setName(Random);
	battlePlayer2.setName(Random2);

	

	weapon weapons[4] = {
		weapon("Iron Sword", 100, 1, 1),
		weapon("Diamond Pickaxe", 100, 1, 1),
		weapon("Wooden Shovel", 100, 1, 1),
		weapon("Stone Sword", 100, 1, 1)
	};

		
	do
	{
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 10);


		system("CLS");

		cout << "---------2 PLAYERS ARE IN BATTLE!----------\n";


		cout << battlePlayer1.pName << endl;
		cout << "-------- VS --------" << endl;
		cout << battlePlayer2.pName << endl << endl << endl;
		
		Sleep(1000);



		if (playerOneWon == true) {

			for (int i = 0; i < dist6(rng); i++)
			{
				if (dist6(rng) == 4 || dist6(rng) == 7 || dist6(rng) == 2 || dist6(rng) == 10)
				{
					

					battlePlayer2.health -= 1;
					battlePlayer2.skillLevel = dist6(rng);
					cout << battlePlayer1.pName << "  is attacking  " << battlePlayer2.pName << endl;
					for (int w = 0; w < distItems(rng); w++)
					{
						cout << "Using a: " << weapons[w].getName() << endl;
					}
					cout << battlePlayer2.pName << "  health is at:  " << battlePlayer2.health << endl << endl;
				}

				if (dist6(rng) == 1 || dist6(rng) == 2 || dist6(rng) == 8 || dist6(rng) == 9)
				{
					battlePlayer1.health -= 1;
					battlePlayer2.skillLevel = dist6(rng);
					cout << battlePlayer2.pName << "  is attacking  " << battlePlayer1.pName << endl;
					for (int w = 0; w < distItems(rng); w++)
					{
						cout << "Using a: " << weapons[w].getName() << endl;
					}
					cout << battlePlayer1.pName << "  health is at:  " << battlePlayer1.health << endl << endl;
				}
			}

		

			winningPlayer = battlePlayer1;
			Sleep(1000);
		}
		else
		{
			for (int i = 0; i < dist6(rng); i++)
			{
				if (dist6(rng) == 4 || dist6(rng) == 7 || dist6(rng) == 2 || dist6(rng) == 10)
				{
					battlePlayer2.health -= 1;
					battlePlayer1.skillLevel = dist6(rng);
					cout << battlePlayer1.pName << "  is attacking  " << battlePlayer2.pName << endl;
					for (int w = 0; w < distItems(rng); w++)
					{
						cout << "Using a: " << weapons[w].getName() << endl;
					}
					cout << battlePlayer2.pName << "  health is at:  " << battlePlayer2.health << endl << endl;
				}

				if (dist6(rng) == 1 || dist6(rng) == 2 || dist6(rng) == 8 || dist6(rng) == 9)
				{
					battlePlayer1.health -= 1;
					battlePlayer1.skillLevel = dist6(rng);
					cout << battlePlayer2.pName << "  is attacking  " << battlePlayer1.pName << endl;
					for (int w = 0; w < distItems(rng); w++)
					{
						cout << "Using a: " << weapons[w].getName() << endl;
					}
					cout << battlePlayer1.pName << "  health is at:  " << battlePlayer1.health << endl << endl;
				}
			}

			winningPlayer = battlePlayer2;
			Sleep(1000);
		}



		if (battlePlayer1.hasDied() || battlePlayer2.hasDied()) {
			battleOver = true;
		}
		Sleep(1000);

	} while (!battleOver);

	cout << "Congrats "  + winningPlayer.pName + " You Won! \n\n";

	winningPlayer.displayStats();

	cout << "Fight over... Press any key to continue... \n\n";
	_getch();
	gameMenu();
}

void gameHandler::gameInit()
{
	//creates lists that will later be populated
	//list<Item*> inventory;
//	list<Item*> eqipped;
	selectedItem = Item();
	selectedItem.useVal = -1;
	selectedItem.durability = -1;
	curEnemy = 0;
	selected = 0;
	createPlayer();
	createEnemies();




	cout << "------------Welcome to the HCC Combat Simulator------------\n"
		<< "  Please enter a character name:";
	cin >> playerName;
	gamePlayer.setName(playerName);

	//_getch();
	gameMenu();

}

void gameHandler::quitGame(string message)
{
	system("CLS");
	cout << message << endl;

	Sleep(1000000);
}




//Inventory update

void gameHandler::createItem(string name, int stat, list<Item*>& list)
{
	Item* newItem = new Item();
	newItem->name = name;
	newItem->useVal = -1;
	newItem->id++;

	list.push_back(newItem);
	inventorySize++;
}

void gameHandler::useItemFromInventory(Item& i)
{
	int index = 0;
	list<Item*>::iterator it;
	it = inventory.begin();
	while (index < selectorIndex)
	{
		index++;
		it++;
	}

	if ((*it)->useVal == 0 || (*it)->useVal == 1)
	{
		Item* itemPointer = *it;

		inventory.remove(itemPointer);
		i = Item();
	}
}

void gameHandler::createPotion(string name, int boost, int qty, list<Item*>& list)
{
	for (int i = 0; i < qty; i++)
	{
		Item* newItem = new Item();
		newItem->name = name;
		newItem->useVal = 0;
		newItem->id++;

		list.push_back(newItem);
		inventorySize++;
	}
}

void gameHandler::createWeapon(string name, int dmg, int uses, list<Item*>& list)
{
	weapon* newItem = new weapon(name, uses, dmg, 1);
	newItem->useVal = 1;
	newItem->durability = uses;
	newItem->id++;

	list.push_back(newItem);
	inventorySize++;
}

void gameHandler::displayList(list<Item*>& itemList, int key)
{
	list<Item*>::iterator it;
	if (!itemList.empty())
	{
		it = itemList.begin();
		cout << "--INVENTORY--\n";
		do
		{
			cout << "\t|" << (*it)->name << "|" << endl;
			//cout << "\t|" << (*it)->id << "|" <<
			//	(*it)->getStat() << (*it)->stat << "|" << endl;
			it++;
		} while (it != itemList.end());
		cout << "Would you like to enter select mode?\n"
			<< "\t Enter yes or no ( y/n )\n";
		string x;
		cin >> x;
		if (x == "y" || x == "yes" || x == "Yes")
		{
			selectorMenu(itemList, key);
		}
	}
	else
	{
		cout << "The list is empty!\n"
			<< "\tPress enter to return to the main menu.\n";
		_getch();
		gameMenu();
	}
}

void gameHandler::addtoEquipped(string id, Item gameItem, list<Item*>& equipped)
{
	if (gameItem.useVal == 0 || gameItem.useVal == 1)
	{
		equipped.push_back(&gameItem);
		selectedItem = gameItem;
		cout << "Item equipped!" << endl;
	}
	else
		cout << "This item is not equippable.\n";
}

void gameHandler::itemSelected(int selectorIndex, list<Item*> itemList, int key)
{
	int index = 0;
	list<Item*>::iterator it;
	it = itemList.begin();
	while (index < selectorIndex)
	{
		index++;
		it++;
	}
	//cout << "You have chosen: " << (*it)->id << endl
	//	<< "\t" << (*it)->getStat() << (*it)->stat;
	cout << "You have chosen: " << (*it)->name << endl;

	if ((*it)->useVal == 0 || (*it)->useVal == 1)
	{
		Item* itemPointer = *it;
		cout << "\nWould you like to equip this item? ( Y or N )\n";
		char choice = _getch();
		if (choice == 'y' || choice == 'Y')
		{
			addtoEquipped((*it)->name, *itemPointer, equipped);
		}
	}
	_getch();
	selectorMenu(itemList, key);
}

void gameHandler::selectorMenu(list<Item*> itemList, int key)
{
	list<Item*>::iterator it;
	it = itemList.begin();
	int listSize = 0;
	system("CLS");
	do
	{
		listSize++;
		it++;
	} while (it != itemList.end());
	char* place;
	place = new (nothrow) char[listSize];
	for (int i = 0; i < listSize; i++)
	{
		if (i != selectorIndex)
			place[i] = '-';
		else
			place[i] = '>';
	}
	int i = 0;
	cout << "--INVENTORY ( Select Mode )--\n";
	it = itemList.begin();
	do
	{
		//cout << place[i] << "\t|" << (*it)->id << "|" <<
		//	(*it)->getStat() << (*it)->stat << "|" << endl;
		cout << place[i] << "\t|" << (*it)->name << "|" << endl;

		i++;
		it++;
	} while (it != itemList.end());

	cout << "Use the following commands to navigate...\n"
		<< "\tw to move the selector up\n"
		<< "\ts to move the selector down\n"
		<< "\td to select an item\n"
		<< "\ta to go back to the game menu\n\n";

	switch (_getch())
	{
	case 's':
		//code for down
		if (selectorIndex < listSize - 1)
			selectorIndex++;
		else
			selectorIndex = 0;
		selectorMenu(itemList, key);
		break;
	case 'w':
		//code for up
		if (selectorIndex > 0)
			selectorIndex--;
		else
			selectorIndex = listSize - 1;
		selectorMenu(itemList, key);
		break;
	case 'd':
		//code for select
		itemSelected(selectorIndex, itemList, key);
		break;
	case 'a':
		//code for back
		if (key == 1)
			gameMenu();
		else if (key == 2)
			return;
		break;
	default:
		break;
	}

	delete[] place;
}