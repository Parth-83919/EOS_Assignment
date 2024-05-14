#include<stdio.h>
#include"square.h"
#include"rectangle.h"
#include"circle.h"

int main(){
	int side,len,wid,rad;

	side=2,len=4,wid=5,rad=2;

	printf("area of circle : %d\n",cir_area(rad));
	printf("area of square : %d\n",squ_area(side));
	printf("area of rectangle : %d\n",rec_area(len,wid));

}
