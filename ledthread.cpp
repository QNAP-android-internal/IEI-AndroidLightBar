#include "ledthread.h"
#include "ledhandler.h"

ledThread::ledThread() {}

ledThread::~ledThread() {}

void ledThread::triggerFunc(ledHandler *handler) { handler->run(); }
