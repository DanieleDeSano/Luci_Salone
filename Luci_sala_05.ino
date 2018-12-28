

#define STATUS_HALF_OFF     1
#define STATUS_FULL_OFF     2
#define STATUS_HALF_ON      3
#define STATUS_FULL_ON      4
#define STATUS_HALF_A_OFF     5
#define STATUS_HALF_B_OFF     6
#define STATUS_HALF_A_ON      7
#define STATUS_HALF_B_ON      8

#define TOGGLE_NONE         1
#define TOGGLE_HALF         2
#define TOGGLE_ALL          3
#define TOGGLE_HALF_A       4
#define TOGGLE_HALF_B       5

#define BUTTON_TAVOLO_PIN       2
#define BUTTON_GOLA_PIN         3

#define LOAD_TAVOLO_1_PIN       4
#define LOAD_TAVOLO_2_PIN       5
#define LOAD_GOLA_1_PIN         6
#define LOAD_GOLA_2_PIN         7

int nStatusTavolo ;
int nStatusGola ;


void toggleTavolo(int nToggleSet)
{
    switch (nToggleSet) 
      {
        case TOGGLE_NONE :
            digitalWrite(LOAD_TAVOLO_1_PIN, LOW);
            digitalWrite(LOAD_TAVOLO_2_PIN, LOW);
            break;
            
        case TOGGLE_HALF :
            digitalWrite(LOAD_TAVOLO_1_PIN, HIGH);
            digitalWrite(LOAD_TAVOLO_2_PIN, LOW);
            break;

        case TOGGLE_ALL :
            digitalWrite(LOAD_TAVOLO_1_PIN, HIGH);
            digitalWrite(LOAD_TAVOLO_2_PIN, HIGH);
            break;

        default:
            break;
      }
}
 
void toggleGola(int nToggleSet)
{
    switch (nToggleSet) 
      {
        case TOGGLE_NONE :
            digitalWrite(LOAD_GOLA_1_PIN, LOW);
            digitalWrite(LOAD_GOLA_2_PIN, LOW);
            break;
            
        case TOGGLE_HALF_A :
            digitalWrite(LOAD_GOLA_1_PIN, HIGH);
            digitalWrite(LOAD_GOLA_2_PIN, LOW);
            break;

        case TOGGLE_HALF_B :
            digitalWrite(LOAD_GOLA_1_PIN, LOW);
            digitalWrite(LOAD_GOLA_2_PIN, HIGH);
            break;

        case TOGGLE_ALL :
            digitalWrite(LOAD_GOLA_1_PIN, HIGH);
            digitalWrite(LOAD_GOLA_2_PIN, HIGH);
            break;

        default:
            break;
      }
}

void setup() 
{
  nStatusTavolo = STATUS_HALF_OFF ;
  nStatusGola = STATUS_FULL_OFF ;
  
  pinMode(BUTTON_TAVOLO_PIN, INPUT_PULLUP);
  pinMode(LOAD_TAVOLO_1_PIN, OUTPUT);
  pinMode(LOAD_TAVOLO_2_PIN, OUTPUT);

  pinMode(BUTTON_GOLA_PIN, INPUT_PULLUP);
  pinMode(LOAD_GOLA_1_PIN, OUTPUT);
  pinMode(LOAD_GOLA_2_PIN, OUTPUT);
}

