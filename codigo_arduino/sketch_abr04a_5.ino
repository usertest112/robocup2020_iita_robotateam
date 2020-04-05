/////////programa de seguidor con luz reflejada//////////

//librerias/////////////////////////////////////////////


#include <Wire.h>
#include <EVShield.h>
#include <EVShieldAGS.h>
#include <EVs_EV3Color.h>

EVShield     evshield(0x34,0x36); //  Create shield object
EVs_EV3Color sensorDerecha;
EVs_EV3Color sensorIzquierda;
/*EVs_EV3Color COLORIZQ;//
EVs_EV3Color COLORDER;//*/


////////////////////////////////////////////////

//iniciando los sensores////////////////////////
void setup()
{

    Serial.begin(9600);       // start serial for output

    evshield.init( SH_HardwareI2C );


    // COLORIZQ.init( &evshield, SH_BBS1 );
    //COLORDER.init( &evshield, SH_BAS1 );
     sensorIzquierda.init( &evshield, SH_BBS1 );
     sensorDerecha.init( &evshield, SH_BAS1 );
    
    sensorDerecha.setMode(MODE_Color_ReflectedLight);
    sensorIzquierda.setMode(MODE_Color_ReflectedLight);

    //COLORDER.setMode(MODE_Color_MeasureColor);
    //COLORIZQ.setMode(MODE_Color_MeasureColor);

    
    evshield.bank_a.motorReset();
    evshield.bank_b.motorReset();
    
    
    Serial.println("setup terminado");
}
    
///////////////////////////////////////////////
    int LUZ_DERECHA;
    int LUZ_IZQUIERDA;
    int verdeDerecha;
    int verdeIzquierda;
//LOOP//////////////////////////////////////////
void loop(){

//DECLARO LA VARIABLE DONDE SE ALMACENA EL VALOR QUE NOS DA EL SENSOR///////////////////



    LUZ_DERECHA = sensorDerecha.getVal();
    LUZ_IZQUIERDA = sensorIzquierda.getVal();
    Serial.print("izquierda : ");
    Serial.print(LUZ_IZQUIERDA);
    Serial.print("      ");
    Serial.print("Derecha : ");
    Serial.print(LUZ_DERECHA);
    Serial.println("");
    
    

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


 /////////////////GIRO IZQUIERDA//////////////////////// ¿¿con un while no dejarian de andar los otros sensores??
  if( LUZ_IZQUIERDA < 35){
  

   evshield.bank_a.motorRunUnlimited(SH_Motor_1, //izquierdo
                     SH_Direction_Reverse, 
                     30);

    delay(15);}
   else{                  
    evshield.bank_a.motorRunUnlimited(SH_Motor_1, //izquierdo 
                   SH_Direction_Forward, 
                   10);              
  }
  
  
 //////////////////GIRO DERECHA//////////////////////

   if( LUZ_DERECHA < 35){
  

   evshield.bank_a.motorRunUnlimited(SH_Motor_2, //derecho
                     SH_Direction_Reverse, 
                     30);
                     
      delay(15);}
   

   else{                  
    evshield.bank_a.motorRunUnlimited(SH_Motor_2, //derecho
                   SH_Direction_Forward, 
                   10);              
  }
   }//CIERRO EL LOOP
/*
//////////////////////////////////////////////////////
///////////////VERDES////////////////////////////////
//////////////////////////////////////////////////////

 
  
///////////////VERDE DERECHA///////////////////////////////////////
  if(LUZ_DERECHA > 8 && LUZ_DERECHA < 16){  //posible verde en el sensor de la derecha
    if( verificarVerdeDerecha() == true ){
      doblar90Derecha();
      
    }//if de verificacion
    
  }//primer if
//////////////VERDE IZQUIERDA//////////////////////////////////////
  if(LUZ_IZQUIERDA > 8 && LUZ_IZQUIERDA < 16){  //posible verde en el sensor de la derecha
    if( verificarVerdeIzquierda() == true ){
      doblar90Izquierda();
      
    }//while true  
     
   }//primer if  

*/   



