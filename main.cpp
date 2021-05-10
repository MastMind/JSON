#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json.h"


int main() {
	const char* str = "{\"head\":{\"format\":\"EngineFormatUser\",\"errorCode\":\"ResOK\"},\"data\":{\"users\":[{\"userName\":\"admin\",\"userGroup\":\"Admin\"},{\"userName\":\"user1\",\"userGroup\":\"Operator\"}]}}";

	json_value_t v = json_from_string(str);

	if (!v) {
		fprintf(stdout, "v is null\n");
		return 0;
	}

	json_object_t json_msg = (json_object_t)(v->value);
    json_object_t json_head = (json_object_t)((json_object_get_element(json_msg, "head"))->value);
    json_object_t json_data = (json_object_t)((json_object_get_element(json_msg, "data"))->value);

    json_array_t json_users = (json_array_t)((json_object_get_element(json_data, "users"))->value);

    if (!json_users) {
        fprintf(stdout, "Warning: users not found!\n");
    }

    for (unsigned int i = 0; i < json_users->size; i++) {
        json_value_t element = json_array_get_element(json_users, i);

        if (element->type != JSON_OBJECT) { //skip
            fprintf(stdout, "Unknown user\n");
            continue;
        }

        json_object_t element_user = (json_object_t)(element->value);
        char* user_name = (char*)((json_object_get_element(element_user, "userName"))->value);
        char* group_name = (char*)((json_object_get_element(element_user, "userGroup"))->value);

        fprintf(stdout, "%12s|%13s\n", user_name, group_name);
    }

    fprintf(stdout, "            |             |\n");
    fprintf(stdout, "--------------------------|\n\n");

    json_object_clear(json_msg);
    free(v);

	return 0;
}
