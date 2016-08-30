#include "mesh.h"

Mesh::Mesh(void)	{

    glGenVertexArrays(1, &arrayObject);
    //glClearColor(1, 1, 1, 1);

    for (int i = 0; i < MAX_BUFFER; ++i) {
        bufferObject[i] = 0;
    }

    texture = 0;
    numVertices = 0;
    type = GL_TRIANGLES;

    //Later tutorial stuff
    numIndices = 0;
    vertices = NULL;
    normals = NULL;
    textureCoords = NULL;
    indices = NULL;
    colours = NULL;
}


Mesh::~Mesh(void)	{
    glDeleteVertexArrays(1, &arrayObject);			//Delete our VAO
    glDeleteBuffers(MAX_BUFFER, bufferObject);		//Delete our VBOs


    //Later tutorial stuff
    delete[]vertices;
    delete[]normals;
    delete[]indices;
    delete[]textureCoords;
    delete[]colours;
}

void Mesh::render()	{
    glBindVertexArray(arrayObject);
    if (bufferObject[INDEX_BUFFER]) {
        glDrawElements(type, numIndices, GL_UNSIGNED_INT, 0);
    }
    else{
        glDrawArrays(type, 0, numVertices);	//Draw the triangle!
    }
    glBindVertexArray(0);
}

