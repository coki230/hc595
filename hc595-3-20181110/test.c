#include <stdio.h>
int tab[64] = {
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x10,0x20,0x10,0x20,0x11,0xFC,0x10,0x20,0xFC,0x20,0x24,0x20,0x27,0xFE,0x24,0x00,
0x24,0x20,0x48,0x20,0x29,0xFC,0x10,0x20,0x28,0x20,0x44,0x20,0x83,0xFE,0x00,0x00,
/*--  文字:  哈  --*/
/*--  Fixedsys12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x40,0x00,0x40,0x78,0xA0,0x49,0x10,0x4A,0x08,0x4C,0x06,0x4B,0xF8,0x48,0x00,
0x48,0x00,0x4B,0xF8,0x7A,0x08,0x4A,0x08,0x02,0x08,0x02,0x08,0x03,0xF8,0x02,0x08,
};

/**
**********************************************
***获取数组内元素的相对位置上的bit值**********
***clo：扫描列；row：扫描行（从最左面开始扫描）
***arr：需要取值的数组************************
**********************************************
*/

int get_bit(int col, int row, int *arr) {
	// 数组内到第几个元素
	int arrIndex;
	// 元素到第几位
	int valueBit;
	int cur, ret;
	int rowIndex, colIndex;
    // 默认从0开始，因为行列一般从1开始，所以需要转换，原值减去1
    col = col - 1;
    row = row - 1;
	
	rowIndex = row % 16;
	colIndex = col / 8;
	// 如果colIndex大于1，也就是大于 2 * 8,已经换下一个字了所以需要特殊处理
	arrIndex = 2 * rowIndex + colIndex / 2 * 32 + colIndex % 2;
	valueBit = col % 8;
	// cur = arr[arrIndex + 2 * col];
	cur = arr[arrIndex];
	// printf("the cur is : %x \n", cur);

	// 把需要到位移动到最右面，然后只取最右面到一位数
	ret = cur >> (8 - valueBit -1);
	ret = ret & 0x01;
	return ret;

}

/**********************************************
***获取数组内元素的相对位置上的bit值**********
***clo：扫描列；row：扫描行（从最左面开始扫描）
***arr：需要取值的数组************************
**********************************************
*/

unsigned long get_offset_value(int col, int row, int col_offset, int *arr) {
	unsigned long ret = 0;
	// 数组内到第几个元素
	int arrIndex;
	// 元素到第几位
	int valueBit;
	// 当前元素，当前元素剩余的位数
	int cur, left_index;
	int rowIndex, colIndex;
    // 默认从0开始，因为行列一般从1开始，所以需要转换，原值减去1
    col = col - 1;
    row = row - 1;
	
	rowIndex = row % 16;
	colIndex = col / 8;
	// 如果colIndex大于1，也就是大于 2 * 8,已经换下一个字了所以需要特殊处理
	arrIndex = 2 * rowIndex + colIndex / 2 * 32 + colIndex % 2;
	valueBit = col % 8;
	// cur = arr[arrIndex + 2 * col];
	cur = arr[arrIndex];
	// printf("the cur is : %x \n", cur);

	// 把需要到位移动到最右面，然后只取最右面到一位数
	ret = cur >> (8 - valueBit -1);
	// 当前元素剩余的位数
	left_index = 8 - valueBit;
	if (col_offset - left_index >= 0) {
		// 取元素index后面可用的位数
		ret = ret | (0xff >> valueBit);
		// 取到偏移量的返回数据
		ret = ret >> col_offset;
	}
	return ret;

}

/*
 * 返回位无符号的long，最多为4个字节，即为：4 * 8
 * 
 * 
 */
unsigned long get_row(int col_offset, int row, int *arr, int arrSize){
	unsigned long ret = 0;
	// 显示的LED的长度，三个LED，每个8位
	int ledLen = 3 * 8;
	int arrLen = arrSize * 8;
	int col_scan = 1;
	int col_start, col_end;
	int i;
	if(col_offset <= ledLen) {
		col_start = 1;
	} else {
		col_start = col_offset - ledLen;
	}
	col_end = col_offset + 1;
	col_scan = col_start;

	for(i = col_start; i < col_end; i++) {
		
		// 如果扫描的行大于数组的长度，则重新扫描
		if (i > arrLen && col_scan == 1)
		{
			col_scan = 0;
		}
		// 先整体右移 
		ret = ret << 1;
		// 如果当前位有值则最后为置1
		
		if (get_bit(col_scan, row, arr))
		{
			ret = ret | 0x01;
		}
		col_scan ++;
	}
	return ret;
}
void main() {
    // unsigned long row = get_row(24,3, tab, 64);
	unsigned long row = get_offset_value(2,6, 4, tab);
    printf("the row is: %x \n", row );

    // printf("the bit is: %x \n", 0x20 >> 6 );
}
	
