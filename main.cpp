
#include "mbed.h"
#include "USBSerial.h"

USBSerial pc(0x1f00, 0x2012, 0x0001, false, 20480);  // connect_blocking = false, buf_size = 20480
RawSerial wifi_serial(P7_1, P0_1);

InterruptIn button0(USER_BUTTON0);
InterruptIn button1(USER_BUTTON1);

DigitalOut wifi_en(P5_3);
DigitalOut wifi_io0(P3_14);

static uint8_t usb_send_buff[64];

static void settings_change(int baud, int bits, int parity, int stop) {
    wifi_serial.baud(baud);
    wifi_serial.format(bits, (SerialBase::Parity)parity, (stop == 0) ? 1 : stop);
}

static void button0_fall(void) {
    wifi_en = 0;
}

static void button0_rise(void) {
    wifi_en = 1;
}

static void button1_fall(void) {
    wifi_io0 = 0;
}

static void button1_rise(void) {
    wifi_io0 = 1;
}

int main() {
    pc.attach(&settings_change);

    // check ESP_IO0
    if (button1 == 0) {
        wifi_io0 = 0;
    } else {
        wifi_io0 = 1;
    }

    // button setting
    button0.fall(&button0_fall);
    button0.rise(&button0_rise);
    button1.fall(&button1_fall);
    button1.rise(&button1_rise);

    // reset
    wifi_en  = 0;
    Thread::wait(100);
    wifi_en  = 1;

    while (1) {
        if (wifi_serial.readable()) {
            int idx = 0;
            usb_send_buff[idx++] = wifi_serial.getc();
            while (wifi_serial.readable() && (idx < 64)) {
                usb_send_buff[idx++] = wifi_serial.getc();
            }
            pc.writeBlock(usb_send_buff, idx);
        }
        if (pc.readable()) {
            wifi_serial.putc(pc._getc());
        }
    }
}
