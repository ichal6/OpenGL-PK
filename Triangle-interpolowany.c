/*
 * Laboratorium Grafiki Komputerowej
 * Pierwszy program wykorzystuj¹cy OpenGL'a
 */

/* System */
#include<stdio.h>
#include<stdlib.h>

/* Biblioteka GLUT */
#include <GL/freeglut.h>

/* Deklaracje funkcji narzêdziowych */

/* Funkcja do rysowania */
void DrawScene(void);

/* Funkcja do inicjacji OpenGLa */
void InitOpenGL(void);

/* Funkcja wywo³ywana w momentach zmiany rozmiarów okna */
void ReshapeWindow(int width, int height);

/* Deklaracja globalnych zmiennych */

/* Globalny identyfikator g³ównego okna programu */
int mainWindow;

/* Funkcja main */
int main(int argc, char **argv)
{
	// Inicjujemy bibliotekê GLUT
	glutInit(&argc, argv);
	// Inicjujemy: format koloru, jeden bufor ramki
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	// Ustawiamy pocz¹tkowe wymiary okna
    glutInitWindowSize(800, 600);
	// Ustawiamy pozycjê okna - lewy górny naroznik
	glutInitWindowPosition(150,150);
	// Tworzymy g³ówne okno programu
    mainWindow = glutCreateWindow("Pierwsze Laboratorium");

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
	glLineWidth(5.0f);
	
	// Tworzenie prymitywów graficznych zawsze ograniczamy funkcjami glBegin i glEnd
	glBegin(GL_TRIANGLES);
	
		// Ustawiamy bie¿¹cy kolor rysowania na czerwony
		glColor3f(1.0f, 0.0f, 0.0f);
		
		// Dwa koñce pierwszego odcinka
		glVertex2f(-50.0f, 0.0f);
		
		// Zmieniamy kolor rysowania na zielony
		glColor3f(0.0f, 1.0f, 0.0f);
		
		// Dwa koñce drugiego odcinka
		glVertex2f(0.0f, 50.0f);
		
		// Zmieniamy kolor rysowania na niebieski
		glColor3f(0.0f, 0.0f, 1.0f);
		
		// Dwa koñce drugiego odcinka
		glVertex2f(50.0f, 0.0f);
	
	glEnd();
	
	// Komenda wykonania poleceñ rysuj¹cych
	glFlush();
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
