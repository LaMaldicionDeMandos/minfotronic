//
// Created by Macbook pro Retina on 2019-05-11.
//
#include "../inc/DR_lcd.h"
#include "../inc/PR_lcd.h"
#include "shared_memory.h"
#include <stdio.h>
#include <unistd.h>

uint8_t* lcd_data = NULL;

#define DISPLAY_SIZE 16
#define CHAR(i, j) lcd_data[29 + i*DISPLAY_SIZE + j]

#define EMPTY_TEXT "                "
#define START_POSITION 0

#define LINE_0 0
#define LINE_1 1

/***********************************************************************************************************************************
*** FUNCIONES PRIVADAS AL MODULO
**********************************************************************************************************************************/
uint8_t* init_data() {
    int shmid;
    if (!lcd_data) {
        shmid = init_shared_memory();
        if (shmid < 0) {
            perror("Hubo un error con la libreria infotronic, por favor reinicie.\n");
            return 0;
        }
        lcd_data = shmat(shmid, NULL, 0);
    }
    return lcd_data;
}
/***********************************************************************************************************************************
*** FUNCIONES GLOBALES AL MODULO
**********************************************************************************************************************************/
void LCD_Display(const char *string, uint8_t line ,uint8_t pos) {
    lcd_data = init_data();

    for (int i = 0; i < pos; i++) {
        CHAR(line, i) = ' ';
    }

    for (int i = 0; i < DISPLAY_SIZE - pos && string[i]; i++ ) {
        CHAR(line, pos + i) = string[i];
    }
}

int8_t LCD_Push( uint8_t data , uint8_t control ) {
    LCD_Display(EMPTY_TEXT, LINE_0, START_POSITION);
    LCD_Display(EMPTY_TEXT, LINE_1, START_POSITION);
    return 0;
}
