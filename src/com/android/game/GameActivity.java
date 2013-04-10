package com.android.game;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.nio.ShortBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import com.android.game.GameGLSurfaceView;
import com.android.game.GameRenderer;

import android.app.Activity;
import android.content.*;
import android.opengl.GLSurfaceView;
import android.opengl.GLU;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.view.WindowManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLUtils;
import android.view.Window;

import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStreamWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.FileWriter;
import android.os.*;
import java.io.BufferedOutputStream;
import java.io.OutputStream;

public class GameActivity extends Activity {
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        requestWindowFeature(Window.FEATURE_NO_TITLE);  
        mGLView = new GameGLSurfaceView(this);
        
        //mGLView.setEGLConfigChooser(false);
        setContentView(mGLView);
        
    }
    
    private GLSurfaceView mGLView;
}

class GameGLSurfaceView extends GLSurfaceView {
    public GameGLSurfaceView(Context context) {
        super(context);
        mRenderer = new GameRenderer(context);
        setRenderer(mRenderer);
        setRenderMode(GLSurfaceView.RENDERMODE_CONTINUOUSLY);
        //setEGLConfigChooser(8, 8, 8, 8, 16, 0);
    }
    public boolean onTouchEvent(final MotionEvent event) {
       /* if (event.getAction() == MotionEvent.ACTION_MOVE) 
        	return true;*/
        nativeOnTouch(event.getAction(),event.getX(),event.getY());
        
    	/*StringBuilder result=new StringBuilder(300);
    	result.append("Action: ").append(event.getAction()).append("\n");
    	result.append("Location: ").append(event.getX()).append(" x ").append(event.getY()).append("\n");
    	result.append("Presure: ").append(event.getPressure()).append("\n");
    	result.append("Size: ").append(event.getSize()).append("\n");
    	result.append("Down Time: ").append(event.getDownTime()).append("\n");
    	result.append("Event Time(ms): ").append(event.getEventTime()).append("\n");
    	result.append("Elapsed(ms): ").append(event.getEventTime()-event.getDownTime()).append("\n");
    	Log.i("Game",result.toString());*/
        return true;
    }
    GameRenderer mRenderer;
    private static native void nativeOnTouch(int event,float x,float y);
}

class GameRenderer implements GLSurfaceView.Renderer {
	
	private int mTextureID;
	private Context mContext;
	private final static int verts =3;
    private FloatBuffer mFVertexBuffer;
    private FloatBuffer mTexBuffer;
    private ShortBuffer mIndexBuffer;
    private int H;
    private int W;
    
	static {
        System.loadLibrary("gamenative");
    }
	public GameRenderer(Context context) {
		mContext=context;
		ByteBuffer vbb=ByteBuffer.allocateDirect(4*2*4);
		vbb.order(ByteOrder.nativeOrder());
		mFVertexBuffer=vbb.asFloatBuffer();
		
		ByteBuffer vtbb=ByteBuffer.allocateDirect(4*2*4);
		vtbb.order(ByteOrder.nativeOrder());
		mTexBuffer=vtbb.asFloatBuffer();
		
		ByteBuffer ibb=ByteBuffer.allocateDirect(6*2);
		ibb.order(ByteOrder.nativeOrder());
		mIndexBuffer=ibb.asShortBuffer();
		
	}
	
	public void loadTexture(int id){
		InputStream is = mContext.getResources().openRawResource(id);
        Bitmap bitmap;
        try {
            bitmap = BitmapFactory.decodeStream(is);
        } finally {
            try {
                is.close();
            } catch(IOException e) {
                // Ignore.
            }
        }
        int[] pixels = new int[bitmap.getWidth()*bitmap.getHeight()]; 
        bitmap.getPixels(pixels, 0, bitmap.getWidth(), 0, 0, bitmap.getWidth(), bitmap.getHeight()); 
        nativePushTexture(pixels,bitmap.getWidth(),bitmap.getHeight());
        bitmap.recycle();
	}
	
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
    	loadTexture(R.raw.zero);
    	loadTexture(R.raw.one);
    	loadTexture(R.raw.two);
    	loadTexture(R.raw.three);
    	loadTexture(R.raw.four);
    	loadTexture(R.raw.five);
    	loadTexture(R.raw.six);
    	loadTexture(R.raw.seven);
    	loadTexture(R.raw.eight);
    	loadTexture(R.raw.nine);
    	loadTexture(R.raw.background);
    	loadTexture(R.raw.tube);
    	loadTexture(R.raw.pbup);
    	loadTexture(R.raw.pbuppress);
    	loadTexture(R.raw.pbdown);
    	loadTexture(R.raw.pbdownpress);
    	loadTexture(R.raw.pbleft);
    	loadTexture(R.raw.pbleftpress);
    	loadTexture(R.raw.pbright);
    	loadTexture(R.raw.pbrightpress);
    	loadTexture(R.raw.noteup);
    	loadTexture(R.raw.notedown);
    	loadTexture(R.raw.noteleft);
    	loadTexture(R.raw.noteright);
        nativeInit();
    }

    public void onSurfaceChanged(GL10 gl, int w, int h) {
    	gl.glViewport(0, 0, w, h);
    	float ratio = (float) w/h;
    	gl.glMatrixMode(GL10.GL_PROJECTION);
    	gl.glLoadIdentity();
    	gl.glFrustumf(-ratio, ratio, -1, 1, 3, 7);
    	nativeResize(w, h);
        /*new Thread(new Runnable() {
			public void run() {
				nativeGameThread();
			}
		}).start();*/ 
        
    }
           
    public void onDrawFrame(GL10 gl) {
    	nativeRender();
    	return;
   }
    
    private static native void nativeInit();
    private static native void nativeResize(int w, int h);
    private static native void nativeRender();
    private static native void nativeGameThread();
    private static native void nativePushTexture(int[] pixels, int w, int h);
}