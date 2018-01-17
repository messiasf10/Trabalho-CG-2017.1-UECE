#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <time.h>

#define LARGURA  1000
#define ALTURA   600
#define QUANTIDADE_ESTRELAS 1000
#define TAMANHO_UNIVERSO 20

#define pi 4*atan(1)

GLfloat angle,fAspect,x,z,c=1;

GLfloat xMercurio,zMercurio;
GLfloat xVenus,zVenus;
GLfloat xTerra,zTerra;
GLfloat xMarte,zMarte;
GLfloat xJupter,zJupter;
GLfloat xSaturno,zSaturno;
GLfloat xUrano,zUrano;
GLfloat xNetuno,zNetuno;

float tetaMercurio = 0;
float tetaVenus = 0;
float tetaTerra = 0;
float tetaMarte = 0;
float tetaJupter = 0;
float tetaSaturno = 0;
float tetaUrano = 0;
float tetaNetuno = 0;

int starsX[QUANTIDADE_ESTRELAS], starsY[QUANTIDADE_ESTRELAS], starsZ[QUANTIDADE_ESTRELAS];
int flagStars = 0;

GLint rox = 0, roy = 0 , roz = 0, ang;

int year = 0, day = 0, wire = 0;

double rotationX = 0.0;
double rotationY = 0.0;
double scaleXYZ = 1.0;
double variacaoScale = 0.005;

int last_press_x = 0;
int last_press_y = 0;

void Desenha_Origem() {
    /* Define a cor Azul (BLUE) */
    glColor3f(0.0, 0.0, 1.0);
    /* Define o tamanho do ponto para 4x4 pixels */
    glPointSize(4);
    glBegin(GL_POINTS);
    glVertex3i(0, 0, 0);
    glEnd();
}

