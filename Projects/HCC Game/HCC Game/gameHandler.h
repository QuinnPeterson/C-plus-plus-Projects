#pragma once
#include <list>
#include <vector>

#include "Item.h"
#include "enemy.h"
#include "player.h"
using namespace std;


class gameHandler
{
	/*
	Create two Player objects, utilizing the existing classes, have these two players battle.
	*/
private:
	player battlePlayer1, battlePlayer2;
	void doPlayerVPlayerBattle();

public:
	string playerName;
	player gamePlayer;
	int input;
	int inventorySize;
	int selectorIndex;
	int selectorIndex2;
	int selected;

	//Items 
	list<Item*> inventory;
	list<Item*> equipped;
	Item selectedItem;

	int curEnemy;
	vector<enemy> enemies;

	void gameInit();
	void gameMenu();
	void createPlayer();
	void createEnemies();
	void battle();
	void quitGame(string message);

	bool checkRange(int numToCheck, int min, int max);

	int fightMenu(Item selectedWeapon, list<Item*> inventory, enemy curEnemy);

	void createWeapon(string id, int dmg, int uses, list<Item*>& list);
	void createPotion(string id, int boost, int qty, list<Item*>& list);
	void createItem(string id, int stat, list<Item*>& list);
	void useItemFromInventory(Item& i);

	void addtoEquipped(string id, Item gameItem, list<Item*>& equipped);
	void selectorMenu(list<Item*> itemList, int key);
	void displayList(list<Item*>& itemList, int key);
	void itemSelected(int selectorIndex, list<Item*> list, int key);
	
};

