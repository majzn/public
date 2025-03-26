#define MZN_LIB_IMPLEMENTATION
#include "mzncore.h"

static uint32 GLOBAL_BUFFER[800*600];

static real32 GLOBAL_TIME = 0.0f;

int32 fill_buffer(uint32* buffer, uint32 width, uint32 height) {
	real32 rval = 0.0f;
	uint32 x, y;
	for(y = 0; y < height; y++) {
		for(x = 0; x < width; x++) {
			rval = mzn_sin(GLOBAL_TIME + (real32)x*0.01f)*0.5f + 0.5f;
			buffer[x + y*width] = 0xFF0F2F00 | (uint8)(rval*255);
		}
	}
	GLOBAL_TIME += 0.016f;
	return TRUE;
}

int main(void) {
    mznContext ctx;
    mznWindowContext winCtx;
		int running = TRUE;
    mzn_context_init(&ctx);

    mzn_printf("Hello, world from mzn_lib!\n");

    if (mzn_sys_window_context_init(&winCtx, "MZN Example Window", 800, 600)) {
        winCtx.hwnd = mzn_sys_window_create(&winCtx, NULL);
        if (winCtx.hwnd) {
            mzn_printf("Window created successfully.\n");

            while(running) {
                if (!mzn_sys_window_update(&winCtx)) {
                    break;
                }
								fill_buffer(GLOBAL_BUFFER, 800, 600);
								mzn_sys_window_blit(&winCtx, GLOBAL_BUFFER, 800, 600);
						}

            mzn_sys_window_close(&winCtx);
        } else {
            mzn_printf("Failed to create window.\n");
        }
    } else {
        mzn_printf("Failed to initialize window context.\n");
    }

    mzn_printf("Exiting application.\n");
    return 0;
}
