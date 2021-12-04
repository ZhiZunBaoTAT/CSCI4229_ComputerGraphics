

#include "CSCIx229.h"

double asp=1;     //  Aspect ratio
double dim=3.0;   //  Size of world

unsigned int textures[7]; // Texture names
float personTrans = 0;
float oribitAngle = 90.0;
float oribitHeight = 30;
float carTrans = 0;


void xoy_foor(float len, float tex_repeat, int subdivision)
{
   glPushMatrix();
   glScalef(len, len, 1);
   glNormal3f(0, 0, 1);
   float u = 1.0f / subdivision;
   float tu = tex_repeat / subdivision;
   for (int i = 0; i < subdivision; ++i)
      for (int j = 0; j < subdivision; ++j) {
         float ox = u * i, oy = u * j;
         float tox = tu * i, toy = tu * j;
         glBegin(GL_POLYGON);
         glTexCoord2f(tox, toy);    glVertex3f(ox, oy, 0);
         glTexCoord2f(tox + tu, toy);     glVertex3f(ox + u, oy, 0);
         glTexCoord2f(tox + tu, toy + tu);   glVertex3f(ox + u, oy + u, 0);
         glTexCoord2f(tox, toy + tu);  glVertex3f(ox, oy + u, 0);
         glEnd();
      }
   glPopMatrix();
}


void drawPlane() {
   glEnable(GL_TEXTURE_2D);
   glColor3f(1, 1, 1);
   glBindTexture(GL_TEXTURE_2D, textures[0]);
   glPushMatrix();
   glRotatef(90, -1, 0, 0);
   glTranslatef(-100, -100, 0);
   xoy_foor(200, 1, 100);
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}




void drawTextureQuads() {
   glPushMatrix();
   {
      glBegin(GL_QUADS);
      glNormal3f(0, 1, 0);
      glTexCoord2f(0, 0);  glVertex3f(-0.5, 0, 0.5);
      glTexCoord2f(0, 4);  glVertex3f(-0.5, 0, -0.5);
      glTexCoord2f(4, 4);  glVertex3f(0.5, 0, -0.5);
      glTexCoord2f(4, 0);  glVertex3f(0.5, 0, 0.5);
      glEnd();

   }
   glPopMatrix();
}

void drawFloor(void) {
   // Big basis
   glPushMatrix();
   glColor3ub(210, 180, 140);
   glTranslatef(0, 0.1, 0);
   glScalef(65, 1.0, 65);
   drawTextureQuads();
   glPopMatrix();

   glPushMatrix();
   glColor3ub(255, 222, 173);
   glTranslatef(0, 0.2, 0.);
   glScalef(55, 0.8, 55);
   glutSolidCube(1.0);
   glPopMatrix();

   glEnable(GL_TEXTURE_2D);
   glColor3f(1, 1, 1);
   glBindTexture(GL_TEXTURE_2D, textures[1]);
   glColor3f(1, 1, 1);
   glPushMatrix();
   glTranslatef(0, 0.7, 0);
   glScalef(45, 1.0, 45);
   drawTextureQuads();
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);



}

void drawBaseTextureCube() {
   glPushMatrix();
   glColor3f(1, 1, 1);
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, textures[2]);
   glTranslatef(0, 1.3, 0.0);
   glScaled(4, 2.6, 2);
   glutSolidCube(1.0);
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();
}


void drawHence() {
   glPushMatrix();
   // Basis
   {
      glPushMatrix();
      glTranslatef(-24.5, 0, -23);
      for (int i = 0; i < 11; ++i) {
         glTranslatef(4, 0, 0);
         drawBaseTextureCube();

      }
      // extra
      glTranslatef(1, 0, 0);
      glPushMatrix();
      drawBaseTextureCube();
      glPopMatrix();
      glPopMatrix();
   }

   // left
   {
      glPushMatrix();
      glTranslatef(-23, 0, -26.1);
      for (int i = 0; i < 12; ++i) {
         glTranslatef(0, 0, 4);
         glPushMatrix();
         glRotatef(90, 0, 1, 0);
         drawBaseTextureCube();
         glPopMatrix();
         
      }
      glPopMatrix();
   }

   // right
   {
      glPushMatrix();
      glTranslatef(23, 0, -26.1);
      for (int i = 0; i < 12; ++i) {
         glTranslatef(0, 0, 4);
         glPushMatrix();
         glRotatef(90, 0, 1, 0);
         drawBaseTextureCube();
         glPopMatrix();

      }
      glPopMatrix();
   }

   // front
   {
      glPushMatrix();
      glTranslatef(-22, 0, 23);
      for (int i = 0; i < 5; ++i) {
         drawBaseTextureCube();
         glTranslatef(3.5, 0, 0);
      }
      glPopMatrix();

      glPushMatrix();
      glTranslatef(22, 0, 23);
      for (int i = 0; i < 5; ++i) {
         drawBaseTextureCube();
         glTranslatef(-3.5, 0, 0);
      }
      glPopMatrix();
   }

   glPopMatrix();
}

