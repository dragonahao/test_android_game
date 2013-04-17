#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include "graphics.h"
#include <android/log.h>
/* x0,y0 *
 * 		  *
 * 		   *
 * 		    *
 *           *x1,y1
 * */
class Texture {
public:
	Texture(int idTex = 0, bool alpha = false) ;
	virtual ~Texture();
	void setUseAlpha(bool alpha);
	void setDiagonal(const Diagonal& _diagonal);
	Diagonal getDiagonal();
	void setID(const GLint& id);
	virtual void draw();
protected:
	GLint idTexture;
	bool useAlpha;
	Diagonal diagonal;
	GLfloat coordsTex[8];
	GLfloat coords[8];
	GLshort coordIndex[4];
};
#endif
