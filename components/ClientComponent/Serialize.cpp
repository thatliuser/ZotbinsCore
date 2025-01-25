#include "Serialize.hpp"
#include <esp_mac.h>

cJSON* Client::serialize(float fullness, uint32_t usage, bool overflow, int32_t weight) {
    // Use the ESP32's MAC address as a UUID (since it is a UUID)
    uint8_t mac_addr_arr[6];
    uint64_t mac_addr;
    if (esp_base_mac_addr_get(mac_addr_arr) != ESP_OK) {
        // TODO: Handle mac address being unset properly
        mac_addr = 0x112233445566;
    } else {
        mac_addr =
            ((uint64_t)mac_addr_arr[5] <<  0) |
            ((uint64_t)mac_addr_arr[4] <<  8) |
            ((uint64_t)mac_addr_arr[3] << 16) |
            ((uint64_t)mac_addr_arr[2] << 24) |
            ((uint64_t)mac_addr_arr[1] << 32) |
            ((uint64_t)mac_addr_arr[0] << 40);
    }
    cJSON* root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "bin_id", mac_addr);
    cJSON_AddNumberToObject(root, "fullness", fullness);
    cJSON_AddNumberToObject(root, "usage", usage);
    cJSON_AddBoolToObject(root, "overflow", overflow);
    cJSON_AddNumberToObject(root, "weight", weight);
    return root;
}
