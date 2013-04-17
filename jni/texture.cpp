#include "texture.h"

void Texture::draw(){
    glDisable(GL_DITHER);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    if(useAlpha){
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GEQUAL, 0.5);
    }
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindTexture(GL_TEXTURE_2D, idTexture);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterx(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glVertexPointer(2, GL_FLOAT, 0, coords);
    glTexCoordPointer(2, GL_FLOAT, 0, coordsTex);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, coordIndex);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    if(useAlpha)
        glDisable(GL_ALPHA_TEST);
    glDisable(GL_TEXTURE_2D);
}

Texture::Texture(int idTex, bool alpha) : idTexture(idTex),useAlpha(alpha) {
    coordsTex[0] = 0;
    coordsTex[1] = 1;
    coordsTex[2] = 1;
    coordsTex[3] = 1;
    coordsTex[4] = 0;
    coordsTex[5] = 0;
    coordsTex[6] = 1;
    coordsTex[7] = 0;
    for(int i = 0; i < 4; i++){
        coordIndex[i] = i;
    }
}

Texture::~Texture(){

}

void Texture::setUseAlpha(bool alpha){
    useAlpha = alpha;
}

void Texture::setDiagonal(const Diagonal& _diagonal){
    diagonal =  _diagonal;
    coords[0] = _diagonal.pos0.x;
    coords[1] = _diagonal.pos1.y;
    coords[2] = _diagonal.pos1.x;
    coords[3] = _diagonal.pos1.y;
    coords[4] = _diagonal.pos0.x;
    coords[5] = _diagonal.pos0.y;
    coords[6] = _diagonal.pos1.x;
    coords[7] = _diagonal.pos0.y;
}

Diagonal Texture::getDiagonal(){
    return diagonal;
}

void Texture::setID(const GLint& id){
    idTexture = id;
}
