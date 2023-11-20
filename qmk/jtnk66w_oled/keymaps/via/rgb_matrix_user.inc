// !!! DO NOT ADD #pragma once !!! //

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(my_cool_effect)
RGB_MATRIX_EFFECT(my_cool_effect2)
RGB_MATRIX_EFFECT(my_cool_effect3)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

// e.g: A simple effect, self-contained within a single method

HSV my_math(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    uint16_t effect = tick - dist;
    if (effect > 255) effect = 255;
    hsv.v = qadd8(hsv.v, 255 - effect);
    return hsv;
}

extern uint8_t g_rgb_frame_buffer2[DRIVER_LED_TOTAL];
extern uint8_t g_rgb_frame_buffer3[DRIVER_LED_TOTAL];
extern uint8_t g_rgb_frame_buffer4[DRIVER_LED_TOTAL];


static uint8_t counter = 0;
static uint8_t is_initial = 0;

#if defined(RGB_MATRIX_KANJANI)
	#define MEMCOL 4
	const uint8_t memcol[MEMCOL][2]=
		{
		{23,255},//orange
		{92,255},//green
		{162,255},//blue
		{208,255},//purple
	//	{0,0} //white
	};
#else
	#define MEMCOL 7
	const uint8_t memcol[MEMCOL][2]=
		{
		{0,255},//red
		{30,255},//orange
		{46,255},//yallow
		{69,255},//green
		{162,255},//blue
		{201,255},//purple
		{231,255},//pink
	//	{255,0} //white
	};
#endif


HSV jt_set_color(int i, uint8_t v, effect_params_t* params) {
    HSV hsv = {memcol[rand() % MEMCOL][0], memcol[rand() % MEMCOL][1], v};
    if (!HAS_ANY_FLAGS(g_led_config.flags[i], params->flags)) return hsv;
    RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    return hsv;
}

HSV sp_math(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    uint16_t effect = tick + dist;
    effect = effect * 4;
    if (effect > 255) effect = 255;
    hsv.v = qadd8(hsv.v, 255 - effect);
    return hsv;
}

bool my_cool_effect(effect_params_t* params) {


    uint8_t row, col;
    uint8_t led[LED_HITS_TO_REMEMBER];

    RGB_MATRIX_USE_LIMITS(led_min, led_max);
        // Change one LED every tick, make sure speed is not 0
        if (scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed, 16)) % 31 == 0) {
        	uint8_t i = rand() % DRIVER_LED_TOTAL;
	        row = i % MATRIX_ROWS;
    	    col = i / MATRIX_ROWS;
	        led[0] = 255;
	        if(g_rgb_frame_buffer4[i] == 0){
		        rgb_matrix_map_row_column_to_led(row, col, led);
			        HSV hsv = jt_set_color(i, rgb_matrix_config.hsv.v, params);
				    g_rgb_frame_buffer2[i] = hsv.h;
				    g_rgb_frame_buffer3[i] = hsv.s;
				    g_rgb_frame_buffer4[i] = hsv.v;
			}
	        counter++;
        }


    for (uint8_t i = led_min; i < led_max; i++) {
	    	uint8_t start = 0;
	    	uint8_t count = g_last_hit_tracker.count;

        RGB_MATRIX_TEST_LED_FLAGS();
        HSV hsv = {memcol[(counter>>4) % MEMCOL][0], memcol[(counter>>4) % MEMCOL][1], 255};
        hsv.v   = 0;
        for (uint8_t j = start; j < count; j++) {
            int16_t  dx   = g_led_config.point[i].x - g_last_hit_tracker.x[j];
            int16_t  dy   = g_led_config.point[i].y - g_last_hit_tracker.y[j];
            uint8_t  dist = sqrt16(dx * dx + dy * dy);
            uint16_t tick = scale16by8(g_last_hit_tracker.tick[j], qadd8(rgb_matrix_config.speed, 1));
            hsv           = my_math(hsv, dx, dy, dist, tick);
        }
				    //g_rgb_frame_buffer2[i] = hsv.h;
				    //g_rgb_frame_buffer3[i] = hsv.s;
	    	 	    //g_rgb_frame_buffer4[i] = hsv.v;

        hsv.v   = scale8(hsv.v, rgb_matrix_config.hsv.v);
        RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);


	        row = i % MATRIX_ROWS;
	        col = i / MATRIX_ROWS;
	        //HSV hsv;
	        hsv.h = g_rgb_frame_buffer2[i];
	        hsv.s = g_rgb_frame_buffer3[i];
	        hsv.v = g_rgb_frame_buffer4[i];

	        led[0] = 255;
	        rgb_matrix_map_row_column_to_led(row, col, led);
		 	   g_rgb_frame_buffer3[i] = qsub8(hsv.s, 0);
		 	   g_rgb_frame_buffer4[i] = qsub8(hsv.v, 1);
            if(g_rgb_frame_buffer4[i] > 0){
			    rgb = rgb_matrix_hsv_to_rgb(hsv);
			    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
            }
	    }

    return led_max < DRIVER_LED_TOTAL;

}

