#pragma once
// This file handles the connection to the mistral API :3
// why is tcp so complicated XD

#include <string>
#include <functional>



#define MISTRAL_API_KEY "ggs"

#define API_HOST "api.mistral.ai"
#define API_PORT 443
#define API_PATH "/v1/chat/completions"


static void send_promt(std::string prompt, std::function<void(std::string)> callback) {
    
    callback("You wrote: " + prompt);

}