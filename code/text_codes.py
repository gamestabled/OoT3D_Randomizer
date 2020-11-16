def MESSAGE_END():
    return "\x7F\x00"

def WAIT_FOR_INPUT():
    return "\x7F\x01"

def HORIZONTAL_SPACE(x):
    return "\x7F\x02" + chr(x)

def GOTO_MESSAGE_ID(x):
    return "\x7F\x03" + chr(x / 0x100) + chr(x % 0x100) #TODO: endiannes correct?

def INSTANT_TEXT_ON():
    return "\x7F\x04"

def INSTANT_TEXT_OFF():
    return "\x7F\x05"

def SHOP_MESSAGE_BOX():
    return "\x7F\x06"

def EVENT_TRIGGER():
    return "\x7F\x07"

def DELAY_FRAMES(x):
    return "\x7F\x08" + chr(x)

def CLOSE_AFTER(x):
    return "\x7F\x0A" + chr(x)

def PLAYER_NAME():
    return "\x7F\x0B"

def PLAY_OCARINA():
    return "\x7F\x0C"

def PLAY_SOUND(x):
    return "\x7F\x0E" + chr(x / 0x100) + chr(x % 0x100) #TODO: endiannes correct?

def ITEM_OBTAINED(x):
    return "\x7F\x0F" + chr(x)

def SET_SPEED(x):
    return "\x7F\x10" + chr(x)

def SKULLTULAS_DESTROYED():
    return "\x7F\x15"

def CURRENT_TIME():
    return "\x7F\x17"

def UNSKIPPABLE():
    return "\x7F\x19"

def NEWLINE():
    return "\x7F\x1C"

def COLOR(x):
    return "\x7F\x1D" + chr(x)

def CENTER_TEXT():
    return "\x7F\x1E"

WHITE  = 0x00
RED    = 0x41
GREEN  = 0x42
BLUE   = 0x43
LBLUE  = 0x44
PINK   = 0x45
YELLOW = 0x46
BLACK  = 0x47