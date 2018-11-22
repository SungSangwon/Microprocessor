.include "m128def.inc"
	.ORG 0
      LDI R16,HIGH(RAMEND)
      OUT SPH,R16
      LDI R16,LOW(RAMEND)
      OUT SPL,R16
						//Stack 초기화

	  LDI R16,0xff
	  OUT DDRA,R16
	  LDI R16,0x00
						//A를 출력으로 사용
 
LDI R16,0x80			//R16 Shift시켜서 R17의변동을 주기위한 레지스터
MOV R17,R16				// R17 출력

main : 
	   SBIC PINE,4
       RJMP main		//switch를 누르면 프로그램이 동작

      LDI R20,0x11		//R20 --> 입력
     
      CBI PORTC,0
      CBI PORTB,0
      CBI PORTD,0		//PORTC,B,D의 값은 Converter로부터 받아야 하므로 RJMP뒤에 초기화 해주기 위해 main문 안에 넣어주었다.

      CALL Converter	//R20과 R17의 대소를 비교하여 출력 값을 어떻게 변화해야 할지 결정해주는 함수

      SBIC PORTD,0		// PORTD.0이 1이면 출력 값이 정해 짐 즉, 입력=출력
      RJMP LED_OUT
      SBIC PORTB,0		//출력이 입력보다 작음
      RJMP L1
      SBIC PORTC,0		//출력이 입력보다 큼
      RJMP L2
   
   L1: LSR R16
      OR R17,R16		//R16 을 LSR 한 뒤 R17과 OR함으로써, 입력 값의 추정범위를 줄여가며 입력을 찾아간다.
      RJMP main
   
   L2: EOR R17,R16		//출력이 입력보다 크게 나왔으므로 출력 값을 R16과 XOR해줌으로써 원래 값으로 되돌려준다.
      LSR R16
      OR R17,R16		//그후 LSR한번 실행한 R16과 OR해줌으로써 입력 값의 추정범위를 줄여가며 입력을 찾는다.
      RJMP main

   LED_OUT: OUT PORTA, R17
          RJMP LED_OUT

Converter:   
	     SUB R20,R17
		 BRCC C1	//R20 >= R17
         BRCS C2		//R20 < R17

      C1: BREQ C3		//R20=R17
         SBI PORTB,0	//R20>R17 이면 PORTB.0 을 1로 만들어 줌
         RET
      C2: SBI PORTC,0   //R20<R17 이면 PORTC.0을 1로 만들어 줌
         RET 
      C3: SBI PORTD,0   //R20=R17 이면 PORTD.0을 1로 만들어 줌
         RET