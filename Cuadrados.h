#include "miniwin.h"
#include <math.h>
#include <stdlib.h>
#include <string>
using namespace std;
using namespace miniwin;
//SOLUCIONAR LOS PROBLEMAS DE INCOMPLETE TYPE
bool isBetween(int,int,int);
//int colorPicker();

class Cuadrado;
class Enemy;
class Proj;
class Player;
class Boss;
class BProj;
class Part;

class Cuadrado{
	public:
		int width,height,colR,colG,colB;
		float posX,posY;
		Cuadrado();
		dibuja();
};

class Player : public Cuadrado{
	private:
		int life, score;
	public:
		int shoot=1;
		Player();
		~Player();
		void giveScore(int sc){
			score+=sc;
		}
		void giveLife(int lf){
			life+=lf;
		}
		bool collision(Enemy en);
		bool collision(BProj en);
		int getScore(){
			int sc=score;
			string scr="Puntuación: "+to_string(sc);
			texto(20,20,scr);
			return score;
		}
		int getLife(){
			color(VERDE);
			rectangulo_lleno(20,40,life+20,60);
			return life;
		}
	
};

//Proyectiles del jugador
class Proj: public Cuadrado{
	public:
		int stype;
		float asd=0;
		Proj(int);
		~Proj();
//		bool collision(Enemy en);
};

class Enemy : public Cuadrado{
	public:
		float asd;
		int life,type;
		Enemy(int,int,int);
		~Enemy();
		bool collision(Proj);
		bool collision(Player);
};

class Boss : public Cuadrado{
	public:
		int life;
		float asd;
		int porc;
		Boss();
		~Boss();
		bool collision(Proj);
		dibuja();
};

class BProj:public Cuadrado{
	public:
		float dx,dy,asd,m,ang;
		int type;
		BProj(Player,int,int,int);
		~BProj();
};

class EProj:public Cuadrado{
	public:
		float dx,dy;
		EProj(Player p,int);
		~EProj();	
};

class Part:public Cuadrado{
	public:
		Part(float,float);
		~Part();
};

Cuadrado::Cuadrado(){
}

Player::Player():Cuadrado(){
	posX=raton_x();
	posY=raton_y();
	life=150;
	score=0;
	//color_rgb(66, 220, 244);
	colR=66;
	colG=220;
	colB=244;
	width=40;
	height=40;
}


Enemy::Enemy(int winW,int Y, int t):Cuadrado(){
	posX=winW+55;
	posY=Y;
	width=40;
	height=80;
	asd=0;
	type=t;
	switch(t){
		case 1:
			life=4;
			break;
		case 2: case 3:
			life=8;
			break;
		case 4:
			life=10000;
			
	}
	colR=(rand()%100)+120;
	colG=(rand()%100)+120;
	colB=(rand()%100)+120;
}

Proj::Proj(int s):Cuadrado(){
	posX=raton_x();
	posY=raton_y();
	colR=0;
	colG=255;
	colB=200;
	width=10;
	height=10;
	stype=s;
}

Boss::Boss():Cuadrado(){
	life=1000;
	porc==(life*100)/1000;
	asd=0;
	colG=255;
	posX=750;
	posY=250;
	width=110;
	height=110;
}

BProj::BProj(Player p,int x,int y,int t){
	type=t;
	asd=0;
	colR=10*(t*t);
	colG=250-(t*t);
	colB=0;
	posX=x;
	posY=y;
	width=15;
	height=15;
	dy=(p.posY-posY);
	dx=(p.posX-posX);
	m=dy/dx;
	ang=atan(m);
	dx=20*cos(ang);
	dy=20*sin(ang);
}		

EProj::EProj(Player p, int speed){
	colR=255;
	colG=0;
	colB=0;
	width=10;
	height=10;
	posX=300;
	posY=300;
	dx=p.posX-posX;
	dy=p.posY-posY;
	
}

Part::Part(float x,float y){
	posX=x;
	posY=y;
	colR=255;
	colG=255;
	colB=255;
	width=3;
	height=3;
}

