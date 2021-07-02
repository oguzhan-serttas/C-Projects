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


void trapez(struct Poly p, double a, double b, double n) {	//a alt sýnýr, b ust sýnýr, n yamuk sayýsý

	int i;
	double h;
	double answer = 0; //sonucumuz
	
	h = (b - a) / n;
	
	answer += (evaluate(p, b) + evaluate(p, a)) / 2;
	
	printf("x\t\tf(x)\n");
	printf("%f\t%f\n", a, evaluate(p, a));
	
	for(i = 1; i <= n - 1; i++) {
		answer += evaluate(p, a + h * i);
		printf("%f\t%f\n", a + h * i, evaluate(p, a + h * i));
	}
	
	printf("%f\t%f\n", b, evaluate(p, b));
	
	answer *= h;
	
	printf("\n\n 	Integralin sonucu : %f", answer);
	
	
	
}



int main() {
	struct Poly p1;
	double a, b, n;
	
	printf("Integrali hesaplanacak polinomun girilmesi \n");
	
	create(&p1);
	display(p1);
	
	printf("Integralin alt siniri : ");
	scanf("%lf", &a);
	
	printf("Integralin ust siniri : ");
	scanf("%lf", &b);
	
	printf("n degerini giriniz : ");
	scanf("%lf", &n);
	
	trapez(p1, a, b, n);
}
