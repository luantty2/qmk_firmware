RGB_MATRIX_EFFECT(CAPS_ONLY)
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

bool CAPS_ONLY(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min; i < led_max; i++) {
        rgb_matrix_set_color(i, 0, 0, 0);
    }
    return led_max < DRIVER_LED_TOTAL;
}

#endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