bool my_cool_effect2(effect_params_t* params) {


    uint8_t row, col;
    uint8_t led[LED_HITS_TO_REMEMBER];

    RGB_MATRIX_USE_LIMITS(led_min, led_max);
        // Change one LED every tick, make sure speed is not 0
        if (scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed, 16)) % 31 == 0) {
        	uint8_t i = rand() % DRIVER_LED_TOTAL;
	        row = i % MATRIX_ROWS;
    	    col = i / MATRIX_ROWS;
	        led[0] = 255;
	        if(g_rgb_frame_buffer4[i] == 0){
		        rgb_matrix_map_row_column_to_led(row, col, led);
			        HSV hsv = jt_set_color(i, rgb_matrix_config.hsv.v, params);
				    g_rgb_frame_buffer2[i] = hsv.h;
				    g_rgb_frame_buffer3[i] = hsv.s;
				    g_rgb_frame_buffer4[i] = hsv.v;
			}
	        counter++;
        }


	    for (int i = led_min; i < led_max; i++) {

	    	uint8_t start = qsub8(g_last_hit_tracker.count, 1);
	    	uint8_t count = g_last_hit_tracker.count;
	        for (uint8_t j = start; j < count; j++) {
	            int16_t  dx   = (int16_t)(g_led_config.point[i].x) - (int16_t)(g_last_hit_tracker.x[j]);
	            int16_t  dy   = (int16_t)(g_led_config.point[i].y) - (int16_t)(g_last_hit_tracker.y[j]);
	            uint8_t  dist = sqrt16(dx * dx + dy * dy);
	            uint16_t tick = scale16by8(g_last_hit_tracker.tick[j], qadd8(rgb_matrix_config.speed, 1));

				if(dx > 32 || dx < -32 || dy > 32 || dy < -32) dist = 100;

			    HSV hsv = {memcol[counter % MEMCOL][0], memcol[counter % MEMCOL][1], 255};
			    hsv.v  = 0;
	            hsv           = sp_math(hsv, dx, dy, dist, tick);
	            row = i % MATRIX_ROWS;
	        	col = i / MATRIX_ROWS;

	            if(hsv.v && (dist < 32)){
				    g_rgb_frame_buffer2[i] = hsv.h;
				    g_rgb_frame_buffer3[i] = hsv.s;
	    	 	    g_rgb_frame_buffer4[i] = hsv.v;
				}
			}

	        row = i % MATRIX_ROWS;
	        col = i / MATRIX_ROWS;
	        HSV hsv;
	        hsv.h = g_rgb_frame_buffer2[i];
	        hsv.s = g_rgb_frame_buffer3[i];
	        hsv.v = g_rgb_frame_buffer4[i];

	        led[0] = 255;
	        rgb_matrix_map_row_column_to_led(row, col, led);
		 	   g_rgb_frame_buffer3[i] = qsub8(hsv.s, 0);
		 	   g_rgb_frame_buffer4[i] = qsub8(hsv.v, 1);
            if(g_rgb_frame_buffer4[i] > 0){
			    RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
			    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
            }
	    }

    return led_max < DRIVER_LED_TOTAL;

}

  // Physical Layout
  //  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17ROWS
  // __  5  6 13 14 20 21 28 29 36 37 44 45 52 53 54 61 62   0
  // __  4  7 12 15 19 22 27 30 35 38 43 46 51 __ 55 60 63   1
  //  0  3  8 11 16 18 23 26 31 34 39 42 47 50 __ 56 59 64   2
  //  1  2  9 10 17 __ 24 25 32 33 40 41 48 49 __ 57 58 65   3


char ledTable[]={
5,  6, 13, 14, 20, 21, 28, 29, 36, 37, 44, 45, 52, 53, 54, 61, 62,
63,64,65,58,57,49,48,41,40,33,32,25,24,17,10,9,2,1,0,
4,  7, 12, 15, 19, 22, 27, 30, 35, 38, 43, 46, 51, 55, 60,
59,56,50,47,42,39,34,31,26,23,18,16,11,8,3

};

bool my_cool_effect3(effect_params_t* params) {

    RGB_MATRIX_USE_LIMITS(led_min, led_max);
        // Change one LED every tick, make sure speed is not 0
        if (scale16by8(g_rgb_timer, qadd8(rgb_matrix_config.speed, 16)) % 31 == 0) {
	        counter++;
        }

    if(is_initial < DRIVER_LED_TOTAL){
        HSV hsv = rgb_matrix_config.hsv;
        hsv.v   = scale8(hsv.v, rgb_matrix_config.hsv.v);
        RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
        rgb_matrix_set_color(ledTable[is_initial], rgb.r, rgb.g, rgb.b);
        is_initial++;
        return false;
    }


    for (uint8_t i = led_min; i < led_max; i++) {
	    	uint8_t start = 0;
	    	uint8_t count = g_last_hit_tracker.count;

            RGB_MATRIX_TEST_LED_FLAGS();
            HSV hsv = {memcol[(counter>>4) % MEMCOL][0], memcol[(counter>>4) % MEMCOL][1], 255};
            hsv.v   = 0;
            for (uint8_t j = start; j < count; j++) {
                int16_t  dx   = g_led_config.point[i].x - g_last_hit_tracker.x[j];
                int16_t  dy   = g_led_config.point[i].y - g_last_hit_tracker.y[j];
                uint8_t  dist = sqrt16(dx * dx + dy * dy);
                uint16_t tick = scale16by8(g_last_hit_tracker.tick[j], qadd8(rgb_matrix_config.speed, 1));
                hsv           = my_math(hsv, dx, dy, dist, tick);
            }
            if(hsv.v == 0){
                hsv = rgb_matrix_config.hsv;
                hsv.v   = scale8(hsv.v, rgb_matrix_config.hsv.v);
                RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
                rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
            } else{
                hsv.v   = scale8(hsv.v, rgb_matrix_config.hsv.v);
                RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
                rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
            }
	}

    return led_max < DRIVER_LED_TOTAL;

}


#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
