#include "imx6u.h"
#include "bsp_clk.h"
#include "bsp_led.h"
#include "bsp_delay.h"
#include "bsp_beep.h"
#include "bsp_key.h"
#include "bsp_int.h"
#include "bsp_exti.h"
#include "bsp_epit.h"
int main(void)
{
    int_init();
    imx6u_clk_init();
    clk_enable();
    led_init();
    beep_init();
    key_init();
    exti_init();
    epit1_init(0,33000000);/*初始化定时器1,1分频66MHz,定时时间为500ms*/
    while(1)
    {
        delay_ms(500);
    }
    return 0;
}