void drawPiallar(void) {
   glPushMatrix();
   {
      glColor3ub(105, 105, 105);
      glPushMatrix();
      glTranslatef(0, 1.25, 0);
      glScalef(0.8, 2.5, 0.8);
      glutSolidCube(1.0);
      glPopMatrix();

      glPushMatrix();
      glTranslated(0, 2.8, 0);
      glutSolidSphere(0.5, 32, 32);
      glPopMatrix();
   }
   glPopMatrix();
}

void drawPiallars() {
   glPushMatrix();
   glPushMatrix();
   glTranslatef(-5.5, 0, 23);
   drawPiallar();
   glTranslatef(11, 0, 0);
   drawPiallar();
   glPopMatrix();
   glPopMatrix();
}


void drawDoor() {
   glPushMatrix();
   glTranslated(0, 0, 23);
   
   glPushMatrix();
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, textures[3]);
   glColor3f(1, 1, 1);
   glBegin(GL_QUADS);
   glNormal3f(0, 0, 1);
   glTexCoord2f(0, 0);  glVertex3f(-5, 0, 0);
   glTexCoord2f(1, 0);  glVertex3f(-0.05, 0, 0);
   glTexCoord2f(1, 1);  glVertex3f(-0.05, 5, 0);
   glTexCoord2f(0, 1);  glVertex3f(-5, 2.5, 0);
   glEnd();
   
   glBegin(GL_QUADS);
   glNormal3f(0, 0, 1);
   glTexCoord2f(0, 0);  glVertex3f(0.05, 0, 0);
   glTexCoord2f(1, 0);  glVertex3f(5, 0, 0);
   glTexCoord2f(1, 1);  glVertex3f(5, 2.5, 0);
   glTexCoord2f(0, 1);  glVertex3f(0.05, 5, 0);
   glEnd();
   glDisable(GL_TEXTURE_2D);
   glPopMatrix();
   
   // Ring
   glColor3ub(255, 0, 0);
   glPushMatrix();
   glTranslatef(-0.8, 2.0, 0.1);
   glutSolidTorus(0.1, 0.5, 32, 32);

   glTranslatef(1.6, 0.0, 0.0);
   glutSolidTorus(0.1, 0.5, 32, 32);
   glPopMatrix();

   glPopMatrix();
}

void drawTriangle(void) {
   glPushMatrix();
   glBegin(GL_TRIANGLES);
   glNormal3f(0, 1, 0);
   glVertex3f(-2, 0, 0);
   glVertex3f(2, 0, 0);
   glVertex3f(0, 0, 2);
   glEnd();
   glPopMatrix();
}

void drawCircle(float r) {
   glPushMatrix();
   glBegin(GL_POLYGON); // Draw regular polynon
   int n = 1000;
   glNormal3f(0, 1, 0);
   for (int i = 0; i < n; ++i)
      glVertex3f(r * cos(2 * 3.1415926535 / n * i), 0, r * sin(2 * 3.1415926535 / n * i));
   glEnd();
   glPopMatrix();
}

