//
// Created by Leo on 2019/2/8.
//
#include "head.h"

double decrease(double armor){
    double rate=armor/(armor+602.0);
    return rate;
}

void attack::show() {
    cout<<"damage: "<<damage<<'('<<original_damage<<'+'<<additional_damage<<')'<<endl;
    cout<<"penetration: "<<penetration<<endl;
    cout<<"crit_rate: "<<crit_rate<<endl;
    cout<<"crit_effect: "<<crit_effect<<endl;
    cout<<"has_Master: "<<((has_Master) ? "has_Master":"no_Master")<<endl;
    cout<<"Inscription:\n"<<"Unparalleled: "<<inscription_array[0]<<" Source: "<<inscription_array[1]
    <<" Variance: "<<inscription_array[2]<<endl;
}

void attack::equip_weapon(weapon weapon1) {
    damage+=weapon1.damage;
    additional_damage+=weapon1.damage;
    crit_effect+=weapon1.crit_effect;
    crit_rate+=weapon1.crit_rate;
    penetration+=weapon1.penetration;
    if(weapon1.has_Master)
        has_Master=1;
}

void attack::equip_inscription(int *arr) {
    inscription_array=arr;
    int Unparalleled_num=arr[0];
    int Source_num=arr[1];
    int Variance_num=arr[2];
    for (int i = 0; i < Unparalleled_num; ++i) {
        equip_inscription(Unparalleled);
    }
    for (int i = 0; i < Source_num; ++i) {
        equip_inscription(Source);
    }
    for (int i = 0; i < Variance_num; ++i) {
        equip_inscription(Variance);
    }
}

void attack::equip_inscription(inscription inscription1) {
    damage+=inscription1.damage;
    additional_damage+=inscription1.damage;
    crit_effect+=inscription1.crit_effect;
    crit_rate+=inscription1.crit_rate;
    penetration+=inscription1.penetration;
}

void attack::result() {
    crit_damage=true_damage_rate*(damage*has_Master*0.33+(300*skill_2+damage*crit_effect)*1.5);
    normal_damage=true_damage_rate*(damage*has_Master*0.33+(300*skill_2+damage)*1.5);
    average_damage=crit_damage*crit_rate+normal_damage*(1-crit_rate);
}

void attack::show_result() {
    cout<<"Inscriptions:\n"<<"Unparalleled: "<<inscription_array[0]<<" Source: "<<inscription_array[1]
        <<" Variance: "<<inscription_array[2]<<endl;
    cout<<"crit_damage: "<<crit_damage<<" normal_damage: "<<normal_damage<<" average_damage: "<<average_damage<<endl;
}

void generate_list(vector<int *> &inscription_list) {
    for (int i = 0; i <= 10; ++i) {
        for (int j = 0; j <= 10-i; ++j) {
            int *array=new int;
            array[0]=i;
            array[1]=j;
            array[2]=10-i-j;
            inscription_list.push_back(array);
//            cout<<i<<'\t'<<j<<'\t'<<array[2]<<endl;
        }
    }
}

void attack_show(int *arr) {
    attack Only_attack;
    Only_attack.equip_weapon(Endless);
    Only_attack.equip_weapon(Master);
    Only_attack.equip_weapon(Black_Cut);
    Only_attack.equip_inscription(arr);
    Only_attack.show();
}

void Black_Cut_output(vector<int *> inscription_list, attack Attack, ofstream &out) {
    Attack.equip_weapon(Black_Cut);
    for (int i = 0; i < 66; ++i) {
        attack Attack1=Attack;
        Attack1.equip_inscription(inscription_list[i]);
        Attack1.initialization();
        Attack1.result();
        Attack1.output(out);
        out<<','<<"Black_Cut"<<endl;
    }
}

void Endless_output(vector<int *> inscription_list, attack Attack, ofstream &out) {
    Attack.equip_weapon(Endless);
    for (int i = 0; i < 66; ++i) {
        attack Attack1=Attack;
        Attack1.equip_inscription(inscription_list[i]);
        Attack1.initialization();
        Attack1.result();
        Attack1.output(out);
        out<<','<<"Endless"<<endl;
    }
}

