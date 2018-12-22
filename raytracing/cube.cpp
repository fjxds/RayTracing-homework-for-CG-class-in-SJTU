#include "cube.h"
#include "intersectresult.h"
Cube::Cube()
{
	index = 2;
	center = GVector3(0, 0, 0);
}
Cube::Cube(Cube& obj)
{
	center = obj.getCenter();
	length = obj.getLength();
	index = obj.index;
	while (!vertexes.empty())
	{
		vertexes.pop_back();
	}
	for (int i = 0; i < obj.vertexes.size(); i++)
	{
		vertexes.push_back(obj.vertexes[i]);
	}
	while (!normals.empty())
	{
		normals.pop_back();
	}
	for (int i = 0; i < obj.normals.size(); i++)
	{
		normals.push_back(obj.normals[i]);
	}
	while (!mid.empty())
	{
		mid.pop_back();
	}
	for (int i = 0; i < obj.mid.size(); i++)
	{
		mid.push_back(obj.mid[i]);
	}
	pl = new GVector3*[6];
	for (int i = 0; i < 6; i++)
	{
		pl[i] = new GVector3[4];
		for (int j = 0; j < 4; j++)
			pl[i][j] = obj.pl[i][j];
	}
}
Cube::Cube(const vector<GVector3> &v)
{
	index = 2;
	while (!vertexes.empty())
	{
		vertexes.pop_back();
	}
	while (!normals.empty())
	{
		normals.pop_back();
	}
	while (!mid.empty())
	{
		mid.pop_back();
	}
	while (!d.empty())
	{
		d.pop_back();
	}
	pl = new GVector3*[6];
	for (int i = 0; i < 6; i++)
	{
		pl[i] = new GVector3[4];
	}
	for (int j = 0; j < v.size(); j++)
		vertexes.push_back(v[j]);
	center = GVector3(0, 0, 0);
	for (int i = 0; i < vertexes.size(); i++)
	{
		center = center + v[i];
	}
	center = center / float(vertexes.size());
	length = float(10000);
	for (int i = 1; i < vertexes.size(); i++)
	{
		if (length > (vertexes[0] - vertexes[i]).getLength())
			length = (vertexes[0] - vertexes[i]).getLength();
	}
	mid.push_back((vertexes[0] + vertexes[1] + vertexes[2] + vertexes[3]) / 4);
	pl[0][0] = vertexes[0]; pl[0][1] = vertexes[1]; pl[0][2] = vertexes[2]; pl[0][3] = vertexes[3];
	mid.push_back((vertexes[0] + vertexes[3] + vertexes[4] + vertexes[5]) / 4);
	pl[1][0] = vertexes[5]; pl[1][1] = vertexes[0]; pl[1][2] = vertexes[3]; pl[1][3] = vertexes[4];
	mid.push_back((vertexes[0] + vertexes[1] + vertexes[5] + vertexes[6]) / 4);
	pl[2][0] = vertexes[5]; pl[2][1] = vertexes[6]; pl[2][2] = vertexes[1]; pl[2][3] = vertexes[0];
	mid.push_back((vertexes[1] + vertexes[2] + vertexes[6] + vertexes[7]) / 4);
	pl[3][0] = vertexes[1]; pl[3][1] = vertexes[6]; pl[3][2] = vertexes[7]; pl[3][3] = vertexes[2];
	mid.push_back((vertexes[2] + vertexes[3] + vertexes[4] + vertexes[7]) / 4);
	pl[4][0] = vertexes[3]; pl[4][1] = vertexes[2]; pl[4][2] = vertexes[7]; pl[4][3] = vertexes[4];
	mid.push_back((vertexes[4] + vertexes[5] + vertexes[6] + vertexes[7]) / 4);
	pl[5][0] = vertexes[5]; pl[5][1] = vertexes[6]; pl[5][2] = vertexes[7]; pl[5][3] = vertexes[4];
	for (int i = 0; i < mid.size(); i++)
	{
		normals.push_back((mid[i] - center).normalize());
	}
	for (int i = 0; i < mid.size(); i++)
	{
		d.push_back(mid[i].dotMul(normals[i]));
	}
}
Cube::~Cube()
{

}
GVector3 Cube::getCenter()
{
	return center;
}
double Cube::getLength()
{
	return length;
}
GVector3 Cube::getNormal(GVector3 point)
{
	GVector3 v;
	GVector3 inormal;
	inormal = normals[0];
	v = point - center;
	v.normalize();
	for (int i = 0; i < normals.size(); i++)
	{
		if (v.dotMul(inormal) < v.dotMul(normals[i]))
			inormal = normals[i];
	}
	return inormal;
}
IntersectResult Cube::isIntersected(CRay& RAY)
{
	IntersectResult result = IntersectResult::noHit();
	float s = float(10000);
	for (int i = 0; i < normals.size(); i++)
	{
		bool flag = false;
		float a = RAY.getDirection().dotMul(normals[i]);
		if (a < 0)
		{
			//float dis = normals[i].dotMul(RAY.getOrigin() - normals[i] * d[i]) / a;
			float dis = (d[i] - normals[i].dotMul(RAY.getOrigin())) / a;
			//dis = -dis;
			number++;
			if (dis > 0)
			{
				flag = false;
				pos++;
				GVector3 target = RAY.getPoint(dis);
				//if (normals[i].dotMul(mid[i]) == normals[i].dotMul(target))
				//{
					GVector3 v1 = (pl[i][2] - pl[i][3]).normalize();
					GVector3 v2 = (pl[i][1] - pl[i][2]).normalize();
					GVector3 v0 = (target-mid[i]).normalize();
					float f1 = v1.dotMul(pl[i][3]);
					float f2 = v2.dotMul(pl[i][2]);
					float pd1 = (f1 - v1.dotMul(mid[i])) / (v0.dotMul(v1));
					float pd2 = (f2 - v2.dotMul(mid[i])) / (v0.dotMul(v2));
					float mind = fabs(pd1);
					if (mind > fabs(pd2))
					{
						mind = fabs(pd2);
					}
					if (mind >= (target-mid[i]).getLength())
						flag = true;
				//}
				if (flag == true)
				{
					if (s > dis)
					{
						s = dis;
						result.isHit = 1;
						result.distance = s;
						result.position = target;
						result.normal = normals[i];
						result.object = this;
					}
				}
				/*for (int j = 0; j < 4; j++)
				{
					if ((target.x == pl[i][j].x) && (target.y == pl[i][j].y) && (target.z == pl[i][j].z))
					{
						if (s > dis)
						{
							s = dis;
							result.isHit = 1;
							result.distance = s;
							result.position = target;
							result.normal = normals[i];
							result.object = this;
						}
					}
				}
				GVector3 v1 = (pl[i][2] - pl[i][3]).normalize();
				GVector3 v2 = (pl[i][1] - pl[i][2]).normalize();
				GVector3 v0 = (pl[i][0] - target).normalize();
				float f1 = v1.dotMul(pl[i][3]);
				float f2 = v2.dotMul(pl[i][2]);
				float pd1 = (f1 - v1.dotMul(target)) / (v0.dotMul(v1));
				float pd2 = (f2 - v2.dotMul(target)) / (v0.dotMul(v2));
				GVector3 t1 = pl[i][3] + v1*pd1;
				GVector3 t2 = pl[i][2] + v2*pd2;
				if (((t1 - pl[i][3]).getLength() <= length && (t1 - pl[i][2]).getLength() <= length && pd1 >= 0) || ((t2 - pl[i][2]).getLength() <= length && (t2 - pl[i][1]).getLength() <= length && pd2 >= 0))
				{
					if (s > dis)
					{
						s = dis;
						result.isHit = 1;
						result.distance = s;
						result.position = target;
						result.normal = normals[i];
						result.object = this;
					}
				}*/
				/*GVector3 dpl[4];
				GVector3 tmp;
				for (int j = 0; j < 4; j++)
					dpl[j] = pl[i][j];
				for (int j = 0; j < 3; j++)
				{
					for (int k = j + 1; k < 4; k++)
					{
						if ((target - dpl[j]).getLength() < (target - dpl[k]).getLength())
						{
							tmp = dpl[j];
							dpl[j] = dpl[k];
							dpl[k] = tmp;
						}
					}
				}
				float re = 0;
				for (int j = 0; j < 4; j += 2)
					re += (dpl[j] - target).dotMul(dpl[j + 1] - target);
				if (re > 0)
				{
					if (s > dis)
					{
						s = dis;
						result.isHit = 1;
						result.distance = s;
						result.position = target;
						result.normal = normals[i];
						result.object = this;
						//cout << "hit" << endl;
					}
					//cout << dis << endl;
				}*/

			}
		}
	}
	return result;
}
void Cube::getinfo()
{
	cout << "center: " << center.x << " " << center.y << " " << center.z << endl;
	cout << "length: " << length << endl;
	for (int i = 0; i < normals.size(); i++)
		cout << "normal" << i << ": " << normals[i].x << " " << normals[i].y << " " << normals[i].z << endl;
	for (int i = 0; i < mid.size(); i++)
		cout << "mid" << i << ": " << mid[i].x << " " << mid[i].y << " " << mid[i].z << endl;
	//cout << "positive rate: " << pos / number << endl;
	for (int i = 0; i < normals.size(); i++)
	{
		GVector3 tmp = normals[i] * d[i];
		cout << tmp.x << " " << tmp.y << " " << tmp.z << endl;
	}
}