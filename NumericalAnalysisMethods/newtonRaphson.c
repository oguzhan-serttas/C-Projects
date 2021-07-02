#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Term {
	double coeff;
	int exp;
};

struct Poly {
	int n;	//terim sayýsý
	struct Term* terms;
	
};

void create(struct Poly* p) {
	int i ,degree;
	printf("Polinomum derecesi : ");
	scanf("%d", &degree);
	p->n = degree + 1;
	
	p->terms = (struct Term*)calloc(p->n , sizeof(struct Term));
	
	for (i = p->n - 1; i >= 0; i--) {
		p->terms[i].exp = i;
		printf("x ^ %d  katsayisi : ", i);
		scanf("%lf", &p->terms[i].coeff);
		
	}
	
}

void display(struct Poly p) {
	int i;
	
	for(i = p.n - 1; i > 0; i--) {
		if(p.terms[i].coeff != 0)
			printf("%.2lfx^%d + ", p.terms[i].coeff, p.terms[i].exp);
	}
	if(p.terms[0].coeff != 0)
		printf("%.2lf ", p.terms[0].coeff);
	printf("\n");
}

double evaluate (struct Poly p, double x) {
	int i;
	double sum = 0;
	
	for(i = 0; i < p.n; i++) {
		sum += p.terms[i].coeff * pow(x, p.terms[i].exp);
	}
	
	return sum;
}

// p -> fonksiyon, dp-> türevi alýnmýþ fonksiyon
void newtonRaphson(struct Poly p, struct Poly dp, double epsilon, double x) {
	double prev, current, error;
	int step = 0;
	current = x;
	
	printf("\nStep\tprev\t\tcurrent\t\tf(prev)\t\tf'(prev)\tf(current)\tError\n");
	
	do {
		step += 1;
		prev = current;
		current = prev - (evaluate(p, prev) / evaluate(dp, prev));
		error = fabs(current - prev);
		printf("%d\t%f\t%f\t%f\t%f\t%f\t%f\n",step, prev, current, evaluate(p, prev), evaluate(dp, prev), evaluate(p, current), error);
				
	}while(error >= epsilon);
	
	printf("\n Bulunan Kok : %f\n", current);
	
}



int main() {
	struct Poly p1;
	struct Poly dp1;
	double x, epsilon;
	
	create(&p1);
	display(p1);
	
	printf("\nFonksiyonun turevinin girilme islemi \n\n");
	create(&dp1);
	display(dp1);
	
	printf("\nBaslangic degeri : ");
	scanf("%lf", &x);
	
	printf("Hata orani : ");
	scanf("%lf", &epsilon);
	
	newtonRaphson(p1, dp1, epsilon, x);
}