void drawFountainBase() {
   glPushMatrix();
   glTranslatef(-4, 0.7, 5);

   glPushMatrix();
   glColor3ub(50, 205, 50);

   glScalef(10, 1, 10);
   glutSolidCube(1.0);
   glPopMatrix();

   {
      glPushMatrix();
      glTranslatef(6, 0.2, 0);

      glPushMatrix();
      glRotatef(90, 0, 1, 0);
      drawTriangle();
      glPopMatrix();

      glTranslatef(-12, 0.0, 0);
      glPushMatrix();
      glRotatef(-90, 0, 1, 0);
      drawTriangle();
      glPopMatrix();

      glTranslatef(6, 0.0, 6);
      glPushMatrix();
      drawTriangle();
      glPopMatrix();

      glTranslatef(0, 0.0, -12);
      glPushMatrix();
      glRotatef(180, 0, 1, 0);
      drawTriangle();
      glPopMatrix();

      glPopMatrix();
   }

   // circular ring
   {
      glPushMatrix();
      glColor3ub(205, 92, 92);
      glTranslatef(0, 0.5, 0);
      glRotatef(90, 1, 0, 0);
      glScalef(1.0, 1.0, 1.5);
      glutSolidTorus(0.5, 4.5, 32, 32);
      glPopMatrix();
   }

   // cirlce on the fround
   {
      glPushMatrix();
      glColor3ub(135, 206, 250);
      glTranslatef(0, 0.7, 0);
      drawCircle(4.5);
      glPopMatrix();
   }

   glPopMatrix();
}

void drawBaseBuding(int isDrawTree) {
   glPushMatrix();
      glPushMatrix();
      glColor3ub(210, 105, 30);
      glScalef(6.0, 5.0, 6.0);
      glutSolidCube(1.0);
      glPopMatrix();

      // windows
      glColor3ub(72, 209, 204);
      glPushMatrix();
      glTranslatef(-1.5, 4, 2.7);
      glutSolidCube(1.5);
      glTranslatef(0, 2, 0);
      glutSolidCube(1.5);
      glTranslatef(0, 2, 0);
      glutSolidCube(1.5);
      glTranslatef(3, 0, 0);
      glutSolidCube(1.5);
      glTranslatef(0, -2, 0);
      glutSolidCube(1.5);
      glTranslatef(0, -2, 0);
      glutSolidCube(1.5);
      glPopMatrix();

      // strape
      glPushMatrix();
      glColor3f(0.8, 0.8, 0.8);
      glTranslatef(0, 0, 3.2);
      glScalef(6.2, 0.2, 0.2);
      glutSolidCube(1.0);
      glPopMatrix();

      glPushMatrix();
      glTranslatef(0, 0, -3.2);
      glScalef(6.2, 0.2, 0.2);
      glutSolidCube(1.0);
      glPopMatrix();

      glPushMatrix();
      glTranslatef(-3.2, 0, 0);
      glRotatef(90, 0, 1, 0);
      glScalef(6.2, 0.2, 0.2);
      glutSolidCube(1.0);
      glPopMatrix();

      glPushMatrix();
      glTranslatef(3.2, 0, 0);
      glRotatef(90, 0, 1, 0);
      glScalef(6.2, 0.2, 0.2);
      glutSolidCube(1.0);
      glPopMatrix();

      glColor3ub(255, 255, 0);
      glPushMatrix();
      glTranslatef(0, 6.5, 0);
      glScalef(6.0, 8.0, 6.0);
      glutSolidCube(1.0);
      glPopMatrix();

      if (isDrawTree) {
         // tree
         glPushMatrix();
         glColor3ub(250, 240, 230);
         glTranslatef(0, -2.7, 4);
         glPushMatrix();
         glScalef(6.0, 0.8, 3.0);
         glutSolidCube(1.0);
         glPopMatrix();

         glPushMatrix();
         glColor3ub(0, 100, 0);
         glTranslatef(-1.7, 1.0, 0);
         glutSolidSphere(1.0, 32, 32);
         glTranslatef(1.5, 0.0, 0);
         glutSolidSphere(0.8, 32, 32);
         glTranslatef(1.5, 0.0, 0);
         glutSolidSphere(1.0, 32, 32);
         glPopMatrix();

         glPopMatrix();
      }

   glPopMatrix();
}


