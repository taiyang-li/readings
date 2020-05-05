#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <cstring>
#include <queue>
#include <cstdio>
using namespace std;
class Headquarter;
class Iceman;
class Warrior;
class Ninja;
class Wolf;
class Lion;
class Dragon;
class Weapon;
class City;
class Report;

int dHP, iHP, lHP, nHP, wHP;    // 全局魔兽初始生命
int M, nCity, arr_atk, K, T;
int dATK, iATK, lATK, nATK, wATK;

/* Clock 游戏钟表类 设计+实现 开始*/
const int minSet[11] = {0, 5, 10, 20, 30, 35, 38, 40, 50, 55};
class Clock
{
    public:
        Clock()
        {
            hour = 0;
            curr_min_peek = 0;
        }
        bool tick()
        {
            curr_min_peek = (curr_min_peek + 1) % 10;
            if(curr_min_peek % 10 == 0)
                hour++;
            if(getTime() <= T) return true;
            else return false;
        }
        void printTime()
        {
            printf("%03d:%02d", hour, minSet[curr_min_peek % 10]);
        }
        void reset()
        {
            hour = curr_min_peek = 0;
        }
        int getTime()
        {
            return hour * 60 + minSet[curr_min_peek];
        }
    private:
        int hour;
        int curr_min_peek;
} CLOCK;                            // 全局游戏时钟
/* Clock 游戏钟表类 设计+实现 结束 */
/* Report 游戏报告类 设计 开始 */
class Report
{
    public:
        void born(Warrior* warrior);
        void lionRunAway(Warrior* lion);
        void dragonYell(Warrior* dragon);
        void march();
        void shoot(Warrior* w1, Warrior* w2);
        void bomb(Warrior* w1, Warrior* w2);
        void attack(Warrior* w1, Warrior* w2);
        void fightback(Warrior* w1, Warrior* w2);
        void dead(Warrior* deadman);
        void raiseFlag(City* city);
        void reach_headquarter(Headquarter* head);
        void elements(Headquarter& head);
        void weapons();
        void contribute(Warrior* w, int elemtents);
    private:
        void warriorMarch(Warrior* warrior, int cityno);
        void warriorWeapon(Warrior* w);
} REPORT;                       // 全局游戏报告引擎
/* Report 游戏报告类 设计 结束 */
/* Headquarter 司令部类 设计 开始 */
class Headquarter
{
    public:
        Headquarter(string color_, int M): color(color_), elements(M), nWarrior(0), produce_peek(0), newbaby(NULL), enemy(NULL), takenTime(0), extraElments(0) {}
        int elements;
        Warrior* newbaby;
        string color;
        void produceWarrior();
        priority_queue<Warrior*> creditList;
        void reset(int M);
        void giveCredit();
        void receiveExtraElements();
        Warrior* enemy;
        int takenTime;
        int extraElments;
    private:
        Warrior* producePeek(int peek);             
        Warrior* produce(string type, int HP);
        int produce_peek;                       
        int nWarrior;
}red("red", M), blue("blue", M);
/* Headquarter 司令部类 设计 结束 */
/* City 城市类 设计 开始 */
class City
{
    public:
        City(): elements(0), redWarrior(NULL), blueWarrior(NULL), flagColor("white"), winnerColor("white"){};
        int elements;
        Warrior* redWarrior;
        Warrior* blueWarrior;
        string flagColor;
        string winnerColor;
        void produce();
        bool isBattleField();
        string attackColor();
        void duel(Warrior* w1, Warrior* w2);
        int id;
}*CITY;                 // 全局城市变量
/* City 城市类 设计 结束 */
/* Weapon 武器类 设计 开始 */
class Weapon
{
    public:
        Weapon(string type_, int atk_): type(type_), atk(atk_){};
        string type;
        int atk;
};
class Sword: public Weapon
{
    public:
        Sword(int atk_): Weapon("sword", atk_){};
        void use(){
            atk = (int) atk * 0.8;
        }
};
class Arrow: public Weapon
{
    public:
        Arrow(): Weapon("arrow", arr_atk), remain(3){};
        void use(){
            remain -= 1;
        }
        int remain;
};
class Bomb: public Weapon
{
    public:
        Bomb(): Weapon("bomb", 100){};
};
/* Weapon 武器类 设计 结束 */
/* Warrior 武士类 设计 开始 */
class Warrior
{
    public:
        Warrior(int id_, int hp_, int atk_, string type_, Headquarter* headquarter_);
        ~Warrior()
        {
            delete sword;
            delete arrow;
            delete bomb;
        }
        friend bool operator < (Warrior& w1, Warrior& w2);
        void shoot(Warrior* warrior);
        void runaway();
        void march();
        bool will_be_killed_by(City& city, Warrior* w);
        void attack(Warrior* target);
        void fightback(Warrior* target);
        void applyCredit();
        void contribute();
        void win(City& city, Warrior* loser);
        int get_atk();
        int get_fightback_atk();
        string type;
        string color;
        int atk;
        int id;
        int hp;
        int last_hp;
        int position;
        int loyalty;
        bool marched;
        double morale;
        Sword* sword;
        Arrow* arrow;
        Bomb* bomb;
        Headquarter* headquarter;
    private:
        bool isNewBaby;
        int step;
};
/* Warrior 武士类 设计 结束 */
/* Headquarter 司令部类 实现 开始 */
void Headquarter::produceWarrior()
{
    newbaby = producePeek(produce_peek % 5);
    if(newbaby != NULL)
    {
        produce_peek = (produce_peek + 1) % 5;
        REPORT.born(newbaby);
    }
}
void Headquarter::reset(int M)
{
    elements = M; nWarrior = 0; produce_peek = 0; newbaby = NULL; enemy = NULL; takenTime = 0; extraElments = 0;
}
Warrior* Headquarter::producePeek(int peek)
{
    if(color == "red")                      // 在函数执行中书写武士生产顺序，以color区别不同的顺序
    {
        switch(peek)
        {
            case 0:
                return produce("iceman", iHP);
            case 1:
                return produce("lion", lHP);
            case 2:
                return produce("wolf", wHP);
            case 3:
                return produce("ninja", nHP);
            case 4:
                return produce("dragon", dHP);
            default:
                return false;
        }
    }
    if(color == "blue")
    {
        switch(peek)
        {
            case 0:
                return produce("lion", lHP);
            case 1:
                return produce("dragon", dHP);
            case 2:
                return produce("ninja", nHP);
            case 3:
                return produce("iceman", iHP);
            case 4:
                return produce("wolf", wHP);
            default:
                return false;
        }
    }
}

