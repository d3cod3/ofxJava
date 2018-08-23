/*
 *      ----------------------------------------------------------
 *      Mosaic | OF Visual Patching Developer Platform
 *
 *      Copyright (c) 2018 Emanuele Mazza aka n3m3da
 *
 *      Mosaic is distributed under the MIT License. This gives everyone the
 *      freedoms to use Mosaic in any context: commercial or non-commercial,
 *      public or private, open or closed source.
 *
 *      See https://github.com/d3cod3/Mosaic for documentation
 *      ----------------------------------------------------------
 *
 *
 *      MosaicProcessingClass.java: A Processing template for Mosaic
 *
 *      see https://processing.org/reference for Language Reference
 *
 */

import processing.core.*;

public class MosaicProcessingClass extends PApplet{

    //////////////////////////////////////////////////////
    public static void main(String[] args) {
        PApplet.main("MosaicProcessingClass");
    }

    String[]    _data;
    float[]     _mosaicData;
    byte[]      _pix;
    boolean     _savedImage = false;
    //////////////////////////////////////////////////////


    float yoff = 0.0f;

    public void settings() {
        size(640, 360);
        smooth();
    }

     public void setup() {
        //////////////////////////////////////////////////////
        frameRate(30);
        surface.setVisible(false);
        //////////////////////////////////////////////////////
     }

     public void draw() {
        //////////////////////////////////////////////////////
        _data = loadStrings("data.txt");
        _mosaicData = new float[_data.length];
        for (int i = 0 ; i < _data.length; i++) {
            _mosaicData[i] = Float.parseFloat(_data[i]);
        }
        //////////////////////////////////////////////////////

        //background(0);

        fill(0,0,0,10);
        rect(0,0,width,height);

        fill(55,255,5,30);

        beginShape(); 
  
        float xoff = 0;
  
        // Iterate over horizontal pixels
        for (float x = 0; x <= width; x += 10) {
            // Calculate a y value according to noise, map to 
            float y = map(noise(xoff, yoff), 0, 1, 200,300);
            // Set the vertex
            vertex(x, y); 
            // Increment x dimension for noise
            xoff += 0.05;
        }
        // increment y dimension for noise
        yoff += 0.01;
        vertex(width, height);
        vertex(0, height);
        endShape(CLOSE);

        //println(_mosaicData[0]);

        //////////////////////////////////////////////////////
        loadPixels();
        _pix = new byte[pixels.length*3];
        int index = 0;
        for (int i = 0; i < pixels.length; i++) {
            _pix[index] = (byte)red(pixels[i]);
            index++;
            _pix[index] = (byte)green(pixels[i]);
            index++;
            _pix[index] = (byte)blue(pixels[i]);
            index++;
        }
        saveBytes("MosaicProcessingClass.dat", _pix);

        if(!_savedImage){
            _savedImage = true;
            saveFrame("MosaicProcessingClass.png");
        }
        //////////////////////////////////////////////////////
     }

     public void mousePressed() {

     }

     public void mouseDragged() {

     }

     public void mouseReleased() {

     }

     public void keyPressed() {

     }
}