////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Ejemplo: cONFIGURACION de entradas PullUP/PullDOWN/INTERRUPCIONES - prof.martintorres@educ.ar - ETI Patagonia
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const int boton_1 = 4;   
const int boton_2 = 5;
const int boton_3 = 6; 
const int LED_B3  = 9;
const int LED_B2  =10;
const int LED_B1  =11;
const int LED_INT =12;

int a;
//variables pulsador B1
        uint8_t valB1=0;
        int val_B1_viejo=1; //button old
        int val_B1_nuevo;   //buton new
        int L1_estado=0;    //led estado
//variables pulsador B2
        uint8_t valB2=0;
        int val_B2_viejo=0; //button old
        int val_B2_nuevo;   //buton new
        int L2_estado=0;    //led estado
//variables pulsador B3
        uint8_t valB3=0;
        int val_B3_viejo=1; //button old
        int val_B3_nuevo;   //buton new
        int L3_estado=0;    //led estado

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void setup()
  {
  Serial.begin(9600);        // Para ver información en el Seria Monitor.
  //CONFIGURAMOS LA INTERRUPCION EN LOS PUERTOS 2 Y 3 
  attachInterrupt(0, enciende, RISING); // 0 es la interrupción 0, es decir el pin 2
  attachInterrupt(1, apaga, RISING);    // 1 es la interrupción 1, es decir el pin 3
  //CONFIGURAMOS LOS PUERTOS COMO ENTRADAS
  pinMode(boton_1, INPUT_PULLUP); //pulsador que enciende Led B1 y esta seteada la entrada con la configuracion PullUP interna
  pinMode(boton_2, INPUT); //pulsador que enciende Led B2 y esta seteada la entrada con la configuracion externa PullDOWN
  pinMode(boton_3, INPUT); //pulsador que enciende Led B3 y esta seteada la entrada con la configuracion externa PullUP
  //CONFIGURAMOS LOS PUERTOS COMO SALIDAS 
  pinMode(LED_B3, OUTPUT);   // led comandado por el pulsador B3
  pinMode(LED_B2, OUTPUT);   // led comandado por el pulsador B2
  pinMode(LED_B1, OUTPUT);   // led comandado por el pulsador B1
  pinMode(LED_INT, OUTPUT);   //  led comandado por el pulsador de interrupcion 2
  digitalWrite(LED_B3, LOW); 
  digitalWrite(LED_B2, LOW); 
  digitalWrite(LED_B1, LOW); 
  //digitalWrite(LED_INT, LOW); 
  }
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void loop()
           {
           lecturaPULSADOR();
           CtrlSALIDAS();
           }

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void lecturaPULSADOR()
{
  ///////////////// LECTURA PULSADOR B1 /////////////////
     valB1 = digitalRead(boton_1);
        val_B1_nuevo = valB1;
///////////////// LECTURA PULSADOR B2 /////////////////
     valB2 = digitalRead(boton_2);
        val_B2_nuevo = valB2;
///////////////// LECTURA PULSADOR B3 /////////////////
     valB3 = digitalRead(boton_3);
        val_B3_nuevo = valB3;   
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void CtrlSALIDAS()
{
//////////////////////////////////////////////////
/// CONTROL LED_B1 configurado PullUP interno ///

if (val_B1_nuevo == LOW && val_B1_viejo== HIGH)
   {
    if (L1_estado==0)
       {
        L1_estado=1;
         for (a = 0; a < 50; a++)
        {       
        digitalWrite(LED_B1, HIGH);
        delay (800);
        lecturaPULSADOR();
        CtrlSALIDAS();
        digitalWrite(LED_B1, LOW);
        delay (800);
        lecturaPULSADOR();
        CtrlSALIDAS();
       }
       }
    else
       {
       digitalWrite(LED_B1, LOW);
       L1_estado=0;   
       }
   }
   val_B1_viejo = val_B1_nuevo;
//////////////////////////////////////////////////
///CONTROL LED_B2 configurado PullDOWN externo///

if (val_B2_nuevo == HIGH && val_B2_viejo== LOW)
   {
    if (L2_estado==0)
       {
        L2_estado=1;
        digitalWrite(LED_B2, HIGH);
        }
    else
       {
       digitalWrite(LED_B2, LOW);
       L2_estado=0;   
       }
   }
   val_B2_viejo = val_B2_nuevo;
//////////////////////////////////////////////////
/// CONTROL LED_B3 configurado PullUP externo ///

if (val_B3_nuevo == LOW && val_B3_viejo== HIGH)
   {
    if (L3_estado==0)
       {
        digitalWrite(LED_B3, HIGH);
        L3_estado=1;
       }
    else
       {
       digitalWrite(LED_B3, LOW);
       L3_estado=0;   
       }
   }
   val_B3_viejo = val_B3_nuevo;
 }
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Las rutinas de las interrupciones se llaman ISR.
void enciende() // Cuando hay interrupción 0 (terminal 2), actúa esta rutina.
{
  for (int i = 0; i < 50; i++)
        {
        digitalWrite(LED_INT, HIGH);
        }
}

void apaga()  // Cuando hay interrupción 1 (terminal 3), actúa esta rutina.
{
   digitalWrite(LED_INT, LOW);
   a=48;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////