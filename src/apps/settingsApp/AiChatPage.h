#include "elements/Element.h"
#include "elements/Keyboard.h"
#include "elements/TextEditScreen.h"
#include "storage/Storage.h"

class AiChatPage : public TextEditScreen {
public:
  override std::function<void()> onSave = [this](){
    printf("saving apikey")

    strncpy(Storage::data.mistralApiKey, this.string.c_str(), sizeof(Storage::data.mistralApiKey) - 1);
    Storage::data.wifiPASS[sizeof(Storage::data.mistralApiKey) - 1] = '\0';

    Storage::save();
  }
};







