#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#define LARGURA  600		/* Width */
#define ALTURA   600		/* Heigth */

#define pi 4*atan(1)

GLfloat angle, fAspect,x,z,c=1;

GLfloat xTerra=10,zTerra=10;

GLint rox=0, roy=0 , roz=0,ang;
static int year = 0, day = 0, wire = 0;
float teta=0;
float tetaTerra=0;

double rotationX = 0.0;
double rotationY = 0.0;

int last_press_x = 0;
int last_press_y = 0;

void Desenha_Origem()
{
	/* Define a cor Azul (BLUE) */
	glColor3f(0.0, 0.0, 1.0);
	/* Define o tamanho do ponto para 4x4 pixels */
	glPointSize(4);

	glBegin(GL_POINTS);
		glVertex3i(0, 0, 0);
	glEnd();
}

void Desenha_Eixos_Coordenados()
{
	/* Desenha Eixo +Y */
	glColor3f(1.0, 0.0, 0.0); /* RED */
	glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(0, ALTURA/2, 0);
	glEnd();

	/* Desenha Eixo -Y */
	glColor3f(1.0, 0.8, 0.8); /* RED claro */
	glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(0, -ALTURA/2, 0);
	glEnd();

	/* Desenha Eixo +X */
	glColor3f(0.0, 0.0, 1.0); /* BLUE */
	glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(LARGURA/2, 0, 0);
	glEnd();

	/* Desenha Eixo -X */
	glColor3f(0.8, 0.8, 1.0); /* BLUE claro */
	glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(-LARGURA/2, 0, 0);
	glEnd();

	/* Desenha Eixo +Z */
	glColor3f(0.0, 1.0, 0.0); /* GREEN */
	glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 0, LARGURA/2);
	glEnd();

	/* Desenha Eixo -Z */
	glColor3f(0.8, 1.0, 0.8); /* GREEN claro */
	glBegin(GL_LINES);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 0, -LARGURA/2);
	glEnd();

}

void Desenha_Estrelas(){
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(5,5,5);
    glutSolidSphere(0.02, 7, 7);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(-5,-5,-5);
    glutSolidSphere(0.02, 7, 7);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(3,-5,-5);
    glutSolidSphere(0.02, 7, 7);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(4,1,2);
    glutSolidSphere(0.02, 7, 7);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(1,2,3);
    glutSolidSphere(0.02, 7, 7);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(-5,5,2);
    glutSolidSphere(0.02, 7, 7);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(-2,2,3);
    glutSolidSphere(0.02, 7, 7);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(5,-3,3);
    glutSolidSphere(0.02, 7, 7);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(1,2,-4);
    glutSolidSphere(0.02, 7, 7);
    glPopMatrix();
    //glPointSize(10);
    //glBegin(GL_POINTS);
        //glVertex3i(5,5,5);
        //glVertex3i(5,20,20);
        //glVertex3i(10,10,10);
    //glEnd();
}

void Desenha(void)
{
	// Limpa a janela e o depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 0.0f);

	glMatrixMode(GL_PROJECTION);
    /* Rotaciona os objetos para visualizar a 3 dimens�o */
	glRotatef(rotationY, 1.0, 0.0, 0.0); /* Rotaciona em torno do X */
	glRotatef(rotationX, 0.0, 1.0, 0.0); /* Rotaciona em torno de Y */
	glTranslatef(rox,roy,roz);

	glMatrixMode(GL_MODELVIEW);
    Desenha_Estrelas();
	Desenha_Origem();
	Desenha_Eixos_Coordenados();

//--------------------------------------------------------------------------------------------------
  glPushMatrix(); //SOL
	glRotatef ((GLfloat) day/10, 0.0, 1.0, 0.0);
	glColor3f (0.89, 0.79, 0.09);
	if (wire == 0) glutSolidSphere(1.0, 25, 25);
	else glutWireSphere(1.0, 25, 25);
  glPopMatrix();
//--------------------------------------------------------------------------------------------------
  glPushMatrix(); //P1
	//glRotatef ((GLfloat) year, 0.0, 1.0, 0.0);//Veloc de Translacao
	//glTranslatef (0.0, 0.0, 2.0);//raio do Planeta
	//glRotatef ((GLfloat) day, 0.0, 1.0, 0.0);//Veloc de Rotacao
	glTranslatef (x, 0, z);
	glColor3f (0.0, 0.0, 1.0);
	//glColor3f (1.0, 0.5, 0.0);
	if (wire == 0) glutSolidSphere(0.3, 25, 25);
	else glutWireSphere(0.3, 25, 25);
  glPopMatrix();
//--------------------------------------------------------------------------------------------------
glPushMatrix(); //P2
	//glRotatef ((GLfloat) year, 0.0, 1.0, 0.0);//Veloc de Translacao
	//glTranslatef (0.0, 0.0, 2.0);//raio do Planeta
	//glRotatef ((GLfloat) day, 0.0, 1.0, 0.0);//Veloc de Rotacao
	glTranslatef (xTerra, 0, zTerra);
	glColor3f (0.0, 1.0, 0.0);
	//glColor3f (1.0, 0.5, 0.0);
	if (wire == 0) glutSolidSphere(0.3, 25, 25);
	else glutWireSphere(0.3, 25, 25);
  glPopMatrix();

/*
glPushMatrix();
glBegin(GL_LINE_STRIP);
	glColor3f( 1.0, 1.0 , 1.0);
	z=-3; c=1;
	while (z<=3)
	{
	z=z+c/10;
	x= sqrt(9-z*z);
	glVertex3f(x, z,0);
	//glVertex3f(-x, z,0);
	}
glEnd();
glPopMatrix();*/
//--------------------------------------------------------------------------------------------------

glutSwapBuffers();
}

