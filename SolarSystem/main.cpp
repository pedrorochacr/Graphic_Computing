/*
Nomes Integrantes:
Pedro Henrique Rocha de Castro- 20213004828
Matheus Shimizu Araujo- 20203000880
Luis Felipe Pessoa Lopes -20193002006
Ivia Marques Pereira Costa-20213006500

*/


#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <Math.h>


#define num_planetas 7
GLfloat  angle, cameraY, cameraZ ;

GLboolean luz=true;//luz inicia ligada

GLuint textSol;


struct Planetas{
    float translacao;//auxilia na posicao dos planetas
    float anguloTranslacao=0;//realiza a translacao
    float auxRaio=0;
    float raio;
    GLuint text;//inicializa as texturas dos planetas
};
struct Planetas planeta[num_planetas];

GLuint carregaTextura(const char* arquivo){//funcao para carregar texturas
  GLuint idTextura = SOIL_load_OGL_texture(
                     arquivo,
                     SOIL_LOAD_AUTO,
                     SOIL_CREATE_NEW_ID,
                     SOIL_FLAG_INVERT_Y
                    );

  if (idTextura == 0){
    printf("Erro do SOIL: '%s' - '%s'\n", arquivo, SOIL_last_result());
  }

  return idTextura;
}

void atualiza(int periodo){
    for(int i=0;i<num_planetas; i++){
        planeta[i].auxRaio+=2;
        if(planeta[i].auxRaio>360){
            planeta[i].auxRaio-=360;
        }
    }

    planeta[0].anguloTranslacao+= 3.04;
    if(planeta[0].anguloTranslacao>360){
        planeta[0].anguloTranslacao=0;
    }
    planeta[1].anguloTranslacao+= 2.43;
    if(planeta[1].anguloTranslacao>360){
        planeta[1].anguloTranslacao=0;
    }
    planeta[2].anguloTranslacao+= 2.0;
    if(planeta[2].anguloTranslacao>360){
        planeta[2].anguloTranslacao=0;
    }
    planeta[3].anguloTranslacao+= 1.5;
    if(planeta[3].anguloTranslacao>360){
        planeta[3].anguloTranslacao=0;
    }
    planeta[4].anguloTranslacao+= 1.3;
    if(planeta[4].anguloTranslacao>360){
        planeta[4].anguloTranslacao=0;
    }
    planeta[5].anguloTranslacao+= 1.2;
    if(planeta[5].anguloTranslacao>360){
        planeta[5].anguloTranslacao=0;
    }
    planeta[6].anguloTranslacao+= 1;
    if(planeta[6].anguloTranslacao>360){
        planeta[6].anguloTranslacao=0;
    }



    glutPostRedisplay();
    glutTimerFunc(periodo,atualiza, periodo);

}
void inicializaPlanetas(){

    planeta[0].translacao=2.8;//mercurio
    planeta[1].translacao=4.0;//venus
    planeta[2].translacao=7.5;//terra
    planeta[3].translacao=11;//marte
    planeta[4].translacao=14;//jupiter
    planeta[5].translacao=17;//saturno
    planeta[6].translacao=18;//urano

    planeta[0].raio= .5;
    planeta[1].raio= .9;
    planeta[2].raio= .7;
    planeta[3].raio= .63;
    planeta[4].raio= 1.3;
    planeta[5].raio= 0.9;
    planeta[6].raio= 1;

}
void inicializaTexturas(){

    textSol=carregaTextura("sol.jpg");
    planeta[0].text=carregaTextura("mercurio.png");;
    planeta[1].text=carregaTextura("venus.png");;
    planeta[2].text=carregaTextura("terra.jpg");;
    planeta[3].text=carregaTextura("marte.png");;
    planeta[4].text=carregaTextura("jupiter.png");;
    planeta[5].text= carregaTextura("saturno.png");
    planeta[6].text= carregaTextura("urano.png");

}
void inicializa(){
    glEnable(GL_DEPTH_TEST);

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    glClearColor(0.0, 0.0, 0.0, 0.0);//cor de fundo preta
    inicializaPlanetas();
    inicializaTexturas();
    cameraY=10;
    cameraZ=25;

}

