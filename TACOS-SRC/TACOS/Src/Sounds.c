#include "Sounds.h"
#include "Beep.h"

void Sounds_PlayBoot(void) {
    BeepSec(1000, .25);
    BeepSec(1500, .25);
    BeepSec(1250, .25);
}
void Sounds_PlaySystemEnd(void) {
    BeepSec(1250, .4);
    BeepSec(1000, .4);
    BeepSec(1250, .4);
    BeepSec(1500, .8);
}
void Sounds_PlaySelect(void) {
    BeepSec(600, .5);
}
