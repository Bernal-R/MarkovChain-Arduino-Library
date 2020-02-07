#include <MarkovChain.h>

MarkovChain chain;

//Definir matriz de entrenamiento
  char trainingSet[3][5] = {
    {'a', 'b', 'c', 'c', '\0'},
    {'a', 'c', 'c', 'c', '\0'},
    {'a', 'b', 'c', 'c', '\0'}
  };
  
void setup() {
  Serial.begin(9600);

  char estados [] = {'a', 'b', 'c'};

  double* probabilidad = chain.predict('a', estados, 3, trainingSet, 3); //Calcular cadena a partir del set de entrenamiento

  Serial.println("Probabilidad:");
  for (int i = 0; i < 3; i++) {
    Serial.print(estados[i]);
    Serial.print(":");
    Serial.println(probabilidad[i]);
  }

}

void loop() {
}
