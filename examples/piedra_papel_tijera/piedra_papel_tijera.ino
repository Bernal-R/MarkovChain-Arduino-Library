#include <MarkovChain.h>

MarkovChain chain;
char last_choose = 'r';
char trainingSet[5][5];

char elements [] = {'r', 's', 'p'};
boolean r_button, p_button, s_button = true;
unsigned long previousMillis = 0;
const long interval = 1000;
int num_round_training = 3;

int choose_more_likely(double* probabilities) {
  int major = 0;
  if (probabilities[0] < probabilities[1]) {
    major = 1;
  } else {
    major = 0;
  }
  if (probabilities[major] < probabilities[2]) {
    major = 2;
  }
  return major;
}


void takeDesicion(char elements) {
  //Game rules
  if (elements == 's') { //Rock beats sissor
    last_choose = 's';
    Serial.println("Machine choose Rock");
  } else if (elements == 'r') { // Paper beats rock
    last_choose = 'r';
    Serial.println("Machine choose Paper");
  } else if (elements == 'p') { //Sissors beats paper
    last_choose = 'p';
    Serial.println("Machine choose Sissors");
  }
}


void train() {
  String states[3] = {"rock", "paper", "sissors"};
    
  char selection;

  Serial.println("****************** Ready for the train ******************");

  for (int i = 0; i < num_round_training; i++) {
    Serial.println(" NEW ROUND!!");
    for (int j = 0; j < num_round_training; j++) {
      if (j != num_round_training) {

        Serial.println("1...");
        delay(800);
        Serial.println("2...");
        delay(800);
        Serial.println("3...");

        while (r_button == true || p_button == true || s_button == true) {
          r_button = digitalRead(12);
          p_button = digitalRead(11);
          s_button = digitalRead(10);

          if (r_button == false) {
            unsigned long currentMillis = millis();
            if (currentMillis - previousMillis >= interval) {
              previousMillis = currentMillis;
              selection = 'r';
              Serial.println("You choose: Rock");
              break;
            }

          } else if (p_button == false) {
            unsigned long currentMillis = millis();
            if (currentMillis - previousMillis >= interval) {
              previousMillis = currentMillis;
              selection = 'p';
              Serial.println("You choose: Paper");
              break;
            }
          } else if (s_button == false) {
            unsigned long currentMillis = millis();
            if (currentMillis - previousMillis >= interval) {
              previousMillis = currentMillis;
              selection = 's';
              Serial.println("You choose: Sissors");
              break;
            }
          }
        }
      } else {
        trainingSet[i][j] = '\0';
      }
      Serial.print("Machine choose: ");
      Serial.println(states[random(0, 3)]);
      trainingSet[i][j] = selection;

      delay(1000);
    }
  }
  Serial.println("****************** Training end ******************");
}


void setup() {
  Serial.begin(9600);
  pinMode(12, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  train();
}

void loop() {
  Serial.println("****************** Game Start!! ******************");

  Serial.println("1...");
  delay(800);
  Serial.println("2...");
  delay(800);
  Serial.println("3...");

  double* probabilities = chain.predict(last_choose, elements, 3, trainingSet, 3);
  int major = choose_more_likely(probabilities);
  //Serial.print(". Machine predict that now player will choose: ");
  //Serial.println(elements[major]);
  takeDesicion(elements[major]);


  while (r_button == true || p_button == true || s_button == true) {
    r_button = digitalRead(12);
    p_button = digitalRead(11);
    s_button = digitalRead(10);

    if (r_button == false) {
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        last_choose = 'r';
        Serial.println("You choose: Rock");
        break;
      }

    } else if (p_button == false) {
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        last_choose = 'p';
        Serial.println("You choose: Paper");
        break;
      }
    } else if (s_button == false) {
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        last_choose = 's';
        Serial.println("You choose: Sissors");
        break;
      }
    }
  }

  delay(1000);
}
