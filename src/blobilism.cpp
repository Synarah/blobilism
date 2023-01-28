#include <iostream>
#include <vector>
#include "tinygl-cpp.h"
using namespace tinygl;

struct colors{
  float red;
  float green;
  float blue;
  float trans;
};
struct cir{
  float x;
  float y; 
  float size;
};

class MyWindow : public Window {
 public:
  MyWindow(int w, int h) : Window(w, h) {}

  void setup() override {
    std::cout << "Window size: " << width() << ", " << height() << std::endl;
  }

  virtual void mouseMotion(int x, int y, int dx, int dy) {
    if (mouseIsDown(GLFW_MOUSE_BUTTON_LEFT)) {
      // todo: store a circle with the current color, size, x, y
      circs.x = x;
      circs.y = y;
      circs.size = cirSize;
      curCol.trans = curTran;
      drCol.push_back(curCol);
      dr.push_back(circs);
    }
  }

  
  virtual void mouseDown(int button, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
      // todo: check if user clicked a color 
      float mx = mouseX();  // current mouse pos x
      float my = mouseY();  // current mouse pos y
      float d;
      d = sqrt(pow(2,double(mx-40)) + pow(2,double(my-35)));
      if(d < 30){
        curCol.red = 1;
        curCol.green = 0;
        curCol.blue = 0; 
      }
      else {
        d = sqrt(pow(2,double(mx-110)) + pow(2,double(my-35)));
        if(d < 30){
          curCol.red = 0;
          curCol.green = 1;
          curCol.blue = 0; 
        }
        else{
          d = sqrt(pow(2,double(mx-180)) + pow(2,double(my-35)));
          if(d < 30){
            curCol.red = 0;
            curCol.green = 0;
            curCol.blue = 1; 
         }
         else{
           d = sqrt(pow(2,double(mx-250)) + pow(2,double(my-35)));
          if(d < 30){
            curCol.red = 0;
            curCol.green = 1;
            curCol.blue = 1; 
          }
          else{
            d = sqrt(pow(2,double(mx-320)) + pow(2,double(my-35)));
            if(d < 30){
              curCol.red = 1;
              curCol.green = 1;
              curCol.blue = 0; 
            }
          } 
          }
         }
        }
      }
      
      
      
      
  }

  void keyDown(int key, int mods) {
    if (key == GLFW_KEY_UP) {
      // increase size of circle
      cirSize = cirSize + 1;
    } 
    else if (key == GLFW_KEY_DOWN) {
      // decrease size of circle
      if(cirSize < 2){
        cirSize = cirSize;
      }
      else{
        cirSize = cirSize - 1;
        std::cout << "Window size: " << key << ", " << cirSize << std::endl;
      }
    }
    else if (key == GLFW_KEY_LEFT) {
      // decrease alpha
      if(curTran <= 0.1){
        curTran = curTran;
      }
      else{
        curTran = curTran - 0.1;
      }
    }
    else if (key == GLFW_KEY_RIGHT) {
      // increase alpha
      curTran = curTran + 0.1;
    }
    else if (key == GLFW_KEY_C) {
      // clear vector of circles
        dr.clear();
        drCol.clear();

      
    }
  }

  void draw() override {
    background(0.95f, 0.95f, 0.95f); // parameters: r, g, b

    //color(1.0f, 0.5f, 0.5f);
    //circle(width() * 0.5f, height() * 0.5, cirSize);

    // todo : draw pallet
      color(0.1f, 0.1f, 0.1f);
      square(width()/2.0f, 35, width(), 70);

      struct cir c = {40, 35, 60};
      struct colors col = {1, 0, 0};
      pal.push_back(c);
      colPal.push_back(col);
      c.x = 110;
      col.red = 0;
      col.green = 1;
      col.blue = 0;
      pal.push_back(c);
      colPal.push_back(col);
      c.x = 180;
      col.red = 0;
      col.green = 0;
      col.blue = 1;
      pal.push_back(c);
      colPal.push_back(col);
      c.x = 250;
      col.red = 0;
      col.green = 1;
      col.blue = 1;
      pal.push_back(c);
      colPal.push_back(col);
      c.x = 320;
      col.red = 1;
      col.green = 1;
      col.blue = 0;
      pal.push_back(c);
      colPal.push_back(col);
      for(int i = 0; i < pal.size(); i++){
        color(colPal[i].red, colPal[i].green, colPal[i].blue);
        circle(pal[i].x, pal[i].y, pal[i].size);
      }   
      for(int i = 0; i < dr.size(); i++){
        color(drCol[i].red, drCol[i].green, drCol[i].blue, drCol[i].trans);
        circle(dr[i].x, dr[i].y, dr[i].size);
      }  
  }
 private:

  // todo: create member variables for 
  // current circle size
  // current transparency
  // current color
  // list of circles to draw each frame
  // color pallet
  float cirSize = 40;
  float curTran = 1;
  struct colors curCol = {1,0,0}; 
  struct cir circs;
  std::vector<colors> colPal;
  std::vector<cir> pal;

  //for drawing color an pallet
  std::vector<cir> dr;
  std::vector<colors> drCol;
};

int main() {
  MyWindow window(500, 500);
  window.run();
}
