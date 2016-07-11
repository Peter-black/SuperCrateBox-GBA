#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include "gba.h"
#include "font.h"
#include "background.h"
#include "sprites.h"
#include "entity.h"

void enterMenu(int menu);

std::string toString(int number);
void drawText(int x, int y, std::string string);
void clearText();

void shoot();
void explode(int x, int y);
int spawnBullet(int type);
void spawnMonster();
bool tryMove(int x, int y, int testX, int testY, Entity& entity);
int checkMapCollision(int x, int y, int testX, int testY);
bool checkEntityCollision(Entity e1, Entity e2);

//Object locations - 0 = weapon, 1 = crate, 2 = player, 3-23 = enemies, 24-44 = bullets, 45-128 text

Player player(0,0);

std::vector<Monster> enemies;
const int MAX_ENEMIES = 20;

std::vector<Bullet> bullets;
const int MAX_BULLETS = 20;

Crate crate(0, 0, 0);

int weapon;
int score;

void init(){
	// Set display options.
	REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ | DCNT_BG0 | DCNT_BG1 | DCNT_BG2 | DCNT_BG3;
	
	// Set background 0 options.
	REG_BG0CNT = BG_CBB(0) | BG_SBB(30) | BG_8BPP | BG_REG_32x32;
	REG_BG0HOFS = 0;
	REG_BG0VOFS = 0;
	// Set background 1 options.
	REG_BG1CNT = BG_CBB(0) | BG_SBB(29) | BG_8BPP | BG_REG_32x32;
	REG_BG1HOFS = 0;
	REG_BG1VOFS = 0;
	// Set background 2 options.
	REG_BG2CNT = BG_CBB(0) | BG_SBB(28) | BG_8BPP | BG_REG_32x32;
	REG_BG2HOFS = 0;
	REG_BG2VOFS = 0;
	// Set background 3 options.
	REG_BG3CNT = BG_CBB(0) | BG_SBB(27) | BG_8BPP | BG_REG_32x32;
	REG_BG3HOFS = 0;
	REG_BG3VOFS = 0;
	
	LoadTileData(0, 0, backgroundTiles, backgroundTilesLen);
	LoadPaletteBGData(0, menuBGPal, menuBGPalLen);
	
	LoadTileData(4, 0, spritesTiles, spritesTilesLen);
	LoadTileData(4, 64, font_bold, 8192);
	LoadPaletteObjData(0, spritesPal, spritesPalLen);
	
	//Clear backgrounds
	for (int y = 0; y < 32; ++y){
	for (int x = 0; x < 32; ++x){
		SetTile(30, x, y, 0);
		SetTile(29, x, y, 0);
		SetTile(28, x, y, 0);
		SetTile(27, x, y, 0);
	}
	}
	
	//Set-up backgrounds from maps
	for(int i = 0; i < cloudBGMapLen; i++){
		SetTile(27, i%32, i/32, cloudBGMap[i]);
	};
	for(int i = 0; i < buildingBGMapLen; i++){
		SetTile(28, i%32, i/32, buildingBGMap[i]);
	};
	for(int i = 0; i < fenceBGMapLen; i++){
		SetTile(29, i%32, i/32, fenceBGMap[i]);
	};
	for(int i = 0; i < girderMapLen; i++){
		SetTile(30, i%32, i/32, girderMap[i]);
	};
}

void gameInit(){
	(&player)->~Player();
    new (&player) Player(116,76);
	
	for(int i = 0; i < enemies.size(); i++){
		enemies.at(i).setDead(true);
	}
	
	for(int i = 0; i < bullets.size(); i++){
		bullets.at(i).setDead(true);
	}
	
	(&crate)->~Crate();
    new (&crate) Crate(0,0,0);
	
	weapon = 1;
	score = 0;

	//Set-up Objects
	ClearObjects();
	
	//Weapon
	int shape = 0;
	if(weapon == 8)shape = 1;
	SetObject(0,
	          ATTR0_SHAPE(shape) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(player.getY()+1),
			  ATTR1_SIZE(0) | ATTR1_X(player.getX()+4),
			  ATTR2_ID8(22+weapon));
	
	//Crate
	SetObject(1,
	          ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(crate.getY()),
			  ATTR1_SIZE(0) | ATTR1_X(crate.getX()),
			  ATTR2_ID8(14));
	
	//Player
	SetObject(2,
	          ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(player.getY()),
			  ATTR1_SIZE(0) | ATTR1_X(player.getX()),
			  ATTR2_ID8(1));
}

