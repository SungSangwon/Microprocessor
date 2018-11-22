.include "m128def.inc"
	.ORG 0
      LDI R16,HIGH(RAMEND)
      OUT SPH,R16
      LDI R16,LOW(RAMEND)
      OUT SPL,R16
						//Stack �ʱ�ȭ

	  LDI R16,0xff
	  OUT DDRA,R16
	  LDI R16,0x00
						//A�� ������� ���
 
LDI R16,0x80			//R16 Shift���Ѽ� R17�Ǻ����� �ֱ����� ��������
MOV R17,R16				// R17 ���

main : 
	   SBIC PINE,4
       RJMP main		//switch�� ������ ���α׷��� ����

      LDI R20,0x11		//R20 --> �Է�
     
      CBI PORTC,0
      CBI PORTB,0
      CBI PORTD,0		//PORTC,B,D�� ���� Converter�κ��� �޾ƾ� �ϹǷ� RJMP�ڿ� �ʱ�ȭ ���ֱ� ���� main�� �ȿ� �־��־���.

      CALL Converter	//R20�� R17�� ��Ҹ� ���Ͽ� ��� ���� ��� ��ȭ�ؾ� ���� �������ִ� �Լ�

      SBIC PORTD,0		// PORTD.0�� 1�̸� ��� ���� ���� �� ��, �Է�=���
      RJMP LED_OUT
      SBIC PORTB,0		//����� �Էº��� ����
      RJMP L1
      SBIC PORTC,0		//����� �Էº��� ŭ
      RJMP L2
   
   L1: LSR R16
      OR R17,R16		//R16 �� LSR �� �� R17�� OR�����ν�, �Է� ���� ���������� �ٿ����� �Է��� ã�ư���.
      RJMP main
   
   L2: EOR R17,R16		//����� �Էº��� ũ�� �������Ƿ� ��� ���� R16�� XOR�������ν� ���� ������ �ǵ����ش�.
      LSR R16
      OR R17,R16		//���� LSR�ѹ� ������ R16�� OR�������ν� �Է� ���� ���������� �ٿ����� �Է��� ã�´�.
      RJMP main

   LED_OUT: OUT PORTA, R17
          RJMP LED_OUT

Converter:   
	     SUB R20,R17
		 BRCC C1	//R20 >= R17
         BRCS C2		//R20 < R17

      C1: BREQ C3		//R20=R17
         SBI PORTB,0	//R20>R17 �̸� PORTB.0 �� 1�� ����� ��
         RET
      C2: SBI PORTC,0   //R20<R17 �̸� PORTC.0�� 1�� ����� ��
         RET 
      C3: SBI PORTD,0   //R20=R17 �̸� PORTD.0�� 1�� ����� ��
         RET