//FUNCIONES/////////////////////////////////////////////////////////////////////////////////////////////////////////

   int verificarVerdeDerecha(){
   sensorDerecha.setMode(MODE_Color_MeasureColor);
     verdeDerecha = sensorDerecha.getVal();
     sensorDerecha.setMode(MODE_Color_ReflectedLight);
     //verdeIzquierda = COLORIZQ.getVal();
      if(verdeDerecha == 3){
        return(true);
      }
      
      else{
        return(false);
      }
}//FIN DE FUNCION DERECHA



int verificarVerdeIzquierda(){
   sensorIzquierda.setMode(MODE_Color_MeasureColor);
       verdeIzquierda =  sensorIzquierda.getVal();
       sensorIzquierda.setMode(MODE_Color_ReflectedLight);
     //verdeIzquierda = COLORIZQ.getVal();
      if(verdeIzquierda == 3){
        return(true);
      }
      
      else{
        return(false);
      }
}//Fin de funcion izquierda*/

int doblar90Derecha(){
   evshield.bank_a.motorRunRotations(SH_Motor_Both,    //AVANZA
                     SH_Direction_Forward, 
                     SH_Speed_Medium,
                     1.50, 
                     SH_Completion_Wait_For,
                     SH_Next_Action_BrakeHold);
  

    evshield.bank_a.motorRunRotations(SH_Motor_1,    //UN MOTOR GIRA HACIA ADELANTE
                     SH_Direction_Forward, 
                     SH_Speed_Medium,
                     1.50, 
                     SH_Completion_Dont_Wait,       //SH_Completion_Dont_Wait  hace que se ejecute esta accion al mismo tiempo que la de abajo.
                     SH_Next_Action_BrakeHold);

   evshield.bank_a.motorRunRotations(SH_Motor_2,    //UN MOTOR GIRA HACIA ATRAS
                       SH_Direction_Reverse, 
                       SH_Speed_Medium,
                       1.50, 
                       SH_Completion_Wait_For,      
                       SH_Next_Action_BrakeHold);

     evshield.bank_a.motorRunRotations(SH_Motor_Both,    //UNA VEZ FINALIZADO EL GIRO EL ROBOT RETROCEDE UN POCO
                     SH_Direction_Reverse, 
                     SH_Speed_Medium,
                     1.50, 
                     SH_Completion_Wait_For,
                     SH_Next_Action_BrakeHold);
    
}// fin de funcion de giro hacia la derecha

///////////////////////////////////////////////////
int doblar90Izquierda(){
   evshield.bank_a.motorRunRotations(SH_Motor_Both,    //AVANZA
                     SH_Direction_Forward, 
                     SH_Speed_Medium,
                     1.50, 
                     SH_Completion_Wait_For,
                     SH_Next_Action_BrakeHold);
  

    evshield.bank_a.motorRunRotations(SH_Motor_2,    //UN MOTOR GIRA HACIA ADELANTE
                     SH_Direction_Forward, 
                     SH_Speed_Medium,
                     1.50, 
                     SH_Completion_Dont_Wait,       //SH_Completion_Dont_Wait  hace que se ejecute esta accion al mismo tiempo que la de abajo.
                     SH_Next_Action_BrakeHold);

   evshield.bank_a.motorRunRotations(SH_Motor_1,    //UN MOTOR GIRA HACIA ATRAS
                       SH_Direction_Reverse, 
                       SH_Speed_Medium,
                       1.50, 
                       SH_Completion_Wait_For,      
                       SH_Next_Action_BrakeHold);

     evshield.bank_a.motorRunRotations(SH_Motor_Both,    //UNA VEZ FINALIZADO EL GIRO EL ROBOT RETROCEDE UN POCO
                     SH_Direction_Reverse, 
                     SH_Speed_Medium,
                     1.50, 
                     SH_Completion_Wait_For,
                     SH_Next_Action_BrakeHold);
    
}// fin de funcion de giro hacia la izquierda.
