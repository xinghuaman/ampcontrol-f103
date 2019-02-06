#ifndef SWTIMERS_H
#define SWTIMERS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define SW_TIM_OFF       -1

typedef uint8_t SwTimer;
enum {
    SW_TIM_DISPLAY,
    SW_TIM_SP_CONVERT,
    SW_TIM_TUNER_POLL,
    SW_TIM_INIT_HW,
    SW_TIM_RC_REPEAT,

    SW_TIM_END,
};

void swTimUpdate(void);

void swTimSet(SwTimer timer, int32_t value);
int32_t swTimGet(SwTimer timer);

#ifdef __cplusplus
}
#endif

#endif // SWTIMERS_H