/*
======================================================================
JUEGO CREADO COMPLETAMENTE POR EMMANUEL ALEJANDRO HERNÁNDEZ VELÁZQUEZ
BASÁNDOSE EN UN PROYECTO DE JAVASCRIPT SIN NOMBRE.
								~Ein~
=====================================================================
*/

#include <iostream>   // std::cout
#include <string>     // std::string, std::to_string
#include <typeinfo> //typeid()
#include <vector>  //
#include "miniwin.h"
#include "Cuadrados.h" //Cabecera donde tengo todas mis clases
#include <math.h>
#include <conio.h>
#include <time.h>
using namespace miniwin;
using namespace std;
bool ref=true;
long long int et=time(NULL); //enemy timer
long long int pt; //projectile timer
long long int ept=time(NULL);

clock_t ut=clock();
clock_t rt=clock();
clock_t part=clock();
//int mt=float(clock()-t)/CLOCKS_PER_SEC*1000;
int lastUp;
int lastRen;
float fr=65;
int frm=(1/fr)*1000;

void gameAction();
void createEnemy();
void pickShoot();
void createPart();
void createProj();

Player player= Player();
Boss boss;
vector<BProj> bProj;
vector<Proj> proj;
vector<Enemy> enemy;
vector<Part> parts;
vector<EProj> eProj;
string score,life;

int tec; //tecla
int sc; //score
bool bAlive=false; //Jefe vivo?
bool pAlive=true; //Player alive?
main(){
	
	//Generación de semilla para aleatorio
	srand(time(NULL));
	//enemy.push_back(Enemy(600,250));
	vredimensiona(600,600);
	do{
		
		lastUp=float(clock()-ut)/CLOCKS_PER_SEC*1000;
		lastRen=float(clock()-rt)/CLOCKS_PER_SEC*1000;
		
		if(lastUp>=15){
			gameAction();
		}
		
		if(lastRen>=frm){
			texto(30,570,"Render Update: "+to_string(int(1/((float)lastRen/1000))));
			refresca();
			rt=clock();
		}
				
	}while(tec!=ESCAPE && pAlive);
	vcierra();
}

