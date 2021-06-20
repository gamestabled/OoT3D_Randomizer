#ifndef _ENTRANCE_H_
#define _ENTRANCE_H_

typedef struct {
    s16 index;
    s16 blueWarp;
    s16 override;
} EntranceOverride;

void Entrance_Init(void);
s16 GetRequiemEntrance(void);

#endif //_ENTRANCE_H_
