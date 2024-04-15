//main 里面用到多少个 就用多少个
void Oled_Write_Cmd(char dataCmd);


void Oled_Write_Data(char dataData);


void Oled_Init();


void Oled_Clear();

void Oled_Show_Str(char row,char col,char *str);