int main()
{
	init();
	
	enterMenu(0);

	int cloudScroll = 0;
	int loopSlower = 0;
	bool shootCoolDown = true;
	int reloadTimer = 0;
	
	//GAME LOOP
	while (true)
	{	
		//INPUT
		if((REG_KEYINPUT & KEY_RIGHT) == 0){
			tryMove(2,0,player.getWidth()-2,player.getHeight()/2,player);
			player.setRunning(true);
			player.setDir(true);
		}
		if((REG_KEYINPUT & KEY_LEFT) == 0){
			tryMove(-2,0,0,player.getHeight()/2,player);
			player.setRunning(true);
			player.setDir(false);
		}
		if((REG_KEYINPUT & KEY_UP) == 0 || (REG_KEYINPUT & KEY_B) == 0){
			if(player.getLanded()){
				player.jump();
				player.updateFrame();
			}
			player.setJumpHeight(player.getJumpHeight()+4);
		}
		if((REG_KEYINPUT & KEY_A) == 0){
			if(shootCoolDown){
				if(weapon == 8){
					if(player.getDir())tryMove(-2,0,0,player.getHeight()/2,player);
					else tryMove(2,0,player.getWidth()-2,player.getHeight()/2,player);
				}else if(weapon == 1){
					if(player.getDir())tryMove(-1,0,0,player.getHeight()/2,player);
					else tryMove(1,0,player.getWidth()-2,player.getHeight()/2,player);
				}
				shoot();
				shootCoolDown = false;
				reloadTimer = 0;
			}
		}
		
		//Player movement
		if(player.getJumping()){
			if(!tryMove(0,-3,player.getWidth()/2,0,player)){
				player.setJumping(false);
			}
		}else{
			if(!tryMove(0,2,player.getWidth()/2,player.getHeight(),player)){
				tryMove(0,1,player.getWidth()/2,player.getHeight(),player);
				player.setLanded(true);
				player.setJumping(false);
			}else{
				player.setLanded(false);
			}
		}

		//Monster Movement
		for(int i = 0; i < enemies.size(); i++){
			if(!enemies.at(i).isDead()){
				if(enemies.at(i).getDir()){
					if(!tryMove(1,0,enemies.at(i).getWidth(),(enemies.at(i).getHeight()/2)+1,enemies.at(i))){
						enemies.at(i).setDir(false);
					}
				}else{
					if(!tryMove(-1,0,0,(enemies.at(i).getHeight()/2)+1,enemies.at(i))){
						enemies.at(i).setDir(true);
					}
				}
				tryMove(0,2,enemies.at(i).getWidth()/2,enemies.at(i).getHeight(),enemies.at(i));
				ObjBuffer[i+3].attr0 &= ~(ATTR0_HIDE);
			}else{
				ObjBuffer[i+3].attr0 |= ATTR0_HIDE;
			}
		}
		
		//Bullet movement
		for(int i = 0; i < bullets.size(); i++){
			if(!bullets.at(i).isDead()){
			
				int yMove = 0;
				if(rand() % 3 == 0)yMove = bullets.at(i).getLift(); 
				
				if(bullets.at(i).getType() == 4){
				
					tryMove(0,1,bullets.at(i).getWidth(),bullets.at(i).getHeight()+4,bullets.at(i));
					
				}else if(bullets.at(i).getType() == 6){
					if(player.getDir()){
						ObjBuffer[i+24].attr1 &= ~(ATTR1_HFLIP);
						bullets.at(i).move(player.getX()+8, player.getY());
					}else{
						ObjBuffer[i+24].attr1 |= ATTR1_HFLIP;
						bullets.at(i).move(player.getX()-8, player.getY());
					}	
					if(bullets.at(i).charge()){
						bullets.at(i).setDead(true);
						int number = 0;
						if(player.getDir())number = (SCREEN_WIDTH - player.getX())/8;
						else number = (0 + player.getX())/8;
	
						for(int i = 0; i < number; i++){
							spawnBullet(7);
						}
					}
				}else if(bullets.at(i).getType() == 7){
					if(bullets.at(i).charge())bullets.at(i).setDead(true);
				}else{
					if(bullets.at(i).getDir()){
						if(!tryMove(2,yMove,bullets.at(i).getWidth(), bullets.at(i).getHeight(), bullets.at(i))){	
							if(bullets.at(i).getType() == 3 && !bullets.at(i).getBounce()){
								bullets.at(i).setBounce(true);
								bullets.at(i).setDir(false);
							}else{
								bullets.at(i).setDead(true);
								if(bullets.at(i).getType() == 0
								|| bullets.at(i).getType() == 4){
									explode(bullets.at(i).getX(), bullets.at(i).getY());
								}
							}
						}
					}else{ 
						if(!tryMove(-2,yMove,bullets.at(i).getWidth(), bullets.at(i).getHeight(), bullets.at(i))){
							if(bullets.at(i).getType() == 3 && !bullets.at(i).getBounce()){
								bullets.at(i).setBounce(true);
								bullets.at(i).setDir(true);
							}else{
								bullets.at(i).setDead(true);
								if(bullets.at(i).getType() == 0
								|| bullets.at(i).getType() == 4){
									explode(bullets.at(i).getX(), bullets.at(i).getY());
								}
							}
						}
					}
				}
				ObjBuffer[i+24].attr0 &= ~(ATTR0_HIDE);
			}else{
				ObjBuffer[i+24].attr0 |= ATTR0_HIDE;
			}
		}
		
		for(int i = 0; i < enemies.size(); i++){
			if(!enemies.at(i).isDead()){
				if(checkEntityCollision(player, enemies.at(i))){
					player.setDead(true);
				}
				
				for(int k = 0; k < bullets.size(); k++){
					if(!bullets.at(k).isDead()){
						if(checkEntityCollision(bullets.at(k), enemies.at(i))){
							enemies.at(i).hurt(bullets.at(k).getDamage());
							if(bullets.at(k).getType() != 3
							&& bullets.at(k).getType() != 6
							&& bullets.at(k).getType() != 7){
								bullets.at(k).setDead(true);
								if(bullets.at(k).getType() == 0
								|| bullets.at(k).getType() == 4){
									explode(bullets.at(k).getX(), bullets.at(k).getY());
								}
							}
							break;
						}
					}
				}
			}
		}
		
		if(checkEntityCollision(player, crate)){
			crate.setDead(true);
			weapon = crate.getWeapon();
			score++;
		}
		
		if(crate.isDead()){
			switch(rand() % 7){
				case 0:crate.move(80,32);
				break;
				case 1:crate.move(150,32);
				break;
				case 2:crate.move(30,64);
				break;
				case 3:crate.move(200,64);
				break;
				case 4:crate.move(115,104);
				break;
				case 5:crate.move(80,144);
				break;
				case 6:crate.move(150,144);
				break;
			}
			int newWep = 0;
			do newWep = rand() % 9;
			while(newWep == weapon || newWep == 6);
			crate.setWeapon(newWep);
			crate.setDead(false);
		}
		
		//General Slow things
		if(loopSlower % 7 == 0){
			cloudScroll++;
			REG_BG3HOFS = cloudScroll;
		
			SetTile(30, 14, 19, 16+rand()%5);
			SetTile(30, 15, 19, 16+rand()%5);
			
			player.updateFrame();
			
			for(int i = 0; i < enemies.size(); i++){
				if(!enemies.at(i).isDead()){
					enemies.at(i).updateFrame();
				}
			}
			ObjBuffer[2].attr2 = ATTR2_ID8(player.getFrame());
			for(int i = 0; i < enemies.size(); i++){
				ObjBuffer[i+3].attr2 = ATTR2_ID8(enemies.at(i).getFrame());
			}
			
		}
		
		reloadTimer++;
		if(weapon == 0 || weapon == 5 || weapon == 6 || weapon == 7){
			if(reloadTimer >= 60){
				shootCoolDown = true;
			}
		}else if(weapon == 2 || weapon == 4){
			if(reloadTimer >= 45){
				shootCoolDown = true;
			}
		}else if (weapon == 3){
			if(reloadTimer >= 20){
				shootCoolDown = true;
			}
		}else if(weapon ==  1){
			if(reloadTimer >= 10){
				shootCoolDown = true;
			}
		}else{
			if(reloadTimer >= 5){
				shootCoolDown = true;
			}
		}
		if(reloadTimer > 1000)reloadTimer = 60;
		
		//Monster spawner
		if(rand()%100 == 0){
			spawnMonster();	
		}
		
		//Player state updates
		if(player.getJumping())player.setState(2);
		else if(player.getRunning())player.setState(1);
		else player.setState(0);
		
		if(!player.getDir()){
			ObjBuffer[0].attr1 |= ATTR1_HFLIP;
			ObjBuffer[2].attr1 |= ATTR1_HFLIP;
		}else{
			ObjBuffer[0].attr1 &= ~(ATTR1_HFLIP);
			ObjBuffer[2].attr1 &= ~(ATTR1_HFLIP);
		}
		
		if(weapon == 8)ObjBuffer[0].attr0 |= ATTR0_SHAPE(1);
		else ObjBuffer[0].attr0 &= ~(ATTR0_SHAPE(1));
		
		ObjBuffer[0].attr2 = ATTR2_ID8(22+weapon);
			
		for(int i = 0; i < enemies.size(); i++){
			if(!enemies.at(i).isDead()){
				if(!enemies.at(i).getDir())ObjBuffer[i+3].attr1 |= ATTR1_HFLIP;
				else ObjBuffer[i+3].attr1 &= ~(ATTR1_HFLIP);
			}
		}
		
		player.update();
		
		if(player.isDead())enterMenu(2);
	
		//Render
		if(!player.getDir()){
			if(weapon != 8)SetObjectX(0, player.getX()-4);
			else{
				if(player.getX()-12 <= 0) SetObjectX(0, 0);
				else SetObjectX(0, player.getX()-12);
			}	
		}else{
			SetObjectX(0, player.getX()+4);
		}
		SetObjectY(0, player.getY()+1);
		
		SetObjectX(1, crate.getX());
		SetObjectY(1, crate.getY());
		
		SetObjectX(2, player.getX());
		SetObjectY(2, player.getY());
		
		for(int i = 0; i < enemies.size(); i++){
			if(!enemies.at(i).isDead()){
				SetObjectX(i+3, enemies.at(i).getX());
				SetObjectY(i+3, enemies.at(i).getY());
			}
		}
		
		for(int i = 0; i < bullets.size(); i++){
			if(!bullets.at(i).isDead()){
				SetObjectX(i+24, bullets.at(i).getX());
				SetObjectY(i+24, bullets.at(i).getY());
			}
		}

		drawText(112,10,toString(score));
		
		WaitVSync();
		UpdateObjects();
		clearText();
		loopSlower++;
	}

	return 0;

}