void Inicializa (void)
{
	GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0};
	GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};	   // "cor"
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho"
	GLfloat posicaoLuz[4]={.0, .0, 0, 1.0};

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
	GLint especMaterial = 60;

 	// Especifica que a cor de fundo da janela sera' preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glShadeModel(GL_SMOOTH);// Habilita o modelo de colorizacao de Gouraud
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);// Define a refletancia do material
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);// Define a concentracao do brilho
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);// Ativa o uso da luz ambiente

	// Define os parametros da luz de numero 0
	//glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

	glEnable(GL_COLOR_MATERIAL);// Habilita a definicao da cor do material a partir da cor corrente
	glEnable(GL_LIGHTING);//Habilita o uso de iluminacao
	glEnable(GL_LIGHT0);// Habilita a luz de numero 0
	glEnable(GL_DEPTH_TEST);// Habilita o depth-buffering

	angle=25;
}

// Funcao usada para especificar o volume de visualizacao
void EspecificaParametrosVisualizacao(void)
{
	glMatrixMode(GL_PROJECTION);// Especifica sistema de coordenadas de projecao
	glLoadIdentity();// Inicializa sistema de coordenadas de projecao
	gluPerspective(angle,fAspect,0.4,500);// Especifica a projecao perspectiva
	glMatrixMode(GL_MODELVIEW);// Especifica sistema de coordenadas do modelo
	glLoadIdentity();// Inicializa sistema de coordenadas do modelo
	gluLookAt(30.0, 0.0, 0.0,		/* eye */
    		  0.0, 0.0, 0.0,		/* look */
    		  0.0, 1.0, 0.0);		/* up */
	// if (rox>0) gluLookAt(rox,roy,roz, 0,0,0, 0,1,0);
	// else gluLookAt(0,0,rox, 0,0,0, 0,1,0);
	// gluLookAt(rox,roy,roz, 0,0,0, 0,1,0);
	
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	if ( h == 0 ) h = 1;
	glViewport(0, 0, w, h);
	fAspect = (GLfloat)w/(GLfloat)h;
	EspecificaParametrosVisualizacao();
}

void spinDisplay(void)
{
  year = (year + 1);
  day  = (day + 2 );
  glutPostRedisplay();
}

void GerenciaMouse(int button, int state, int x, int y)
{
    if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
	{
		/* Pega a posi��o atua do mouse */
		last_press_x = x;
		last_press_y = y;
	}
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-in
		//	if (angle >= 10) angle -= 5;
			//glutIdleFunc(spinDisplay);
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-out
			//if (angle <= 130) angle += 5;
		}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

void GerenciaTEspeciais(int key, int x, int y){

if(key == GLUT_KEY_UP)
	{
	roy+=1; 
	// roy=0; roz=0;
	// ang+=10;
	}
if(key == GLUT_KEY_DOWN)
	{
	roy-=1;
	// roy=0; roz=0;
	// ang-=10;
	}
if(key == GLUT_KEY_LEFT)
	{
	// rox=0; 
	rox-=1;
	//  roz=0;
	// ang+=10; wire=0;
	}
if(key == GLUT_KEY_RIGHT)
	{
	rox+=1;
	//  roy-=1; roz=0;
	// ang-=10; wire=1;
	}

Desenha;
glutPostRedisplay();
}

void Keyboard_Function(unsigned char key, int x, int y)
{
 switch (key)
 {
  case 65:   // A
  {
  ++rox;
   break;
  }
  case 97:   // a
  {
  --rox;
   break;
  }
  case 'S' :    // S
  {
  ++roy;
   break;
  }
  case 's':    // s
  {
  --roy;
   break;
  }

  case 68 :    //D
  {
  ++roz;
   break;
  }

  case 100:    //d
  {
  --roz;
   break;
  }
 }

glutPostRedisplay();
}


void Timer(int value)
{

//if (z>=3 || z<=-3) c=c*(-1);
//z=z+c/10;
//x= (9-z*z)*c;

x=5*cos(teta);
z=3*sin(teta);

xTerra=7*cos(tetaTerra);
zTerra=5*sin(tetaTerra);
//teta = teta*180/pi + 1;
teta=teta+0.01;
tetaTerra=tetaTerra+0.02;
//if (teta==2*pi) teta=0;

spinDisplay();

EspecificaParametrosVisualizacao();
Desenha;
glutPostRedisplay();
glutTimerFunc(10,Timer, 5);
}

/* Callback chamada quando o mouse � movido com
 * alguma tecla pressionada */
void Mouse_Motion(int x, int y)
{
	/* Se o mouse � movido para a esquerda, rotationX � decrementado
	 * caso contr�rio, aumentado. Mesma ideia para rotationY */
	rotationX += (double)(x - last_press_x);
	rotationY += (double)(y - last_press_y);

	last_press_x = x;
	last_press_y = y;

	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600,600);
	//glutInitWindowSize(400,350);
	glutCreateWindow("Visualizacao 3D");
	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela);
	glutMouseFunc(GerenciaMouse);
	glutMotionFunc(Mouse_Motion);
	glutSpecialFunc(GerenciaTEspeciais);
	glutKeyboardFunc(Keyboard_Function);
	glutTimerFunc(500, Timer, 1);
	Inicializa();
	glutMainLoop();
}

