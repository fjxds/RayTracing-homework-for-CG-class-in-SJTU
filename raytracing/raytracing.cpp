// raytracing.cpp : 定义控制台应用程序的入口点。
//

#include <GL/glut.h>
#include <vector>
#include "cray.h"
#include "csphere.h"
#include "gvector3.h"
#include "intersectresult.h"
#include "perspectivecamera.h"
#include "cobject.h"
#include "plane.h"
#include "material.h"
#include "color.h"
#include "checkermaterial.h"
#include "phongmaterial.h"
#include "union.h"
#include "directlight.h"
#include "pointlight.h"
#include "cube.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

Color rayTraceRecursive(CObject* scene, CRay& ray, long maxReflect)
{
	IntersectResult result = scene->isIntersected(ray);
	if (result.object)
	{
		float reflectiveness = result.object->material->getRef();
		Color color = result.object->material->sample(ray, result.position, result.normal);
		color = color.multiply(1 - reflectiveness);
		if ((reflectiveness > 0) && (maxReflect > 0))
		{
			GVector3 r = result.normal*(-2 * result.normal.dotMul(ray.getDirection())) + ray.getDirection();
			CRay ray = CRay(result.position, r);
			Color reflectedColor = rayTraceRecursive(scene, ray, maxReflect - 1);
			color = color.add(reflectedColor.multiply(reflectiveness));
		}
		return color;
	}
	else return Color::black();
}

void renderLight()
{
	Union scene;
	perspectiveCamera camera(GVector3(0, 10, 10), GVector3(0, 0, -1), GVector3(0, 1, 0), 90);
	Plane* plane1 = new Plane(GVector3(0, 1, 0), 0.0);
	Plane* plane2 = new Plane(GVector3(0, 0, 1), -50);
	Plane* plane3 = new Plane(GVector3(1, 0, 0), -20);
	CSphere* sphere1 = new CSphere(GVector3(-5, 30, -30), 10.0);
	vector<GVector3> a;
	a.push_back(GVector3(-14, 20, -26));
	a.push_back(GVector3(2, 20, -14));
	a.push_back(GVector3(2, 0, -14));
	a.push_back(GVector3(-14, 0, -26));
	a.push_back(GVector3(-2, 0, -42));
	a.push_back(GVector3(-2, 20, -42));
	a.push_back(GVector3(14, 20, -30));
	a.push_back(GVector3(14, 0, -30));
	Cube* cube1 = new Cube(a);
	cube1->material = new PhongMaterial(Color::blue(), Color::white(), 16);
	cube1->getinfo();
	sphere1->material = new PhongMaterial(Color::red(), Color::white(), 16);
	DirectLight light1(Color::white().multiply(1), GVector3(-1.75, -2, -1.5), true);
	PointLight light2(Color::white().multiply(200), GVector3(10, 20, 10), true);

	scene.push(plane1);
	scene.push(plane2);
	scene.push(plane3);
	scene.push(cube1);
	//scene.push(sphere1);
	long maxDepth = 20;
	float dx = 1.0f / WINDOW_WIDTH;
	float dy = 1.0f / WINDOW_HEIGHT;
	float dD = 255.0f / maxDepth;
	float red, green, blue;
	glBegin(GL_POINTS);
	for (long y = 0; y < WINDOW_HEIGHT; ++y)
	{
		float sy = 1 - dy*y;
		for (long x = 0; x < WINDOW_WIDTH; ++x)
		{
			float sx = dx*x;
			CRay ray(camera.generateRay(sx, sy));
			IntersectResult result = scene.isIntersected(ray);

			if (result.isHit)
			{
				Color color = light1.intersect(scene, result);
				color.saturate();
				//如果加入材质和颜色
				/*if (result.object->index > 0)
				{
					Color color1 = result.object->material->sample(ray, result.position, result.normal).modulate(color);
					color1.saturate();
					glColor3ub(color1.r * 255, color1.g * 255, color1.b * 255);
					glVertex2f(sx, sy);
				}
				else
				{*/
				//不加入材质和颜色，仅用光强计算
					red = (color.r * 255 > 255) ? 255 : color.r * 255;
					green = (color.g * 255 > 255) ? 255 : color.g * 255;
					blue = (color.b * 255 > 255) ? 255 : color.b * 255;
					glColor3ub(red, green, blue);
					glVertex2f(sx, sy);
				//}
			}
		}
	}
	glEnd();
	// 交换缓冲区
	glutSwapBuffers();
}
void renderRecursive()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();                                   // Reset The View
	glTranslatef(-0.5f, -0.5f, -1.0f);
	glPointSize(2.0);
	perspectiveCamera camera(GVector3(0, 10, 10), GVector3(0, -0.5, -1), GVector3(0, 1, 0), 90);
	Plane* plane1 = new Plane(GVector3(0, 1, 0), 1.0);
	CSphere* sphere1 = new CSphere(GVector3(-2, 5, -2), 4.0);
	CSphere* sphere2 = new CSphere(GVector3(5, 5, -7), 3.0);
	plane1->material = new CheckerMaterial(0.1f, 0.5f);
	sphere1->material = new PhongMaterial(Color::red(), Color::white(), 16, 0.25);
	sphere2->material = new PhongMaterial(Color::green(), Color::white(), 16, 0.25);
	Union scene;
	scene.push(plane1);
	scene.push(sphere1);
	scene.push(sphere2);
	long maxDepth = 20;
	long maxReflect = 5;
	float dx = 1.0f / WINDOW_WIDTH;
	float dy = 1.0f / WINDOW_HEIGHT;
	float dD = 255.0f / maxDepth;
	glBegin(GL_POINTS);
	for (long y = 0; y < WINDOW_HEIGHT; ++y)
	{
		float sy = 1 - dy*y;
		for (long x = 0; x < WINDOW_WIDTH; ++x)
		{
			float sx = dx*x;
			CRay ray(camera.generateRay(sx, sy));
			IntersectResult result = scene.isIntersected(ray);
			//IntersectResult result = plane1.isIntersected(ray);
			if (result.isHit)
			{
				Color color = rayTraceRecursive(&scene, ray, maxReflect);
				//Color color = result.object->material->sample(ray, result.position, result.normal);
				//Color color =plane1.material->sample(ray, result.position, result.normal);
				color.saturate();
				//color.show();
				glColor3ub(color.r * 255, color.g * 255, color.b * 255);
				glVertex2f(sx, sy);
			}
		}
	}
	glEnd();
	// 交换缓冲区
	glutSwapBuffers();
}








int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(150, 100);
	glutInitWindowSize(600,600);
	glutCreateWindow("Raytracing");
	glutDisplayFunc(renderLight);

	glutMainLoop();
}

