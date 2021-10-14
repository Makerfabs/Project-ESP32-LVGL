

#include "FT6236.h"

#define TOUCH_THRESHOLD 80
#define I2C_SDA 26
#define I2C_SCL 27

FT6236 ts = FT6236();

void setup()
{

  Serial.begin(115200); /* prepare for possible serial debug */

  if (!ts.begin(TOUCH_THRESHOLD, I2C_SDA, I2C_SCL))
  {
    Serial.println("Unable to start the capacitive touchscreen.");
  }

  ledcSetup(10, 5000 /*freq*/, 10 /*resolution*/);
  ledcAttachPin(32, 10);
  analogReadResolution(10);
  ledcWrite(10, 768);

  lv_init();

#if USE_LV_LOG != 0
  lv_log_register_print_cb(my_print); /* register print function for debugging */
#endif

  tft.begin(); /* TFT init */
  tft.setRotation(3);

  uint16_t calData[5] = {275, 3620, 264, 3532, 1};
  //tft.setTouch(calData);

  lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 10);

  /*Initialize the display*/
  lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.buffer = &disp_buf;
  lv_disp_drv_register(&disp_drv);

  /*Initialize the input device driver*/
  lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);          /*Descriptor of a input device driver*/
  indev_drv.type = LV_INDEV_TYPE_POINTER; /*Touch pad is a pointer-like device*/
  indev_drv.read_cb = my_touchpad_read;   /*Set your driver function*/
  lv_indev_drv_register(&indev_drv);      /*Finally register the driver*/

  //Set the theme..
  lv_theme_t *th = lv_theme_material_init(LV_THEME_DEFAULT_COLOR_PRIMARY, LV_THEME_DEFAULT_COLOR_SECONDARY, LV_THEME_DEFAULT_FLAG, LV_THEME_DEFAULT_FONT_SMALL, LV_THEME_DEFAULT_FONT_NORMAL, LV_THEME_DEFAULT_FONT_SUBTITLE, LV_THEME_DEFAULT_FONT_TITLE);
  lv_theme_set_act(th);

  my_page();
}

void my_page_test1()
{
  //lv_obj_t * tv = lv_tabview_create(scr, NULL);
  //lv_obj_set_size(tv, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));

  /* Create simple label */
  // lv_obj_t *label = lv_label_create(lv_scr_act(), NULL);
  // lv_label_set_text(label, "Makerfabs LVGL DEMO");
  // lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);

  // /* Create a slider in the center of the display */
  // lv_obj_t * slider = lv_slider_create(lv_scr_act(), NULL);
  // lv_obj_set_width(slider, screenWidth-50);                        /*Set the width*/
  // lv_obj_set_height(slider, 50);
  // lv_obj_align(slider, NULL, LV_ALIGN_CENTER, 0, 0);    /*Align to the center of the parent (screen)*/
  // lv_obj_set_event_cb(slider, slider_event_cb);         /*Assign an event function*/

  // /* Create a label below the slider */
  // slider_label = lv_label_create(lv_scr_act(), NULL);
  // lv_label_set_text(slider_label, "0");
  // lv_obj_set_auto_realign(slider, true);
  // lv_obj_align(slider_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
}

void my_page-_test2()
{
  lv_obj_t *page1 = lv_page_create(NULL, NULL);
  lv_page_set_scrollbar_mode(page1, LV_SCROLLBAR_MODE_DRAG);
  lv_disp_load_scr(page1);

  lv_obj_t *label = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(label, "Makerfabs LVGL DEMO");
  lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);

  extern const lv_img_dsc_t logo;
  lv_obj_t *image1 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(image1, &logo);
  lv_obj_align(image1, NULL, LV_ALIGN_IN_TOP_MID, 0, 20);

  /*Create a style for the shadow*/
  static lv_style_t style_1;
  lv_style_init(&style_1);
  lv_style_set_text_font(&style_1, LV_STATE_DEFAULT, &lv_font_montserrat_24);

  static lv_style_t style_2;
  lv_style_init(&style_2);
  lv_style_set_text_font(&style_2, LV_STATE_DEFAULT, &lv_font_montserrat_24);
  lv_style_set_text_opa(&style_2, LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA);

  lv_obj_t *label1 = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_long_mode(label1, LV_LABEL_LONG_SROLL_CIRC); /*Circular scroll*/
  lv_obj_set_width(label1, 400);
  lv_obj_set_height(label1, 30);
  lv_label_set_recolor(label1, true);
  lv_obj_align(label1, NULL, LV_ALIGN_IN_TOP_MID, 0, 100);

  lv_obj_add_style(label1, LV_BTN_PART_MAIN, &style_1);
  lv_label_set_text(label1, "  #0000ff Makerfabs# is Open Hardware, Arduino, Raspberry Pi, mbed, BeagleBone, IoT, Smart Home, etc, Related Products& Services Vendor for Makers and new Startups.. ");

  lv_obj_t *label1_s = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_long_mode(label1_s, LV_LABEL_LONG_SROLL_CIRC); /*Circular scroll*/
  lv_obj_set_width(label1_s, 400);
  lv_obj_set_height(label1_s, 30);
  lv_label_set_recolor(label1_s, true);
  lv_obj_align(label1_s, NULL, LV_ALIGN_IN_TOP_MID, 2, 102);

  lv_obj_add_style(label1_s, LV_BTN_PART_MAIN, &style_2);
  lv_label_set_text(label1_s, lv_label_get_text(label1));

  lv_obj_t *label4 = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_long_mode(label4, LV_LABEL_LONG_BREAK); /*Break the long lines*/
  lv_label_set_recolor(label4, true);                  /*Enable re-coloring by commands in the text*/
  lv_obj_set_width(label4, 400);
  lv_obj_align(label4, NULL, LV_ALIGN_IN_TOP_MID, 0, 160);

  lv_label_set_text(label4, "#0000ff Makerfabs# is an open hardware facilitation company based in Shenzhen, China."
                            " Benefiting from the largest electronic market, local manufacture power, and convenient global logistic system, a vast number of funny and exciting products are created every day. "
                            "We integrate resources to serve a new era of innovation."
                            "To make your making and innovation easier, we offer various development platforms, modules, tools, electronics components, and other open source hardware."
                            "we also provide many kinds of service, include Fusion PCB service, Component Sourcing service and PCB Assembly service, etc."
                            "No matter whether you're a curious student, a qualified engineer, or a hobbyist who loves to create, there will always be something here to meet your needs - and if there isn't, we'd love to know. "
                            "Please list your wishes through the Forum or contact with us.");
}