void enterMenu(int menu){
	LoadPaletteBGData(0, menuBGPal, menuBGPalLen);
	
	bool active = true;
	int option = 0;
	int keyPressCoolDown = 30;
	if(menu == 0)ClearObjects();
	
	//MENU LOOP
	while(active){
		keyPressCoolDown--;
		if(keyPressCoolDown <= 0)keyPressCoolDown = 0;
		clearText();
		switch(menu){
			case 0://Main menu
			if((REG_KEYINPUT & KEY_UP) == 0){
				option = 0;
			}
			if((REG_KEYINPUT & KEY_DOWN) == 0){
				option = 1;
			}
			if((REG_KEYINPUT & KEY_A) == 0 && keyPressCoolDown == 0){
				if(option == 0){
					active = false;
					gameInit();
				}else{
					menu = 1;
					keyPressCoolDown = 30;
				}
			}
			drawText(60,20,"Super Crate Box");
			drawText(105,65,"PLAY");
			drawText(93,90,"CREDITS");
			
			if(option == 0)drawText(90, 65, ">      <");
			if(option == 1)drawText(78, 90, ">         <");
			break;
			
			case 1://Credits
			if((REG_KEYINPUT & KEY_A) == 0 && keyPressCoolDown == 0){
				menu = 0;
				keyPressCoolDown = 30;
			}
			if((REG_KEYINPUT & KEY_B) == 0 && keyPressCoolDown == 0){
				menu = 0;
				keyPressCoolDown = 30;
			}
			
			drawText(30, 20, "GBA - Super Crate Box");
			drawText(30,60, "Created by Peter Black");
			drawText(70,80, "for CGA 2014");
			drawText(8, 135, "Assets & Gameplay C Vlambeer");
			break;
			
			case 2://Game Over
			if((REG_KEYINPUT & KEY_A) == 0 && keyPressCoolDown == 0){
				active = false;
				gameInit();
			}
			if((REG_KEYINPUT & KEY_B) == 0 && keyPressCoolDown == 0){
				menu = 0;
				ClearObjects();
				keyPressCoolDown = 30;
			}
		
			drawText(82,60,"GAME OVER");
			drawText(85,80,"Score:");
			drawText(133,80,toString(score));
			drawText(77, 125,"A = Retry");
			drawText(65, 135,"B = Main Menu");
			
			
			break;
		}
		
		
		WaitVSync();
		UpdateObjects();
	}
	
	LoadPaletteBGData(0, backgroundPal, backgroundPalLen);
}