void Master_output(vector<int *> inscription_list, attack Attack, ofstream &out) {
    Attack.equip_weapon(Master);
    for (int i = 0; i < 66; ++i) {
        attack Attack1=Attack;
        Attack1.equip_inscription(inscription_list[i]);
        Attack1.initialization();
        Attack1.result();
        Attack1.output(out);
        out<<','<<"Master"<<endl;
    }
}

void Endless_Master(vector<int*> inscription_list,attack Attack) {
    Attack.equip_weapon(Master);
    Attack.equip_weapon(Endless);
    for (int i = 0; i < 66; ++i) {
        cout<<i+1<<" -> ";
        attack Attack1=Attack;
        Attack1.equip_inscription(inscription_list[i]);
        Attack1.initialization();
        Attack1.result();
        Attack1.show_result();
    }
}

void Endless_Black_Cut(vector<int*> inscription_list,attack Attack) {
    Attack.equip_weapon(Endless);
    Attack.equip_weapon(Black_Cut);
    for (int i = 0; i < 66; ++i) {
        cout<<i+1<<" -> ";
        attack Attack1=Attack;
        Attack1.equip_inscription(inscription_list[i]);
        Attack1.initialization();
        Attack1.result();
        Attack1.show_result();
    }
}

void Black_Cut_Master(vector<int*> inscription_list,attack Attack) {
    Attack.equip_weapon(Master);
    Attack.equip_weapon(Black_Cut);
    for (int i = 0; i < 66; ++i) {
        cout<<i+1<<" -> ";
        attack Attack1=Attack;
        Attack1.equip_inscription(inscription_list[i]);
        Attack1.initialization();
        Attack1.result();
        Attack1.show_result();
    }
}

void normal(vector<int *> inscription_list) {
    attack Attack;
    cout<<"\nEndless_Master:\n";
    Endless_Master(inscription_list,Attack);
    cout<<"\nEndless_Black_Cut:\n";
    Endless_Black_Cut(inscription_list,Attack);
    cout<<"\nBlack_Cut_Master:\n";
    Black_Cut_Master(inscription_list,Attack);
}

void skill_2(vector<int *> inscription_list) {
    attack Attack;
    Attack.skill_2=1;
    cout<<"\nEndless_Master:\n";
    Endless_Master(inscription_list,Attack);
    cout<<"\nEndless_Black_Cut:\n";
    Endless_Black_Cut(inscription_list,Attack);
    cout<<"\nBlack_Cut_Master:\n";
    Black_Cut_Master(inscription_list,Attack);
}

void skill_ultimate(vector<int *> inscription_list) {
    attack Attack;
    Attack.skill_ultimate=1;
    cout<<"\nEndless_Master:\n";
    Endless_Master(inscription_list,Attack);
    cout<<"\nEndless_Black_Cut:\n";
    Endless_Black_Cut(inscription_list,Attack);
    cout<<"\nBlack_Cut_Master:\n";
    Black_Cut_Master(inscription_list,Attack);
}

void attack::output(ofstream &out) {
    out<<inscription_array[0]<<','<<inscription_array[1]<<','<<inscription_array[2]<<','
    <<crit_damage<<','<<normal_damage<<','<<average_damage;
}

void EM_output(vector<int *> inscription_list, attack Attack, ofstream &out) {
    Attack.equip_weapon(Master);
    Attack.equip_weapon(Endless);
    for (int i = 0; i < 66; ++i) {
        attack Attack1=Attack;
        Attack1.equip_inscription(inscription_list[i]);
        Attack1.initialization();
        Attack1.result();
        Attack1.output(out);
        out<<','<<"Master"<<','<<"Endless"<<endl;
    }
}

void EB_output(vector<int *> inscription_list, attack Attack, ofstream &out) {
    Attack.equip_weapon(Black_Cut);
    Attack.equip_weapon(Endless);
    for (int i = 0; i < 66; ++i) {
        attack Attack1=Attack;
        Attack1.equip_inscription(inscription_list[i]);
        Attack1.initialization();
        Attack1.result();
        Attack1.output(out);
        out<<','<<"Black_Cut"<<','<<"Endless"<<endl;
    }
}

