/*
 * Laboratorium Grafiki Komputerowej
 * Program do rysowania dywanu Sierpinskiego
 */

/* System */
#include<stdio.h>
#include<stdlib.h>

/* Biblioteka GLUT */
#include <GL/freeglut.h>

/* Deklaracje funkcji narzêdziowych */

/* Funkcja do rysowania */
void DrawScene(void);

/* Funkcja do rysowania Dywanu Sierpinskiego */
void drawCarpet(float x, float y, float width, int iteration, int maxIteration);

/* Funkcja do inicjacji OpenGLa */
void InitOpenGL(void);

/* Funkcja wywo³ywana w momentach zmiany rozmiarów okna */
void ReshapeWindow(int width, int height);

/* Funkcja rysujaca kwadratu */
void drawSquare(float x1, float y1, float sideLength, int isWhite);

/* Deklaracja globalnych zmiennych */

const int WIDTH = 490;
const int HEIGHT = 600;
int maxIteration;
float aSquare = 75.0f;

/* Globalny identyfikator g³ównego okna programu */
int mainWindow;

/* Funkcja main */
int main(int argc, char **argv)
{
	printf("Prosze podac liczbe iteracji: ");
	maxIteration = getchar() - 49;
	
	// Inicjujemy bibliotekê GLUT
	glutInit(&argc, argv);
	// Inicjujemy: format koloru, jeden bufor ramki
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	// Ustawiamy pocz¹tkowe wymiary okna
    glutInitWindowSize(600, 600);
	// Ustawiamy pozycjê okna - lewy górny naroznik
	glutInitWindowPosition(150, 150);
	// Tworzymy g³ówne okno programu
    mainWindow = glutCreateWindow("Dywan Sierpinskiego");

	// Sprawdzamy powodzenie operacji
	if(mainWindow == 0){
		puts("Nie mozna stworzyc okna!!!\nWyjscie z programu.\n");
		exit(-1);
	}

	// Czynimy aktywnym okno g³ówne programu
	glutSetWindow(mainWindow);

	// Tutaj rejestrujemy funkcje narzêdziowe - tzw. callbacks
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(ReshapeWindow);

	// ustawienia pocz¹tkowe
	InitOpenGL();

	// Wejœcie do pêtli programu
	glutMainLoop();
	
	return(0);
}

/* W tej funkcji okreœlamy to co ma byc narysowane na ekranie.
 * Jest wywo³ywana zawsze wtedy, gdy trzeba przerysowaæ ekran - bufor ramki.
 */
void DrawScene(void)
{
	// Czyœcimy okno aktualnym (domyœlnym) kolorem
	glClear(GL_COLOR_BUFFER_BIT);
	
	// Ustawiamy gruboœæ linii
	glLineWidth(1.0f);
	
	// Rysuj t³o pod dywan
	drawSquare(0.0f, 0.0f, aSquare, 1);
	
	// Rysuj dywan
	drawCarpet(0.0f, 0.0f, aSquare, 0, maxIteration);
	
	// Komenda wykonania poleceñ rysuj¹cych
	glFlush();
}

void drawCarpet(float x, float y, float width, int iteration, int maxIteration) {
    if(iteration > maxIteration) {
    	// warunek zerowy - rysujemy kwadrat
        drawSquare(x, y, width, 0);
    } else {
    	// Obliczamy nowa szerokosc rowna 1/3 starej
        width /= 3;
        // Uruchamiamy rekurencyjnie funkcje rysowania dywanu dla 8 podczesci
        drawCarpet(x,              y,                width, iteration + 1, maxIteration);
        drawCarpet(x+width,        y,                width, iteration + 1, maxIteration);
        drawCarpet(x+width+width,  y,                width, iteration + 1, maxIteration);
        drawCarpet(x,              y-width,          width, iteration + 1, maxIteration);
//        drawCarpet(x,              y+width,          width, iteration + 1, maxIteration); // srodek powinien byc pusty
        drawCarpet(x+width+width,  y-width,          width, iteration + 1, maxIteration);
        drawCarpet(x,              y-width-width,    width, iteration + 1, maxIteration);
        drawCarpet(x+width,        y-width-width,    width, iteration + 1, maxIteration);
        drawCarpet(x+width+width,  y-width-width,    width, iteration + 1, maxIteration);
    }
}

void drawSquare(float x1, float y1, float sideLength, int isWhite)
{
	if(isWhite == 1){
		// Ustawiamy bie¿¹cy kolor rysowania na bialy
		glColor3ub(255, 255, 255);
	} else{
		// Ustawiamy bie¿¹cy kolor rysowania na brazowy
		glColor3ub(150, 75, 0);
	}
    
    // Ustawiamy krawedzie kwadratu
    glBegin(GL_POLYGON);

	    glVertex2d(x1, y1);
	    glVertex2d(x1 + sideLength, y1);
	    glVertex2d(x1 + sideLength, y1 - sideLength);
	    glVertex2d(x1, y1 - sideLength);

    glEnd();
}

/* Ta funkcja s³u¿y do wstêpnej konfiguracji OpenGLa.
 * Zanim coœ narysujemy musimy wywo³aæ tê funkcjê.
 */
void InitOpenGL(void)
{
	// Usawiamy domyœlny, czarny kolor t³a okna - bufor ramki malujemy na czarno
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

/* Tê funkcjê wywo³uje system w momencie gdy uytkownik zmieni mysz¹
 * rozmiar g³ownego okna. jej zadaniem jest zachowanie propocji wymiarów
 * rysowanych obiektów niezale¿nie od wymiarów okna.
 */
void ReshapeWindow(int width, int height)
{
	int aspectRatio; // = width / height
	
	// Na wypadek dzielenia przez 0
	if(height == 0) height = 1;

	// Wyliczamy wspó³czynnik proporcji
	aspectRatio = width / height;

	// Ustawiamy wielkoœci okna okna urz¹dzenia w zakresie
	// od 0,0 do wysokoœæ, szerokoœæ
	glViewport(0, 0, width, height);
     
	// Ustawiamy uk³ad wspó³rzêdnych obserwatora
    glMatrixMode(GL_PROJECTION); 

	// Resetujemy macierz projkecji 
    glLoadIdentity();
    
	// Korekta  
    if(width <= height)
		glOrtho(-100.0, 100.0, -100.0/aspectRatio, 100.0/aspectRatio, 1.0, -1.0);  
     else
		glOrtho(-100.0*aspectRatio, 100.0*aspectRatio, -100.0, 100.0, 1.0, -1.0);
 
	// Ustawiamy macierz modelu
    glMatrixMode(GL_MODELVIEW);
    
	// Resetujemy macierz modelu
    glLoadIdentity();
	
}

