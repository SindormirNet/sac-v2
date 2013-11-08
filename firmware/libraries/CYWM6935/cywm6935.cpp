#include "cywm6935.h"

CYWM6935::CYWM6935() {
  IRQ_CNT = 0;
  IRQ = LOW;
  clear_rx_buf();
  clear_tx_buf();
}

CYWM6935::~CYWM6935() {

}

void CYWM6935::clear_rx_buf() {
  for (int i=0; i<sizeof(rxbuf); i++) rxbuf[i] = 0;
}

void CYWM6935::clear_tx_buf() {
  for (int i=0; i<sizeof(txbuf); i++) txbuf[i] = 0;
}

void CYWM6935::cy_isr_handler() {
  IRQ = HIGH;
  IRQ_CNT++;
}

void CYWM6935::config() {
  pinMode(ACT_LED,       OUTPUT);
  pinMode(CY_nRST,       OUTPUT);
  pinMode(CY_nPD,        OUTPUT);
  pinMode(CY_IRQ,        INPUT);
}

byte CYWM6935::tx() {
  byte i;
  byte tx_locked;

  do {
    IRQ_CNT=0;
    tx_locked=0;

    digitalWrite(ACT_LED, HIGH);

    status[0] = spi.read(REG_TX_INT_STAT);            // Clear transmit status
    spi.write(REG_TX_INT_EN, 0x01);                   // Enable empty flag on IRQ pin
    spi.write(REG_CONTROL, 0x50);                     // Enable tx
    delayMicroseconds(350);
    for(i=0;i<sizeof(txbuf);i++) {
      uwait_irq(1000);
      spi.write(REG_TX_DATA, txbuf[i]);               // Send data
    }
    spi.write(REG_TX_INT_EN, 0x02);                   // Enable done flag on IRQ pin
    uwait_irq(1000);                                  // uwait 'til REG_TX_DATA done

    spi.write(REG_CONTROL, 0x00);                     // Return to idle
    status[0] = spi.read(REG_TX_INT_STAT);            // Clear transmit status

    if (IRQ_CNT >= 7 || IRQ_CNT <= 4) {               // TX lockout detected. Resetting module
      Serial.print(IRQ_CNT);
      Serial.println("[xTXE]");
      td_Init();
      tx_locked=1;
    }
    digitalWrite(ACT_LED, LOW);
  } while (tx_locked);
  

  return status[0];

}

int CYWM6935::rx(int timeout) {
  int len=0;
  volatile unsigned long int timer;

  IRQ_CNT=0;

  digitalWrite(ACT_LED, HIGH);
  status[4] = spi.read(REG_RX_VALID_A);               // Clear rxvalids
  status[2] = spi.read(REG_RX_INT_STAT);              // Clear receive status
  status[3] = spi.read(REG_RX_DATA_A);                // Clear rxbuf

  spi.write(REG_RX_INT_EN, 0x03);                     // Enable EOFA and FULLA flags on IRQ pin
  spi.write(REG_CONTROL, 0x90);                       // Enable rx
  delayMicroseconds(235);

  timer=millis();
  while(1) {
    wait_irq(100);    // Wait 'til either EOFA or FULLA receive flag fires. SYV (Era 100) en versiones anteriores //ANTES DE GIT
    //uwait_irq(10000);

    status[2] = spi.read(REG_RX_INT_STAT);            // REG_RX_INT_STAT - check receive status
    if(status[2]&0x01)  {
      // Store REG_RX_DATA_A and REG_RX_VALID_A in user's rxbuf
      spi.fileRead(REG_RX_DATA_A, 2, &rxbuf[len]);
      if(rxbuf[len+1] > 3) len += 2;
    }
    if(status[2]&0x02 && len) break;
    if(len >= sizeof(rxbuf)) {
      len = sizeof(rxbuf);
      break;
    }      
    if ((timeout != 0) && (millis()-timer > timeout)){ 
      len=-1;
      break;
    }
  }
  spi.write(REG_CONTROL, 0x00);                       // REG_CONTROL - return to idle
  if (IRQ_CNT==0) td_Init(); 

  digitalWrite(ACT_LED, LOW);   


  return len;  
}


void CYWM6935::reset() {
  digitalWrite      (CY_nRST, LOW);  
  digitalWrite      (CY_nPD,  LOW);  
  spi.setClock      (LOW);  
  spi.setSlave      (HIGH);
  delayMicroseconds (1300);
  digitalWrite      (CY_nPD,  HIGH);
  delayMicroseconds (2000);
  digitalWrite      (CY_nRST, HIGH);
  delayMicroseconds (5);
  digitalWrite      (CY_nPD,  HIGH);
  delayMicroseconds (2100);
}