void Desenha_Eixos_Coordenados() {
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

void Define_Posicao_Estrelas(){
    if(flagStars != 0)
        return;
    int i = 0;
    srand(time(NULL));
    for(i = 0; i < QUANTIDADE_ESTRELAS; i++){
        starsX[i] = (rand() % TAMANHO_UNIVERSO);
        starsY[i] = (rand() % TAMANHO_UNIVERSO);
        starsZ[i] = (rand() % TAMANHO_UNIVERSO);
    }
    flagStars = 1;
}

void Desenha_Estrelas() {
    Define_Posicao_Estrelas();
    int i;
    srand(time(NULL));
    for (i = 0; i < 200; i++) {
        // + + +
        glPushMatrix();
        glColor3f(1.0,1.0,1.0);
        glTranslatef(starsX[i],starsY[i],starsZ[i]);
        glutSolidSphere(0.02, 7, 7);
        glPopMatrix();
        // + + -
        glPushMatrix();
        glColor3f(1.0,1.0,1.0);
        glTranslatef(starsX[i],starsY[i],-starsZ[i]);
        glutSolidSphere(0.02, 7, 7);
        glPopMatrix();
        // - + -
        glPushMatrix();
        glColor3f(1.0,1.0,1.0);
        glTranslatef(-starsX[i],starsY[i],-starsZ[i]);
        glutSolidSphere(0.02, 7, 7);
        glPopMatrix();
        // - + +
        glPushMatrix();
        glColor3f(1.0,1.0,1.0);
        glTranslatef(-starsX[i],starsY[i],starsZ[i]);
        glutSolidSphere(0.02, 7, 7);
        glPopMatrix();
        // + - -
        glPushMatrix();
        glColor3f(1.0,1.0,1.0);
        glTranslatef(starsX[i],-starsY[i],-starsZ[i]);
        glutSolidSphere(0.02, 7, 7);
        glPopMatrix();
        // - - -
        glPushMatrix();
        glColor3f(1.0,1.0,1.0);
        glTranslatef(-starsX[i],-starsY[i],-starsZ[i]);
        glutSolidSphere(0.02, 7, 7);
        glPopMatrix();
        // - - +
        glPushMatrix();
        glColor3f(1.0,1.0,1.0);
        glTranslatef(-starsX[i],-starsY[i],starsZ[i]);
        glutSolidSphere(0.02, 7, 7);
        glPopMatrix();
        // + - +
        glPushMatrix();
        glColor3f(1.0,1.0,1.0);
        glTranslatef(starsX[i],-starsY[i],starsZ[i]);
        glutSolidSphere(0.02, 7, 7);
        glPopMatrix();
    }
}

void definirIluminacao(void) {
    GLfloat luzAmbiente[4]= {0.2,0.2,0.2,1.0};
    GLfloat luzDifusa[4]= {0.7,0.7,0.7,1.0};
    GLfloat luzEspecular[4]= {1.0, 1.0, 1.0, 1.0};
    GLfloat posicaoLuz[4]= {0.0, 0.0, 0.0, 1.0};
    GLfloat posicaoLuzEsquerda[4]= {3.0, 0.0, 0.0, 1.0};
    GLfloat posicaoLuzDireita[4]= {-3.0, 0.0, 0.0, 1.0};
    GLfloat posicaoLuzCima[4]= {0.0, 3.0, 0.0, 1.0};
    GLfloat posicaoLuzBaixo[4]= {0.0, -3.0, 0.0, 1.0};

    // Capacidade de brilho do material
    GLfloat especularidade[4]= {1.0,1.0,1.0,1.0};
    GLint especMaterial = 60;

    // Define a refletancia do material
    glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
    // Define a concentracao do brilho
    glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

    // Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

    // Define os parametros da luz de numero 0 (Dentro do Sol)
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

    // Define os parametros da luz de numero 1 (Lado esquedro do sol)
    //glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa );
    //glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular );
    glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuzEsquerda );

    // Define os parametros da luz de numero 2 (Lado direito do sol)
    glLightfv(GL_LIGHT2, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, luzDifusa );
    //glLightfv(GL_LIGHT2, GL_SPECULAR, luzEspecular );
    glLightfv(GL_LIGHT2, GL_POSITION, posicaoLuzDireita );

    // Define os parametros da luz de numero 3 (Em cima do sol)
    //glLightfv(GL_LIGHT3, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, luzDifusa );
    //glLightfv(GL_LIGHT3, GL_SPECULAR, luzEspecular );
    glLightfv(GL_LIGHT3, GL_POSITION, posicaoLuzCima );

    // Define os parametros da luz de numero 4 (Abaixo do sol)
    glLightfv(GL_LIGHT4, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT4, GL_DIFFUSE, luzDifusa );
    //glLightfv(GL_LIGHT4, GL_SPECULAR, luzEspecular );
    glLightfv(GL_LIGHT4, GL_POSITION, posicaoLuzBaixo );
}

