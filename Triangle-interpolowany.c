/*
 * Laboratorium Grafiki Komputerowej
 * Pierwszy program wykorzystuj?cy OpenGL'a
 */

/* System */
#include<stdio.h>
#include<stdlib.h>

/* Biblioteka GLUT */
#include <GL/freeglut.h>

/* Deklaracje funkcji narz?dziowych */

/* Funkcja do rysowania */
void DrawScene(void);

/* Funkcja do inicjacji OpenGLa */
void InitOpenGL(void);

/* Funkcja wywo?ywana w momentach zmiany rozmiar?w okna */
void ReshapeWindow(int width, int height);

/* Deklaracja globalnych zmiennych */

/* Globalny identyfikator g??wnego okna programu */
int mainWindow;

/* Funkcja main */
int main(int argc, char **argv)
{
	// Inicjujemy bibliotek? GLUT
	glutInit(&argc, argv);
	// Inicjujemy: format koloru, jeden bufor ramki
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	// Ustawiamy pocz?tkowe wymiary okna
    glutInitWindowSize(800, 600);
	// Ustawiamy pozycj? okna - lewy g?rny naroznik
	glutInitWindowPosition(150,150);
	// Tworzymy g??wne okno programu
    mainWindow = glutCreateWindow("Pierwsze Laboratorium");

	// Sprawdzamy powodzenie operacji
	if(mainWindow == 0){
		puts("Nie mozna stworzyc okna!!!\nWyjscie z programu.\n");
		exit(-1);
	}

	// Czynimy aktywnym okno g??wne programu
	glutSetWindow(mainWindow);

	// Tutaj rejestrujemy funkcje narz?dziowe - tzw. callbacks
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(ReshapeWindow);

	// ustawienia pocz?tkowe
	InitOpenGL();

	// Wej?cie do p?tli programu
	glutMainLoop();
	
	return(0);
}

/* W tej funkcji okre?lamy to co ma byc narysowane na ekranie.
 * Jest wywo?ywana zawsze wtedy, gdy trzeba przerysowa? ekran - bufor ramki.
 */
void DrawScene(void)
{
	// Czy?cimy okno aktualnym (domy?lnym) kolorem
	glClear(GL_COLOR_BUFFER_BIT);
	
	// Ustawiamy grubo?? linii
	glLineWidth(5.0f);
	
	// Tworzenie prymityw?w graficznych zawsze ograniczamy funkcjami glBegin i glEnd
	glBegin(GL_TRIANGLES);
	
		// Ustawiamy bie??cy kolor rysowania na czerwony
		glColor3f(1.0f, 0.0f, 0.0f);
		
		// Dwa ko?ce pierwszego odcinka
		glVertex2f(-50.0f, 0.0f);
		
		// Zmieniamy kolor rysowania na zielony
		glColor3f(0.0f, 1.0f, 0.0f);
		
		// Dwa ko?ce drugiego odcinka
		glVertex2f(0.0f, 50.0f);
		
		// Zmieniamy kolor rysowania na niebieski
		glColor3f(0.0f, 0.0f, 1.0f);
		
		// Dwa ko?ce drugiego odcinka
		glVertex2f(50.0f, 0.0f);
	
	glEnd();
	
	// Komenda wykonania polece? rysuj?cych
	glFlush();
}

/* Ta funkcja s?u?y do wst?pnej konfiguracji OpenGLa.
 * Zanim co? narysujemy musimy wywo?a? t? funkcj?.
 */
void InitOpenGL(void)
{
	// Usawiamy domy?lny, czarny kolor t?a okna - bufor ramki malujemy na czarno
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

/* T? funkcj? wywo?uje system w momencie gdy uytkownik zmieni mysz?
 * rozmiar g?ownego okna. jej zadaniem jest zachowanie propocji wymiar?w
 * rysowanych obiekt?w niezale?nie od wymiar?w okna.
 */
void ReshapeWindow(int width, int height)
{
	int aspectRatio; // = width / height
	
	// Na wypadek dzielenia przez 0
	if(height == 0) height = 1;

	// Wyliczamy wsp??czynnik proporcji
	aspectRatio = width / height;

	// Ustawiamy wielko?ci okna okna urz?dzenia w zakresie
	// od 0,0 do wysoko??, szeroko??
	glViewport(0, 0, width, height);
     
	// Ustawiamy uk?ad wsp??rz?dnych obserwatora
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
