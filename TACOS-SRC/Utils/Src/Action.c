#include "Action.h"

void Action_TryExecute(Action action) {
	if (action == NULL) return;
	action();
}
