#ifndef _MESH_H
#define _MESH_H

#include <windows.h>
#include <vector>

#include <GL\glew.h>
#include <SDL.h>

#include <glm\vec2.hpp>
#include <glm\vec3.hpp>
#include <glm\vec4.hpp>


#include <string>
#include <fstream>
using std::ifstream;
using std::string;

#include "AABB.h"


/*
    Mesh Class, taken from the framework provided with some modifications
*/

enum MeshBuffer {
    VERTEX_BUFFER = 0,
    COLOUR_BUFFER = 1,
    TEXTURE_BUFFER,
    INDEX_BUFFER,
    NORMAL_BUFFER,
    MAX_BUFFER
};

class Mesh
{
public:
    Mesh();
    ~Mesh();

    void render();
    AABB* getAABB();
    AABB* getAABB(glm::mat4 model);

    static Mesh* GenerateTriangle();
    static Mesh* generateCube(float width, float height, float depth);
    static Mesh*	LoadMeshFile(const string &filename);
    static Mesh*	LoadObj(const string &filename);


protected:
    void bufferData();

    GLuint  arrayObject;
    GLuint	bufferObject[MAX_BUFFER];
    GLuint	numVertices;
    GLuint  type;
    GLuint	texture;

    GLuint			numIndices;
    glm::vec3*		vertices;
    glm::vec3*		normals;
    glm::vec4*		colours;
    glm::vec2*		textureCoords;
    unsigned int*	indices;

};

#endif