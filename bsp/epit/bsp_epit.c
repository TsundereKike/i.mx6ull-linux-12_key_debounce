#include "bsp_epit.h"
#include "bsp_int.h"
#include "bsp_led.h"
#include "bsp_beep.h"
/*初始化定时器EPIT1*/
void epit1_init(unsigned int frac, unsigned int value)
{
    if(frac>4095)
        frac = 4095;
    /*配置EPIT1_CR寄存器*/
    EPIT1->CR = 0;
    EPIT1->CR = (1<<1) | (1<<2) | (1<<3) | (frac<<4) | (1<<24);
    EPIT1->LR = value;/*加载值寄存器*/
    EPIT1->CMPR = 0;/*比较值寄存器*/

    /*EPIT1定时器中断初始化*/
    GIC_EnableIRQ(EPIT1_IRQn);
    system_register_irqhandler(EPIT1_IRQn, epit1_irq_handler, NULL);

    /*使能EPIT1*/
    EPIT1->CR |= (1<<0);
}
void epit1_irq_handler(unsigned int gicciar,void *param)
{
    static uint8_t state = 0;
    if((EPIT1->SR & (1<<0)))
    {
        state = !state;
        led_switch(LED0, state);
        beep_switch(state);  
    }
    EPIT1->SR |= (1<<0);
}
