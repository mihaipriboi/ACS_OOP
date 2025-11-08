/*
Creați o clasă “Volume” care să aibă o metodă supraîncărcată pentru a calcula și afișa volumul pentru cub, sferă și piramidă, plus o metodă care să aibă același nume și să afișeze un mesaj. 
*/

#include <stdio.h>
#include <cmath>

using namespace std;

class Volume {
public:
  void display() {
    printf("Metoda display afiseaza volumul geometric.\n");
  }

  void display(double side) {
    double volume = side * side * side;
    printf("Volumul cubului cu latura %.2f este: %.2f\n", side, volume);
  }

  void display(double radius, bool isSphere) {
    if (!isSphere) return;
    
    double volume = (4.0 / 3.0) * M_PI * radius * radius * radius;
    printf("Volumul sferei cu raza %.2f este: %.2f\n", radius, volume);
  }

  void display(double baseLength, double height) {
    double volume = (1.0 / 3.0) * baseLength * baseLength * height;
    printf("Volumul piramidei cu latura bazei %.2f si inaltimea %.2f este: %.2f\n", baseLength, height, volume);
  }
};

int main() {
  Volume vol;

  vol.display();
  vol.display(3.0); // Cub cu latura 3.0
  vol.display(2.0, true); // Sfera cu raza 2.0
  vol.display(4.0, 5.0); // Piramida cu latura bazei 4.0 si inaltimea 5.0

  return 0;
}
