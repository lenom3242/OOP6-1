#include <iostream>
#include <ctime>
#include <string>
using namespace std;
class GeomFigure {
public:
	virtual int getx() = 0;
	virtual int gety() = 0;
	virtual void information()=0;
	virtual void changeloc(int newx, int newy)=0;
	virtual float ploshadcalc()=0;
	virtual int perimetrcalc()=0;
	protected: GeomFigure(){}
public:
	virtual ~GeomFigure() {	cout << "GeomFigure is deleted" << endl;}
};

class Rectangle : public GeomFigure {
private:
	int x, y;
	int dlina;
	int shirina;
public:
	void changeloc(int newx, int newy) {
		x = newx;
		y = newy;
	}
	void setdlina(int newdlina) { dlina = newdlina; }
	void setshirina(int newshirina) { shirina = newshirina; }
	int getdlina() { return dlina; }
	int getshirina() { return shirina; }
	void information() {
		cout << "Dlina: " << dlina << endl;
		cout << "Shirina " << shirina << endl;
		cout << "(" << x << "; " << y << ")" << endl;
	}
	int getx() { return x; }
	int gety() { return y; }

	float ploshadcalc() {
		return dlina*shirina;
	}
	int perimetrcalc() {
		return (dlina+shirina)*2;
	}
	Rectangle(int dlina = 1, int shirina = 1,int x = 0, int y = 0) : x(x), y(y),GeomFigure(),dlina(dlina), shirina(shirina) {}
	~Rectangle() { cout << "Rectangle is deleted" << endl; }
};

class Circle : public GeomFigure {
private:
	int x, y;
	int rad;
public:
	int getx() { return x; }
	int gety() { return y; }
	void changeloc(int newx, int newy) {
		x = newx;
		y = newy;
	}
	void setrad(int newrad) { rad = newrad; }
	int getrad() { return rad; }
	void information() {
		cout << "radius: " << rad << endl;
		cout << "(" << x << "; " << y << ")" << endl;
	}
	float ploshadcalc() { return 3.14*rad*rad; }
	int perimetrcalc() { return 2*3.14*rad; }
	Circle(int rad = 1, int x = 0, int y = 0) : GeomFigure(),rad(rad),x(x), y(y)  {}
	~Circle() { cout << "Circle is deleted" << endl; }
};
class Triangle : public GeomFigure {
private:
	int x, y;
	int a = 0, b = 0, c = 0;
public:
	int getx() { return x; }
	int gety() { return y; }
	void changeloc(int newx, int newy){
		x = newx;
		y = newy;
	}
	void setabc(int newa, int newb, int newc) {
		if (newa + newb > newc && newa + newc > newb && newc + newb > newa) {
			a = newa; b = newb; c = newc;
		}
	}
	int geta() { return a; }
	int getb() { return b; }
	int getc() { return c; }
	void information() {
		cout << "A,B,C: " << a << "," << b << "," << c << endl;
		cout << "(" << x << "; " << y << ")" << endl;
	}
	float ploshadcalc() {
		int p = (a + b + c) / 2;
		return sqrt(p * (p - a) * (p - b) * (p - c));
	}
	int perimetrcalc() {
		return a + b + c;
	}
	Triangle(int x = 0, int y = 0, int newa = 3, int newb = 4, int newc = 3) : GeomFigure(),a(newa), b(newb), c(newc),x(x), y(y)  {
		if (newa + newb > newc && newa + newc > newb && newc + newb > newa) {
			a = newa; b = newb; c = newc;
		}
		else {
			a = 3;	b = 4;	c = 5;
		}
	}
	~Triangle() { cout << "Triangle is deleted" << endl; }
};
void changeloc(GeomFigure** ar) {
	for (int i = 0; i < 10; i++) {
		ar[i]->changeloc(0, 0);
	}
}
void FMAMF(int choice, GeomFigure* figure[]) {
	float max_sqr = INT_MIN, min_sqr =INT_MAX;
	int Index_min, Index_max;
	for (int i = 0; i < choice; i++) {
		if (figure[i]->ploshadcalc() > max_sqr) {
			max_sqr = figure[i]->ploshadcalc();
			Index_max = i;
		}
		if (figure[i]->ploshadcalc() < min_sqr) {
			min_sqr = figure[i]->ploshadcalc();
			Index_min = i;
		} 
	}
	figure[Index_max]->information();
	figure[Index_min]->information();
}
void replacemax(int choice, GeomFigure** figure) {
	float max = 0;
	int maxi = 0;
	for (int i = 0; i < choice; i++)
		if (sqrt(figure[i]->getx() * figure[i]->getx() + figure[i]->gety() * figure[i]->gety()) > max) {
			max = sqrt(figure[i]->getx() * figure[i]->getx() + figure[i]->gety() * figure[i]->gety());
			maxi = i;
		}
	figure[maxi]->information();
	figure[maxi]->changeloc(0, 0);
	figure[maxi]->information();
}
void calculatep(float a, float b, float c) {
	cout << "Rectangles " << a / (a + b + c) * 100 << "%\n";
	cout << "Circles " << b / (a + b + c) * 100 << "%\n";
	cout << "Triangles " << c / (a + b + c) * 100 << "%\n";
}
void main() {
	int RecC = 0, CirC = 0, TriC = 0;
	srand(time(0));
	GeomFigure** figures = new GeomFigure * [100];
	int counter = rand() % 3;
	for (int i = 0; i < 100; i++) {
		switch (counter) {
		case 0: {
			figures[i] = new Rectangle(rand() % 25, rand() % 25, rand() % 25, rand() % 25);
			counter++;
			RecC++;
			break;
		}
		case 1: {
			figures[i] = new Circle(rand() % 10, rand() % 25, rand() % 25);
			counter++;
			CirC++;
			break;
		}
		case 2: {
			figures[i] = new Triangle(rand() % 25, rand() % 25, rand() % 25, rand() % 25, rand() % 25);
			counter++;
			TriC++;
			break;
		}
		}
		counter = rand() % 3;
	}
	int AllP=0, AllS=0;
	for (int i = 0; i < 100; i++) {
		AllP = AllP + figures[i]->perimetrcalc();
		
		AllS = AllS + figures[i]->ploshadcalc();
	}
	calculatep(RecC, CirC, TriC);
	cout << "All perimeters " << AllP << endl;
	cout << "All squares " << AllS << endl;
	FMAMF(100,figures);
	replacemax(100, figures);
}