Warrior* Headquarter::produce(string type, int HP)
{
    if(elements >= HP)
    {
        nWarrior++;
        elements -= HP;
        if(type == "wolf")
            return new Warrior(nWarrior, HP, wATK, "wolf", this);
        else if(type == "dragon")
            return new Warrior(nWarrior, HP, dATK, "dragon", this);
        else if(type == "iceman")
            return new Warrior(nWarrior, HP, iATK, "iceman", this);
        else if(type == "lion")
            return new Warrior(nWarrior, HP, lATK, "lion", this);
        else return new Warrior(nWarrior, HP, nATK, "ninja", this);
    }
    else return NULL;
}
void Headquarter::giveCredit()
{
    while(!creditList.empty())
    {
        Warrior* w = creditList.top();
        creditList.pop();
        if(elements >= 8){
            elements -= 8;
            w->hp += 8;
        }else break;
    }
    creditList.empty();
}
void Headquarter::receiveExtraElements()
{
    elements += extraElments;
    extraElments = 0;
}
/* Headquarter 司令部类 实现 结束 */
/* Report 游戏报告类 实现 开始 */
void Report::born(Warrior* warrior)
{
    CLOCK.printTime();
    printf(" %s %s %d born\n", warrior->color.c_str(), warrior->type.c_str(), warrior->id);

    if(warrior->type == "dragon")
        printf("Its morale is %.2f\n", warrior->morale);
    if(warrior->type == "lion")
        printf("Its loyalty is %d\n", warrior->loyalty);
}
void Report::lionRunAway(Warrior* lion)
{
    CLOCK.printTime();
    printf(" %s lion %d ran away\n", lion->color.c_str(), lion->id);
}
void Report::dragonYell(Warrior* dragon)
{
    CLOCK.printTime();
    printf(" %s dragon %d yelled in city %d\n", dragon->color.c_str(), dragon->id, dragon->position);
}
void Report::march()    
{
    if(red.enemy != NULL && red.enemy->marched) reach_headquarter(&red);
    for(int i = 1; i <= nCity; i++)
    {
        if(CITY[i].redWarrior != NULL && CITY[i].redWarrior->marched)
            warriorMarch(CITY[i].redWarrior, i);
        if(CITY[i].blueWarrior != NULL && CITY[i].blueWarrior->marched)
            warriorMarch(CITY[i].blueWarrior, i);
    }
    if(blue.enemy != NULL && blue.enemy->marched) reach_headquarter(&blue);
}
void Report::warriorMarch(Warrior* warrior, int cityno)
{
    CLOCK.printTime();
    warrior->marched = false;
    printf(" %s %s %d marched to city %d with %d elements and force %d\n", warrior->color.c_str(), warrior->type.c_str(), warrior->id, warrior->position, warrior->hp, warrior->atk);
}
void Report::shoot(Warrior* w1, Warrior* w2)
{
    CLOCK.printTime();
    printf(" %s %s %d shot", w1->color.c_str(), w1->type.c_str(), w1->id);
    if(w2->hp <= 0)
        printf(" and killed %s %s %d", w2->color.c_str(), w2->type.c_str(), w2->id);
    printf("\n");
}
void Report::bomb(Warrior* w1, Warrior* w2)
{
    CLOCK.printTime();
    printf(" %s %s %d used a bomb and killed %s %s %d\n", w1->color.c_str(), w1->type.c_str(), w1->id, w2->color.c_str(), w2->type.c_str(), w2->id);
}
void Report::attack(Warrior* w1, Warrior* w2)
{
    CLOCK.printTime();
    printf(" %s %s %d attacked %s %s %d in city %d with %d elements and force %d\n",
            w1->color.c_str(), w1->type.c_str(), w1->id, w2->color.c_str(), w2->type.c_str(), w2->id, w1->position, w1->hp, w1->atk);
}
void Report::fightback(Warrior* w1, Warrior* w2)
{
    CLOCK.printTime();
    printf(" %s %s %d fought back against %s %s %d in city %d\n", w1->color.c_str(), w1->type.c_str(), w1->id, w2->color.c_str(), w2->type.c_str(), w2->id, w1->position);
}
void Report::dead(Warrior* deadman)
{
    CLOCK.printTime();
    printf(" %s %s %d was killed in city %d\n", deadman->color.c_str(), deadman->type.c_str(), deadman->id, deadman->position);
}
void Report::raiseFlag(City* city)
{
    CLOCK.printTime();
    printf(" %s flag raised in city %d\n",  city->flagColor.c_str(), city->id);
}
void Report::reach_headquarter(Headquarter* head)
{
    if(head->enemy != NULL && head->enemy->marched)
    {
        head->enemy->marched = false;
        CLOCK.printTime();
        printf(" %s %s %d reached %s headquarter with %d elements and force %d\n", head->enemy->color.c_str(), head->enemy->type.c_str(), head->enemy->id, head->color.c_str(), head->enemy->hp, head->enemy->atk);
    }
    if(head->takenTime >= 2)
    {
        CLOCK.printTime();
        printf(" %s headquarter was taken\n", head->color.c_str());
    }
}
void Report::elements(Headquarter& head)
{
    CLOCK.printTime();
    printf(" %d elements in %s headquarter\n", head.elements, head.color.c_str());
}
void Report::weapons()
{
    for(int i = 1; i <= nCity; i++)
        if(CITY[i].redWarrior != NULL) warriorWeapon(CITY[i].redWarrior);
    if(blue.enemy != NULL) warriorWeapon(blue.enemy);
    if(red.enemy != NULL) warriorWeapon(red.enemy);
    for(int i = 1; i <= nCity; i++)
        if(CITY[i].blueWarrior != NULL) warriorWeapon(CITY[i].blueWarrior);
}
void Report::warriorWeapon(Warrior* w)
{
    CLOCK.printTime();
    printf(" %s %s %d has ", w->color.c_str(), w->type.c_str(), w->id);
    if(w->sword != NULL && w->sword->atk <= 0) w->sword = NULL;
    if(w->arrow != NULL) printf("arrow(%d)", w->arrow->remain);
    if(w->bomb != NULL){
        if(w->arrow != NULL) printf(",bomb");
        else printf("bomb");
    }
    if(w->sword != NULL){
        if(w->arrow != NULL || w->bomb != NULL) printf(",sword(%d)", w->sword->atk);
        else printf("sword(%d)", w->sword->atk);
    }
    if(w->arrow == NULL && w->sword == NULL && w->bomb == NULL)
        printf("no weapon");
    printf("\n");
}
void Report::contribute(Warrior* w, int elements)
{
    CLOCK.printTime();
    printf(" %s %s %d earned %d elements for his headquarter\n", w->color.c_str(), w->type.c_str(), w->id, elements);
}
/* Report 游戏报告类 实现 结束 */
/* Warrior 武士类 实现 开始 */
bool operator < (Warrior& w1, Warrior& w2)
{
    if(w1.color == "red")
        return w1.position < w2.position;
    else return w2.position < w1.position;
}
void Warrior::runaway()
{
    if(loyalty <= 0)
    {
        REPORT.lionRunAway(this);
        if(isNewBaby)
        {
            headquarter->newbaby = NULL;
        }
        if(color == "red")
            CITY[position].redWarrior = NULL;
        else CITY[position].blueWarrior = NULL;
    }
}
void Warrior::march()
{
    if(color == "red")
    {
        CITY[position + 1].redWarrior = this;
        if(isNewBaby)
            headquarter->newbaby = NULL;
        else CITY[position].redWarrior = NULL;
        position += 1;
        if(position == nCity + 1){
            blue.takenTime++;
            blue.enemy = this;
        }
    }
    if(color == "blue")
    {
        CITY[position - 1].blueWarrior = this;
        if(isNewBaby)
            headquarter->newbaby = NULL;
        else CITY[position].blueWarrior = NULL;
        position -= 1;
        if(position == 0){
            red.takenTime++;
            red.enemy = this;
        }
    }
    step++;
    if(step % 2 == 0 && type == "iceman"){
        hp -= 9;
        if(hp <= 0) hp = 1;
        atk += 20;
    }
    marched = true;
    isNewBaby = false;
}
bool Warrior::will_be_killed_by(City& city, Warrior* w)
{
    if(w->hp <= 0) return false;
    if(city.attackColor() == w->color) return (w->get_atk() >= this->hp);
    if(this->get_atk() >= w->hp) return false;
    if(w->type == "ninja") return false;
    return (w->get_fightback_atk() >= this->hp);
}
void Warrior::shoot(Warrior* warrior)
{
    arrow->remain -= 1;
    if(arrow->remain <= 0) arrow = NULL;
    warrior->hp -= arr_atk;
    REPORT.shoot(this, warrior);

}
void Warrior::attack(Warrior* target)
{
    target->last_hp = target->hp;
    target->hp -= atk;
    if(sword != NULL){
        target->hp -= sword->atk;
        sword->use();
        if(sword->atk <= 0) sword = NULL;
    }
    if(type == "dragon"){
        if(target->hp <= 0) { morale += 0.2;  }
        else { morale -= 0.2;  }
    } 
    if(type == "lion" && target->hp > 0) loyalty -= K;
    REPORT.attack(this, target);
}
void Warrior::fightback(Warrior* target)
{
    target->last_hp = target->hp;
    target->hp -= atk / 2;
    if(sword != NULL){
        target->hp -= sword->atk;
        sword->use();
        if(sword->atk <= 0) sword = NULL;
    }
    if(type == "dragon"){
        if(target->hp <= 0) { morale += 0.2;  }
        else { morale -= 0.2; }
    } 
    if(type == "lion" && target->hp > 0) loyalty -= K;
    REPORT.fightback(this, target);
}
int Warrior::get_atk()
{
    int atk_ = atk;
    if(sword != NULL) atk_ += sword->atk;
    return atk_;
}
int Warrior::get_fightback_atk()
{
    int atk_ = atk / 2;
    if(sword != NULL) atk_ += sword->atk;
    return atk_;
}
void Warrior::applyCredit()
{
    headquarter->creditList.push(this);
}
void Warrior::contribute()
{
    headquarter->extraElments += CITY[position].elements;
    REPORT.contribute(this, CITY[position].elements);
    CITY[position].elements = 0;
}
void Warrior::win(City& city, Warrior* loser)
{
    if(type == "wolf"){
        if(sword == NULL) { sword = loser->sword; loser->sword = NULL; }
        if(arrow == NULL) { arrow = loser->arrow; loser->arrow = NULL; }
        if(bomb == NULL) { bomb = loser->bomb; loser->bomb = NULL; }
    }
    if(color == "red") city.blueWarrior = NULL;
    else city.redWarrior = NULL;
    delete loser;
    applyCredit();
    contribute();
    if(city.winnerColor == color && city.flagColor != color){
        city.flagColor = color;
        REPORT.raiseFlag(&city);
    }
    city.winnerColor = color;
}
Warrior::Warrior(int id_, int hp_, int atk_, string type_, Headquarter* headquarter_):
    id(id_), hp(hp_), atk(atk_), type(type_), headquarter(headquarter_), marched(false), isNewBaby(true), step(0), last_hp(0)
{
    sword = NULL; arrow = NULL; bomb = NULL;
    color = headquarter->color;
    if(color == "red")
        position = 0;
    else
        position = nCity + 1;
    if(type != "wolf" && type != "lion")
    {
        switch (id % 3){
            case 0: sword = new Sword(atk_ / 5); if(sword->atk <= 0) sword = NULL; break;
            case 1: bomb = new Bomb(); break;
            case 2: arrow = new Arrow(); break;
        }
    }
    if(type == "ninja")
    {
        switch ((id + 1) % 3){
            case 0: sword = new Sword(atk_ / 5); break;
            case 1: bomb = new Bomb(); break;
            case 2: arrow = new Arrow(); break;
        }
    }
    if(type == "dragon"){
        morale = (double)headquarter->elements / dHP;
    }
    if(type == "lion"){
        loyalty = headquarter->elements;
    }
}
/* Warrior 武士类 实现 结束 */
/* 城市类实现开始 */
void City::duel(Warrior* w1, Warrior* w2){
    if(w1->hp <= 0 && w2->hp < 0){
        blueWarrior = redWarrior = NULL;
        return;
    }
    if(w1->hp > 0 && w2->hp <= 0){
        if(w1->type == "dragon" && w1->morale >= 0.8) REPORT.dragonYell(w1);
        w1->win(*this, w2);
        return;
    }
    if(w2->hp > 0 && w1->hp <= 0){
        w2->win(*this, w1);
        return;
    }
    w1->attack(w2);
    if(w2->hp <= 0)
    {
        if(w2->type == "lion") w1->hp += w2->last_hp;
        REPORT.dead(w2);
        if(w1->type == "dragon"){
            if(w1->morale >= 0.8) REPORT.dragonYell(w1);
        }
        w1->win(*this, w2);
    }else{
        if(w2->type != "ninja"){
            w2->fightback(w1);
            if(w1->hp <= 0){
                if(w1->type == "lion") w2->hp += w1->last_hp;
                REPORT.dead(w1);
                w2->win(*this, w1);
            }else{
                winnerColor = "white";
            }
            if(w1->hp > 0 && w1->type == "dragon" && w1->morale >= 0.8) REPORT.dragonYell(w1);
        }
        else{
            winnerColor = "white";
            if(w1->hp > 0 && w1->type == "dragon" && w1->morale >= 0.8) REPORT.dragonYell(w1);
        }
    }
}
void City::produce(){
    elements += 10;
}
bool City::isBattleField(){
    return(redWarrior != NULL && blueWarrior != NULL);
}
string City::attackColor(){
    if(flagColor != "white") return flagColor;
    if(id % 2 == 0) return "blue";
    else return "red"; 
}
int main()
{
    int nCase;
    cin >> nCase;
    /* 以上，初始化战场模型，数据 */
    for(int C = 1; C <= nCase; C++)
    {
        CLOCK.reset();
        cin >> M >> nCity >> arr_atk >> K >> T;
        cin >> dHP >> nHP >> iHP >> lHP >> wHP;
        cin >> dATK >> nATK >> iATK >> lATK >> wATK;
        red.reset(M);
        blue.reset(M);
        bool endflag = false;
        if(CITY != NULL) delete []CITY;
        CITY = new City[nCity + 2];
        for(int i = 0; i <= nCity + 1; i++)
            CITY[i].id = i;
        cout << "Case " << C << ":" << endl;
        while(true)
        {
            red.produceWarrior();
            blue.produceWarrior();
            if(!CLOCK.tick()) break;                                    // 游戏钟表跳
            for(int i = 1; i <= nCity; i++)
            {
                if(CITY[i].redWarrior != NULL && CITY[i].redWarrior->type == "lion")
                    CITY[i].redWarrior->runaway();
                if(CITY[i].blueWarrior != NULL && CITY[i].blueWarrior->type == "lion")
                    CITY[i].blueWarrior->runaway();
            }
            if(red.newbaby != NULL && red.newbaby->type == "lion")
                red.newbaby->runaway();
            if(blue.newbaby != NULL && blue.newbaby->type == "lion")
                blue.newbaby->runaway();
            if(!CLOCK.tick()) break;

            for(int i = 1; i <= nCity; i++)
                if(CITY[i].blueWarrior != NULL && CITY[i].blueWarrior->marched == false)
                    CITY[i].blueWarrior->march();
            for(int i = nCity; i >= 1; i--)
                if(CITY[i].redWarrior != NULL && CITY[i].redWarrior->marched == false)
                    CITY[i].redWarrior->march();
            if(red.newbaby != NULL)
                red.newbaby->march();
            if(blue.newbaby != NULL)
                blue.newbaby->march();
            REPORT.march();
            if(red.takenTime >= 2 || blue.takenTime >= 2){
                endflag = true;
            }
            if(!CLOCK.tick()) break;
            if(endflag) break;

            for(int i = 1; i <= nCity; i++)
                CITY[i].produce();
            if(!CLOCK.tick()) break;

            for(int i = 1; i <= nCity; i++)
            {
                if(!CITY[i].isBattleField())
                    if(CITY[i].redWarrior != NULL) CITY[i].redWarrior->contribute();
                    else if(CITY[i].blueWarrior != NULL) CITY[i].blueWarrior->contribute();
            }
            if(!CLOCK.tick()) break;

            for(int i = 1; i <= nCity; i++)
            {
                if(CITY[i].redWarrior != NULL && CITY[i].redWarrior->arrow != NULL && i + 1 <= nCity)
                {
                    if(CITY[i + 1].blueWarrior != NULL)
                        CITY[i].redWarrior->shoot(CITY[i + 1].blueWarrior);
                }
                if(CITY[i].blueWarrior != NULL && CITY[i].blueWarrior->arrow != NULL && i - 1>= 1)
                    if(CITY[i - 1].redWarrior != NULL)
                        CITY[i].blueWarrior->shoot(CITY[i - 1].redWarrior);
            }

            if(!CLOCK.tick()) break;
            for(int i = 1; i <= nCity; i++)
            {
                if(CITY[i].isBattleField())
                {
                    if(CITY[i].redWarrior->hp > 0 && CITY[i].redWarrior->bomb != NULL && CITY[i].redWarrior->will_be_killed_by(CITY[i], CITY[i].blueWarrior))
                    {
                        REPORT.bomb(CITY[i].redWarrior, CITY[i].blueWarrior);
                        CITY[i].redWarrior = NULL;
                        CITY[i].blueWarrior = NULL;
                    }
                    else if(CITY[i].blueWarrior->hp > 0 && CITY[i].blueWarrior->bomb != NULL && CITY[i].blueWarrior->will_be_killed_by(CITY[i], CITY[i].redWarrior))
                    {
                        REPORT.bomb(CITY[i].blueWarrior, CITY[i].redWarrior);
                        CITY[i].redWarrior = NULL;
                        CITY[i].blueWarrior = NULL;
                    }
                }else{
                    if(CITY[i].redWarrior != NULL && CITY[i].redWarrior->hp <= 0) CITY[i].redWarrior = NULL;
                    if(CITY[i].blueWarrior != NULL && CITY[i].blueWarrior->hp <= 0) CITY[i].blueWarrior = NULL;
                }
            }
            if(!CLOCK.tick()) break;
            for(int i = 1; i <= nCity; i++)
            {
                if(CITY[i].isBattleField())
                {
                    if(CITY[i].attackColor() == "red") CITY[i].duel(CITY[i].redWarrior, CITY[i].blueWarrior);
                    else CITY[i].duel(CITY[i].blueWarrior, CITY[i].redWarrior);
                }
            }
            blue.giveCredit();
            blue.receiveExtraElements();
            red.giveCredit();
            red.receiveExtraElements();
            if(!CLOCK.tick()) break;
            REPORT.elements(red);
            REPORT.elements(blue);
            if(!CLOCK.tick()) break;
            REPORT.weapons();
            if(!CLOCK.tick()) break;
        }
    }
    return 0;
}
