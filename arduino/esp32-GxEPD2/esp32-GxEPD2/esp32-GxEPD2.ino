#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <cmath>

#define BATTERY_WIDTH 50

GxEPD2_BW<GxEPD2_213_B74, GxEPD2_213_B74::HEIGHT> display(
    GxEPD2_213_B74(/*CS=*/15, /*DC=*/27, /*RST=*/26, /*BUSY=*/25)
);

// 'Lightning bolt', 19x35px
const unsigned char lightningBolt14x26 [] PROGMEM = {
	0x01, 0x80, 0x03, 0x80, 0x03, 0x80, 0x07, 0x80, 0x07, 0x80, 0x0f, 0x80, 0x0f, 0x80, 0x1f, 0x80, 
	0x1f, 0x80, 0x3f, 0x00, 0x3f, 0xfc, 0x7f, 0xfc, 0x7f, 0xfc, 0xff, 0xf8, 0xff, 0xf8, 0xff, 0xf0, 
	0x03, 0xf0, 0x07, 0xe0, 0x07, 0xe0, 0x07, 0xc0, 0x07, 0xc0, 0x07, 0x80, 0x07, 0x80, 0x07, 0x00, 
	0x07, 0x00, 0x06, 0x00
};

// -------- CONFIG --------
uint8_t batteryLevel   = 3;   // 0..3
uint8_t batteryPercent = 100;  // 0..100
bool charging          = true;
// ------------------------

void drawVerticalBattery(
  int16_t x,
  int16_t y,
  int16_t height,
  uint8_t level,
  uint8_t percent,
  bool charging
) {
  const int batteryWidth   = BATTERY_WIDTH;
  const int terminalHeight = 10;
  const int barCount       = 3;
  const int barGap         = 5;
  const int bodyXPadding   = 3;

  // Battery body
  display.drawRect(x, y + terminalHeight, batteryWidth, height - terminalHeight, GxEPD_BLACK);

  // Terminal (top)
  display.fillRect(
    x + 12,
    y,
    batteryWidth - 24,
    terminalHeight,
    GxEPD_BLACK
  );

  // Bars
  int innerHeight = height - 2 * bodyXPadding - terminalHeight - 2; // minus 2 for borders
  int barHeight = (innerHeight - (barCount - 1) * barGap) / barCount;

  for (uint8_t i = 0; i < level; i++) {
    int bx = x + 1;
    int by = y + terminalHeight + bodyXPadding + 1 + i * (barHeight + barGap);

    display.fillRect(
      bx,
      by,
      batteryWidth - 2,
      barHeight,
      GxEPD_BLACK
    );
  }

  // -------- Percentage (bottom bar) --------
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_WHITE);

  char percentText[6];
  snprintf(percentText, sizeof(percentText), "%u%%", percent);

  int16_t tbx, tby;
  uint16_t tbw, tbh;
  display.getTextBounds(percentText, 0, 0, &tbx, &tby, &tbw, &tbh);

  int textX = x + 1 + (batteryWidth - 2 - tbw) / 2;
  int textY = y + height - 1 - bodyXPadding - ((barHeight - tbh) / 2);

  display.setCursor(textX - tbx, textY);
  display.print(percentText);

  // -------- Charging indicator (bitmap-based) --------
  if (charging) {
    uint16_t boltColor = (level <= 1) ? GxEPD_BLACK : GxEPD_WHITE;

    const int boltW = 14;
    const int boltH = 26;

    int bx = x + (batteryWidth - boltW) / 2;
    int by = y + terminalHeight + 1 + bodyXPadding + floor(barCount / 2) * (barHeight + barGap) + (barHeight - boltH) / 2;

    display.drawBitmap(
      bx,
      by,
      lightningBolt14x26,
      boltW,
      boltH,
      boltColor
    );
  }
}

void drawLayout() {
  // Vertical separator
  const int verticalSeparatorX = display.width() / 4;
  display.drawLine(verticalSeparatorX, 0, verticalSeparatorX, display.height(), GxEPD_BLACK);

  // Horizontal separators
  const int horizontalSeparatorY1 = display.height() / 3;
  const int horizontalSeparatorY2 = (display.height() / 3) * 2 + 1;
  display.drawLine(verticalSeparatorX + 1, horizontalSeparatorY1, display.width(), horizontalSeparatorY1, GxEPD_BLACK);
  display.drawLine(verticalSeparatorX + 1, horizontalSeparatorY2, display.width(), horizontalSeparatorY2, GxEPD_BLACK);
}

void setup() {
  SPI.begin(13, -1, 14, 15);
  display.init(115200, true, 2, false);

  display.setRotation(1);
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);

    int batteryX = (display.width() / 4 - BATTERY_WIDTH) / 2;
    int margin = 5;
    int batteryHeight = display.height() - margin * 2;

    drawVerticalBattery(
      batteryX,
      margin,
      batteryHeight,
      batteryLevel,
      batteryPercent,
      charging
    );

    drawLayout();
  }
  while (display.nextPage());

  display.hibernate();
}

void loop() {}