void Desenha(void) {
    // Limpa a janela e o depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    definirIluminacao();

    // Definindo cor do Universo
    glColor3f(0.0f, 0.0f, 0.0f);

    glMatrixMode(GL_PROJECTION);

    /* Rotaciona os objetos para visualizar a 3 dimensao */
    glRotatef(rotationY, 1.0, 0.0, 0.0); /* Rotaciona em torno do X */
    glRotatef(rotationX, 0.0, 1.0, 0.0); /* Rotaciona em torno de Y */
    glTranslatef(rox,roy,roz);

    glMatrixMode(GL_MODELVIEW);

    glScalef(scaleXYZ,scaleXYZ,scaleXYZ);
    glRotatef(20.0, 1.0, 0.0, 0.0); /* Rotaciona em torno do X */
    glRotatef(20.0, 0.0, 1.0, 0.0); /* Rotaciona em torno de Y */

    Desenha_Estrelas();
    Desenha_Origem();
    Desenha_Eixos_Coordenados();

    // Sol
    glPushMatrix();
    glRotatef ((GLfloat) day/10, 0.0, 1.0, 0.0);
    glColor3f (0.89, 0.79, 0.09);
    if (wire == 0) glutSolidSphere(2.0, 25, 25);
    else glutWireSphere(2.0, 25, 25);
    glPopMatrix();

    // Mercurio
    glPushMatrix();
    glTranslatef (xMercurio, 0, zMercurio);
    glRotatef ((GLfloat) day/5, 0.0, 1.0, 0.0);
    glColor3f (0.41, 0.41, 0.41);
    if (wire == 0) glutSolidSphere(0.2, 25, 25);
    else glutWireSphere(0.2, 25, 25);
    glPopMatrix();

    // Venus
    glPushMatrix();
    glTranslatef (xVenus, 0, zVenus);
    glRotatef ((GLfloat) day/3, 0.0, 1.0, 0.0);
    glColor3f (1.0, 0.27, 0.0);
    if (wire == 0) glutSolidSphere(0.4, 25, 25);
    else glutWireSphere(0.4, 25, 25);
    glPopMatrix();

    // Terra
    glPushMatrix();
    glTranslatef (xTerra, 0, zTerra);
    glRotatef ((GLfloat) day, 0.0, 1.0, 0.0);
    glColor3f (0.0, 1.0, 0.0);
    if (wire == 0) glutSolidSphere(0.3, 25, 25);
    else glutWireSphere(0.3, 25, 25);
    glPopMatrix();

    // Marte
    glPushMatrix();
    glTranslatef (xMarte, 0, zMarte);
    glRotatef ((GLfloat) day/10, 0.0, 1.0, 0.0);
    glColor3f (1.0, 0.0, 0.0);
    if (wire == 0) glutSolidSphere(0.2, 25, 25);
    else glutWireSphere(0.2, 25, 25);
    glPopMatrix();

    // Jupter
    glPushMatrix();
    glTranslatef (xJupter, 0, zJupter);
    glRotatef ((GLfloat) day/10, 0.0, 1.0, 0.0);
    glColor3f (0.41, 0.41, 0.41);
    if (wire == 0) glutSolidSphere(0.8, 25, 25);
    else glutWireSphere(0.8, 25, 25);
    glPopMatrix();

    // Saturno
    glPushMatrix();
    glTranslatef (xSaturno, 0, zSaturno);
    glRotatef ((GLfloat) day/10, 0.0, 1.0, 0.0);
    glColor3f (0.54, 0.27, 0.07);
    if (wire == 0) glutSolidSphere(0.45, 25, 25);
    else glutWireSphere(0.45, 25, 25);
    glPopMatrix();

    double aneisSaturno = 0;
    glPushMatrix();
    glTranslatef (xSaturno-0.1, 0, zSaturno-0.1);
    glBegin(GL_LINE_STRIP);
        for(; aneisSaturno <= 360; aneisSaturno++){
            xSaturno = 0.7*cos(aneisSaturno);
            zSaturno = 0.7*sin(aneisSaturno);
            glVertex3f(xSaturno,0.0,zSaturno);
            glVertex3f(xSaturno+0.2,0.0,zSaturno+0.2);
        }
    glEnd();
    glPopMatrix();

    // Urano
    glPushMatrix();
    glTranslatef (xUrano, 0, zUrano);
    glRotatef ((GLfloat) day/2, 0.0, 1.0, 0.0);
    glColor3f (0.67, 0.84, 0.90);
    if (wire == 0) glutSolidSphere(0.45, 25, 25);
    else glutWireSphere(0.45, 25, 25);
    glPopMatrix();

    // Netuno
    glPushMatrix();
    glTranslatef (xNetuno, 0, zNetuno);
    glRotatef ((GLfloat) day, 0.0, 1.0, 0.0);
    glColor3f (0.0, 0.74, 1.0);
    if (wire == 0) glutSolidSphere(0.40, 25, 25);
    else glutWireSphere(0.40, 25, 25);
    glPopMatrix();

    double rotaMercurio = 0;
    glColor3f(1.0,1.0,1.0);
    for(;rotaMercurio <= 720; rotaMercurio+=0.1){
        glBegin(GL_LINE_STRIP);
            xMercurio = 5*cos(rotaMercurio);
            zMercurio = 3*sin(rotaMercurio);
            glVertex3f(xMercurio,0.0,zMercurio);
            glVertex3f(xMercurio+0.02,0.0,zMercurio+0.02);
        glEnd();
    }

    double rotaVenus = 0;
    glColor3f(1.0,1.0,1.0);
    for(;rotaVenus <= 720; rotaVenus+=0.1){
        glBegin(GL_LINE_STRIP);
            xVenus = 7*cos(rotaVenus);
            zVenus = 5*sin(rotaVenus);
            glVertex3f(xVenus,0.0,zVenus);
            glVertex3f(xVenus+0.02,0.0,zVenus+0.02);
        glEnd();
    }

    double rotaTerra = 0;
    glColor3f(1.0,1.0,1.0);
    for(;rotaTerra <= 720; rotaTerra+=0.1){
        glBegin(GL_LINE_STRIP);
            xTerra = 9*cos(rotaTerra);
            zTerra = 7*sin(rotaTerra);
            glVertex3f(xTerra,0.0,zTerra);
            glVertex3f(xTerra+0.02,0.0,zTerra+0.02);
        glEnd();
    }

    double rotaMarte = 0;
    glColor3f(1.0,1.0,1.0);
    for(;rotaMarte <= 720; rotaMarte+=0.1){
        glBegin(GL_LINE_STRIP);
            xMarte = 11*cos(rotaMarte);
            zMarte = 9*sin(rotaMarte);
            glVertex3f(xMarte,0.0,zMarte);
            glVertex3f(xMarte+0.02,0.0,zMarte+0.02);
        glEnd();
    }

    double rotaJupter = 0;
    glColor3f(1.0,1.0,1.0);
    for(;rotaJupter <= 720; rotaJupter+=0.1){
        glBegin(GL_LINE_STRIP);
            xJupter = 13*cos(rotaJupter);
            zJupter = 11*sin(rotaJupter);
            glVertex3f(xJupter,0.0,zJupter);
            glVertex3f(xJupter+0.02,0.0,zJupter+0.02);
        glEnd();
    }

    double rotaSaturno = 0;
    glColor3f(1.0,1.0,1.0);
    for(;rotaSaturno <= 720; rotaSaturno+=0.1){
        glBegin(GL_LINE_STRIP);
            xSaturno = 15*cos(rotaSaturno);
            zSaturno = 13*sin(rotaSaturno);
            glVertex3f(xSaturno,0.0,zSaturno);
            glVertex3f(xSaturno+0.02,0.0,zSaturno+0.02);
        glEnd();
    }

    double rotaUrano = 0;
    glColor3f(1.0,1.0,1.0);
    for(;rotaUrano <= 720; rotaUrano+=0.1){
        glBegin(GL_LINE_STRIP);
            xUrano = 17*cos(rotaUrano);
            zUrano = 15*sin(rotaUrano);
            glVertex3f(xUrano,0.0,zUrano);
            glVertex3f(xUrano+0.02,0.0,zUrano+0.02);
        glEnd();
    }

    double rotaNetuno = 0;
    glColor3f(1.0,1.0,1.0);
    for(;rotaNetuno <= 720; rotaNetuno+=0.1){
        glBegin(GL_LINE_STRIP);
            xNetuno = 19*cos(rotaNetuno);
            zNetuno = 17*sin(rotaNetuno);
            glVertex3f(xNetuno,0.0,zNetuno);
            glVertex3f(xNetuno+0.02,0.0,zNetuno+0.02);
        glEnd();
    }

    glutSwapBuffers();
}

