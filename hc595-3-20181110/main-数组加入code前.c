#include <REGX51.H>
#include <INTRINS.H>
// ��ɨ��
sbit shcp_h=P2^2;
sbit ds_h=P2^1;
sbit shcp=P2^0;
// ��ɨ��
sbit shcp_l=P2^3;
sbit ds_l=P2^4;

code int tab[96] = {
/*--  Fixedsys12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x10,0x20,0x10,0x20,0x11,0xFC,0x10,0x20,0xFC,0x20,0x24,0x20,0x27,0xFE,0x24,0x00,
0x24,0x20,0x48,0x20,0x29,0xFC,0x10,0x20,0x28,0x20,0x44,0x20,0x83,0xFE,0x00,0x00,
/*--  ����:  ��  --*/
/*--  Fixedsys12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x00,0x40,0x00,0x40,0x78,0xA0,0x49,0x10,0x4A,0x08,0x4C,0x06,0x4B,0xF8,0x48,0x00,
0x48,0x00,0x4B,0xF8,0x7A,0x08,0x4A,0x08,0x02,0x08,0x02,0x08,0x03,0xF8,0x02,0x08,

/*--  ����:  ��  --*/
/*--  Fixedsys12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x00,0x40,0x00,0x40,0x78,0xA0,0x49,0x10,0x4A,0x08,0x4C,0x06,0x4B,0xF8,0x48,0x00,
0x48,0x00,0x4B,0xF8,0x7A,0x08,0x4A,0x08,0x02,0x08,0x02,0x08,0x03,0xF8,0x02,0x08
};

/**
**********************************************
***���������ƶ�һλ������*�����飬���鳤�ȣ�**
**********************************************
**********************************************
*/
void move_left(int *arr, int size) {
	int first = arr[0];
	int i, nextHiBit;
	for (i = 0; i < size; i++){
			int next;
		// �Ѻ�����������λ��λ�������ݵ����λ�����λû�����ݣ���Ҫ���⴦��
		if (i < (size - 1)) {
			next = arr[i + 1];
		} else {
			next = first;
		}
		nextHiBit = (next & 0x80) >> 7;
		// ��������һλ
		arr[i] = arr[i] << 1;
		// �������Ƶ���һλ
		arr[i] = arr[i] | nextHiBit;
		// ֻȡ��λ
		arr[i] = arr[i] & 0xff;
	}
}

// ��ɨ�躯��
void sendbyte_h(int index){
	int i;
	for(i = 0; i < 16; i++) {
		shcp_h = 0;
		if ((16 - index) == i)
		{
			ds_h = 0;
		} else {
			ds_h = 1;
		}
		shcp_h = 1;
	}
	
}

// ��ɨ�躯��
//void sendbyte_l(char a, char b){
void sendbyte_l(int *tab, int i){
	// ��һ��led����
	int a = tab[2 * i];
	// �ڶ���led����
	int b = tab[2 * i + 1];
	// ������led����
	int c = tab[2 * (16 + i)];
	int j;
	// ȡ������
//	a = ~a;
//	b = ~b;
//	c = ~c;
	for(j = 0; j < 8; j++) {
		shcp_l = 0;
		ds_l = c & 0x01;
		c = c >> 1;
		shcp_l = 1;
	}
	for(j = 0; j < 8; j++) {
		shcp_l = 0;
		ds_l = b & 0x01;
		b = b >> 1;
		shcp_l = 1;
	}
	for(j = 0; j < 8; j++) {
		shcp_l = 0;
		ds_l = a & 0x01;
		a = a >> 1;
		shcp_l = 1;
	}
	

}
void show(){
	shcp = 0;
	_nop_();
	shcp = 1;
}

void main() {
	int i, j;
	int f = 500;
	int size = sizeof(tab) / sizeof(tab[0]); 
	int display_arr[3];
	while(1){
		for (j = 0;j < size; j++ )
		{

	//		int k = 9000;
			// ��ѭ����һ֡��ʾ����
			for(i = 0; i < 16; i++) {
				sendbyte_l(tab, i);
				sendbyte_h(i + 1);
				show();
	//			while(f--);
			}
	//		while(k--);
			move_left(tab, size);
	//			sendbyte_h(0x36,0x45);
	//			sendbyte_l(1);
	//			show();
	//			while(f--);
		}
	}
}
	
