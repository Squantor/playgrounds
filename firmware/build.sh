# build all the templates and clean afterwards
#!/bin/bash
make -j24 PROJECT=PC CONFIG=debug
make -j24 PROJECT=cortexM0_routines CONFIG=debug
make -j24 PROJECT=LPC812_e-ink_display CONFIG=debug
make -j24 PROJECT=LPC812_oled_display CONFIG=debug
make -j24 PROJECT=LPC812_pwm_modulator CONFIG=debug
make -j24 PROJECT=LPC845_sharp_lcd CONFIG=debug
make -j24 PROJECT=systick_template_c CONFIG=debug
make -j24 PROJECT=systick_template_cpp CONFIG=debug
make -j24 PROJECT=RP2040_demo CONFIG=debug
make -j24 PROJECT=RP2040_flash_bringup CONFIG=debug
make -j24 PROJECT=RP2040_oled_demo CONFIG=debug
make -j24 PROJECT=peripheral_abstraction CONFIG=debug
make -j24 PROJECT=LPC812_cpp_prototyping CONFIG=debug
make -j24 PROJECT=RP2040_cpp CONFIG=debug
make -j24 PROJECT=LPC812M101DH20_blinky CONFIG=debug
make -j24 PROJECT=LPC812M101DH20_coro_blinky CONFIG=debug
make -j24 PROJECT=LPC812M101DH20_nuclone_ADC CONFIG=debug
make -j24 PROJECT=LPC845BD48_blink CONFIG=debug
make -j24 PROJECT=LPC845QFP48_UI_SH1106_5btn CONFIG=debug
