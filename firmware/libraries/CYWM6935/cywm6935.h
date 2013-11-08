#ifndef CYWM6935_H
#define CYWM6935_H

#include <cyspi.h>
#include "WProgram.h" //Access to basic arduino IO, functions and datatypes

/* CYWM6935 Register list */
#define REG_ID			0x00
#define REG_CONTROL		0x03
#define REG_DATA_RATE		0x04
#define REG_CONFIG		0x05
#define REG_SERDES_CTL		0x06
#define REG_RX_INT_EN		0x07
#define REG_RX_INT_STAT		0x08
#define REG_RX_DATA_A		0x09
#define REG_RX_VALID_A		0x0A
#define REG_RX_DATA_B		0x0B
#define REG_RX_VALID_B		0x0C
#define REG_TX_INT_EN		0x0D
#define REG_TX_INT_STAT 	0x0E
#define REG_TX_DATA		0x0F
#define REG_TX_VALID		0x10
#define REG_PN_CODE_1		0x11
#define REG_PN_CODE_2		0x12
#define REG_PN_CODE_3		0x13  
#define REG_PN_CODE_4		0x14
#define REG_PN_CODE_5		0x15
#define REG_PN_CODE_6		0x16
#define REG_PN_CODE_7		0x17
#define REG_PN_CODE_8		0x18
#define REG_THRESHOLD_L		0x19
#define REG_THRESHOLD_H		0x1A
#define REG_WAKE_EN		0x1C
#define REG_WAKE_STAT		0x1D
#define REG_ANALOG_CTL		0x20
#define REG_CHANNEL		0x21
#define REG_RSSI		0x22
#define REG_PA			0x23
#define REG_CRYSTAL_ADJ		0x24
#define REG_VCO_CAL		0x26
#define REG_PWR_CTL		0x2E
#define REG_CARRIER_DETECT	0x2F
#define REG_CLOCK_MANUAL	0x32
#define REG_CLOCK_ENABLE	0x33
#define REG_SYN_LOCK_CNT	0x38
#define REG_MID                 0x3C


class CYWM6935 {
public:
    CYWM6935(void);
    ~CYWM6935(void);

    void config();
   
    byte tx();
    int rx(int);

    void cy_isr_handler();
    void reset();
    void init(void);
    void setPnCode();
    void sleep(void);
    void wake(void);
    byte getRssi(void);
    void wait4board();
    void td_Init(void);
    void start();
    void clear_rx_buf();
    void clear_tx_buf();
    void wireless_start();

    int uwait_irq(int timeout);
    int wait_irq(int timeout);

    byte status[6];
    byte rxbuf[8];
    byte txbuf[4];

    void setled(boolean);


private:
    volatile boolean IRQ;
    volatile int IRQ_CNT;

    static const uint8_t CY_IRQ  = 2;
    static const uint8_t ACT_LED = 4;
    static const uint8_t CY_nPD  = 8;
    static const uint8_t CY_nRST = 9;
};

extern CYWM6935 cywm6935;

#endif

