#include "utilities.h"

/**
 * Possible encoding schemes:
 * Message: - Using seperators : Fails if the seperator is part of the message
 *                               We can restrict the messages to certain characters
 *                               No We can check for the last k seperators. Won't fail
 *                               Go in reverse order.
 *          - Message.message|str(from)|str(sendingTime)
 * Request: - Using seperators:
 *          - message$type$id
 * Reply  : - Using seperators:
 *          - message$type$id$status_code
 *
 */
