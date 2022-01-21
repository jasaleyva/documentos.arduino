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

/* declaración de variables */
int Do[5]={131,262,523,1046,2093};       // frecuencias 4 octavas de Do
int Dos[5]={139,277,554,1108,2217};      // Do#
int Re[5]={147,294,587,1175,2349};       // Re
int Res[5]={156,311,622,1244,2489};    // Re#
int Mi[5]={165,330,659,1319,2637};      // Mi
int Fa[5]={175,349,698,1397,2794};       // Fa
int Fas[5]={185,370,740,1480,2960};     // Fa#
int Sol[5]={196,392,784,1568,3136};     // Sol
int Sols[5]={208,415,831,1661,3322};   // Sol#
int La[5]={220,440,880,1760,3520};      // La
int Las[5]={233,466,932,1866,3729};    // La#
int Sib[5]={233,466,932,1866,3729};    // Sib = La#
int Si[5]={247,494,988,1976,3951};      // Si

int corto = 200; //200 milisegundos
int largo = 500; // 500ms
int x = 3; //escala musical, 3,4,5,6
int cuca[] = {
Do[x], Do[x], Do[x], Fa[x], La[x],
Do[x], Do[x], Do[x], Fa[x], La[x],
Fa[x], Fa[x], Mi[x], Mi[x], Re[x], Re[x], Do[x],
Do[x], Do[x], Do[x], Mi[x], Sol[x],
Do[x], Do[x], Do[x], Mi[x], Sol[x],
Dos[x], Res[x], Dos[x], Sib[x], La[x], Sol[x], Fa[x],

Do[x], Do[x],Fa[x], Fa[x],La[x], La[x],Dos[x], La[x],
Dos[x], Res[x], Dos[x], Sib[x], La[x], Dos[x], Si[x], Sol[x],
Do[x], Do[x], Mi[x], Mi[x],Sol[x],Sol[x],Si[x], Sol[x],
Dos[x], Res[x], Dos[x], Sib[x], La[x], Sol[x],Fa[x],

Do[x], Do[x], Do[x], Fa[x], La[x],
Do[x], Do[x], Do[x], Fa[x], La[x],
Fa[x], Fa[x], Mi[x], Mi[x], Re[x], Re[x], Do[x],
Do[x], Do[x], Do[x], Mi[x], Sol[x],
Do[x], Do[x], Do[x], Mi[x], Sol[x],
Dos[x], Res[x], Dos[x], Sib[x], La[x], Sol[x], Fa[x],

};
void setup() {
  // initialize serial communications (for debugging only):
  Serial.begin(9600);

}

void loop() {

int i = 0;
int tamano = sizeof(cuca) / sizeof(int); //siempre hay que dividir el tamaño del array por el tamaño del tipo de datos del array
  do
    {
      Serial.println(cuca[i]+ tamano);
      tone(7, cuca[i], 300);
      delay(300);        // retardo entre tonos por estabilidad
      i++;
  

    } while (i < tamano);
  noTone(7);//silencio final en el pin 7
  delay (2000);//2 segundos y a empezar...

}
