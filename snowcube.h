#define NUM_X (6)
#define NUM_Y (6)
#define COLUMN_OFF (0x00)
#define COLUMN_ON (0x3F)
#define STD_DELAY (30)
#define NUM_LED (6 * 6 * 6)

void LEDDiagnosticLoop();

void LEDDiagnosticSetup();

void displayCubeBuffer();

uint8_t readLED(uint8_t, uint8_t, uint8_t);

void setPins();

void snowDisc();

void writeColumn(int);

void writeControl(int, int, uint8_t);

void writeLED(uint8_t, uint8_t, uint8_t, uint8_t);

void zeroCubeBuffer();
