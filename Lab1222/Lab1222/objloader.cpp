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

	namespace fs = std::filesystem;
	std::string path = ".";
	for (const auto & entry : fs::directory_iterator(path))
		std::cout << entry.path() << std::endl;
	while (std::getline(file, line))
	{
		if (line.substr(0, 1) == "v")
		{
			std::vector<GLfloat> Point;
			GLfloat x, y, z;
			std::istringstream s(line.substr(2));
			s >> x; s >> y; s >> z;

			//�����̤j�ȳ̤p��
			if (i == 0) {
				minX = maxX = x;
				minY = maxY = y;
				minZ = maxZ = z;
				std::cout << "maxX:" << maxX << std::endl;
				std::cout << "minX:" << minX << std::endl;
				std::cout << "maxY:" << maxY << std::endl;
				std::cout << "minY:" << minY << std::endl;
				std::cout << "maxZ:" << maxY << std::endl;
				std::cout << "minZ:" << minY << std::endl;
			}

			if (maxX < x)
				maxX = x;
			if (minX > x) {
				minX = x;
				// std::cout << "��" << i << "���I" << std::endl;
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
	std::cout << "maxZ:" << maxY << std::endl;
	std::cout << "minZ:" << minY << std::endl;
}

void ObjLoader::Draw()
{
	//glBegin(GL_TRIANGLES);//�}�lø�s
	glColor3f(255.0f, 255.0f, 255.0f);
	for (int i = 0; i < f.size(); i++) {
		//�T�ӳ��I
		vertex a, b, c, normal, temp;

		GLint firstVertexIndex = (f[i])[0];//���X���I����
		GLint secondVertexIndex = (f[i])[1];
		GLint thirdVertexIndex = (f[i])[2];

		glBegin(GL_POLYGON);

		for (int j = 0; j < f[i].size(); j++) {
			GLint VertexIndex = (f[i])[j];
			temp.x = (v[VertexIndex])[0];
			temp.y = (v[VertexIndex])[1];
			temp.z = (v[VertexIndex])[2];

			glVertex3f(temp.x, temp.y, temp.z);
		}
		glEnd();
		//a.x = (v[firstVertexIndex])[0];//�Ĥ@�ӳ��I
		//a.y = (v[firstVertexIndex])[1];
		//a.z = (v[firstVertexIndex])[2];

		//b.x = (v[secondVertexIndex])[0]; //�ĤG�ӳ��I
		//b.y = (v[secondVertexIndex])[1];
		//b.z = (v[secondVertexIndex])[2];

		//c.x = (v[thirdVertexIndex])[0]; //�ĤT�ӳ��I
		//c.y = (v[thirdVertexIndex])[1];
		//c.z = (v[thirdVertexIndex])[2];

		//glVertex3f(a.x, a.y, a.z);//ø�s�T����
		//glVertex3f(b.x, b.y, b.z);
		//glVertex3f(c.x, c.y, c.z);
	}

}