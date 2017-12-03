#define NUM_X (6)
#define NUM_Y (6)
#define COLUMN_OFF (0x00)
#define COLUMN_ON (0x3F)
#define STD_DELAY (30)
#define NUM_LED (6 * 6 * 6)

void LEDDiagnosticLoop();

void LEDDiagnosticSetup();

void displayFrameBuffer();

void setPins();

void writeColumn(int);

void writeControl(int, int, uint8_t);
