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


void derivative(struct Poly p, double h, double x) {

	
	printf("Merkezi\t\tileri\t\tgeri\n");
	printf("%f\t", (evaluate(p, x + h) - evaluate(p, x - h)) / (2 * h));	//Merkezi Farklar Ýle Sayýsal Türev
	printf("%f\t", (evaluate(p, x + h) - evaluate(p, x)) / h);	//Ýleri Farklar Ýle Sayýsal Türev
	printf("%f\n", (evaluate(p, x) - evaluate(p, x - h)) / h);	//Geri Farklar Ýle Sayýsal Türev
}



int main() {
	struct Poly p1;
	double x, h;
	
	create(&p1);
	display(p1);
	
	printf("\nTurevi hesaplanacak nokta : ");
	scanf("%lf", &x);
	
	printf("h degeri : ");
	scanf("%lf", &h);
	
	derivative(p1, h, x);
}