std::string toString(int number){
	int holder = number;
	
	int digits = 0; 
	
	do { holder /= 10; digits++; } while (holder > 0);
	char arr[digits+1];
	arr[digits] = 0;
	
	int divider = 1;
	for(int i = 0; i < digits; i++) divider *= 10;
	int value = 0;
	
	for(int i = 0; i < digits; i++){
		divider /= 10;
		
		int holder = number;
		value = holder/divider;
		
		arr[i] = (value%10) +48;
	}
	
	std::string str(arr);
	return str;
}

int activeLetters = 0;
void drawText(int x, int y, std::string string){
	int startPos = activeLetters;
	for(int i = 0; i < string.length(); i++){
		activeLetters++;
		SetObject(startPos+i+45,
	          ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(y),
			  ATTR1_SIZE(0) | ATTR1_X(x+(i*8)),
			  ATTR2_ID8(string.at(i) + 64));
	}
}

void clearText(){
	for(int i = 0; i < activeLetters; i++){
		SetObject(i+45, ATTR0_HIDE, 0, 0);
	}
	activeLetters = 0;
}

void shoot(){
	switch(weapon){
	case 0://bazooka
		spawnBullet(0);
	break;
	case 1://machine gun
		spawnBullet(1);
	break;
	case 2://shotgun
		for(int i = 0; i < 5; i++){
			bullets.at(spawnBullet(1)).setLift(rand() % 3 + (-1));
		}
	break;
	case 3://revolver
		spawnBullet(2);
	break;
	case 4://disc gun
		spawnBullet(3);
	break;
	case 5://mine
		spawnBullet(4);
	break;
	case 6://grenade launcher - not in game
		bullets.at(spawnBullet(5)).setLift(1);
	break;
	case 7://laser gun
		spawnBullet(6);
	break;
	case 8://minigun
		bullets.at(spawnBullet(1)).setLift(rand() % 3 + (-1));
	break;
	}
}

