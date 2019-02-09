//
// Created by Leo on 2019/2/8.
//

#ifndef KAI_HEAD_H
#define KAI_HEAD_H

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

//Weapons and Properties
struct weapon{
    double damage=0.0;
    double crit_rate=0.0;
    double crit_effect=0.0;
    double penetration=0.0;
    int has_Master=false;
    weapon(double damage1, double crit_rate1, double crit_effect1, double penetration1, int has_Master1=0)
    : damage(damage1),crit_rate(crit_rate1),crit_effect(crit_effect1),penetration(penetration1), has_Master(has_Master1){};
};

//Inscription and Properties
struct inscription{
    double penetration=0.0;
    double crit_rate=0.0;
    double crit_effect=0.0;
    double damage=0.0;
    inscription(double crit_rate1, double crit_effect1, double penetration1, double damage1=0.0)
            : crit_rate(crit_rate1),crit_effect(crit_effect1),penetration(penetration1),damage(damage1){};
};

//Armor and damage decrease
double decrease(double armor);

//Attack and Properties
class attack{
private:
//    double original_damage=347.0;  //late period
    double original_damage=266.0;  //early period
    double additional_damage=0.0;  //damage from weapon
    double damage=original_damage;
    double penetration=64.0;
    double crit_rate=0.0;
    double crit_effect=2.0;
    int has_Master=0;
    double crit_damage;
    double normal_damage;
    double average_damage;
//    double armor=346.0;  //late period
    double armor=200.0;  //early period
    double true_armor;  //true_armor=armor-penetration
    double true_damage_rate;
    int *inscription_array;  //choice of inscriptions

public:
    attack(){inscription_array=new int;};
    int skill_2=0;  //whether using skill 2
    int skill_ultimate=0;  //whether using ultimate skill
    void show();  //display current properties
    void equip_weapon(weapon weapon1);  //add one weapon
    void equip_inscription(inscription inscription1);  //add one inscription
    void equip_inscription(int *arr);  //add inscriptions
    void initialization(){
        damage+=200*skill_ultimate;
        true_armor=armor-penetration;
        true_damage_rate=1-decrease(true_armor);
    }
    void result();  //calculate the final damage
    void show_result();  //display the final damage
    void output(ofstream &out);  //write in the .csv file
};

extern weapon Black_Cut;
extern weapon Master;
extern weapon Endless;
extern inscription Unparalleled;
extern inscription Source;
extern inscription Variance;


void generate_list(vector<int*> &inscription_list);  //generate all inscriptions combinations(for 3 kinds, 66 in total)
void attack_show(int *arr);
void Endless_Master(vector<int*> inscription_list,attack Attack);
void Endless_Black_Cut(vector<int*> inscription_list,attack Attack);
void Black_Cut_Master(vector<int*> inscription_list,attack Attack);

void normal(vector<int*> inscription_list);  //only attack but with master's buff if equipped
void skill_2(vector<int*> inscription_list);  //after skill 2
void skill_ultimate(vector<int*> inscription_list);  //after ultimate skill

void Black_Cut_output(vector<int*> inscription_list,attack Attack,ofstream &out);
void Endless_output(vector<int*> inscription_list,attack Attack,ofstream &out);
void Master_output(vector<int*> inscription_list,attack Attack,ofstream &out);

void EM_output(vector<int*> inscription_list,attack Attack,ofstream &out);
void EB_output(vector<int*> inscription_list,attack Attack,ofstream &out);
void BM_output(vector<int*> inscription_list,attack Attack,ofstream &out);

//four situations with two weapons
void normal_output(vector<int*> inscription_list);
void skill_2_output(vector<int*> inscription_list);
void skill_ultimate_output(vector<int*> inscription_list);
void skill_2_ultimate_output(vector<int*> inscription_list);  //after ultimate skill and skill 2

void one_weapon_output(vector<int*> inscription_list);  //only equipped with one weapon

#endif //KAI_HEAD_H