Enemy::~Enemy(){
}

Player::~Player(){
}


Proj::~Proj(){
}

Boss::~Boss(){
}

BProj::~BProj(){
}

EProj::~EProj(){
}


Part::~Part(){
}

Cuadrado::dibuja(){
	color_rgb(colR,colG,colB);
	rectangulo_lleno(posX-width/2,posY-height/2,posX+width/2,posY+height/2);
}


bool Player::collision(Enemy en){
	if ((isBetween(en.posX-en.width/2,this->posX-width/2,this->posX+width/2) || isBetween(en.posX+en.width/2,this->posX-width/2,this->posX+width/2)) && (isBetween(en.posY-en.height/2,this->posY-height/2,this->posY+height/2) || isBetween(en.posY+en.height/2,this->posY-height/2,this->posY+height/2)))
        return true;
    else
        return false;
}

bool Player::collision(BProj en){
	if ((isBetween(en.posX-en.width/2,this->posX-width/2,this->posX+width/2) || isBetween(en.posX+en.width/2,this->posX-width/2,this->posX+width/2)) && (isBetween(en.posY-en.height/2,this->posY-height/2,this->posY+height/2) || isBetween(en.posY+en.height/2,this->posY-height/2,this->posY+height/2)))
        return true;
    else
        return false;
}
		
bool Enemy::collision(Proj pr){
        if ((isBetween(pr.posX, this->posX-width/2,this->posX+width/2) || isBetween(pr.posX+pr.width/2,this->posX-width/2,this->posX+width/2)) && (isBetween(pr.posY,this->posY-height/2,this->posY+height/2) || isBetween(pr.posY+pr.height/2,this->posY-height/2,this->posY+height/2)))
            return true;
        else
            return false;
    }
    
bool Enemy::collision(Player pl){
        if ((isBetween(pl.posX, this->posX-width/2,this->posX+width/2) || isBetween(pl.posX+pl.width/2,this->posX-width/2,this->posX+width/2)) && (isBetween(pl.posY,this->posY-height/2,this->posY+height/2) || isBetween(pl.posY+pl.height/2,this->posY-height/2,this->posY+height/2)))
            return true;
        else
            return false;
    }

//bool Proj::collision(Enemy en){
//			if ((isBetween(en.posX-25,this->posX,this->posX+5) || isBetween(en.posX+en.width/2,this->posX,this->posX+5)) && (isBetween(en.posY,this->posY,this->posY+40) || isBetween(en.posY+en.height,this->posY,this->posY+40)))
//            return true;
//        else
//            return false;
//		}

Boss::dibuja(){
	//Rect superior
	color_rgb(0,colG,0);
	rectangulo_lleno(posX+70-55,posY-40-55,posX+70-55+40,posY-55);
	//Rect Medio
	rectangulo_lleno(posX-55,posY-55,posX-55+110,posY-55+110);
	//Rect inferior
	rectangulo_lleno(posX+70-55,posY+55,posX+70-55+40,posY+55+40);

	//Rect superior
	color_rgb(0,colG-50,0);
	rectangulo_lleno(posX+75-55,posY-35-55,posX+75-55+30,posY-55-5);
	//Rect Medio
	rectangulo_lleno(posX-50,posY-50,posX-55+105,posY-55+105);
	//Rect inferior
	rectangulo_lleno(posX+75-55,posY+60,posX+75-55+30,posY+60+30);
}

bool Boss::collision(Proj pr){
	if ((isBetween(pr.posX, this->posX-55,this->posX+55) || isBetween(pr.posX+pr.width/2,this->posX-55,this->posX+55)) && (isBetween(pr.posY,this->posY-55,this->posY+55) || isBetween(pr.posY+pr.height/2,this->posY-55,this->posY+55)))
            return true;
        else
            return false;
    }

bool isBetween(int val,int min,int max){
    if(val>=min && val<=max)
        return true;
    else
        return false;
}

