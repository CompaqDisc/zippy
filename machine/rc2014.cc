#include "rc2014.h"

RC2014::RC2014() {
	machine_id_ = "rc2014";
	target_speed_hz_ = 7372880;
}

void RC2014::Start() {
	// Do nothing...
}

void RC2014::TaskThread() {
	// Never called...
}