void CYWM6935::init(void) {
  delay(100);//new
//new  spi.unsafeWrite   (REG_ANALOG_CTL,   0x05);         // Parece que es indiferente 0x45 que 0x41
//new  delayMicroseconds (250);
  spi.write         (REG_CLOCK_MANUAL, 0x41);
  delayMicroseconds (250);
  spi.write         (REG_CLOCK_ENABLE, 0x41);
  delayMicroseconds (250);
  spi.write         (REG_ANALOG_CTL,   0x04);         // Parece que es indiferente 0x44 que 0x40   
  delayMicroseconds (250);
  spi.unsafeWrite   (REG_VCO_CAL,      0xC0);
  delayMicroseconds (250);
  spi.write         (REG_SERDES_CTL,   0x0B);
  delayMicroseconds (250);
  spi.unsafeWrite   (REG_TX_VALID,     0xFF);
  delayMicroseconds (250);
  spi.write         (REG_CONFIG,       0x01);
  delayMicroseconds (250);

  spi.write         (REG_THRESHOLD_L,  0x0C);        // NUEVO Era por defecto (0x08)
  delayMicroseconds (250);   
  spi.write         (REG_THRESHOLD_H,  0x34);        // NUEVO Era por defecto (0x38)
  delayMicroseconds (250);   

  spi.write         (REG_SYN_LOCK_CNT, 0x7D);
  delayMicroseconds (250);
  spi.write         (REG_CRYSTAL_ADJ,  0x40);
  delayMicroseconds (250);
  setPnCode();
  delayMicroseconds (250);
  spi.write         (REG_PA,           0x07);       // NUEVO Era PA=5
  delayMicroseconds (250);
  spi.write         (REG_CHANNEL,      0x09);
}

void CYWM6935::setPnCode() {
  spi.write         (REG_PN_CODE_1,    0x3F);
  delayMicroseconds (250);  
  spi.write         (REG_PN_CODE_2,    0x2C);
  delayMicroseconds (250);  
  spi.write         (REG_PN_CODE_3,    0x4E);
  delayMicroseconds (250);  
  spi.write         (REG_PN_CODE_4,    0xAA);
  delayMicroseconds (250);  
  spi.write         (REG_PN_CODE_5,    0x71);
  delayMicroseconds (250);  
  spi.write         (REG_PN_CODE_6,    0x48);
  delayMicroseconds (250);  
  spi.write         (REG_PN_CODE_7,    0x7A);
  delayMicroseconds (250);  
  spi.write         (REG_PN_CODE_8,    0xC9);
}

void CYWM6935::sleep(void) {
  spi.write         (REG_CONTROL,      0x00);       // Idle mode
  digitalWrite      (CY_nPD,  LOW);                 // Sleep
  delayMicroseconds (100);
}

void CYWM6935::wake(void) {
  digitalWrite      (CY_nPD,HIGH);                 // Idle mode
  delayMicroseconds (3000);                        // ~Xmsec for crystal start to stable - idle
}

byte CYWM6935::getRssi(void) {
  spi.unsafeWrite   (REG_CARRIER_DETECT, 0x80);    // Force radio to manually acquire rssi reading
  spi.write         (REG_CONTROL, 0x90);           // Put radio in receive mode - triggers rssi adc
  delayMicroseconds (285);
  status[5] = spi.read(REG_RSSI);                  // Flush stale rssi reading
  delayMicroseconds (50);                          // Wait for 5-bit rssi adc to complete
  status[5] = spi.read(REG_RSSI);                  // Get rssi reading
  spi.unsafeWrite   (REG_CARRIER_DETECT, 0x00);    // Manually clear CDET
  spi.write         (REG_CONTROL, 0x00);           // Put radio in idle mode

  return status[5];
}

void CYWM6935::wait4board() {
  while (spi.read(REG_ID)!=0x07) {}
}

void CYWM6935::td_Init(void) {
  reset();
  init();
  setPnCode();
  delay(2);
}

void CYWM6935::wireless_start() {
  spi.init();
  //syv reset();
  td_Init();
  //spi.write(REG_WAKE_EN, 0x00);
  wait4board();
}


int CYWM6935::uwait_irq(int timeout) {
  unsigned long int timer;
  int irq_timeout=0;

  timer=micros();

  while (!digitalRead(CY_IRQ)) {
    if (micros() - timer >= timeout) {
      irq_timeout=1;
      break;
    }   
  }
  IRQ=LOW;
  return irq_timeout;
}

int CYWM6935::wait_irq(int timeout) {
  unsigned long int timer;
  int irq_timeout=0;

  timer=millis();

  while (!digitalRead(CY_IRQ)) {
    if (millis() - timer >= timeout) {
      irq_timeout=1;
      break;
    }   
  }
  IRQ=LOW;
  return irq_timeout;
}

void CYWM6935::setled(boolean status) {
    digitalWrite(ACT_LED, status);
}

