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
class Texture{
public:
	Texture(int idTex=0,bool alpha=false) : idTexture(idTex),useAlpha(alpha) {
		coordsTex[0]=0;
		coordsTex[1]=1;
		coordsTex[2]=1;
		coordsTex[3]=1;
		coordsTex[4]=0;
		coordsTex[5]=0;
		coordsTex[6]=1;
		coordsTex[7]=0;
		for(int i=0;i<4;i++){
			coordIndex[i]=i;
		}
	}
	inline void setUseAlpha(bool alpha){
		useAlpha=alpha;
	}
	inline void setDiagonal(const Diagonal& _diagonal){//Point2f pos0,Point2f pos1){
		diagonal= _diagonal;
		coords[0]=_diagonal.pos0.x;
		coords[1]=_diagonal.pos1.y;
		coords[2]=_diagonal.pos1.x;
		coords[3]=_diagonal.pos1.y;
		coords[4]=_diagonal.pos0.x;
		coords[5]=_diagonal.pos0.y;
		coords[6]=_diagonal.pos1.x;
		coords[7]=_diagonal.pos0.y;
	}
	inline Diagonal getDiagonal(){
		return diagonal;
	}
	inline void setID(const GLint& id){
		idTexture=id;
	}
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
