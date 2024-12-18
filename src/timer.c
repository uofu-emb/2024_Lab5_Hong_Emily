#include <stdio.h>
#include <pico/stdlib.h>
#include <pico/sync.h>

int toggle = 1;
bool timer_callback(__unused struct repeating_timer *t)
{
    toggle = !toggle;
    gpio_put(11, toggle);
    return true;
}

int main(void)
{
    stdio_init_all();
    // Create a repeating timer that calls timer_callback.
    // If the delay is > 0 then this is the delay between the previous
    // callback ending and the next starting.
    // If the delay is negative (see below) then the next call to the
    // callback will be exactly 500ms after the start of the call to
    // the last callback
    repeating_timer_t timer;
    gpio_init(11);
    gpio_set_dir(11, GPIO_OUT);
    gpio_put(11, toggle);

    add_repeating_timer_ms(-100, timer_callback, NULL, &timer);
    while(1) __nop();
    return 0;
}
