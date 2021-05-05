#include "objloader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

ObjLoader::ObjLoader(std::string filename)
{
	std::ifstream file(filename);
	std::string line;
	int i = 0;

	//namespace fs = std::filesystem;
	//std::string path = ".";
	//for (const auto & entry : fs::directory_iterator(path))
	//	std::cout << entry.path() << std::endl;

	std::cout << "檔名" << filename << std::endl;
	while (std::getline(file, line))
	{
		if (line.substr(0, 1) == "v")
		{
			std::vector<GLfloat> Point;
			GLfloat x, y, z;
			std::istringstream s(line.substr(2));
			s >> x; s >> y; s >> z;

			//偵測最大值最小值
			if (i == 0) {
				minX = maxX = x;
				minY = maxY = y;
				minZ = maxZ = z;
				std::cout << "初始值:" << std::endl;
				std::cout << "maxX:" << maxX << std::endl;
				std::cout << "minX:" << minX << std::endl;
				std::cout << "maxY:" << maxY << std::endl;
				std::cout << "minY:" << minY << std::endl;
				std::cout << "maxZ:" << maxZ << std::endl;
				std::cout << "minZ:" << minZ << std::endl;
			}

			if (maxX < x)
				maxX = x;
			if (minX > x) {
				minX = x;
				// std::cout << "第" << i << "個點" << std::endl;
			}

			if (maxY < y)
				maxY = y;
			if (minY > y)
				minY = y;

			if (maxZ < z)
				maxZ = z;
			if (minZ > z)
				minZ = z;

			Point.push_back(x);
			Point.push_back(y);
			Point.push_back(z);
			v.push_back(Point);

			//std::cout << "read: x = " << x << " y = " << y << " z = " << z << std::endl;
			i++;
		}
		else if (line.substr(0, 1) == "f")
		{
			std::vector<GLint> vIndexSets;
			GLint u, v, w, x;
			std::istringstream vtns(line.substr(2));
			//vtns >> u; vtns >> v; vtns >> w;

			//vIndexSets.push_back(u - 1);
			//vIndexSets.push_back(v - 1);
			//vIndexSets.push_back(w - 1);

			while (!vtns.eof()) {
				vtns >> x;
				vIndexSets.push_back(x - 1);
			}
			f.push_back(vIndexSets);
		}

		//std::cout << "reading...." << std::endl;
	}
	file.close();
	std::cout << "v size : " << v.size() << "f size:" << f.size() << std::endl;
	std::cout << "maxX:" << maxX << std::endl;
	std::cout << "minX:" << minX << std::endl;
	std::cout << "maxY:" << maxY << std::endl;
	std::cout << "minY:" << minY << std::endl;
	std::cout << "maxZ:" << maxZ << std::endl;
	std::cout << "minZ:" << minZ << std::endl;

	midX = (maxX + minX) / 2;
	midY = (maxY + minY) / 2;
	midZ = (maxZ + minZ) / 2;

	std::cout << "midX:" << midX << std::endl;
	std::cout << "midY:" << midY << std::endl;
	std::cout << "midZ:" << midZ << std::endl;

	lengthX = abs(maxX - minX);
	lengthY = abs(maxY - minY);
	lengthZ = abs(maxZ - minZ);

	std::cout << "lengthX:" << lengthX << std::endl;
	std::cout << "lengthY:" << lengthY << std::endl;
	std::cout << "lengthZ:" << lengthZ << std::endl;

	draw_BoundingBox = true;
}

void ObjLoader::Draw()
{
	//glBegin(GL_TRIANGLES);//開始繪製
	glColor3f(255.0f, 255.0f, 255.0f);
	for (int i = 0; i < f.size(); i++) {
		vertex temp;

		glBegin(GL_POLYGON);

		for (int j = 0; j < f[i].size(); j++) {
			GLint VertexIndex = (f[i])[j];
			temp.x = (v[VertexIndex])[0];
			temp.y = (v[VertexIndex])[1];
			temp.z = (v[VertexIndex])[2];

			glVertex3f(temp.x, temp.y, temp.z);
		}
		glEnd();
	}
	//std::cout << "obj draw:" << std::endl;


	//畫六面的框框，偷懶只畫五個面，第六個面的線剛好都有
	if (draw_BoundingBox) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glBegin(GL_POLYGON);
		glVertex3f(minX, maxY, minZ);
		glVertex3f(maxX, maxY, minZ);
		glVertex3f(maxX, minY, minZ);
		glVertex3f(minX, minY, minZ);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(maxX, maxY, minZ);
		glVertex3f(maxX, minY, minZ);
		glVertex3f(maxX, minY, maxZ);
		glVertex3f(maxX, maxY, maxZ);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(minX, maxY, minZ);
		glVertex3f(maxX, maxY, minZ);
		glVertex3f(maxX, maxY, maxZ);
		glVertex3f(minX, maxY, maxZ);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(minX, maxY, minZ);
		glVertex3f(minX, maxY, maxZ);
		glVertex3f(minX, minY, maxZ);
		glVertex3f(minX, minY, minZ);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex3f(minX, maxY, maxZ);
		glVertex3f(maxX, maxY, maxZ);
		glVertex3f(maxX, minY, maxZ);
		glVertex3f(minX, minY, maxZ);
		glEnd();
	}
}