void Inicializa (void) {
    // Código da iluminação vinha aqui.

    glEnable(GL_COLOR_MATERIAL);// Habilita a definicao da cor do material a partir da cor corrente
    glEnable(GL_LIGHTING);//Habilita o uso de iluminacao
    glEnable(GL_LIGHT0);// Habilita a luz de numero 0
    glEnable(GL_LIGHT1);// Habilita a luz de numero 1
    glEnable(GL_LIGHT2);// Habilita a luz de numero 2
    glEnable(GL_LIGHT3);// Habilita a luz de numero 3
    glEnable(GL_LIGHT4);// Habilita a luz de numero 4
    glEnable(GL_DEPTH_TEST);// Habilita o depth-buffering

    angle = 25;
}

// Funcao usada para especificar o volume de visualizacao
void EspecificaParametrosVisualizacao(void) {
    glMatrixMode(GL_PROJECTION);// Especifica sistema de coordenadas de projecao
    glLoadIdentity();// Inicializa sistema de coordenadas de projecao
    gluPerspective(angle,fAspect,0.4,500);// Especifica a projecao perspectiva
    glMatrixMode(GL_MODELVIEW);// Especifica sistema de coordenadas do modelo
    glLoadIdentity();// Inicializa sistema de coordenadas do modelo
    gluLookAt(0.0, 0.0, 30.0,		/* eye */
              0.0, 0.0, 0.0,		/* look */
              0.0, 1.0, 0.0);		/* up */
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h) {
    if ( h == 0 ) h = 1;
    glViewport(0, 0, w, h);
    fAspect = (GLfloat)w/(GLfloat)h;
    EspecificaParametrosVisualizacao();
}

