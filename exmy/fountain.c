#include "CSCIx229.h"

typedef struct  {
	float x;
	float y;
	float z;
}vec3;

typedef struct  {
	GLfloat time;
	vec3 speed;
	vec3 pos;
	GLfloat AccFactor;

}Drop;

#define RandomFactor 2.0

GLfloat GetRandomFloat(GLfloat range)
{
	return (GLfloat)rand() / (GLfloat)RAND_MAX * range * RandomFactor;
}




Drop fountainDrops[1000];
int dropSize;
void DropGetNewPosition(int index)
{
	fountainDrops[index].time += 0.006 * 20.0f;

	if (fountainDrops[index].time > 0.0f)
	{
		fountainDrops[index].pos.x = fountainDrops[index].speed.x * fountainDrops[index].time;
		fountainDrops[index].pos.y = fountainDrops[index].speed.y * fountainDrops[index].time - fountainDrops[index].AccFactor * fountainDrops[index].time * fountainDrops[index].time;
		fountainDrops[index].pos.z = fountainDrops[index].speed.z * fountainDrops[index].time;
		if (fountainDrops[index].pos.y < 0.0)
		{
			fountainDrops[index].time = fountainDrops[index].time - (int)(fountainDrops[index].time);
			if (fountainDrops[index].time > 0.0) fountainDrops[index].time -= 1.0;
		}
	}
	else
	{
		fountainDrops[index].pos.x = 0.0;
		fountainDrops[index].pos.y = 0.0;
		fountainDrops[index].pos.z = 0.0;
	}
}


void FountainInitialize()
{
	GLint Steps = 3;
	GLint RaysPerStep = 8;
	GLint DropsPerRay = 35;
	GLfloat AngleOfDeepestStep = 75; 
	GLfloat AngleOfHighestStep = 90;
	GLfloat RandomAngleAddition = 0.5;
	GLfloat AccFactor = 0.11;

	dropSize = Steps * RaysPerStep * DropsPerRay;
	GLfloat DropAccFactor;
	//GLfloat TimeNeeded;
	GLfloat StepAngle;
	GLfloat RayAngle;
	GLint i,j,k;
	for (k = 0; k <Steps; k++)
	{
		for (j = 0; j < RaysPerStep; j++)
		{
			for (i = 0; i < DropsPerRay; i++)
			{
				DropAccFactor = AccFactor + GetRandomFloat(0.005);
				if (Steps > 1) 
					StepAngle = AngleOfDeepestStep + (AngleOfHighestStep-AngleOfDeepestStep) 
							* (GLfloat)(k) / (Steps-1) + GetRandomFloat(RandomAngleAddition);
				else
					StepAngle = AngleOfDeepestStep + GetRandomFloat(RandomAngleAddition);
			
				vec3 speed;
				speed.x = cos (StepAngle * 3.1415926535 / 180.0) * (0.2+0.04*k);
				speed.y = sin (StepAngle * 3.1415926535 / 180.0) * (0.2+0.04*k);

				RayAngle = (GLfloat)j / (GLfloat)RaysPerStep * 360.0 + 20;
				speed.z = speed.x * sin ( RayAngle * 3.1415926535 /180.0);
				speed.x = speed.x * cos ( RayAngle * 3.1415926535 /180.0);

				speed.x*= 6.0f;
				speed.y*= 8;
				speed.z*= 6.0f;
				
				fountainDrops[i + j * DropsPerRay + k * DropsPerRay * RaysPerStep].speed = speed;
				fountainDrops[i + j * DropsPerRay + k * DropsPerRay * RaysPerStep].AccFactor = (DropAccFactor);
				fountainDrops[i + j * DropsPerRay + k * DropsPerRay * RaysPerStep].time = speed.y / (0.1 + GetRandomFloat(0.005)) * i / DropsPerRay;
			}
		}
	}

}

void FountainUpdate()
{
	for (int i = 0; i < dropSize; i++)
		DropGetNewPosition(i);

}

void FountainRender() {
	glPushMatrix();
	glBegin(GL_POINTS);
	for (int i = 0; i < dropSize; ++i) {
		glVertex3f(fountainDrops[i].pos.x, fountainDrops[i].pos.y, fountainDrops[i].pos.z);

	}
	glEnd();
	glPopMatrix();
}
