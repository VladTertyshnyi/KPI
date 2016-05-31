#include <stdio.h>
#include <stdlib.h>
#include "SupaDive.h"
#include "list.h"

int main()
{
    data_t * data1 = data_create("data1", "bytes");
    data_t * data2 = data_create("data2", "bytes");

    user_t * user1 = user_create("user1");
    user_t * user2 = user_create("user2");
    user_t * user3 = user_create("user3");

    dataShelter_t * shelter1 = shelter_create("shelter1");

    shelter_addUser(shelter1, user1);
    shelter_addUser(shelter1, user2);
    shelter_addUser(shelter1, user3);

    user_addData(user1, data1);
    user_addData(user1, data2);
    user_addData(user1, data2);
    user_addData(user2, data2);
    user_addData(user3, data2);
    user_addData(user3, data2);

    shelter_printData(shelter1);

    shelter_deleteUser(shelter1, user1);
  //  shelter_deleteUser(shelter1, user2);
    shelter_deleteUser(shelter1, user3);

    shelter_printData(shelter1);

    shelter_delete(shelter1);
    return 0;
}
