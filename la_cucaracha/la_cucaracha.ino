/*
Título: La cucaracha

1ª Do Do Do Fa La
2º Do Do Do Fa La
3º Fa Fa Mi Mi Re Re Do

4ª Do Do Do Mi Sol
5ª Do Do Do Mi Sol
6ª do4 re do Sib La Sol Fa

Frecuencias y notas:
Do 3: 262
Do# 3: 277
Re 3: 294
Re# 3: 311
Mi 3: 330
Fa 3: 349
Fa# 3: 370
Sol 3: 392
Sol#3: 415
La 3: 440
La# 3: 466
Si 3: 494
Do 4: 523 

*/
int Do = 261;
int Re = 293;
int Mi = 329;
int Fa = 349;
int Sol = 392;
int La = 440;
int Si = 494;
int Do4 =523;
int corto = 200; //200 milisegundos
int largo = 500; // 500ms

void setup() {
  // initialize serial communications (for debugging only):
  Serial.begin(9600);

}

void loop() {


  // play the pitch:
  //1ª Do Do Do Fa La   
  
  tone(7, Do, corto);
  delay(corto);        // delay in between reads for stability
  tone(7, Do, corto);
  delay(corto);        // delay in between reads for stability
  tone(7, Do, corto);
  delay(corto);        // delay in between reads for stability
  tone(7, Fa, largo);
  delay(largo);        // delay in between reads for stability
  tone(7, La, corto);
  delay(1000);        // delay in between reads for stability

//2ª Do Do Do Fa La 
  tone(7, Do, corto);
  delay(corto);        // delay in between reads for stability
  tone(7, Do, corto);
  delay(corto);        // delay in between reads for stability
  tone(7, Do, corto);
  delay(corto);        // delay in between reads for stability
  tone(7, Fa, largo);
  delay(largo);        // delay in between reads for stability
  tone(7, La, corto);
  delay(1000);        // delay in between reads for stability

// Fa Fa Mi Mi Re Re Do 3ª
  tone(7, Fa, corto);
  delay(corto);        // delay in between reads for stability
  tone(7, Fa, corto);
  delay(corto);        // delay in between reads for stability
  tone(7, Mi, largo);
  delay(corto);        // delay in between reads for stability
  tone(7, Mi, corto);
  delay(corto);        // delay in between reads for stability
  tone(7, Re, corto);
  delay(corto);        // delay in between reads for stability
  tone(7, Re, corto);
  delay(corto);        // delay in between reads for stability
  tone(7, Do, corto);
  delay(1500);        // delay in between reads for stability


//4ª Do Do Do Mi Sol
  tone(7, Do, corto);
  delay(corto);        // delay in between reads for stability
  tone(7, Do, corto);
  delay(corto);        // delay in between reads for stability
  tone(7, Do, corto);
  delay(corto);        // delay in between reads for stability
  tone(7, Mi, largo);
  delay(largo);        // delay in between reads for stability
  tone(7, Sol, corto);
  delay(1000);        // delay in between reads for stability


//5ª Do Do Do Mi Sol
  tone(7, Do, corto);
  delay(corto);        // delay in between reads for stability
  tone(7, Do, corto);
  delay(corto);        // delay in between reads for stability
  tone(7, Do, corto);
  delay(corto);        // delay in between reads for stability
  tone(7, Mi, largo);
  delay(largo);        // delay in between reads for stability
  tone(7, Sol, corto);
  delay(1000);        // delay in between reads for stability


//6ª do4 re do Sib La Sol Fa
  tone(7, Do4, corto);
  delay(corto);        // delay in between reads for stability
  tone(7, Re, corto);
  delay(corto);        // delay in between reads for stability
  tone(7, Do, corto);
  delay(corto);        // delay in between reads for stability
  tone(7, Si, corto);
  delay(corto);        // delay in between reads for stability
  tone(7, La, corto);
  delay(corto);        // delay in between reads for stability
  tone(7, Sol, corto);
  delay(corto);        // delay in between reads for stability
  tone(7, Fa, corto);
  delay(1000);        // delay in between reads for stability

  
}
