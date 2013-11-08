; -----------------------------------------------------------------------
; SAC 2.0 Project
; Jorge Gómez <syvic@sindormir.net> 2010
; -----------------------------------------------------------------------


; Si he estado alguna vez levantado, al cambiar el estado que solo ponga los motores en marcha cuando haya detectado línea en algún lugar


#include <p16f648a.inc>
	__CONFIG _WDT_OFF & _PWRTE_OFF & _INTOSC_OSC_NOCLKOUT & _MCLRE_OFF & _BODEN_OFF & _LVP_OFF & _DATA_CP_OFF & _CP_OFF

	list    p=16F648A

#define		SensorSD	PORTA,0
#define		SensorPD	PORTA,1
#define		SensorPI	PORTA,2
#define		SensorSI	PORTA,3
#define		TakeExit	PORTA,4
#define		MCLR_Pin	PORTA,5
#define		Speed_LSB	PORTA,6
#define		Speed_MSB	PORTA,7
#define		Interrupt	PORTB,0
#define		Motor_left	PORTB,1
#define		Motor_right	PORTB,2
#define		Motor_fw	PORTB,3
#define		Motor_bw	PORTB,4
#define		OffRoadSignLSB	PORTB,5
#define		OffRoadSignMSB	PORTB,6
#define		TakeExitLed	PORTB,7

;INT_VAR UDATA_SHR
w_saved		equ	0x20
status_saved	equ	0x21
pclath_saved	equ	0x22

reg_speed	equ	0x30
reg_ts		equ	0x31
reg_sensors	equ	0x32
reg_last_seen	equ	0x33	; reg_last_seen,0 => 1 == right, 0 == left
reg_offroad	equ	0x34

; -----------------------------------------------------------------------
; reiniciar vector
 ORG 0x000
	goto	setup

; vector de interrupciones
 ORG 0x004
	goto	ISR
 
 ORG 0x010
ISR
	movwf	w_saved		; save context
	swapf	STATUS,w
	movwf	status_saved
	clrf	STATUS

	clrf	reg_speed	; read speed pins and save PWM duty cycle
	clrw			
	btfsc	Speed_LSB
	addlw	d'64'
	btfsc	Speed_MSB
	addlw	d'128'
	movwf	reg_speed

	;nuevo metodo de calcular vel
	;movlw	0xC0		; Leemos Speed_MSB Y Speed_LSB
	;andwf	PORTB,W
	;movwf	reg_speed
	;btfss	STATUS,Z
	;movlw	0x20		; Añadimos 64 si era más de 0
	;movf	reg_speed,F
	;btfss	STATUS,Z
	;addwf	reg_speed

	bcf	reg_ts,0	; read take exit pin
	btfsc	TakeExit
	bsf	reg_ts,0
	
	swapf	status_saved,w	; recover context
	movwf	STATUS
	swapf	w_saved,f
	swapf	w_saved,w

	bcf	INTCON,INTF
	retfie

 ORG 0x030

setup
	movlw	0X07 		; turns off comparers and enable pins
	movwf	CMCON 		; for I/O
	
	bsf	INTCON,INTE	; Interruputs
	bsf	INTCON,GIE

	banksel	PCON		; Banco 1
	
	movlw	b'00001011'	; speed clock setting
	movwf	PCON
	
	movlw	b'11111111'	; Porta configuration
	movwf	TRISA
	movlw	b'00000001'	; Portb configuration
	movwf	TRISB

	movlw	0xF9		; Timer2 period register
	movwf	PR2

	banksel	CCPR1L		; Banco 0

	movlw	0x00		; pwm off
	movwf	CCPR1L

	movlw	b'00001100'	; Enable PWM mode
	movwf	CCP1CON

	movlw	b'00000100'	; Switch on timer2 with no pre/post scaler
	movwf	T2CON
	
	clrf	PORTB 		; clear ports
	clrf	PORTA
	
	; Clear registers
	clrf	reg_speed
	clrf	reg_ts
	clrf	reg_sensors
	clrf	reg_last_seen
	clrf	reg_offroad

	goto	pre_init

