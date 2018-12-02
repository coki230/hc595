#include <REGX51.H>
#include <INTRINS.H>
// ��ɨ��
sbit shcp_h=P2^2;
sbit ds_h=P2^1;
sbit shcp=P2^0;
// ��ɨ��
sbit shcp_l=P2^3;
sbit ds_l=P2^4;

code int tab[64] = {
/*--  Fixedsys12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x10,0x20,0x10,0x20,0x11,0xFC,0x10,0x20,0xFC,0x20,0x24,0x20,0x27,0xFE,0x24,0x00,
0x24,0x20,0x48,0x20,0x29,0xFC,0x10,0x20,0x28,0x20,0x44,0x20,0x83,0xFE,0x00,0x00,
/*--  ����:  ��  --*/
/*--  Fixedsys12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x00,0x40,0x00,0x40,0x78,0xA0,0x49,0x10,0x4A,0x08,0x4C,0x06,0x4B,0xF8,0x48,0x00,
0x48,0x00,0x4B,0xF8,0x7A,0x08,0x4A,0x08,0x02,0x08,0x02,0x08,0x03,0xF8,0x02,0x08,
};

int get_next(int col, int row, int *arr, int num_of_display) {
	int nextHiBit;
	int cur, next;
	
	if(num_of_display == 0){
		cur = arr[2 * col];
	} else if(num_of_display == 1){
		cur = arr[2 * col + 1];
	} else if(num_of_display == 2){
		cur = arr[2 * (16 + col)];
	}
	if (row > 0)
	{
		if(num_of_display == 0){
			next = arr[2 * (col + row)];
		} else if(num_of_display == 1){
			next = arr[2 * (col + row) + 1];
		} else if(num_of_display == 2){
			next = arr[2 * (16 + (col + row))];
		}
		// ȡ��һλ�����λ����λ��ǰһλ�����λ��
		nextHiBit = (next & 0x80) >> 7;
		// ��������һλ
		cur = cur << 1;
		// �������Ƶ���һλ
		cur = cur | nextHiBit;
		// ֻȡ��λ
		cur = cur & 0xff;
	}
	return cur;

}


/**
**********************************************
***���������ƶ�һλ������*�����飬���鳤�ȣ�**
**********************************************
**********************************************
*/


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
void sendbyte_l(int *tab, int col, int row){
	// ��һ��led����
	int a = get_next(col, row, tab, 0);
	// �ڶ���led����
	int b = get_next(col, row, tab, 1);
	// ������led����
	int c = get_next(col, row, tab, 2);
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
	int size = sizeof(tab) / sizeof(tab[0]); 
	while(1){
		// ���ƶ���һ����3 * 8����
		for (j = 0;j < 24; j++ )
		{
			// ��ѭ����һ֡��ʾ����
			for(i = 0; i < 16; i++) {
				sendbyte_l(tab, i, j);
				sendbyte_h(i + 1);
				show();
			}
		}
	}
}
	
