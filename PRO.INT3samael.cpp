#include<stdio.h>
int main()
{
    float cant, cm, ft, inc, yd;
    char tin;

   

    do {
    	 printf("Ingresa tu cantidad en metros: \n");
    scanf("%f", &cant);
        cm = cant / 0.01;
        inc = cant * 39.37;
        ft = cant * 3.28;
        yd = cant * 1.093;

        printf("Su equivalencia en: \n");
        printf("Centímetros: %f\n", cm);
        printf("Pulgadas: %f\n", inc);
        printf("Pies: %f\n", ft);
        printf("Yardas: %f\n", yd);

        printf("Ingresa cualquier letra para continuar (escribe 's' para terminar):\n");
        scanf(" %c", &tin); 
    } while (tin != 's' );
		
       
}