void teclado(unsigned char key, int x, int y){
    switch(key) {
    case 27:// esc
        exit(0);  // Sai da aplicação
        break;
    case 99:// c

        cameraY=100;//altera a camera
        break;
    case 100:// d
        //volta para a camera inicial
        cameraY=10;
        cameraZ=25;
        break;
    case 108://l
        luz= !luz;//desativa e ativa a iluminação
        break;
    default:
        break;
    }

    glutPostRedisplay();




}

void desenhaEsfera(GLfloat raio, GLint stacks, GLint columns){
//função chamada pra desenhar o Sol e os planetas do jogo.
   GLUquadric* quadObj = gluNewQuadric();
   gluQuadricDrawStyle(quadObj, GLU_FILL);
   gluQuadricNormals(quadObj, GLU_SMOOTH);
   gluQuadricTexture(quadObj, GL_TRUE);
   gluSphere(quadObj, raio, stacks, columns);
   gluDeleteQuadric(quadObj);

}

void habilitaLuz(){
    if(luz){
        GLfloat luzAmbiente[4]={0.8 , 0.8 , 0.8 ,1.0};
        GLfloat luzDifusa[4]={ 0.8, 0.8, 0.8 ,1.0};	   // "cor"
        GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho"
        GLfloat posicaoLuz[4]={0, 0, 0, 1.0};//posiciona a luz no centro

        GLfloat luzGlobal[4]={0.2, 0.2, 0.2, 1};

        GLfloat especMaterial []= {60};
        glShadeModel(GL_SMOOTH);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

        glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
        glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
        glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
        glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);

        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobal);

        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, luzEspecular);
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, luzDifusa);
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, luzAmbiente);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,especMaterial);



        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_NORMALIZE);


	}

    else{
        glDisable(GL_LIGHT0);//luz= false.
    }

}

void desenha_sol(){

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textSol);



    glPushMatrix();
        habilitaLuz();

        glTranslatef(0.0, 0.0, 0.0);
        glColor3f(1, 1, 1);
        glRotatef(90, 1, 0, 0);
        glRotatef(0.0, 0, 0 , 1);

        desenhaEsfera(2.3, 20.0, 20.0);//desenha o sol com raio 2.3


    glPopMatrix();


    glDisable(GL_TEXTURE_2D);
}

void desenha_planetas(struct Planetas planeta[]){

    glEnable(GL_TEXTURE_2D);
    for(int i=0; i<num_planetas; i++){
       glBindTexture(GL_TEXTURE_2D, planeta[i].text);
        glPushMatrix();
            glColor3f(1, 1, 1);
            glRotatef(planeta[i].anguloTranslacao, 0, 1, 0);
            glTranslatef(planeta[i].translacao, 0, 0);

            glRotatef(-90, 1, 0, 0);
            glRotatef(planeta[i].auxRaio, 0, 0, 1);

            desenhaEsfera(planeta[i].raio, 20, 20);



        glPopMatrix();
    }
    glDisable(GL_TEXTURE_2D);
}
void desenha(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0,cameraY,cameraZ, 0,0,0, 0,1,0);


    desenha_planetas(planeta);
    desenha_sol();


    glutSwapBuffers();
}
void redimensiona(int w, int h){
    glViewport(0, 0, w, h);

    float aspect = (float)w / (float)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 1, 200.0);

    glMatrixMode(GL_MODELVIEW);
}

// Programa Principal
int main(int argc, char *argv[]){

    glutInit(&argc, argv);
    glutInitContextVersion(1, 1);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(800,700);
    glutCreateWindow("Sistema Solar");
    glutDisplayFunc(desenha);
    glutReshapeFunc(redimensiona);
    glutKeyboardFunc(teclado);

    inicializa();
    glutTimerFunc(0, atualiza, 33);


    glutMainLoop();
}
