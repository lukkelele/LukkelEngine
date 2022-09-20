#include "Engine.h"


Engine::Engine() {
	this->width = 800;
	this->height = 600;
	createWindow(width, height, "Lukkelele", NULL, NULL);

};

Engine::Engine(int width, int height) {
	this->width = width;
	this->height = height;
	createWindow(width, height, "Lukkelele", NULL, NULL);

};


int Engine::initGLFW() {
	if (!glfwInit())
		return -1;
	return 0;
}

/*
int Engine::initOLC() {
	if (this->olcEngine.Construct(640, 480, 4, 4))
		this->olcEngine.Start();
	return 0;
}
*/


int Engine::createWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share) {
	this->window = glfwCreateWindow(width, height, title, monitor, share);
	if (!window) {
		glfwTerminate();
		return -1;
	}
}

bool Engine::onUserCreate() {

	createCube();
	// PROJECTION MATRIX
	float z_near = 0.1f;
	float z_far = 1000.f;
	float fov = 90.f;
	float aspectRatio = getAspectRatio();
	float fovRad = degreeToRadian(fov);
	float fovRadian = 1.0f / tanf(fovRad * 0.5f); 

	// matProj.m[ROW][COLUMN]
	matProj.m[0][0] = aspectRatio * fovRadian;
	matProj.m[1][1] = fovRadian;
	matProj.m[2][2] = z_far / (z_far - z_near);
	matProj.m[2][3] = 1.0f;
	matProj.m[3][2] = -(z_far * z_near) / (z_far - z_near);
	matProj.m[3][3] = 0.0f;

	return true;
}

float Engine::degreeToRadian(float degrees) {
	// 180 degrees = 1 rad --> 1 degree = 1/180 rad
	return degrees * (1 / 180.0f) * 3.14f;
}

bool Engine::onUserUpdate(float elapsedTime) {
	clearScreen();

	for (auto tri : meshCube.tris) {
		triangle triProj, triTranslated;
		for (int i = 0; i < 3; i++) {
			triTranslated.p[i].z = tri.p[0].z + 3.0f;
			multiplyMatrix(triTranslated.p[i], triProj.p[i], matProj);
			if (i < 2)	// TODO: Fix draw line
				drawLine(triTranslated.p[i], triTranslated.p[i + 1]);
		}
	}
	return true;
}


/* Matrix multiplication -> a*mat = b
   Input vector: a
   Output vector: b  */
void Engine::multiplyMatrix(vec3& a, vec3& b, mat4& mat) {
	b.x = a.x * mat.m[0][0] + a.y * mat.m[1][0] + a.z * mat.m[2][0] + mat.m[3][0];
	b.y = a.x * mat.m[0][1] + a.y * mat.m[1][1] + a.z * mat.m[2][1] + mat.m[3][1];
	b.z = a.x * mat.m[0][2] + a.y * mat.m[1][2] + a.z * mat.m[2][2] + mat.m[3][2];
	float w = a.x * mat.m[0][3] + a.y * mat.m[1][3] + a.z * mat.m[2][3] + mat.m[3][3];
	// Fourth element needs to be set to 1 to get back to 3D, divide xyz with w
	if (w != 0.0f) { b.x /= w; b.y /= w; b.z /= w; }
}

bool Engine::createCube() {
	meshCube.tris = {
		// South
		{ 0.0f, 0.0f, 0.0f,   0.0f, 1.0f, 0.0f,  1.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f },
		// East
		{ 1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 0.0f,  1.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,  1.0f, 0.0f, 1.0f },
		// North
		{ 1.0f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 1.0f,   0.0f, 1.0f, 1.0f,  0.0f, 0.0f, 0.0f },
		// West
		{ 0.0f, 0.0f, 1.0f,   0.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f,   0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 0.0f },
		// Top
		{ 0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f,   1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 0.0f },
		// Bottom
		{ 0.0f, 0.0f, 0.0f,   0.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f,   1.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f }
	};
	return true;
}


void Engine::clearScreen() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// Only works when on window is on primary monitor
void Engine::getScreenSize() {
	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);
	this->height = mode->height;
	this->width = mode->width;
}

float Engine::getAspectRatio() {
	getScreenSize();
	return (float)(this->height / this->width);
}

/* Draw a line from vec1 -> vec2 */
void Engine::drawLine(vec3 vec1, vec3 vec2) {
	std::vector<float> vertices = {
		vec1.x, vec1.y, vec1.z,
		vec2.x, vec2.y, vec2.z
	};
	// DRAW LINE

}

int Engine::getHeight() {
	return this->height;
}

int Engine::getWidth() {
	return this->width;
}


bool Engine::LoadFromObjectFile(std::string sFilename, bool bHasTexture) {
	std::ifstream f(sFilename);
	if (!f.is_open())
		return false;

	// Local cache of verts
	std::vector<Engine::vec3> verts;
	std::vector<Engine::vec2> texs;
	std::vector<triangle> tris;

	while (!f.eof())
	{
		char line[128];
		f.getline(line, 128);
		std::strstream s;
		s << line;

		char junk;

		if (line[0] == 'v') {
			if (line[1] == 't') {
				Engine::vec2 v;
				s >> junk >> junk >> v.u >> v.v;
				// A little hack for the spyro texture
				//v.u = 1.0f - v.u;
				//v.v = 1.0f - v.v;
				texs.push_back(v);
			}
			else {
				Engine::vec3 v;
				s >> junk >> v.x >> v.y >> v.z;
				verts.push_back(v);
			}
		}
		if (!bHasTexture)
		{
			if (line[0] == 'f')
			{
				int f[3];
				s >> junk >> f[0] >> f[1] >> f[2];
				tris.push_back({ verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1] });
			}
		}
		else {
			if (line[0] == 'f')
			{
				s >> junk;
				std::string tokens[6];
				int nTokenCount = -1;


				while (!s.eof())
				{
					char c = s.get();
					if (c == ' ' || c == '/')
						nTokenCount++;
					else
						tokens[nTokenCount].append(1, c);
				}
				tokens[nTokenCount].pop_back();

				//tris.push_back({ verts[stoi(tokens[0]) - 1], verts[stoi(tokens[2]) - 1], verts[stoi(tokens[4]) - 1],
				//	texs[stoi(tokens[1]) - 1], texs[stoi(tokens[3]) - 1], texs[stoi(tokens[5]) - 1] });
			}
		}
	}
	return true;
}