void gameAction(){
		ut=clock();	
		borra();
		
		//Particle control
		createPart();
		//forEach particle
		for(int i=0;i<parts.size();i++){
			parts[i].posX-=8;
			if(parts[i].posX<-5)
				parts.erase(parts.begin()+i);
			if(parts.size()>120)
				parts.erase(parts.begin());
			parts[i].dibuja();
		}
		
		//mt=float(clock()-t)/CLOCKS_PER_SEC*1000;
		//t=clock()-t;
		//Show player stats
		color(BLANCO);
		sc=player.getScore();
		player.getLife();
		
		//Give the player movement
		player.posX=raton_x();
		player.posY=raton_y();
		player.dibuja();
		if(player.getLife()<=0)
			pAlive=false;	
		
		//Create projectiles if W is pressed
		tec=tecla();
		
		switch(tec){
			case '1':
				player.shoot=1;
				break;
			case '2':
				player.shoot=2;
				break;
			case '3':
				player.shoot=3;
				break;
		}
		
		if(tec=='w'||tec=='W'){
			
			switch(player.shoot){
				case 1:
					proj.push_back(Proj(1));
					break;
				case 2:
					proj.push_back(Proj(1));
					proj.push_back(Proj(2));
					proj.push_back(Proj(3));
					break;
			}
		}
		
		
		if(tec=='m' || tec=='M'){
			fr+=5;
			frm=(1/fr)*1000;
		}
		
		if(tec=='n' || tec=='N'){
			fr-=5;
			frm=(1/fr)*1000;
		}
		
		if(sc>25 && sc%26==0 && !bAlive){
			boss=Boss();
			pt=time(NULL);
			bAlive=true;
		}
		
		//Control de los enemigos y el jefe
		
		if(bAlive){
			boss.dibuja();
			pickShoot();
			if(boss.posX>510)
				boss.posX--;
			boss.posY= (sin(boss.asd*0.2)*180)+300;
			boss.colG=sin(boss.asd*3)*80+175;
			boss.asd+=0.1;
			color_rgb(20,200,0);
			//2 rectangulos que se crean contrarios uno a otro
			rectangulo_lleno(400,25,400-boss.porc*1.5,45);
			rectangulo_lleno(400,25,400+boss.porc*1.5,45);
			boss.porc=(boss.life*100)/1000;
		}
		
		if(boss.life<0 && bAlive){
			boss.~Boss();
			player.giveLife(50);
			player.giveScore(150);
			bProj.clear();
			bAlive=false;
		}
		
		createEnemy();

		//Ciclos forEach
		//forEach projectile
		for(int i=0;i<proj.size();i++){
			if(typeid(proj[i]).name()[1]=='P'){
				proj[i].posX+=15;
				switch(proj[i].stype){
					case 2:
						proj[i].posY+=sin(proj[i].asd)*10;
						proj[i].asd+=0.5;
						break;
					case 3:
						proj[i].posY+=-sin(proj[i].asd)*10;
						proj[i].asd+=0.5;
						break;
						
				}
				proj[i].dibuja();
			}
			if(proj[i].posX>610)
				proj.erase(proj.begin()+i);
				
			if(bAlive && boss.collision(proj[i])){
				boss.life--;
				proj.erase(proj.begin()+i);
			}
		}
		
		//forEach Enemy
		for(int i=0;i<enemy.size();i++){
			if(typeid(enemy[i]).name()[1]=='E'){
				switch(enemy[i].type){
					case 1:
						enemy[i].posX-=2;
						enemy[i].posY+=sin(enemy[i].asd)*2; //Movimiento de los enemigos
						enemy[i].asd+=(rand()%11)/10; //Aumenta asd en un número aleatorio entre 0 y 1
						break;
					case 2:
						enemy[i].posX-=4;
						enemy[i].posY=((1/sin(enemy[i].asd*4))*80)/2+300;
						enemy[i].asd+=0.01;
						break;
					case 3:
						enemy[i].posX-=4;
						enemy[i].posY=((1/cos(enemy[i].asd*4))*80)/2+300;
						enemy[i].asd+=0.01;
						break;
					default:
						enemy[i].posY--;
				}
				enemy[i].dibuja();
			}
			
			if(enemy[i].posX<-20)
				enemy.erase(enemy.begin()+i);
				
			//forEach projectile interacting with enemy
			for(int j=0;j<proj.size();j++){
				if(enemy[i].collision(proj[j])){	
					enemy[i].life--;
					proj.erase(proj.begin()+j); // proj.begin() es un iterador especial de los vectores
					if(enemy[i].life<1){
						enemy.erase(enemy.begin()+i);
						player.giveScore(2);
					}				
					break;
				}
			}
			
			//check collision with player
			if(enemy[i].collision(player)){
				player.giveLife(-10);
				enemy.erase(enemy.begin()+i);
			}
		}
		
		
//		createProj();
//		//forEach Enemy projectile
//		for(int i=0;i<eProj.size();i++){
//			eProj[i].posX+=eProj[i].dx;
//			eProj[i].posY+=eProj[i].dy;
//			eProj[i].dibuja();
//			if(eProj[i].posX>600 || eProj[i].posY>600)
//				eProj.erase(eProj.begin()+i);
//		}
		
		//forEach Boss projectile
		for (int i=0;i<bProj.size();i++){
			
			bProj[i].posX-=bProj[i].dx;
//			bProj[i].posY=(bProj[i].m*bProj[i].posX)+bProj[i].b;
			bProj[i].posY-=bProj[i].dy;
//		proj[i].posY=proj[i].m*proj[i].posX+proj[i].b;
			if(typeid(bProj[i]).name()[1]=='B' && bProj[i].type==2){
				bProj[i].posX+=sin(bProj[i].asd/2)*10;
				bProj[i].asd+=1;
			}
			if(typeid(bProj[i]).name()[1]=='B' && bProj[i].type==3){
				bProj[i].posY+=sin(bProj[i].asd/2)*10;
				bProj[i].asd+=1;
			}
			
			bProj[i].dibuja();
			
			if(player.collision(bProj[i])){
				player.giveLife(-5);
				bProj.erase(bProj.begin()+i);
			}
			
			if(bProj[i].posX<0||bProj[i].posY<0){
				bProj.erase(bProj.begin()+i);
			}

		}
		
	texto(30,550,"Game Update: "+to_string(int(1/((float)lastUp/1000))));
}

void createPart(){
	if(int(float(clock()-part)/CLOCKS_PER_SEC*1000)>=50){
		parts.push_back(Part(605,float(rand()%600)));
		part=clock();
	}
}

void createEnemy(){
	if(time(NULL)==et+1){
		enemy.push_back(Enemy(600,rand()%500+50,(rand()%3)+1));
		et=time(NULL);
	}
}

void pickShoot(){
	if(time(NULL)>=pt+1){
		int sel=rand()%3;
		switch(sel){
			case 0:
				bProj.push_back(BProj(player,boss.posX+85-55,boss.posY-22-55,1));
				bProj.push_back(BProj(player,boss.posX+85-55,boss.posY+70,1));
				break;
			case 1:
				bProj.push_back(BProj(player,boss.posX+85-55,boss.posY-22-55,2));
				bProj.push_back(BProj(player,boss.posX+85-55,boss.posY+70,2));
				break;
			case 2:
				bProj.push_back(BProj(player,boss.posX+85-55,boss.posY-22-55,3));
				bProj.push_back(BProj(player,boss.posX+85-55,boss.posY+70,3));		
				break;
		}
		pt=time(NULL);
	}
}

void createProj(){
	if(time(NULL)>=ept+1){
		eProj.push_back(EProj(player,50));
	}
}