void drawBulding() {
   glPushMatrix();
   
   glTranslatef(-8, 2.5, 0);
   
   // left
   drawBaseBuding(1);

   // middle
   glPushMatrix();
   glTranslatef(5.4, 0, -0.65);
   glScaled(0.8, 1.0, 0.8);
   drawBaseBuding(0);
   glPopMatrix();
   
   // door floor
   glPushMatrix();
   glTranslatef(5.4, -2.3, 3);
   
   glPushMatrix();
   glScalef(4.2, 0.2, 4.0);
   glutSolidCube(1.0);
   glPopMatrix();

   glPushMatrix();
   glColor3ub(30, 144, 255);
   glTranslatef(0, 2, 0);
   glScalef(4.2, 0.4, 4.0);
   glutSolidCube(1.0);
   glPopMatrix();

   // pillar
   glColor3ub(220, 220, 220);
   glTranslatef(-2.0, 2, -1.0);
   glPushMatrix();
   glRotatef(90, 1, 0, 0);
   glutSolidCylinder(0.2, 2.0, 32, 32);
   glPopMatrix();

   glTranslatef(3.8, 0, 0.0);
   glPushMatrix();
   glRotatef(90, 1, 0, 0);
   glutSolidCylinder(0.2, 2.0, 32, 32);
   glPopMatrix();

   glTranslatef(0.0, 0, 2.9);
   glPushMatrix();
   glRotatef(90, 1, 0, 0);
   glutSolidCylinder(0.2, 2.0, 32, 32);
   glPopMatrix();

   glTranslatef(-3.8, 0, 0);
   glPushMatrix();
   glRotatef(90, 1, 0, 0);
   glutSolidCylinder(0.2, 2.0, 32, 32);
   glPopMatrix();

   glPopMatrix();


   //right
   glTranslatef(10.6, 0, 0);
   drawBaseBuding(1);



   glPopMatrix();
}


void drawBuldings() {
   glPushMatrix();
   glTranslatef(0, 0.9, 0);

   glTranslatef(-9, 0.0, -15);
   drawBulding();

   glTranslatef(18, 0.0, 0);
   drawBulding();

   glTranslatef(10, 0.0, 20);
   glPushMatrix();
   glRotatef(-90, 0, 1, 0);
   drawBulding();
   glPopMatrix();
   glPopMatrix();
}


void drawTree1() {
   glPushMatrix();

   // tree1
   glPushMatrix();
   glColor3ub(0, 100, 0);
   glTranslatef(0, 6, 0);
   glScalef(1.5, 1.5, 1.5);
   glutSolidDodecahedron();
   glPopMatrix();

   glPushMatrix();
   glColor3ub(139, 69, 19);
   glTranslatef(0, 5, 0);
   glRotatef(90, 1, 0, 0);
   glutSolidCylinder(0.5, 5.0, 32, 32);
   glPopMatrix();

   glPopMatrix();
}

void drawTree2() {
   glPushMatrix();
   
   // trunk
   glPushMatrix();
   glColor3ub(139, 69, 19);
   glTranslatef(0, 3, 0);
   glRotatef(90, 1, 0, 0);
   glutSolidCylinder(0.5, 3.0, 32, 32);
   glPopMatrix();


   glPushMatrix();
   glColor3ub(0, 100, 0);
   glTranslatef(0, 3, 0);
   glPushMatrix();
   glRotatef(-20, 0, 0, 1);
   glScalef(3.0, 3.0, 3.0);
   glutSolidTetrahedron();
   glPopMatrix();

   glTranslatef(0, 2, 0);
   glPushMatrix();
   glRotatef(-20, 0, 0, 1);
   glScalef(3.0, 3.0, 3.0);
   glutSolidTetrahedron();
   glPopMatrix();

   glTranslatef(0, 2, 0);
   glPushMatrix();
   glRotatef(-20, 0, 0, 1);
   glScalef(3.0, 3.0, 3.0);
   glutSolidTetrahedron();
   glPopMatrix();

   glPopMatrix();

   glPopMatrix();
}

void drawRoad() {
   glPushMatrix();

   glEnable(GL_TEXTURE_2D);
   glColor3f(1, 1, 1);
   glBindTexture(GL_TEXTURE_2D, textures[4]);
   glPushMatrix();
   glTranslatef(0, 0.7, 0);
   glRotatef(90, 0, 1, 0);
   glScalef(8, 1.0, 8);
   glBegin(GL_QUADS);
   glNormal3f(0, 1, 0);
   glTexCoord2f(0, 0);  glVertex3f(-0.5, 0, 0.5);
   glTexCoord2f(0, 1);  glVertex3f(-0.5, 0, -0.5);
   glTexCoord2f(1, 1);  glVertex3f(0.5, 0, -0.5);
   glTexCoord2f(1, 0);  glVertex3f(0.5, 0, 0.5);
   glEnd();
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);

   glPopMatrix();
}

