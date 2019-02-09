#include "head.h"

int main() {
    vector<int*> inscription_list;
    generate_list(inscription_list);

//    normal_output(inscription_list);
//    skill_2_output(inscription_list);
//    skill_ultimate_output(inscription_list);
//    skill_2_ultimate_output(inscription_list);
    one_weapon_output(inscription_list);

    return 0;
}