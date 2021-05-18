#include <mbed.h>

DigitalIn btn(PC_13);
I2C i2c(PB_9, PB_8); 

const int vActAddr = 0b1100000 << 1;
const int vSetAddr = 0b1100001 << 1;

const char setInitState[] = { 0b011'00'01'0, 0, 0 };

void set(const int addr, uint16_t val) {
    uint16_t cmd = __builtin_bswap16(val) & 0xFFF;
    i2c.write(addr, (char*) &cmd, 2);
}

int main() {
    // Write default power-down to EEPROM
    // i2c.write(vActAddr, setInitState, 3);
    // i2c.write(vSetAddr, setInitState, 3);
    
    uint16_t vAct = static_cast<uint16_t>(0xFFF * (1.0/3.3));
    uint16_t vSet = static_cast<uint16_t>(0xFFF * (0.3/3.3));
    
    set(vActAddr, vAct);
    while(true) {
        wait_ms(10);
        set(vSetAddr, btn ? vSet : 0);
    }
    return 0;
}
