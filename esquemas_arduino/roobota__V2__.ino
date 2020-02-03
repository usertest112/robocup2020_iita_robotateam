/////////programa de seguidor con luz reflejada//////////

//librerias/////////////////////////////////////////////


#include <Wire.h>
#include <EVShield.h>
#include <EVShieldAGS.h>
#include <EVs_EV3Color.h>

EVShield     evshield(0x34,0x36); //  Create shield object
EVs_EV3Color sensorDerecha;
EVs_EV3Color sensorIzquierda;
EVs_EV3Color COLORIZQ;
EVs_EV3Color COLORDER;


////////////////////////////////////////////////

//iniciando los sensores////////////////////////
void setup()
{

    Serial.begin(115200);       // start serial for output

    evshield.init( SH_HardwareI2C );

    sensorDerecha.init( &evshield, SH_BBS1 );
    sensorIzquierda.init( &evshield, SH_BAS1 );

    COLORIZQ.init( &evshield, SH_BBS2 );
    COLORDER.init( &evshield, SH_BAS2 );

    
    sensorDerecha.setMode(MODE_Color_ReflectedLight);
    sensorIzquierda.setMode(MODE_Color_ReflectedLight);

    COLORDER.setMode(MODE_Color_MeasureColor);
    COLORIZQ.setMode(MODE_Color_MeasureColor);

    
    evshield.bank_a.motorReset();
    evshield.bank_b.motorReset();
    
    
    Serial.println("setup terminado");
}
    
///////////////////////////////////////////////

//LOOP//////////////////////////////////////////
void loop(){

//DECLARO LA VARIABLE DONDE SE ALMACENA EL VALOR QUE NOS DA EL SENSOR///////////////////

    int verdeDerecha;
    int verdeIzquierda;
    verdeDerecha = COLORDER.getVal();
    verdeIzquierda = COLORIZQ.getVal();
    int LUZ_DERECHA;
    int LUZ_IZQUIERDA;
    LUZ_DERECHA = sensorDerecha.getVal();
    LUZ_IZQUIERDA = sensorIzquierda.getVal();
    delay(100);

/////////////////////INICIA AVANZANDO///////////////////////////////////////////////////////////////
     evshield.bank_a.motorRunUnlimited(SH_Motor_Both,
                         SH_Direction_Forward, 
                         50);
 
 
 //// DOBLE NEGRO //////////////////////////////////////////////////////////////////////////
  if ( LUZ_DERECHA < 15 && LUZ_IZQUIERDA < 15){
      evshield.bank_a.motorRunRotations(SH_Motor_Both, 
                     SH_Direction_Forward, 
                     SH_Speed_Medium,
                     1, 
                     SH_Completion_Wait_For,
                     SH_Next_Action_BrakeHold);
    }


 /////////////////GIRO IZQUIERDA////////////////////////
  if(LUZ_IZQUIERDA < 15){
  

   evshield.bank_a.motorRunUnlimited(SH_Motor_1, 
                     SH_Direction_Reverse, 
                     50);
       evshield.bank_a.motorRunUnlimited(SH_Motor_2, 
                     SH_Direction_Forward, 
                     50);              
  }
  
//////////////////GIRO DERECHA//////////////////////

  if(LUZ_DERECHA < 15){
  
     evshield.bank_a.motorRunUnlimited(SH_Motor_2, 
                       SH_Direction_Reverse, 
                       50);
     evshield.bank_a.motorRunUnlimited(SH_Motor_1, 
                       SH_Direction_Forward , 
                       50);                  
    }

//////////////////////////////////////////////////////
///////////////VERDES////////////////////////////////
//////////////////////////////////////////////////////


///////////////DOBLE VERDE///////////////////////////////////////
  if (verdeDerecha == 3 && verdeIzquierda == 3){
     evshield.bank_a.motorRunRotations(SH_Motor_1,    //GIRA UN POCO PARA SALIR DE CUALQUIER RUIDO
                     SH_Direction_Forward, 
                     SH_Speed_Medium,
                     1.50, 
                     SH_Completion_Wait_For,
                     SH_Next_Action_BrakeHold);
      while(true){
        evshield.bank_a.motorRunUnlimited(SH_Motor_2, 
                     SH_Direction_Reverse, 
                     50);

        if (verdeIzquierda == 1){
           break;
         }//sensor
      }//while true    
    }//primer if







/////////////////DOBLAR DERECHA////////////////////////////////////////
    
  if (verdeDerecha == 3){
    evshield.bank_a.motorRunRotations(SH_Motor_Both,    
                       SH_Direction_Forward, 
                       SH_Speed_Medium,
                       1.50, 
                       SH_Completion_Wait_For,
                       SH_Next_Action_BrakeHold);
  
    
  
    evshield.bank_a.motorRunRotations(SH_Motor_2,    
                         SH_Direction_Forward, 
                         SH_Speed_Medium,
                         1, 
                         SH_Completion_Wait_For,
                         SH_Next_Action_BrakeHold);
      
       while(true){
        evshield.bank_a.motorRunUnlimited(SH_Motor_1, 
                     SH_Direction_Reverse, 
                     50);

          if (verdeIzquierda == 1){
             break;
           }//sensor
      }//while true 

  
////////////////////DOBLAR IZQUIERDA////////////////////////////////////////////////////
    
  if (verdeIzquierda == 3){
    evshield.bank_a.motorRunRotations(SH_Motor_Both,    
                       SH_Direction_Forward, 
                       SH_Speed_Medium,
                       1.50, 
                       SH_Completion_Wait_For,
                       SH_Next_Action_BrakeHold);
  
    
  
    evshield.bank_a.motorRunRotations(SH_Motor_1,    
                         SH_Direction_Forward, 
                         SH_Speed_Medium,
                         1, 
                         SH_Completion_Wait_For,
                         SH_Next_Action_BrakeHold);
      
       while(true){
        evshield.bank_a.motorRunUnlimited(SH_Motor_2, 
                     SH_Direction_Reverse, 
                     50);

          if (verdeDerecha == 1){
             break;
           }//sensor
      }}}}//while true 

  
  
  
  
  
  
  