void	Mesh::bufferData()	{
    glBindVertexArray(arrayObject);

    //Buffer vertex data
    glGenBuffers(1, &bufferObject[VERTEX_BUFFER]);
    glBindBuffer(GL_ARRAY_BUFFER, bufferObject[VERTEX_BUFFER]);
    glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(glm::vec3), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(VERTEX_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(VERTEX_BUFFER);

    ////Buffer texture data
    if (textureCoords) {
        glGenBuffers(1, &bufferObject[TEXTURE_BUFFER]);
        glBindBuffer(GL_ARRAY_BUFFER, bufferObject[TEXTURE_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(glm::vec2), textureCoords, GL_STATIC_DRAW);
        glVertexAttribPointer(TEXTURE_BUFFER, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(TEXTURE_BUFFER);
    }

    //buffer colour data
    if (colours)	{
        glGenBuffers(1, &bufferObject[COLOUR_BUFFER]);
        glBindBuffer(GL_ARRAY_BUFFER, bufferObject[COLOUR_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(glm::vec4), colours, GL_STATIC_DRAW);
        glVertexAttribPointer(COLOUR_BUFFER, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(COLOUR_BUFFER);
    }

    //buffer colour data
    if (normals)	{
        glGenBuffers(1, &bufferObject[NORMAL_BUFFER]);
        glBindBuffer(GL_ARRAY_BUFFER, bufferObject[NORMAL_BUFFER]);
        glBufferData(GL_ARRAY_BUFFER, numVertices*sizeof(glm::vec3), normals, GL_STATIC_DRAW);
        glVertexAttribPointer(NORMAL_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(NORMAL_BUFFER);
    }

    //buffer index data
    if (indices) {
        glGenBuffers(1, &bufferObject[INDEX_BUFFER]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferObject[INDEX_BUFFER]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices*sizeof(GLuint), indices, GL_STATIC_DRAW);
    }



    glBindVertexArray(0);
}

Mesh* Mesh::GenerateTriangle()	{
    Mesh*m = new Mesh();
    m->numVertices = 6;

    m->vertices = new glm::vec3[m->numVertices];
    m->vertices[0] = glm::vec3(0.0f, 0.5f, 0.0f);
    m->vertices[1] = glm::vec3(0.5f, -0.5f, 0.0f);
    m->vertices[2] = glm::vec3(-0.5f, -0.5f, 0.0f);

    m->textureCoords = new glm::vec2[m->numVertices];
    m->textureCoords[0] = glm::vec2(0.5f, 0.0f);
    m->textureCoords[1] = glm::vec2(1.0f, 1.0f);
    m->textureCoords[2] = glm::vec2(0.0f, 1.0f);

    m->colours = new glm::vec4[m->numVertices];
    m->colours[0] = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    m->colours[1] = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    m->colours[2] = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

    m->bufferData();

    return m;
}

Mesh*	Mesh::LoadMeshFile(const string &filename) {
    ifstream f(filename);

    if (!f) {
        return NULL;
    }

    Mesh*m = new Mesh();
    f >> m->numVertices;

    int hasTex = 0;
    int hasColour = 0;

    f >> hasTex;
    f >> hasColour;

    m->vertices = new glm::vec3[m->numVertices];

    if (hasTex) {
        m->textureCoords = new glm::vec2[m->numVertices];
    }
    if (hasColour)
    {
        m->colours = new glm::vec4[m->numVertices];
    }
    
    
    for (unsigned i = 0; i < m->numVertices; ++i) {
        f >> m->vertices[i].x;
        f >> m->vertices[i].y;
        f >> m->vertices[i].z;

    }
    if (hasColour) {
        for (unsigned i = 0; i < m->numVertices; ++i) {

            char r, g, b, a;

            f >> r;
            f >> g;
            f >> b;
            f >> a;

            m->colours[i] = glm::vec4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);

        }
    }
    if (hasTex) {
        for (unsigned i = 0; i < m->numVertices; ++i) {

            f >> m->textureCoords[i].x;
            f >> m->textureCoords[i].y;
        }
    }
    

    m->bufferData();
    return m;
}


Mesh*	Mesh::LoadObj(const string &path) 
{
    printf("Loading OBJ file %s...\n", path.c_str());

    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;

    FILE * file;
    fopen_s(&file, path.c_str(), "r");
    if (file == NULL){
        printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
        getchar();
        return false;
    }

    while (1){
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf_s(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.

        // else : parse lineHeader

        if (strcmp(lineHeader, "v") == 0){
            glm::vec3 vertex;
            fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.push_back(vertex);
        }
        else if (strcmp(lineHeader, "vt") == 0){
            glm::vec2 uv;
            fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
            uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
            temp_uvs.push_back(uv);
        }
        else if (strcmp(lineHeader, "vn") == 0){
            glm::vec3 normal;
            fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        }
        else if (strcmp(lineHeader, "f") == 0){
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            if (matches != 9){
                printf("File can't be read by our simple parser :-( Try exporting with other options\n");
                return false;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices.push_back(uvIndex[0]);
            uvIndices.push_back(uvIndex[1]);
            uvIndices.push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }
        else{
            // Probably a comment, eat up the rest of the line
            char stupidBuffer[1000];
            fgets(stupidBuffer, 1000, file);
        }
    }


    Mesh*m = new Mesh();
    m->numVertices = vertexIndices.size();

    m->vertices = new glm::vec3[m->numVertices];
    m->textureCoords = new glm::vec2[m->numVertices];
    m->colours = new glm::vec4[m->numVertices];
    m->normals = new glm::vec3[m->numVertices];

    // For each vertex of each triangle
    for (unsigned int i = 0; i<vertexIndices.size(); i++){

        // Get the indices of its attributes
        unsigned int vertexIndex = vertexIndices[i];
        unsigned int uvIndex = uvIndices[i];
        unsigned int normalIndex = normalIndices[i];

        // Get the attributes thanks to the index
        m->vertices[i] = temp_vertices[vertexIndex - 1];
        m->textureCoords[i] = temp_uvs[uvIndex - 1];
        m->normals[i] = temp_normals[normalIndex - 1];
        m->colours[i] = glm::vec4(1.0f, .0f, .0f, .0f);
        // Put the attributes in buffers
    }

    m->bufferData();
    return m;
}
    
AABB* Mesh::getAABB()
{
    glm::vec3 b(FLT_MIN);
    glm::vec3 a(FLT_MAX);

    for (unsigned i = 0; i < numVertices; i++)
    {
        if (vertices[i].x > b.x)    b.x = vertices[i].x;
        if (vertices[i].y > b.y)    b.y = vertices[i].y;
        if (vertices[i].x > b.z)    b.z = vertices[i].z;

        if (vertices[i].x < a.x)    a.x = vertices[i].x;
        if (vertices[i].y < a.y)    a.y = vertices[i].y;
        if (vertices[i].x < a.z)    a.z = vertices[i].z;
    }


    return new AABB((a + b) / 2.f, (b - a) / 2.f);
}

AABB* Mesh::getAABB(glm::mat4 model)
{
    glm::vec3 b(FLT_MIN);
    glm::vec3 a(FLT_MAX);

    for (unsigned i = 0; i < numVertices; i++)
    {
        glm::vec4 v = glm::vec4(vertices[i].x, vertices[i].y, vertices[i].z, 1.f);
        v = v * model;

        if (v.x > b.x)    b.x = v.x;
        if (v.y > b.y)    b.y = v.y;
        if (v.x > b.z)    b.z = v.z;

        if (v.x < a.x)    a.x = v.x;
        if (v.y < a.y)    a.y = v.y;
        if (v.x < a.z)    a.z = v.z;
    }


    return new AABB((a + b) / 2.f, (b - a) / 2.f);
}