void drawRoads() {
   glPushMatrix();
   glTranslatef(-35, 0, 35);
   for (int i = 0; i < 13; ++i) {
      glTranslatef(5, 0, 0);
      drawRoad();
   }
   glPopMatrix();

   glPushMatrix();
   glTranslatef(-35, 0, -34);
   for (int i = 0; i < 13; ++i) {
      glTranslatef(5, 0, 0);
      drawRoad();
   }
   glPopMatrix();

   glPushMatrix();
   glTranslatef(-33, 0, -40);
   for (int i = 0; i < 15; ++i) {
      glTranslatef(0, 0, 5);
      glPushMatrix();
      glRotatef(90, 0, 1, 0);
      drawRoad();
      glPopMatrix();
   }
   glPopMatrix();

   glPushMatrix();
   glTranslatef(33, 0, -40);
   for (int i = 0; i < 15; ++i) {
      glTranslatef(0, 0, 5);
      glPushMatrix();
      glRotatef(90, 0, 1, 0);
      drawRoad();
      glPopMatrix();
   }
   glPopMatrix();
}

void drawPerson1() {
   glPushMatrix();
   glTranslatef(5, 3.5, 0);
   GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
   glMaterialf(GL_FRONT, GL_SHININESS, 0);
   glEnable(GL_COLOR_MATERIAL);
   // head
   glPushMatrix();
   glColor3ub(245, 222, 179);
   glTranslatef(0, 1, 0);
   glutSolidSphere(0.6, 32, 32);


   glPushMatrix();
   glColor3ub(255, 250, 240);
   glTranslatef(0, -1.2, 0);
   glScalef(1.5, 1.5, 0.8);
   glutSolidCube(1.0);
   glPopMatrix();

   glPushMatrix();
   glColor3ub(0, 0, 0);
   glTranslatef(0, -3.0, 0);
   glScalef(1.5, 1.8, 0.8);
   glutSolidCube(1.0);
   glPopMatrix();

   glPopMatrix();

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialf(GL_FRONT, GL_SHININESS, 32);
   glEnable(GL_COLOR_MATERIAL);

   glPopMatrix();
}

void drawPerson2() {
   glPushMatrix();
   glTranslatef(5, 3.5, 0);
   GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
   glMaterialf(GL_FRONT, GL_SHININESS, 0);
   glEnable(GL_COLOR_MATERIAL);
   // head
   glPushMatrix();
   glColor3ub(245, 222, 179);
   glTranslatef(0, 1, 0);
   glutSolidSphere(0.6, 32, 32);

   glTranslatef(0, -1, 0);
   glColor3ub(255, 0, 255);
   glutSolidSphere(0.45, 32, 32);

   // skirt
   GLUquadricObj* quadricObj = gluNewQuadric();
   gluQuadricNormals(quadricObj, GL_SMOOTH);
   glTranslatef(0, -0.4, 0);
   glRotatef(90, 1, 0, 0);
   gluCylinder(quadricObj, 0.2, 1.0, 2.0, 32, 32);

   glPopMatrix();

   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialf(GL_FRONT, GL_SHININESS, 32);
   glEnable(GL_COLOR_MATERIAL);

   glPopMatrix();
}

void drawPersons() {
   glPushMatrix();
   glTranslatef(2, 0, 5);
   drawPerson1();

   glTranslatef(2, 0, 7);
   drawPerson2();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(-8 + personTrans, 0, 30);
   drawPerson1();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(10 - personTrans, 0, 27);
   glRotatef(90, 0, 1, 0);
   drawPerson2();
   glPopMatrix();
}

