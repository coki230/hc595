#include <REGX51.H>
#include <INTRINS.H>
// 行扫描
sbit shcp_h=P2^2;
sbit ds_h=P2^1;
sbit shcp=P2^0;
// 列扫描
sbit shcp_l=P2^3;
sbit ds_l=P2^4;

code int tab[96] = {
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x10,0x20,0x10,0x20,0x11,0xFC,0x10,0x20,0xFC,0x20,0x24,0x20,0x27,0xFE,0x24,0x00,
0x24,0x20,0x48,0x20,0x29,0xFC,0x10,0x20,0x28,0x20,0x44,0x20,0x83,0xFE,0x00,0x00,
/*--  文字:  哈  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x40,0x00,0x40,0x78,0xA0,0x49,0x10,0x4A,0x08,0x4C,0x06,0x4B,0xF8,0x48,0x00,
0x48,0x00,0x4B,0xF8,0x7A,0x08,0x4A,0x08,0x02,0x08,0x02,0x08,0x03,0xF8,0x02,0x08,

/*--  文字:  哈  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x40,0x00,0x40,0x78,0xA0,0x49,0x10,0x4A,0x08,0x4C,0x06,0x4B,0xF8,0x48,0x00,
0x48,0x00,0x4B,0xF8,0x7A,0x08,0x4A,0x08,0x02,0x08,0x02,0x08,0x03,0xF8,0x02,0x08
};

/**
**********************************************
***数组向左移动一位，参数*（数组，数组长度）**
**********************************************
**********************************************
*/
void move_left(int *arr, int size) {
	int first = arr[0];
	int i, nextHiBit;
	for (i = 0; i < size; i++){
			int next;
		// 把后面的数据最高位进位到此数据的最低位，最后位没有数据，需要特殊处理
		if (i < (size - 1)) {
			next = arr[i + 1];
		} else {
			next = first;
		}
		nextHiBit = (next & 0x80) >> 7;
		// 数组左移一位
		arr[i] = arr[i] << 1;
		// 补齐右移掉的一位
		arr[i] = arr[i] | nextHiBit;
		// 只取两位
		arr[i] = arr[i] & 0xff;
	}
}

// 行扫描函数
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

// 列扫描函数
//void sendbyte_l(char a, char b){
void sendbyte_l(int *tab, int i){
	// 第一个led内容
	int a = tab[2 * i];
	// 第二个led内容
	int b = tab[2 * i + 1];
	// 第三个led内容
	int c = tab[2 * (16 + i)];
	int j;
	// 取反数据
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
			// 列循环，一帧显示数据
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
	
