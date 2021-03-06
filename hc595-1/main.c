#include <REGX51.H>
#include <INTRINS.H>
// 模拟软件和实际LED的极型不一样，所以需要两端取反（实际led低为1）
#define SHOW_VALUE 1

// 行扫描
sbit ds_h=P1^1;
sbit shcp_h=P3^7;
// 列扫描
sbit ds_l=P3^6;
sbit shcp_l=P3^5;

sbit stcp=P1^0;
unsigned char tab[] = {
0x00,0x3C,0x06,0x06,0x3E,0x66,0x66,0x3E
};

// 行扫描函数
void sendbyte_h(int index){
	unsigned char i;
	for(i = 0; i < 8; i++) {
		shcp_h = 0;
		if ((8 - index) == i)
		{
			ds_h = SHOW_VALUE;
		} else {
			ds_h = !SHOW_VALUE;
		}
		shcp_h = 1;
	}
	
}

// 列扫描函数
void sendbyte_l(unsigned char a){
	unsigned char i;
	// 取反数据
	if (SHOW_VALUE)
	{
		a = ~a;
	}
	for(i = 0; i < 8; i++) {
		shcp_l = 0;
		ds_l = a & 0x01;
		a = a >> 1;
		shcp_l = 1;
	}
	

}
void show(){
	stcp = 0;
	_nop_();
	stcp = 1;
}

void main() {

	unsigned char i, j;
	unsigned int f = 50;
	while(1){
		for(i = 0; i < 8; i++) {
			sendbyte_l(tab[i]);
			sendbyte_h(i + 1);
			show();
//				while(f--);
		}
////		
//			sendbyte_l(0xff);
//			sendbyte_h(1);
//			show();
////			while(f--);
	}
}