void spinDisplay(void) {
    year = (year + 1);
    day  = (day + 2 );
    glutPostRedisplay();
}

void GerenciaMouse(int button, int state, int x, int y) {
    if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ) {
        /* Pega a posicao atual do mouse */
        last_press_x = x;
        last_press_y = y;
    }
    if ( button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN ) {
        /* Pega a posicao atual do mouse */
        last_press_x = x;
        last_press_y = y;
    }
    EspecificaParametrosVisualizacao();
    glutPostRedisplay();
}

void GerenciaTEspeciais(int key, int x, int y) {
    switch(key){
    case GLUT_KEY_UP:
        roy+=1;
        break;
    case GLUT_KEY_DOWN:
        roy-=1;
        break;
    case GLUT_KEY_LEFT:
        rox-=1;
        break;
    case GLUT_KEY_RIGHT:
        rox+=1;
        break;
    }
    Desenha;
    glutPostRedisplay;
}

void Keyboard_Function(unsigned char key, int x, int y) {
    switch (key) {
    case '+':
        scaleXYZ += variacaoScale;
        break;
    case '-':
        scaleXYZ -= variacaoScale;
        break;
    }
    glutPostRedisplay();
}

void Timer(int value) {
    xMercurio = 5*cos(tetaMercurio);
    zMercurio = 3*sin(tetaMercurio);

    xVenus = 7*cos(tetaVenus);
    zVenus = 5*sin(tetaVenus);

    xTerra = 9*cos(tetaTerra);
    zTerra = 7*sin(tetaTerra);

    xMarte = 11*cos(tetaMarte);
    zMarte = 9*sin(tetaMarte);

    xJupter = 13*cos(tetaJupter);
    zJupter = 11*sin(tetaJupter);

    xSaturno = 15*cos(tetaSaturno);
    zSaturno = 13*sin(tetaSaturno);

    xUrano = 17*cos(tetaUrano);
    zUrano = 15*sin(tetaUrano);

    xNetuno = 19*cos(tetaNetuno);
    zNetuno = 17*sin(tetaNetuno);

    tetaMercurio += 0.001;
    tetaVenus += 0.003;
    tetaTerra += 0.002;
    tetaMarte += 0.0025;
    tetaJupter += 0.0008;
    tetaSaturno += 0.004;
    tetaUrano += 0.0015;
    tetaNetuno += 0.0009;

    spinDisplay();
    EspecificaParametrosVisualizacao();
    Desenha;
    glutPostRedisplay;
    glutTimerFunc(10,Timer, 5);
}

/* Callback chamada quando o mouse � movido com
 * alguma tecla pressionada */
void Mouse_Motion(int x, int y) {
    /* Se o mouse e movido para a esquerda, rotationX e decrementado
     * caso contrario, aumentado. Mesma ideia para rotationY */
    rotationX += (double)(x - last_press_x);
    rotationY += (double)(y - last_press_y);

    last_press_x = x;
    last_press_y = y;

    glutPostRedisplay;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(LARGURA,ALTURA);
    glutCreateWindow("Computacao Grafica UECE 2017.1 - Sistema Solar 3D - Alan e Messias");
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
