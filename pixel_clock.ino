#include <M5Core2.h>
#include <time.h>
#include <WiFi.h>

char ssid[] = "ssid"; // 2.4GHz WiFi
char pass[] = "pass";

// Time
char ntpServer[] = "ntp.jst.mfeed.ad.jp";
const long gmtOffset_sec = 9 * 3600;
const int daylightOffset_sec = 0;
struct tm timeinfo;
String dateStr;
String timeStr;
const uint16_t colorvalue = M5.Lcd.color565(197, 218, 237);

void getTimeFromNTP()
{
  // NTPサーバと時刻を同期
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  while (!getLocalTime(&timeinfo))
  {
    delay(1000);
  }
}

void getTime()
{
  // 時刻の取得と表示
  getLocalTime(&timeinfo);
  dateStr = (String)(timeinfo.tm_year + 1900) + "/" + (String)(timeinfo.tm_mon + 1) + "/" + (String)timeinfo.tm_mday;
  timeStr = (String)timeinfo.tm_hour + ":" + (String)timeinfo.tm_min + ":" + (String)timeinfo.tm_sec;

  // M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(BLACK, colorvalue);
  M5.Lcd.setCursor(0, 0, 1);
  M5.Lcd.println(dateStr);
  M5.Lcd.println(timeStr);
}

void setup()
{
  // put your setup code here, to run once:
  // height 240px
  // width 320px
  M5.begin();
  M5.Lcd.setTextSize(3);
  //M5.Lcd.setTextColor(TFT_BLACK);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    M5.Lcd.print(".");
  }
  M5.Lcd.println("\nWiFi connected.");
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.drawJpgFile(SD, "/sea.jpg");

  // timeSet
  getTimeFromNTP();
}

void loop()
{
  getTime();
}
