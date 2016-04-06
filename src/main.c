#include <pebble.h>
#include "delegates_menu.h"

#define CLINTON 0
#define SANDERS 1
#define TRUMP 2
#define CRUZ 3
#define RUBIO 4
#define KASICH 5
#define CARSON 6

char *democrats[2];
char *republicans[5];

static void inbox_received_callback(DictionaryIterator *iterator, void *context){
	strcpy(democrats[0], dict_find(iterator, CLINTON)->value->cstring);
	strcpy(democrats[1], dict_find(iterator, SANDERS)->value->cstring);
	strcpy(republicans[0], dict_find(iterator, TRUMP)->value->cstring);
	strcpy(republicans[1], dict_find(iterator, CRUZ)->value->cstring);
	strcpy(republicans[2], dict_find(iterator, RUBIO)->value->cstring);
	strcpy(republicans[3], dict_find(iterator, KASICH)->value->cstring);
	strcpy(republicans[4], dict_find(iterator, CARSON)->value->cstring);
	delegates_menu_reload();
}

static void inbox_dropped_callback(AppMessageResult reason, void *context){
	APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!!");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context){
	APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context){
	APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send success!!");
}

void init(){
	for(int i = 0; i<2; i++){
		democrats[i] = (char*)malloc(sizeof(char)*25);
		strcpy(democrats[i], "Loading...");
	}
	for(int i = 0; i<5; i++){
		republicans[i] = (char*)malloc(sizeof(char)*25);
		strcpy(republicans[i], "Loading...");
	}
	
	delegates_menu_init(democrats, republicans);
	delegates_menu_show(true);
	
	app_message_register_inbox_received(inbox_received_callback);
	app_message_register_inbox_dropped(inbox_dropped_callback);
	app_message_register_outbox_failed(outbox_failed_callback);
	app_message_register_outbox_sent(outbox_sent_callback);
	
	app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}

void deinit(){
	delegates_menu_destroy();
	for(int i = 0; i<2; i++){
		free(democrats[i]);
	}
	for(int i = 0; i<5; i++){
		free(republicans[i]);
	}
}

int main(){
	init();
	app_event_loop();
	deinit();
}