void explode(int x, int y){
	int radius = 10;
	int bullet = 0;
	for(int i = 0; i < 30; i++){
		bullet = spawnBullet(1);
		bullets.at(bullet).setLift(rand() % 16 + (-7));
		bullets.at(bullet).setDir(rand() % 2);
		bullets.at(bullet).move(x, y);
	}
}

int spawnBullet(int type){
	int i = 0;
	int count = 0;
	
	if(bullets.size() < MAX_BULLETS){
		bullets.push_back(Bullet(player.getX(), player.getY(), type, weapon));
		i = bullets.size()-1;
	}else{
		for(int k = 0; k < MAX_BULLETS; k++){
			if(bullets.at(k).getType() == 7)count++;
			if(bullets.at(k).isDead()){
				if(type == 7){
					if(player.getDir())bullets[k] = Bullet(player.getX()+(count*8),player.getY(),type, weapon);
					else bullets[k] = Bullet(player.getX()-(count*8),player.getY(),type, weapon);
					i = k;
				}else{
					bullets[k] = Bullet(player.getX(),player.getY(),type, weapon);
					i = k;
				}
				break;
			}
		}
	}
	
	SetObject(i+24,
			ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(bullets.at(i).getY()),
			ATTR1_SIZE(0) | ATTR1_X(bullets.at(i).getX()),
			ATTR2_ID8(bullets.at(i).getFrame()));
			
	bullets.at(i).setDir(player.getDir());
	if(!bullets.at(i).getDir()){
		ObjBuffer[i+24].attr1 |= ATTR1_HFLIP;
	}
	
	return i;
}