void loop() 
{
  int nPushTavoloTime = 0 ;
  bool bTriggerTavoloOff = false ;
  bool bTavoloJustEnteredLoop = true; 
  bool bTavoloJustExitedLoop = false; 

  int nPushGolaTime = 0 ;
  bool bTriggerGolaOff = false ;
  bool bGolaJustEnteredLoop = true; 
  bool bGolaJustExitedLoop = false; 
  
  // ======== TAVOLO
  
  while ( digitalRead(BUTTON_TAVOLO_PIN) == LOW )
  {
    if ((nPushTavoloTime > 100) && (bTavoloJustEnteredLoop == true))
    {
      bTavoloJustEnteredLoop = false ;
      
      switch (nStatusTavolo) 
      {
        case STATUS_HALF_OFF :
            nStatusTavolo = STATUS_HALF_ON ;  
            toggleTavolo(TOGGLE_HALF);
            break;
            
        case STATUS_FULL_OFF :
            nStatusTavolo = STATUS_FULL_ON ;  
            toggleTavolo(TOGGLE_ALL);
            break;

        case STATUS_HALF_ON :
            bTriggerTavoloOff = true ;
            break;

        case STATUS_FULL_ON :
            bTriggerTavoloOff = true ;
            break;
            
        default:
            break;
      } // end switch
      
      bTavoloJustExitedLoop = true ;
     } // end if

    if (nPushTavoloTime > 1000)
      {
        switch (nStatusTavolo) 
        {
          case STATUS_HALF_ON :
            nStatusTavolo = STATUS_FULL_ON ;   
            bTriggerTavoloOff = false;
            toggleTavolo(TOGGLE_ALL);
            nPushTavoloTime = 0;
            break;

          case STATUS_FULL_ON :
            nStatusTavolo = STATUS_HALF_ON ;   
            bTriggerTavoloOff = false;
            toggleTavolo(TOGGLE_HALF);
            nPushTavoloTime = 0;
            break;
        }
      }

      delay (10);
      nPushTavoloTime += 10 ;
    } // end while

    if (bTavoloJustExitedLoop == true)
    {
      bTavoloJustExitedLoop = false ;
      if (bTriggerTavoloOff)
      {
        bTriggerTavoloOff = false ;
        
        switch (nStatusTavolo)
        {
          case STATUS_HALF_ON :
            nStatusTavolo = STATUS_HALF_OFF ;  
            toggleTavolo(TOGGLE_NONE);
            break;
            
          case STATUS_FULL_ON :
            nStatusTavolo = STATUS_FULL_OFF ;  
            toggleTavolo(TOGGLE_NONE);
            break;
        }
      } 
    }
 
   // ======== END TAVOLO

  // ======== GOLA
  
  while ( digitalRead(BUTTON_GOLA_PIN) == LOW )
  {
    if ((nPushGolaTime > 100) && (bGolaJustEnteredLoop == true))
    {
      bGolaJustEnteredLoop = false ;
      
      switch (nStatusGola) 
      {
        case STATUS_HALF_A_OFF :
            nStatusGola = STATUS_HALF_A_ON ;  
            toggleGola(TOGGLE_HALF_A);
            break;
            
        case STATUS_HALF_B_OFF :
            nStatusGola = STATUS_HALF_B_ON ;  
            toggleGola(TOGGLE_HALF_B);
            break;
            
        case STATUS_FULL_OFF :
            nStatusGola = STATUS_FULL_ON ;  
            toggleGola(TOGGLE_ALL);
            break;

        case STATUS_HALF_A_ON :
            bTriggerGolaOff = true ;
            break;

        case STATUS_HALF_B_ON :
            bTriggerGolaOff = true ;
            break;

        case STATUS_FULL_ON :
            bTriggerGolaOff = true ;
            break;
            
        default:
            break;
      } // end switch
      
      bGolaJustExitedLoop = true ;
     } // end if

    if (nPushGolaTime > 1000)
      {
        switch (nStatusGola) 
        {
          case STATUS_HALF_A_ON :
            nStatusGola = STATUS_HALF_B_ON ;   
            bTriggerGolaOff = false;
            toggleGola(TOGGLE_HALF_B);
            nPushGolaTime = 0;
            break;

          case STATUS_HALF_B_ON :
            nStatusGola = STATUS_FULL_ON ;   
            bTriggerGolaOff = false;
            toggleGola(TOGGLE_ALL);
            nPushGolaTime = 0;
            break;

          case STATUS_FULL_ON :
            nStatusGola = STATUS_HALF_A_ON ;   
            bTriggerGolaOff = false;
            toggleGola(TOGGLE_HALF_A);
            nPushGolaTime = 0;
            break;
        }
      }

      delay (10);
      nPushGolaTime += 10 ;
    } // end while

    if (bGolaJustExitedLoop == true)
    {
      bGolaJustExitedLoop = false ;
      if (bTriggerGolaOff)
      {
        bTriggerGolaOff = false ;
        
        switch (nStatusGola)
        {
          case STATUS_HALF_A_ON :
            nStatusGola = STATUS_HALF_A_OFF ;  
            toggleGola(TOGGLE_NONE);
            break;
            
          case STATUS_HALF_B_ON :
            nStatusGola = STATUS_HALF_B_OFF ;  
            toggleGola(TOGGLE_NONE);
            break;
            
          case STATUS_FULL_ON :
            nStatusGola = STATUS_FULL_OFF ;  
            toggleGola(TOGGLE_NONE);
            break;
        }
      } 
    }
   // ======== END GOLA
}

