#include "main.h"

void redFront() {
  moveForward(48);
}

void blueFront(){
  moveForward(48);
}
void autonomous() {

  switch (autonIndex) {
    case 0:
    redFront();
    break;
    case 1:
    blueFront();
    break;
  }
}
