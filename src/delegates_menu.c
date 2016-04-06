#include <pebble.h>
#include "delegates_menu.h"

static Window *window;
static MenuLayer *ml;
char *democrats[2];
char *republicans[5];
static char *canidates[] = {"Clinton", "Sanders", "Trump", "Cruz", "Rubio", "Kasich", "Carson"};

void delegates_menu_reload(){
	menu_layer_reload_data(ml);
}

uint16_t get_num_sections(MenuLayer *menu_layer, void *data) {
  return 2;
}

uint16_t get_num_rows(MenuLayer *menu_layer, uint16_t section_index, void *data){
	switch (section_index){
	case 0:
		return 2;
	case 1:
		return 5;
	default:
		return 0;
	}
}

int16_t get_header_height(MenuLayer *menu_layer, uint16_t section_index, void *data) {
	#ifdef PBL_RECT
  	return MENU_CELL_BASIC_HEADER_HEIGHT*2;
	#else
		return 0;
	#endif
}

void draw_header(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
  switch (section_index) {
    case 0:
      menu_cell_basic_header_draw(ctx, cell_layer, "Democrats - 2,382 Needed of 4,763");
      break;
    case 1:
      menu_cell_basic_header_draw(ctx, cell_layer, "Republicans - 1,237 Needed of 2,472");
      break;
  }
}

void draw_rows(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data){
	switch (cell_index->section){
	case 0:
		menu_cell_basic_draw(ctx, cell_layer, canidates[cell_index->row], democrats[cell_index->row], NULL);
		break;
	case 1:
		menu_cell_basic_draw(ctx, cell_layer, canidates[cell_index->row+2], republicans[cell_index->row], NULL);
		break;
	}
}

void selection_changed(MenuLayer *menu_layer, MenuIndex new_index, MenuIndex old_index, void *callback_context){
	#ifdef PBL_COLOR
		switch(new_index.section){
		case 0:
			menu_layer_set_highlight_colors(ml, GColorBlue, GColorWhite);
				break;
		case 1:
			menu_layer_set_highlight_colors(ml, GColorRed, GColorWhite);
			break;
		}
	#endif
}

void menu_window_load(){
	Layer *mLayer = window_get_root_layer(window);
	GRect bounds = layer_get_bounds(mLayer);
	
	ml = menu_layer_create(bounds);
	menu_layer_set_callbacks(ml, NULL, (MenuLayerCallbacks){
		.get_num_rows = get_num_rows,
		.draw_row  = draw_rows,
		.get_num_sections = get_num_sections,
		.draw_header = draw_header,
		.get_header_height = get_header_height,
		.selection_changed = selection_changed
	});
	
	menu_layer_set_click_config_onto_window(ml, window);
	#ifdef PBL_COLOR
		menu_layer_set_highlight_colors(ml, GColorBlue, GColorWhite);
	#endif
	layer_add_child(mLayer, menu_layer_get_layer(ml));
}

void menu_window_unload(){
	menu_layer_destroy(ml);
}

void delegates_menu_show(bool animated){
	window_stack_push(window, animated);
}
void delegates_menu_init(char *democrats_[], char *republicans_[]){
	memcpy(democrats, democrats_, sizeof(democrats));
	memcpy(republicans, republicans_, sizeof(republicans));
	
	window = window_create();
	window_set_window_handlers(window, (WindowHandlers) {
    .load = menu_window_load,
    .unload = menu_window_unload
  });
	
}
void delegates_menu_destroy(){
	window_destroy(window);
}
