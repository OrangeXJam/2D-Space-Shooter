#ifndef MESHHANDLER_H
#define MESHHANDLER_H

#include <glad/glad.h>

unsigned int createMeshTexture(float* points, int size)
{
    //Creats table that stores vertex configs of verticies which are inside the VBO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //Creates a vertex buffer object to hold points and we bind it to the outlet of verticies
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, points, GL_STATIC_DRAW);

    //Creates a slot and saves the VBO config data inside the VAO table
    //First Slot saves the screen coord data
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //Second Slot saves the texture coord data
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(1);
    return VAO;
}

unsigned int createMesh(float* points, int size)
{
    //Creats table that stores vertex configs of verticies which are inside the VBO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //Creates a vertex buffer object to hold points and we bind it to the outlet of verticies
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, points, GL_STATIC_DRAW);

    //Creates a slot and saves the VBO config data inside the VAO table
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    return VAO;
}

#endif // MESHHANDLER_H