void drawCar() {
   glPushMatrix();
   glTranslatef(carTrans, 0.5, 35);

   glPushMatrix();
   glTranslatef(0, 2.5, 0);

   glColor3f(1, 0, 0);
   glPushMatrix(); 
   glScalef(6, 2.0, 4.0);
   glutSolidCube(1.0);
   glPopMatrix();

   glTranslatef(0, 2, 0);
   glPushMatrix();
   glScalef(3, 2.0, 4.0);
   glutSolidCube(1.0);
   glPopMatrix();
   glPopMatrix();

   glPushMatrix();
   glColor3f(0, 0, 0);
   glTranslatef(-2.5, 0.8, 2.0);
   glutSolidTorus(0.3, 0.6, 32, 32);

   glTranslatef(5.0, 0.0, 0.0);
   glutSolidTorus(0.3, 0.6, 32, 32);
   

   glTranslatef(0.0, 0.0, -4.0);
   glutSolidTorus(0.3, 0.6, 32, 32);



   glTranslatef(-5.0, 0.0, 0.0);
   glutSolidTorus(0.3, 0.6, 32, 32);


   glPopMatrix();



   glPopMatrix();
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0f, 1.0, 0.1, 500.);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   float r = 100;
   gluLookAt(r * cos(oribitAngle * 3.1415926 / 180.0), oribitHeight, r * sin(oribitAngle * 3.1415926 / 180.0), 0, 0, 0, 0, 1, 0);



   drawPlane();
   drawFloor();
   drawHence();
   drawPiallars();
   drawDoor();
   drawFountainBase();
   drawBuldings();
   drawRoads();
   drawPersons();
   drawCar();

   glPushMatrix();
   glTranslatef(18, 0.2, 18);
   glScalef(1.6, 1.6, 1.6);
   drawTree2();
   glPopMatrix();

   glPushMatrix();
   glTranslatef(-20, 0.2, -14);
   for (int i = 0; i < 4; ++i) {
      glTranslatef(0, 0.0, 8);
      drawTree1();
   }
   glPopMatrix();
   
   // fountain
   glDisable(GL_LIGHTING);
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE);
   glColor3ub(0, 191, 255);
   glPushMatrix();
   glTranslated(-4, 0.5, 4);
   FountainRender();
   glDisable(GL_BLEND);
   glEnable(GL_LIGHTING);
   glPopMatrix();

   glutSwapBuffers();
}


/*
 *  GLUT calls this routine when the window is resized
 */
float personDir = 1;
float carDir = 1;
void idle() {

   if (personTrans > 30) {
      personDir = -1.0;
   }
   if (personTrans < -30) {
      personDir = 1;
   }
   personTrans += personDir * 0.1;

   if (carTrans > 30) {
      carDir = -1.0;
   }
   if (carTrans < -30) {
      carDir = 1;
   }
   carTrans += carDir * 0.5;

   FountainUpdate();

   display();
   glutPostRedisplay();

}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   switch (ch)
   {
   case '\033':
      exit(0);
      break;
   case 'w':
      oribitHeight += 0.4;
      break;
   case 's':
      oribitHeight -= 0.4;
      break;
   case 'a':
      oribitAngle += 1;
      break;
   case 'd':
      oribitAngle -= 1;
      break;
   }
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, RES*width,RES*height);
   //  Set projection
   Project(45,asp,dim);
}

void initGL() {
   glEnable(GL_DEPTH_TEST);
   glClearColor(135 / 255.0, 206 / 255.0, 250 / 255.0, 1.0);

   GLfloat ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };  // ambient
   GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };  // diffuse
   GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // specular
   GLfloat lightPosition[] = { 20.0, 10.0, 10.0, 1.0 };

   glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
   glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

   srand(time(NULL));
   GLfloat no_mat[] = { 0.3, 0.3, 0.3, 1.0 };
   GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0,1.0 };
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialf(GL_FRONT, GL_SHININESS, 32);
   glEnable(GL_COLOR_MATERIAL);


}




/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(600,600);
   glutCreateWindow("Textures and Lighting");
#ifdef USEGLEW
   //  Initialize GLEW
   if (glewInit()!=GLEW_OK) Fatal("Error initializing GLEW\n");
#endif
   initGL();
   glPointSize(2.0);
   FountainInitialize();

   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);
   //  Load textures
   textures[0] = LoadTexBMP("floor.bmp");
   textures[1] = LoadTexBMP("brick.bmp");
   textures[2] = LoadTexBMP("grass.bmp");
   textures[3] = LoadTexBMP("wen.bmp");
   textures[4] = LoadTexBMP("road.bmp");
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
