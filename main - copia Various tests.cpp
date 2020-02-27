#include <iostream>   // std::cout
#include <string>     // std::string, std::to_string
#include "miniwin.h"
#include "Cuadrados.h"
#include <math.h>
#include<conio.h>
#include <typeinfo>
#include <vector>
using namespace miniwin;
using namespace std;
bool ref=true;

main(){
	int x=95,y=112;
	int angx=1,angy=1;
	float asd=0;
	int wd=500,hg=500;
	int valc,i=0;
	string c;
	char str[5];
	vredimensiona(wd,hg);
	Cuadrado c1(30,15,15,ROJO);
	Cuadrado c2(30,45,15,VERDE);
	Cuadrado c3(30,-15,15,AZUL);
	Cuadrado cuads[]={c1,c2,c3};
	Player pl(30,10,10,ROJO);
	Proj pr1= Proj(10,0,0,VERDE);
	vector<Proj> pr;
	pr.push_back(Proj(10,0,0,VERDE));
	while(ref){
		borra();
		color_rgb(0,0,20);
		rectangulo_lleno(0,0,800,800);
		cuads[0].dibuja();
		cuads[1].dibuja();
		cuads[2].dibuja();
		pl.dibuja();
		pl.x=raton_x();
		pl.y=raton_y();
		color(BLANCO);
		valc=tecla();
		
		if((valc=='w'||valc=='W')){
			pr.push_back(Proj(10,0,0,VERDE));
		}
		c=typeid(pr[0]).name()[1];
		texto(i*4+20,i*4+20,c);
		
		for(i=0;i<pr.size();i++){
//			c=typeid(pr[i]).name()[1];
//			color(BLANCO);
//			texto(i*4+20,i*4+20,c);
			if(typeid(pr[i]).name()[1]=='P'){
				pr[i].dibuja();
				pr[i].x+=10;
			}
			if(pr[i].x>wd+15)
				pr.erase(pr.begin()+i);
		}
		
		color_rgb(66, 217, 244);
		//circulo_lleno(x,y,sin(asd)*8+40);
		if(x>=wd-50||x<=50)
			angx=-angx;
		else if(y>=hg-50||y<=50)
			angy=-angy;
		refresca();
		espera(16);
		y=raton_dentro()?raton_y():y+angy;
		x=raton_dentro()?raton_x():x+angx;
		asd+=0.1;
		if(valc==ESCAPE)
			ref=false;
	}
	vcierra();
}


void 
