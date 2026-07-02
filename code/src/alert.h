#ifndef _ALERT_H_
#define _ALERT_H_

typedef enum AlertType {
    ALERT_NONE = -1,
    ALERT_MISSING_ROMFS,
    ALERT_HASH_MISMATCH,
} AlertType;

// Display a warning message on the top screen.
void Alert_Set(AlertType alert);

#endif //_ALERT_H_