pre_init
	call	stop_motors
	movlw	b'00001111'	; Sensor reading 
	andwf	PORTA,W
	movwf	reg_sensors
	btfsc	STATUS,Z	; Is sensor read 0000 ?
	goto	not_initialized
	
	movlw	b'00001111'	; 1111 ?
	subwf	reg_sensors,W
	btfsc	STATUS,Z
	goto	not_initialized
	goto	post_init

not_initialized
	bsf	reg_offroad,0
	bsf	OffRoadSignLSB
	bsf	OffRoadSignMSB
	goto	pre_init

post_init
	bcf	reg_offroad,0
	bcf	OffRoadSignLSB
	bcf	OffRoadSignMSB	
	movf	reg_speed,F
	btfsc	STATUS,Z	; Estas dos lineas quizá está mejor comentadas
	goto	pre_init	;

	goto 	main

main
	call	motor_forward	; start motors

	movlw	b'00001111'	; Sensor reading
	andwf	PORTA,W
	movwf	reg_sensors

	btfss	reg_offroad,0	; Are we in off road state?
	goto	eval_sensors

	movf	reg_sensors,W	; Still reading 0000?
	btfsc	STATUS,Z
	goto	not_initialized

	sublw	b'00001111'	; Still reading 1111?
	btfss	STATUS,C
	goto	main	

	bsf	reg_offroad,0
	bcf	OffRoadSignLSB
	bcf	OffRoadSignMSB	
	
	bcf	TakeExitLed
	btfsc	reg_ts,0
	bsf	TakeExitLed

	goto	eval_sensors

eval_sensors ;Adaptado sensores
	movlw	0x0F
	andwf	reg_sensors,W
	addwf   PCL,F				; Checked No TS	; Checked TS		; Notas
	goto	case5		; 0000	V			
	goto	case8		; 0001	V	ok		
	goto	case2		; 0010	V			
	goto	case2		; 0011	V			
	goto	case3		; 0100	V			
	goto	case1b		; 0101	V	ok		
	goto	case7		; 0110	V	ok		
	goto	case2		; 0111	V	ok		
	goto	case6		; 1000	V	ok		
	goto	case0		; 1001	V	ok		
	goto	case1a		; 1010	V	ok					?Seguro que last_seen a la derecha?
	goto	case1b		; 1011	V	ok		
	goto	case3		; 1100	V	ok		
	goto	case1a		; 1101	V	ok
	goto	case3		; 1110	V	ok		
	goto	case4		; 1111	V			


case0	; Don't turn, don't alter last seen
	call	go_stright
	goto	main

case1a	; Don't turn, last seen on right
	call	go_stright
	bsf	reg_last_seen,0
	goto	main

case1b	; Don't turn, last seen on left
	call	go_stright
	bcf	reg_last_seen,0
	goto	main

case2	; Turn left, last seen on left
	call	turn_left
	bcf	reg_last_seen,0
	goto	main

case3	; Turn right, last seen on right
	call	turn_right
	bsf	reg_last_seen,0
	goto	main

case4	; Road lost
	btfsc	reg_last_seen,0
	call	turn_right
	btfss	reg_last_seen,0
	call	turn_left
	
	bsf	reg_offroad,0
	bsf	OffRoadSignLSB
	bcf	OffRoadSignMSB
	goto	main

case5	; Game over
	call	go_stright
	call	stop_motors

	goto	not_initialized

case6	; Exit on the right [1000]
	btfsc	reg_ts,0
	call	turn_right
	goto	main

case7	; [0110]
	btfsc	reg_ts,0
	call	turn_right
	btfss	reg_ts,0
	call	turn_left
	goto	main

case8	; Exit on the left [0001]
	btfss	reg_ts,0
	call	turn_left
	goto	main

; -----------------------------------------------------------------------
; movement routines

motor_forward
	movf	reg_speed,W
	movwf	CCPR1L
	return

stop_motors
	clrf	CCPR1L
	bcf	Motor_fw
	bcf	Motor_bw
	bcf	Motor_left
	bcf	Motor_right
	return

go_stright
	bcf	Motor_right
	bcf	Motor_left
	return

turn_left
	bcf	Motor_right
	bsf	Motor_left
	return

turn_right
	bcf	Motor_left
	bsf	Motor_right
	return

	END
