#include <iostream>
#include <string>

#include "miniwin.h"
using namespace miniwin;
using namespace std;
main(){
	int al_ven=300;
	int an_ven=300;
	int centro_X=an_ven/2;
	int centro_Y=al_ven/2;
	vredimensiona(an_ven,al_ven);
	color(BLANCO);

	
	string palabra;
	
	char letras[9];
	char pal[9]="HARDWARE";
	int i=0,tec;
	do{
		tec=tecla();
		if(tec!=17){
			if(tec==pal[i]){
				letras[i]=tec;
				i++;
			}else{
				circulo_lleno(centro_X,20,20);
			}
		}
	refresca();
	}while(i<8);
	palabra=letras;
	texto(centro_X,centro_Y+20,palabra);
	refresca();	
	
}