void BM_output(vector<int *> inscription_list, attack Attack, ofstream &out) {
    Attack.equip_weapon(Master);
    Attack.equip_weapon(Black_Cut);
    for (int i = 0; i < 66; ++i) {
        attack Attack1=Attack;
        Attack1.equip_inscription(inscription_list[i]);
        Attack1.initialization();
        Attack1.result();
        Attack1.output(out);
        out<<','<<"Master"<<','<<"Black_Cut"<<endl;
    }
}

void normal_output(vector<int *> inscription_list) {
    attack Attack;
    ofstream out;
    out.open("Normal_1.csv");
    out<<"Unparalleled,Source,Variance,Crit_Damage,Normal_Damage,Average_Damage,Weapon1,Weapon2\n";
    EM_output(inscription_list,Attack,out);
    EB_output(inscription_list,Attack,out);
    BM_output(inscription_list,Attack,out);
    out.close();
}

void skill_2_output(vector<int *> inscription_list) {
    attack Attack;
    ofstream out;
    out.open("Skill_2_1.csv");
    out<<"Unparalleled,Source,Variance,Crit_Damage,Normal_Damage,Average_Damage,Weapon1,Weapon2\n";
    Attack.skill_2=1;
    EM_output(inscription_list,Attack,out);
    EB_output(inscription_list,Attack,out);
    BM_output(inscription_list,Attack,out);
    out.close();
}

void skill_ultimate_output(vector<int *> inscription_list) {
    attack Attack;
    ofstream out;
    out.open("Skill_Ultimate_1.csv");
    out<<"Unparalleled,Source,Variance,Crit_Damage,Normal_Damage,Average_Damage,Weapon1,Weapon2\n";
    Attack.skill_ultimate=1;
    EM_output(inscription_list,Attack,out);
    EB_output(inscription_list,Attack,out);
    BM_output(inscription_list,Attack,out);
    out.close();
}

void skill_2_ultimate_output(vector<int *> inscription_list) {
    attack Attack;
    ofstream out;
    out.open("Skill_2_Ultimate_1.csv");
    out<<"Unparalleled,Source,Variance,Crit_Damage,Normal_Damage,Average_Damage,Weapon1,Weapon2\n";
    Attack.skill_2=1;
    Attack.skill_ultimate=1;
    EM_output(inscription_list,Attack,out);
    EB_output(inscription_list,Attack,out);
    BM_output(inscription_list,Attack,out);
    out.close();
}

void one_weapon_output(vector<int *> inscription_list) {
    attack Attack;
    ofstream out;
    out.open("Normal_1.csv");
    out<<"Unparalleled,Source,Variance,Crit_Damage,Normal_Damage,Average_Damage,Weapon\n";
    Black_Cut_output(inscription_list,Attack,out);
    Master_output(inscription_list,Attack,out);
    Endless_output(inscription_list,Attack,out);
    out.close();

    attack Attack1;
    ofstream out1;
    out1.open("Skill_2_1.csv");
    out1<<"Unparalleled,Source,Variance,Crit_Damage,Normal_Damage,Average_Damage,Weapon\n";
    Attack1.skill_2=1;
    Black_Cut_output(inscription_list,Attack1,out1);
    Master_output(inscription_list,Attack1,out1);
    Endless_output(inscription_list,Attack1,out1);
    out1.close();

    attack Attack2;
    ofstream out2;
    out2.open("Skill_Ultimate_1.csv");
    out2<<"Unparalleled,Source,Variance,Crit_Damage,Normal_Damage,Average_Damage,Weapon\n";
    Attack2.skill_ultimate=1;
    Black_Cut_output(inscription_list,Attack2,out2);
    Master_output(inscription_list,Attack2,out2);
    Endless_output(inscription_list,Attack2,out2);
    out2.close();

    attack Attack3;
    ofstream out3;
    out3.open("Skill_2_Ultimate_1.csv");
    out3<<"Unparalleled,Source,Variance,Crit_Damage,Normal_Damage,Average_Damage,Weapon\n";
    Attack3.skill_2=1;
    Attack3.skill_ultimate=1;
    Black_Cut_output(inscription_list,Attack3,out3);
    Master_output(inscription_list,Attack3,out3);
    Endless_output(inscription_list,Attack3,out3);
    out3.close();
}