void spawnMonster(){
	bool type = true;
	bool dir = true;
	if(rand()%3 == 0)type = false;
	if(rand()%2 == 0)dir = false;
	
	int startFrame = 32;
	if(type)startFrame = 16;
	
	int i = 0;
	
	if(enemies.size() < MAX_ENEMIES){
		enemies.push_back(Monster(116,0,type));
		i = enemies.size()-1;
	}else{
		for(int k = 0; k < MAX_ENEMIES; k++){
			if(enemies.at(k).isDead()){
				enemies[k] = Monster(116,0,type);
				i = k;
				break;
			}
		}
	}
	
	SetObject(i+3,
			ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(enemies.at(i).getY()),
			ATTR1_SIZE(!type) | ATTR1_X(enemies.at(i).getX()),
			ATTR2_ID8(startFrame));
			
	enemies.at(i).setDir(dir);
}

bool tryMove(int x, int y, int testX, int testY, Entity& entity){
	if(checkMapCollision(entity.getX()+x, entity.getY()+y, testX, testY) == 1){
		entity.move(entity.getX()+x, entity.getY()+y);
		return true;
	}else if(checkMapCollision(entity.getX()+x, entity.getY()+y, testX, testY) == 2){
		entity.setDead(true);
		return true;
	}
	return false;
}

int checkMapCollision(int x, int y, int testX, int testY){
	testY -= 1;
	if(GetTile(30,((x+testX)/8), ((y+testY)/8)) == 0){
		return 1;
	}
	if(GetTile(30, ((x+testX)/8), ((y+testY)/8)) >= 21 
	&& GetTile(30, ((x+testX)/8), ((y+testY)/8)) <= 25){
		return 1;
	}
	if(GetTile(30, ((x+testX)/8), ((y+testY)/8)) >= 16 
	&& GetTile(30, ((x+testX)/8), ((y+testY)/8)) <= 20){
		return 2;
	}
	return 0;
}

bool checkEntityCollision(Entity e1, Entity e2){
	int x1 = e1.getX();
	int x2 = e2.getX();
	int y1 = e1.getY();
	int y2 = e2.getY();
	
	bool xCollide = false;
	bool yCollide = false;

	if(x1 <= x2){
		if(x2 - x1 <= e1.getWidth()){
			xCollide = true;
		}
	}else{
		if(x1 - x2 <= e2.getWidth()){
			xCollide = true;
		}
	}
	
	if(y1 <= y2){
		if(y2 - y1 <= e1.getHeight()){
			yCollide = true;
		}
	}else{
		if(y1 - y2 <= e2.getHeight()){
			yCollide = true;
		}
	}
	
	if(xCollide && yCollide){
		return true;
	}
	
	return false;
}