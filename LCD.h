#include "typedef.h"

#include "lcd_defines.h"

void lcd_cmd(u8 cmd);

void lcd_data(u8 data);

void lcd_init(void);

void lcd_char(s8 ch);

void lcd_str(s8 *str);

void lcd_int(s32 num);

void lcd_float(f32 num,u8 ndp);