void my_page()
{
  lv_obj_t *page1 = lv_page_create(NULL, NULL);
  lv_page_set_scrollbar_mode(page1, LV_SCROLLBAR_MODE_DRAG);
  lv_disp_load_scr(page1);

  lv_obj_t *label = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_text(label, "Makerfabs LVGL DEMO");
  lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);

  extern const lv_img_dsc_t logo;
  lv_obj_t *image_logo = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(image_logo, &logo);
  lv_obj_align(image_logo, NULL, LV_ALIGN_IN_TOP_MID, 0, 20);

  /*Create a style for the shadow*/
  static lv_style_t style_1;
  lv_style_init(&style_1);
  lv_style_set_text_font(&style_1, LV_STATE_DEFAULT, &lv_font_montserrat_24);

  static lv_style_t style_2;
  lv_style_init(&style_2);
  lv_style_set_text_font(&style_2, LV_STATE_DEFAULT, &lv_font_montserrat_24);
  lv_style_set_text_opa(&style_2, LV_STATE_DEFAULT, LV_STYLE_TEXT_OPA);

  lv_obj_t *label1 = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_long_mode(label1, LV_LABEL_LONG_SROLL_CIRC); /*Circular scroll*/
  lv_obj_set_width(label1, 400);
  lv_obj_set_height(label1, 30);
  lv_label_set_recolor(label1, true);
  lv_obj_align(label1, NULL, LV_ALIGN_IN_TOP_MID, 0, 100);

  lv_obj_add_style(label1, LV_BTN_PART_MAIN, &style_1);
  lv_label_set_text(label1, "  #0000ff Makerfabs# is Open Hardware, Arduino, Raspberry Pi, mbed, BeagleBone, IoT, Smart Home, etc, Related Products& Services Vendor for Makers and new Startups.. ");

  lv_obj_t *label1_s = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_long_mode(label1_s, LV_LABEL_LONG_SROLL_CIRC); /*Circular scroll*/
  lv_obj_set_width(label1_s, 400);
  lv_obj_set_height(label1_s, 30);
  lv_label_set_recolor(label1_s, true);
  lv_obj_align(label1_s, NULL, LV_ALIGN_IN_TOP_MID, 2, 102);

  lv_obj_add_style(label1_s, LV_BTN_PART_MAIN, &style_2);
  lv_label_set_text(label1_s, lv_label_get_text(label1));

  extern const lv_img_dsc_t img1;
  lv_obj_t *image_1 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(image_1, &img1);
  lv_obj_align(image_1, NULL, LV_ALIGN_IN_TOP_MID, 0, 180);

  //ESP32 3.5" TFT Touch(Capacitive) with Camera

  lv_obj_t *label2 = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_long_mode(label2, LV_LABEL_LONG_SROLL_CIRC); /*Circular scroll*/
  lv_obj_set_width(label2, 400);
  lv_label_set_text(label2, "\"ESP32 3.5\" TFT Touch(Capacitive) with Camera");
  lv_obj_align(label2, NULL, LV_ALIGN_IN_TOP_MID, 0, 330);

  extern const lv_img_dsc_t img2;
  lv_obj_t *image_2 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(image_2, &img2);
  lv_obj_align(image_2, NULL, LV_ALIGN_IN_TOP_MID, 0, 370);

  //Pico Primer Kit for Raspberry PI

  lv_obj_t *label3 = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_long_mode(label3, LV_LABEL_LONG_SROLL_CIRC); /*Circular scroll*/
  lv_obj_set_width(label3, 400);
  lv_label_set_text(label3, "Pico Primer Kit for Raspberry PI");
  lv_obj_align(label3, NULL, LV_ALIGN_IN_TOP_MID, 0, 530);

  extern const lv_img_dsc_t img3;
  lv_obj_t *image_3 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(image_3, &img3);
  lv_obj_align(image_3, NULL, LV_ALIGN_IN_TOP_MID, 0, 550);

  //PCBA/ Turnkey PCB Assembly Service

  lv_obj_t *label4 = lv_label_create(lv_scr_act(), NULL);
  lv_label_set_long_mode(label4, LV_LABEL_LONG_SROLL_CIRC); /*Circular scroll*/
  lv_obj_set_width(label4, 400);
  lv_label_set_text(label4, "PCBA/ Turnkey PCB Assembly Service");
  lv_obj_align(label4, NULL, LV_ALIGN_IN_TOP_MID, 0, 700);
}