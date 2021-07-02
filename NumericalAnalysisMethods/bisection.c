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

void bisection(double a, double b, struct Poly p, double epsilon) {
	int step = 0;
	double c;
	double error;
	
	if(evaluate(p, a) * evaluate(p, b) >= 0) {
		if(evaluate(p, a) == 0) {
			printf("\n Bulunan Kok : %f\n", a);
			return;
		}
		else if(evaluate(p, b) == 0) {
			printf("\n Bulunan Kok : %f\n", b);
			return;
		}
		printf("F(a) * F(b) < 0 olmali !!\n");
		return;
	}
	
	printf("\nStep\ta\t\tb\t\tc\t\tf(c)\t\tError\n");
	

	do {
		step += 1;
		c = (a + b) / 2;
		//error = fabs(b - a) / pow(2, step);
		//error = fabs(b - a);
		error = fabs(evaluate(p, c));
		
		printf("%d\t%f\t%f\t%f\t%f\t%f\n",step, a, b, c, evaluate(p, c), error);

		if(evaluate(p, a) * evaluate(p, c) < 0)
			b = c;	// root a c arasýnda
		else
			a = c;	//root b c arasýnda
	} while( error >= epsilon);

	
	printf("\n Bulunan Kok : %f\n", c);
	
}

int main() {
	struct Poly p1;
	double a, b, epsilon;
	create(&p1);
	display(p1);
	
	printf("Araligi giriniz\n\n");
	printf("alt sinir : ");
	scanf("%lf", &a);
	
	printf("ust sinir : ");
	scanf("%lf", &b);
	
	printf("Hata orani : ");
	scanf("%lf", &epsilon);
	
	
	bisection(a, b, p1, epsilon);
}
